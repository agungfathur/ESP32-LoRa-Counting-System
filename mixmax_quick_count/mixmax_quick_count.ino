// upload data ke esp32 -> https://github.com/me-no-dev/arduino-esp32fs-plugin

#include <Wire.h>
#include <LoRa.h>
#define MC_WEB
#define MC_DISPLAY
#include "WiFi.h"
#ifdef MC_WEB
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#endif
#ifdef MC_DISPLAY
#include "U8g2lib.h"
#endif

const char*    MC_ssid     = "MICMAC-COUNTER";
const char*    MC_password = "industriawan";
const char*    MC_host     = "micmac";
const uint8_t  PRT_web   = 80;
const uint8_t  PRT_node  = 69;
uint16_t       ID_colony  = 2;
uint16_t       MC_cmd    = 0xFFFF;

const uint8_t  LED_BUILTIN = 2;
const uint8_t  OLED_sda  = 4;
const uint8_t  OLED_scl  = 15;
const uint8_t  OLED_rst  = 16;

const uint16_t MC_header = 0xBE60;
const char*    MC_ack    = "ACK";
const char*    MC_nak    = "NAK";
uint16_t       ID_node;

const uint8_t  PKG_rx_size = 5;
const uint8_t  PKG_tx_size = 8;
const uint8_t  PKG_cmd_size = 7;
uint8_t        PKG_rx[PKG_rx_size];
uint8_t        PKG_tx[PKG_tx_size];
uint8_t        PKG_cmd[PKG_cmd_size];
uint16_t       COW_count   = 0;
String         COW_list    = "\n\nNo Node";
bool           COW_check[65535];
bool           COW_new     = false;

const uint8_t  LORAsck  = 5;
const uint8_t  LORAmiso = 19;
const uint8_t  LORAmosi = 27;
const uint8_t  LORAcs   = 18;
const uint8_t  LORArst  = 12;
const uint8_t  LORAirq  = 26;
const uint32_t LORAspif = 10E6;
const uint32_t LORAfrq  = 923E6;
const uint8_t  LORAsf   = 10;
const uint32_t LORAbw   = 125E3;
const uint8_t  LORAcr   = 6;
const uint8_t  LORApwr  = 17;
const uint8_t  LORAocp  = 240;

#ifdef MC_WEB
AsyncWebServer webserver(PRT_web);
#endif
#ifdef MC_DISPLAY
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, OLED_rst, OLED_scl, OLED_sda);
#endif
WiFiServer   nodeserver(PRT_node);

void setup() {
  memset(COW_check, 0, sizeof(COW_check));
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
#ifdef MC_WEB
  if (!SPIFFS.begin(true)) {

    Serial.println("SPIFFS Error");
    return;
  }
#endif
  WiFi.begin();
  //  WiFi.setTxPower(WIFI_POWER_15dBm);
  WiFi.softAP(MC_ssid, MC_password);
  //  Serial.println(WiFi.getHostname());
  Serial.println(WiFi.softAPIP());
  //  Serial.println(WiFi.getTxPower());
#ifdef MC_WEB
  webserver_handler();
  webserver.begin();
#endif
  oled_init();
  nodeserver.begin();
  lora_init();
}

void loop() {
  if (!digitalRead(0)) {
    Serial.println("START COUNT!");
    wake_node();
    send_cmd();
    delay(1000);
  }
  nodeserver_handler();
  if (COW_new)
    oled_update();
}
