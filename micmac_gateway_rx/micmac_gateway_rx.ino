/*
   Gateway Rx (communicate to Gateway Tx via BLE)
   Functionality:
   1) Receive package from Node
   2) Report Node package validity to Gateway Tx
   3) Create package binary Log in FATFS
   4) Stream Log to Gateway Tx when requested
*/

#include "micmac.h"

//#undef DBG

const uint8_t PkgSize = 15;
uint8_t       Pkg[PkgSize]; // LoRa Data
const uint8_t MsgSize = 15;
uint8_t       Msg[MsgSize]; // BLE Data
const uint8_t LogSize = 11;
uint8_t       Log[LogSize]; // Log Data
String        LogName;

uint16_t Head = 0xBE60,
         Col, Node, Total;
int32_t  Lat, Lon;

int16_t  Rssi;
float    Snr;
int32_t  Fei;
double   Dist;

void setup() {
  systemInit();
  eeprom_init();
  //  bleInit();
  loraInit();
  //  fileInit();
  oledInit();
}

void loop() {
  config_gateway();
  loraHandle();
  //  fileHandle();
  //  bleHandle();
  oledHandle();
}
