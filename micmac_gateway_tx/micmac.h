#include "SPI.h"
#include "LoRa.h"
#include "U8g2lib.h"
#include "EEPROM.h"
#include "BLEDevice.h"
#include "BLE2902.h"
//#include "FS.h"
//#include "SD_MMC.h"
//#include "WiFi.h"
//#include "WiFiClient.h"
//#include "WebServer.h"
//#include "ESPmDNS.h"

#define PC     Serial
#define DBG(x) Serial.printf x

//SERIAL CONFIG
const uint32_t PCbaud = 115200;

//BLE CONFIG
BLEDevice BLE;
static BLEUUID UUIDsrvComm("69696969-BE60-BE60-0000-696969696969"); //srvc communication
static BLEUUID UUIDchrTx  ("69696969-BE60-0001-0000-696969696969"); //chr comm transmitted to client (write)
static BLEUUID UUIDchrRx  ("69696969-BE60-0002-0000-696969696969"); //chr comm received from client (read & notify)
static BLEUUID UUIDsrvInfo("69696969-BE60-BE60-1111-696969696969"); //srvc information
static BLEUUID UUIDchrStat("69696969-BE60-0001-1111-696969696969"); //chr info server/tx status (read only)
static BLEUUID UUIDchrDate("69696969-BE60-0002-1111-696969696969"); //chr info date (read only)
static BLEUUID UUIDchrTime("69696969-BE60-0003-1111-696969696969"); //chr info time (read only)
static BLEUUID UUIDchrLoc ("69696969-BE60-0004-1111-696969696969"); //chr info location (read only)
static BLEUUID UUIDsrvConf("69696969-BE60-BE60-2222-696969696969"); //srvc configuration
static BLEUUID UUIDchrCol ("69696969-BE60-0001-2222-696969696969"); //chr config colony (read only)
static BLEUUID UUIDchrTot ("69696969-BE60-0002-2222-696969696969"); //chr config total node (read only)
BLEServer         *pSr;
BLEService        *pSrvComm, *pSrvInfo, *pSrvConf;
BLECharacteristic *pChrTx, *pChrRx,
                  *pChrStat, *pChrDate, *pChrTime, *pChrLoc,
                  *pChrCol, *pChrTot;
BLEValue          *pValRx;

//LORA CONFIG
const uint8_t  LORAsck  = 5;
const uint8_t  LORAmiso = 19;
const uint8_t  LORAmosi = 27;
const uint8_t  LORAcs   = 18;
const uint8_t  LORArst  = 12;
//const uint8_t  LORArst  = 14;
const uint8_t  LORAirq  = 26;
const uint32_t LORAspif = 10E6;
const uint32_t LORAfrq  = 923E6;
const uint8_t  LORAsf   = 10;
const uint32_t LORAbw   = 125E3;
const uint8_t  LORAcr   = 6;
const uint8_t  LORApwr  = 17;
const uint8_t  LORAocp  = 240;

//PIN CONFIG
const uint8_t  LED = 25;

//EEPROM
const uint8_t  EEPROM_size = 16;
const uint8_t  EEPROM_id_colony_addr  = 0;
const uint8_t  EEPROM_total_node_addr = 2;

//OLED CONFIG
// TTGO NON SDCARD
//const uint8_t  OLEDsda  = 4;
//const uint8_t  OLEDscl  = 15;
//const uint8_t  OLEDrst  = 16;
// TTGO SDCARD
const uint8_t  OLEDsda  = 21;
const uint8_t  OLEDscl  = 22;
const uint8_t  OLEDrst  = 23;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R1, OLEDrst, OLEDscl, OLEDsda);

//FILESYSTEM
const uint8_t  SDcmd = 15;
const uint8_t  SDclk = 14;
const uint8_t  SDd0  =  2;
const uint8_t  SDd1  =  4;
const uint8_t  SDd3  = 13;

typedef struct {
  bool RxMsg, NewMsg, BleOk, FileOk, LoraOk;
} flag_t;
flag_t Flag;

enum {
  PKGhead = 0, PKGcol  = 2,
  PKGnode = 4,
  PKGcrc  = 6
};

enum {
  LOGnode = 0,
  LOGlat  = 2, LOGlon  = 6,
  LOGcrc  = 10
};

//const char* ssid = "MICRO-MACHINA";
//const char* password = "industriawan";
const char* ssid = "Junaediyanto";
const char* password = "9september";
const char* host = "micmac";
//WebServer server(80);
//File      fsUploadFile;

#ifdef DBG
#define INFO(x) DBG(x)
#define WARN(x) DBG(x)
#define ERR (x) DBG(x)
#else
#define INFO(x)
#define WARN(x)
#define ERR (x)
#endif
