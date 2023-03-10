void debug_init() {
#ifdef DBG
  DBG.begin(DBG_baud);
  pinMode(PIN_led, OUTPUT);
#endif
}

void debug_sys_mode() {
#ifdef DBG
  switch (SYS_mode) {
    case NORMAL_mode: DBG.println("NORMAL MODE"); break;
    case GPS_mode:    DBG.println("GPS MODE");    break;
    case WIFI_mode:   DBG.println("WIFI MODE");   break;
    case BLE_mode:    DBG.println("BLE MODE");    break;
    default: break;
  }
#endif
}

void debug_flag() {
#ifdef DBG
  if (memcmp(&flag_prev, &flag, sizeof(flag)) != 0) {
    DBG.printf("FLAG: rx_pkg:%i crc:%i header:%i col:%i node:%i ping:%i cmd:%i wait:%i resp:%i gps_fix:%i gps_valid:%i wifi_resp:%i\n",
               flag.rx_pkg_, flag.crc_, flag.header_, flag.col_, flag.node_, flag.ping_, flag.cmd_, flag.wait_, flag.resp_, flag.gps_fix_, flag.gps_valid_, flag.wifi_resp_);
    memcpy(&flag_prev, &flag, sizeof(flag));
  }
#endif
}

void debug_gps() {
#ifdef DBG
  switch (GPS_status) {
    case GPS_cfg:
      DBG.printf("GPS not configured! GPS baudrate: %i\n", GPS.baudRate());
      DBG.printf("GPS auto config ");
      for (uint8_t i = 0; i < 50; i++) {
        DBG.write('X');
        delay(50);
      }
      DBG.printf("\nGPS auto config done!\n");
      break;
    case GPS_ok:
      DBG.printf("GPS OK!\nGPS baudrate: %i\n", GPS.baudRate());
      break;
    case GPS_none:
      DBG.println("FATAL ERROR > GPS not detected!");
      break;
  }
  switch (GPS_wake_cause) {
    case GPS_chg_mode:
      break;
    case GPS_interrupt:
      DBG.println("GPS wake by interrupt");
      break;
    case GPS_timer:
      DBG.println("GPS wake by timer");
      break;
  }
  if (GPS_retry > 0) DBG.printf("GPS retry attempt %i\n", GPS_retry);
#endif
}

void debug_chg_mode() {
#ifdef DBG
  DBG.print("CHANGE MODE TO: ");
  debug_sys_mode();
#endif
}

void debug_wifi() {
#ifdef DBG
  //DBG.println(WiFi.getTxPower());
  if (WIFI_retry > 0) DBG.printf("WIFI retry attempt %i\n", WIFI_retry);
  switch (WIFI_status) {
    case WIFI_none:
      DBG.println("WIFI not found");
      break;
    case WIFI_fail:
      DBG.println("WIFI fail to connect");
      break;
    case WIFI_ok:
      DBG.println("WIFI OK!");
      break;
  }
#endif
}

void led(bool x) {
#ifdef DBG
  digitalWrite(PIN_led, x);
#endif
}

void debug_pkg(uint8_t * buff, uint8_t x) {
#ifdef DBG
  for (uint8_t i = 0; i < x; i++) {
    DBG.print(buff[i]);
    DBG.print(" ");
  }
  DBG.println();
#endif
}

void debug_rssi() {
#ifdef DBG
  DBG.printf("RSSI %i\n", LoRa.packetRssi());
#endif
}

void debug_snr() {
#ifdef DBG
  DBG.printf("SNR %.3f\n", LoRa.packetSnr());
#endif
}

void debug_fei() {
#ifdef DBG
  DBG.printf("FEI %i\n", LoRa.packetFrequencyError());
#endif
}

void debug_ubx_posllh() {
#ifdef DBG
  DBG.printf("NAV-POSLLH\n");
  DBG.printf("iTOW:\t\t%i\n", NAV_POSLLH.iTOW);
  DBG.printf("lon:\t\t%i\n", NAV_POSLLH.lon);
  DBG.printf("lat:\t\t%i\n", NAV_POSLLH.lat);
  DBG.printf("height:\t\t%i\n", NAV_POSLLH.height);
  DBG.printf("hMSL:\t\t%i\n", NAV_POSLLH.hMSL);
  DBG.printf("hAcc:\t\t%i\n", NAV_POSLLH.hAcc);
  DBG.printf("vAcc:\t\t%i\n", NAV_POSLLH.vAcc);
#endif
}
void debug_ubx_status() {
#ifdef DBG
  DBG.printf("NAV-STATUS\n");
  DBG.printf("iTOW:\t\t%i\n", NAV_STATUS.iTOW);
  DBG.printf("gpsFix:\t\t%i\n", NAV_STATUS.gpsFix);
  DBG.printf("flags:\t\t%i\n", NAV_STATUS.flags);
  DBG.printf("fixStat:\t%i\n", NAV_STATUS.fixStat);
  DBG.printf("flags2:\t\t%i\n", NAV_STATUS.flags2);
  DBG.printf("ttff:\t\t%i\n", NAV_STATUS.ttff);
  DBG.printf("msss:\t\t%i\n", NAV_STATUS.msss);
#endif
}
void debug_ubx_sol() {
#ifdef DBG
  DBG.printf("NAV-SOL\n");
  DBG.printf("iTOW:\t\t%i\n", NAV_SOL.iTOW);
  DBG.printf("fTOW:\t\t%i\n", NAV_SOL.fTOW);
  DBG.printf("week:\t\t%i\n", NAV_SOL.week);
  DBG.printf("gpsFix:\t\t%i\n", NAV_SOL.gpsFix);
  DBG.printf("flags:\t\t%i\n", NAV_SOL.flags);
  DBG.printf("ecefX:\t\t%i\n", NAV_SOL.ecefX);
  DBG.printf("ecefY:\t\t%i\n", NAV_SOL.ecefY);
  DBG.printf("ecefZ:\t\t%i\n", NAV_SOL.ecefZ);
  DBG.printf("pAcc:\t\t%i\n", NAV_SOL.pAcc);
  DBG.printf("ecefVX:\t\t%i\n", NAV_SOL.ecefVX);
  DBG.printf("ecefVY:\t\t%i\n", NAV_SOL.ecefVY);
  DBG.printf("ecefVZ:\t\t%i\n", NAV_SOL.ecefVZ);
  DBG.printf("sAcc:\t\t%i\n", NAV_SOL.sAcc);
  DBG.printf("pDOP:\t\t%i\n", NAV_SOL.pDOP);
  DBG.printf("resv1:\t\t%i\n", NAV_SOL.resv1);
  DBG.printf("numSV:\t\t%i\n", NAV_SOL.numSV);
  DBG.printf("resv2:\t\t%i\n", NAV_SOL.resv2);
#endif DBG
}
void debug_ubx_timeutc() {
#ifdef DBG
  DBG.printf("NAV-STATUS\n");
  DBG.printf("iTOW:\t\t%i\n", NAV_TIMEUTC.iTOW);
  DBG.printf("tAcc:\t\t%i\n", NAV_TIMEUTC.tAcc);
  DBG.printf("nano:\t\t%i\n", NAV_TIMEUTC.nano);
  DBG.printf("year:\t\t%i\n", NAV_TIMEUTC.year);
  DBG.printf("month:\t\t%i\n", NAV_TIMEUTC.month);
  DBG.printf("day:\t\t%i\n", NAV_TIMEUTC.day);
  DBG.printf("hour:\t\t%i\n", NAV_TIMEUTC.hour);
  DBG.printf("min:\t\t%i\n", NAV_TIMEUTC.min);
  DBG.printf("sec:\t\t%i\n", NAV_TIMEUTC.sec);
  DBG.printf("valid:\t\t%i\n", NAV_TIMEUTC.valid);
#endif
}
