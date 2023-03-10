void lora_init() {
  SPI.begin(LORAsck, LORAmiso,  LORAmosi, LORAcs);
  SPI.setFrequency(LORAspif);
  LoRa.setPins(LORAcs, LORArst, LORAirq);
  if (!LoRa.begin(LORAfrq)) {
    Serial.println("Lora fail");
  }
  LoRa.setSpreadingFactor(LORAsf);
  LoRa.setSignalBandwidth(LORAbw);
  LoRa.setCodingRate4(LORAcr);
  LoRa.setTxPower(LORApwr);
  LoRa.setOCP(LORAocp);
}

void wake_node() {
  uint8_t Wake = 'W';
  send_lora(&Wake, 1);
  delay(500);
}

void send_cmd() {
  assign_cmd();
  send_lora(PKG_cmd, PKG_cmd_size);
}

void send_lora(uint8_t *Buf, uint8_t Size) {
  LoRa.idle();
  LoRa.beginPacket();
  LoRa.write(Buf, Size);
  LoRa.endPacket();
}

void assign_cmd() {
  memcpy(PKG_cmd,     &MC_header, 2);
  memcpy(PKG_cmd + 2, &ID_colony,  2);
  memcpy(PKG_cmd + 4, &MC_cmd, 2);
  PKG_cmd[6] = calc_crc(PKG_cmd, PKG_cmd_size - 1);
}
