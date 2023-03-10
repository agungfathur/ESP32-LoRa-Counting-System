#include "mixmax.h"

#define PC  Serial
#define DBG Serial

//DEVICE CONFIG
const uint16_t MC_header  = 0xBE60;
const uint16_t MC_cmd     = 0xFFFF;
uint16_t       ID_colony  = 2;
uint16_t       ID_node    = 3;
uint16_t       TOTAL_node = 5;
//DATA FORMAT
const uint8_t  PKG_tx_size = 15;
const uint8_t  PKG_rx_size = 7;
uint8_t        PKG_tx[PKG_tx_size];
uint8_t        PKG_rx[PKG_rx_size];
/*
  FORMAT
  HEADER 2B, ID_COLONY 2B, ID_NODE 2B,
  LAT 4B, LON 4B, BATT 1B, RSSI 1B, CRC 1B
*/
RTC_DATA_ATTR int32_t Lat;
RTC_DATA_ATTR int32_t Lon;
RTC_DATA_ATTR uint8_t Batt;
RTC_DATA_ATTR uint8_t Rssi;

RTC_DATA_ATTR uint8_t Hour;
RTC_DATA_ATTR uint8_t Min;
RTC_DATA_ATTR uint8_t Sec;
//WIFI CONFIG
const char*    WIFI_ssid = "MICMAC-COUNTER";
const char*    WIFI_pswd = "industriawan";
const char*    WIFI_host = "192.168.4.1";
const uint8_t  WIFI_port = 69;
const uint8_t  WIFI_tx_size = 5;
const uint8_t  WIFI_rx_size = 8;
uint8_t        WIFI_tx[WIFI_tx_size];
uint8_t        WIFI_rx[WIFI_rx_size];
//MISC
const uint8_t  WIFI_max_retry = 20;
const uint8_t  GPS_max_retry  = 20;
const uint16_t TIME_stdby = 5000; // ms
const uint16_t TIME_ping  = 1000; // ms
const uint8_t  TIME_ctr   = 60;   // s
const uint8_t  TIME_gps   = 180;  // s
uint32_t       TIME_sleep = 0;

RTC_DATA_ATTR sys_mode_t SYS_mode = NORMAL_mode;

void setup() {
  mixmax_init();
  mixmax_main();
  mixmax_sleep();
}

void loop() {} //do nothing

void mixmax_init() {
  memset(&flag, 0, sizeof(flag));
  PC.begin(115200);
  eeprom_init();
#ifdef DBG
  debug_init();
#endif
  debug_sys_mode();
  switch (SYS_mode) {
    case NORMAL_mode: lora_init(); break;
    case GPS_mode:    gps_init();  break;
    case WIFI_mode:   wifi_init(); break;
    case BLE_mode:    ble_init();  break;
    default: break;
  }
}

void mixmax_main() {
  switch (SYS_mode) {
    case NORMAL_mode: normal_mode(); break;
    case GPS_mode:    gps_mode();    break;
    case WIFI_mode:   wifi_mode();   break;
    case BLE_mode:    ble_mode();    break;
    default: break;
  }
}
