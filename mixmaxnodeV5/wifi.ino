void wifi_init() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  uint32_t x = WiFi.scanNetworks();
  bool found = false;
  for (uint32_t i = 0; i < x; i++) {
    DBG.println(WiFi.SSID(i));
    if (WiFi.SSID(i) == WIFI_ssid) found = true;
  }
  if (found) {
    WiFi.begin(WIFI_ssid, WIFI_pswd);
    //WiFi.setTxPower(WIFI_POWER_17dBm);
    while (millis() < TIME_stdby * 6) {
      if (WiFi.isConnected()) {
        WIFI_status = WIFI_ok;
        break;
      }
      else WIFI_status = WIFI_fail;
    }
  }
  debug_wifi();
}

bool wifi_count() {
  WiFiClient client;
  if (!client.connect(WIFI_host, WIFI_port)) return false;
  assign_wifi();
  client.write(WIFI_tx, WIFI_tx_size);
  uint32_t t_start = millis();
  while (client.available() == 0) {
    if (millis() - t_start > 5000) {
      client.stop();
      return false;
    }
  }
  while (client.available() >= 2) {
    WIFI_rx[0] = client.read();
    WIFI_rx[1] = client.read();
    if (memcmp(WIFI_rx, &MC_header, 2) == 0 && (client.available() >= 6)) {
      for (uint8_t i = 2; i < WIFI_rx_size; i++) WIFI_rx[i] = client.read();
      if (check_crc(WIFI_rx, WIFI_rx_size)) {
        if ((memcmp(WIFI_rx, WIFI_tx, 4) == 0) && (memcmp(WIFI_rx + 4, "ACK", 3) == 0)) return true;
      }
    }
  }
  return false;
}

void assign_wifi() {
  memcpy(WIFI_tx,     &MC_header, 2);
  memcpy(WIFI_tx + 2, &ID_node, 2);
  WIFI_tx[4] = calc_crc(WIFI_tx, WIFI_tx_size - 1);
}
