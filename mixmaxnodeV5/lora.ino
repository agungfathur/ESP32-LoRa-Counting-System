void lora_init() {
  SPI.begin(LORA_sck, LORA_miso,  LORA_mosi, LORA_cs);
  SPI.setFrequency(LORA_spif);
  LoRa.setPins(LORA_cs, LORA_rst, LORA_irq);
  if (!LoRa.begin(LORA_frq_rx)) {
    Serial.println("Lora Fail");
  }
  LoRa.setSpreadingFactor(LORA_sf);
  LoRa.setSignalBandwidth(LORA_bw);
  LoRa.setCodingRate4(LORA_cr);
  LoRa.setTxPower(LORA_pwr);
  LoRa.setOCP(LORA_ocp);
  LoRa.onReceive(lora_on_rx);
  LoRa.receive();
}

void lora_on_rx(int pkg_size) {
  if (pkg_size == PKG_rx_size) {
    flag.rx_pkg_ = true;
    for (uint8_t i = 0; i < PKG_rx_size; i++) PKG_rx[i] = LoRa.read();
  }
  else LoRa.flush();
}

bool response() {
  if (flag.ping_) response_ping();
  else if (flag.cmd_) response_cmd();
  else if (flag.wait_) response_wait();
  return flag.ping_ || flag.cmd_ || flag.wait_;
}

void response_ping() {
  assign_pkg();
  LoRa.sleep();
  LoRa.setFrequency(LORA_frq_tx);
  LoRa.idle();
  LoRa.beginPacket();
  LoRa.write(PKG_tx, PKG_tx_size);
  LoRa.endPacket();
  debug_pkg(PKG_tx, PKG_tx_size);
  LoRa.sleep();
  LoRa.setFrequency(LORA_frq_rx);
  LoRa.idle();
  LoRa.receive();
  TIME_sleep = (TOTAL_node - ID_node) * TIME_ping * 1000;
}

void response_cmd() {
  //  if (flag.cmd_) {
  //    flag.cmd_ = 0;
  //  }
}

void response_wait() {
  uint16_t cr_node;
  memcpy(&cr_node, PKG_rx + _pkg_node, sizeof(cr_node));
  if (ID_node - cr_node > 2) TIME_sleep = (ID_node - cr_node) * TIME_ping * 1000;
  else if (ID_node - cr_node <= 0) TIME_sleep = (TOTAL_node - cr_node) * TIME_ping * 1000;
  else flag.wait_ = false;
}

void parse_pkg(uint8_t * buff) {
  memset(&flag, 0, sizeof(flag));
  flag.crc_ = check_crc(buff, PKG_rx_size);
  if (flag.crc_)    flag.header_ = memcmp(&MC_header, buff + _pkg_header, 2) == 0 ? true : false;
  if (flag.header_) flag.col_    = memcmp(&ID_colony, buff + _pkg_col,    2) == 0 ? true : false;
  if (flag.col_)    flag.node_   = memcmp(&ID_node,   buff + _pkg_node,   2) == 0 ? true : false;
  if (flag.col_ && flag.node_) flag.ping_ = true;
  if (flag.col_ && !flag.node_) flag.cmd_  = memcmp(&MC_cmd, buff + _pkg_cmd, 2) == 0 ? true : false;
  if (flag.col_ && !flag.node_ && !flag.cmd_)  flag.wait_ = true;
  Rssi = -LoRa.packetRssi();
  debug_pkg(buff, PKG_rx_size);
  debug_rssi();
  debug_snr();
  debug_fei();
}

void assign_pkg() {
  memcpy(PKG_tx,             &MC_header, 2);
  memcpy(PKG_tx + _pkg_col,  &ID_colony, 2);
  memcpy(PKG_tx + _pkg_node, &ID_node,   2);
  memcpy(PKG_tx + _pkg_lat,  &Lat,       4);
  memcpy(PKG_tx + _pkg_lon,  &Lon,       4);
  PKG_tx[_pkg_crc] = calc_crc(PKG_tx, PKG_tx_size - 1);
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
