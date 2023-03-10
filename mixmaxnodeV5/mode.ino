void normal_mode() {
  led(HIGH);
  uint32_t t_start = millis();
  while ((millis() - t_start < TIME_stdby) && !flag.resp_) {
    config_node();
    if (flag.rx_pkg_) parse_pkg(PKG_rx);
    flag.resp_ = response();
//    if (flag.ping_) flag.ping_ = 0;
    debug_flag();
  }
  if (flag.ping_) mixmax_chg_mode(GPS_mode);
  if (flag.cmd_) mixmax_chg_mode(WIFI_mode);
}

void gps_mode() {
  led(HIGH);
  uint32_t t_start = millis();
  while (millis() - t_start < TIME_stdby && !flag.gps_fix_) {
    while (GPS.available()) sync_ubx();
    flag.gps_valid_ = NAV_STATUS.flags & 0x01;
    flag.gps_fix_ = NAV_STATUS.gpsFix == 0x02 || NAV_STATUS.gpsFix == 0x03 ? true : false;
    debug_flag();
  }
  if (flag.gps_fix_) {
    Lat  = NAV_POSLLH.lat;
    Lon  = NAV_POSLLH.lon;
    Hour = NAV_TIMEUTC.hour;
    Min  = NAV_TIMEUTC.min;
    Sec  = NAV_TIMEUTC.sec;
  }
  if ((flag.gps_fix_ && flag.gps_valid_) || GPS_wake_cause == GPS_timer || GPS_retry > GPS_max_retry) {
    GPS_retry = 0;
    mixmax_chg_mode(NORMAL_mode);
  }
}

void wifi_mode() {
  led(HIGH);
  if (WIFI_status == WIFI_ok) {
    uint32_t t_start = millis();
    while (millis() - t_start < TIME_stdby && !flag.wifi_resp_) {
      flag.wifi_resp_ = wifi_count();
      debug_flag();
    }
    if (flag.wifi_resp_ || WIFI_retry > WIFI_max_retry) {
      WIFI_retry = 0;
      mixmax_chg_mode(NORMAL_mode);
    }
  }
}

void ble_mode() {

}

void mixmax_chg_mode(uint8_t x) {
  if (SYS_mode == NORMAL_mode) LoRa.sleep();
  if (SYS_mode == GPS_mode) GPS.end();
  if (SYS_mode == WIFI_mode) WiFi.mode(WIFI_OFF);
  SYS_mode = (sys_mode_t)x;
  if (SYS_mode == GPS_mode) GPS_wake_cause = GPS_chg_mode;
  debug_chg_mode();
  esp_sleep_enable_timer_wakeup(5);
  esp_deep_sleep_start();
}
