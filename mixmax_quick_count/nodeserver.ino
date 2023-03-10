void nodeserver_handler() {
  WiFiClient client = nodeserver.available();
  bool _flag_header = false;
  if (client) {
    uint32_t _t_start = millis();
    bool     _flag_valid = false;
    while (client.connected()) {
      while (client.available() >= 2) {
        PKG_rx[0] = client.read();
        PKG_rx[1] = client.read();
        _flag_header = memcmp(PKG_rx, &MC_header, sizeof(MC_header)) == 0 ? true : false;
        if (_flag_header && client.available() >= 3) {
          PKG_rx[2] = client.read();
          PKG_rx[3] = client.read();
          PKG_rx[4] = client.read();
          memcpy(&ID_node, PKG_rx + 2, 2);
          _flag_valid = true;
        }
      }
      if (_flag_valid || (millis() - _t_start > 3000))break;
    }
    if (_flag_valid) {
      if (check_crc(PKG_rx, PKG_rx_size)) {
        webserver_update(ID_node);
        assign_pkg(MC_ack);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(3);
      }
      else {
        assign_pkg(MC_nak);
      }
      for (uint8_t i = 0; i < 7; i++) {
        if (i < 4)Serial.print(PKG_tx[i], HEX);
        else Serial.write(PKG_tx[i]);
        Serial.print(" ");
      }
      Serial.println();
    }
    client.write(PKG_tx, PKG_tx_size);
    client.stop();
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void assign_pkg(const char* resp) {
  memcpy(PKG_tx,     &MC_header, 2);
  memcpy(PKG_tx + 2, &ID_node, 2);
  PKG_tx[4] = resp[0];
  PKG_tx[5] = resp[1];
  PKG_tx[6] = resp[2];
  PKG_tx[7] = calc_crc(PKG_tx, PKG_tx_size - 1);
}

bool check_crc(uint8_t *buff, uint8_t x) {
  if (calc_crc(buff, x) == 0) return true;
  return false;
}

uint8_t calc_crc(uint8_t *buff, uint8_t x) {
  uint8_t crc = 0;
  for (uint8_t i = 0; i < x; i++) {
    uint8_t a = buff[i];
    for (uint8_t j = 0; j < 8; j++) {
      uint8_t b = (crc ^ a) & 0x01;
      crc >>= 1;
      if (b)
        crc ^= 0x8C;
      a >>= 1;
    }
  }
  return crc;
}
