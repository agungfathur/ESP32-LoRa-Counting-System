#include "micmac.h"

const uint8_t  PkgSize = 7,
               MsgSize = 15;
uint8_t        Pkg[PkgSize],
               Msg[MsgSize];

uint16_t Head  = 0xBE60,
         Col   = 2,
         Total = 5,
         Node;
int32_t  Lat, Lon;

uint8_t  Day    = 9,
         Month  = 12,
         Year   = 19,
         Hour   = 18,
         Minute = 35;

int32_t  GateLat =  -7.782907 * 1E7,
         GateLon = 110.367042 * 1E7;

String Status, Date, Time, Loc;
//void taskClientHandle(void *p);
void setup() {
  systemInit();
  eeprom_init();
  bleInit();
  //  sdcardInit();
//  oledInit();
  loraInit();
  //  serverInit();
  //  xTaskCreatePinnedToCore(taskClientHandle, "ClientHandle", 20000, NULL, 3, NULL, 0);
}

void loop() {
  config_gateway();
  //  loraHandle();
  //  oledHandle();
  pingAll();
}

//void taskClientHandle(void *p) {
//  (void) p;
//  for (;;) {
//    server.handleClient();
//  }
//}
