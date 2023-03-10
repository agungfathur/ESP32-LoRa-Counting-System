void loraInit() {
  SPI.begin(LORAsck, LORAmiso,  LORAmosi, LORAcs);
  SPI.setFrequency(LORAspif);
  LoRa.setPins(LORAcs, LORArst, LORAirq);
  while (!LoRa.begin(LORAfrq));
  LoRa.setSpreadingFactor(LORAsf);
  LoRa.setSignalBandwidth(LORAbw);
  LoRa.setCodingRate4(LORAcr);
  LoRa.setTxPower(LORApwr);
  LoRa.setOCP(LORAocp);
}

void pingAll() {
  //  updateStat("PING");
  Node = 1;
  for (Node = 1; Node <= Total; Node++) {
    config_gateway();
    wakeNode();
    pingNode();
  }
}

void wakeNode() {
  uint8_t Wake = 'W';
  sendPkg(&Wake, 1);
  delay(100);
}

void pingNode() {
  assignPkg();
  sendPkg(Pkg, PkgSize);
  responseHandle();
}

void sendPkg(uint8_t *Buf, uint8_t Size) {
  led(HIGH);
  LoRa.idle();
  LoRa.beginPacket();
  LoRa.write(Buf, Size);
  LoRa.endPacket();
  led(LOW);
}

void assignPkg() {
  memcpy(Pkg + PKGhead, &Head, 2);
  memcpy(Pkg + PKGcol,  &Col,  2);
  memcpy(Pkg + PKGnode, &Node, 2);
  Pkg[PKGcrc] = calcCrc(Pkg, PkgSize - 1);
}

void responseHandle() {
  delay(1500);
  //  updateOled();
  //  uint32_t TimeStart = millis();
  //  while (millis() - TimeStart < 1500) {
  //    // TODO
  //  }
}

bool checkCrc(uint8_t * Buf, uint8_t Size) {
  if (calcCrc(Buf, Size) == 0) return true;
  return false;
}

uint8_t calcCrc(uint8_t * Buf, uint8_t Size) {
  uint8_t Crc = 0;
  for (uint8_t i = 0; i < Size; i++) {
    uint8_t a = Buf[i];
    for (uint8_t j = 0; j < 8; j++) {
      uint8_t b = (Crc ^ a) & 0x01;
      Crc >>= 1;
      if (b)
        Crc ^= 0x8C;
      a >>= 1;
    }
  }
  return Crc;
}
