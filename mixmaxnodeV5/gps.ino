void gps_init() {
  if (GPS_wake_cause != GPS_chg_mode)
    GPS_wake_cause = (gps_wake_cause_t)esp_sleep_get_wakeup_cause();
  uint32_t t_start = millis();
  GPS_status = GPS_none;
  while (millis() - t_start < 5000) {
    gps_wake();
    GPS.begin(0, SERIAL_8N1, GPS_tx, GPS_rx, false, 1000UL);
    if (GPS.baudRate() > 230400 && GPS.baudRate() < 230500) {
      GPS_status = GPS_ok;   break;
    }
    else if (GPS.baudRate() != 921600 && GPS.baudRate() > 0) {
      GPS_status = GPS_cfg;  break;
    }
    else if (GPS.baudRate() == 0) {
      GPS_status = GPS_none; break;
    }
  }
  debug_gps();
  if (GPS_status == GPS_cfg) gps_config();
  if (GPS_status == GPS_none) mixmax_chg_mode(NORMAL_mode);
  //gps_config();
  //gps_reset_default();//setbaud 230423
}

void sync_ubx() {
  while (GPS.available()) {
    uint8_t sync_char[2];
    sync_char[0] = GPS.read();
    sync_char[1] = GPS.read();
    if (memcmp(sync_char, ubx_header, 2) == 0) parse_ubx();
  }
}

void parse_ubx() {
  uint8_t x[64];
  uint8_t  ubx_cls = 0, ubx_id = 0;
  uint16_t ubx_len = 0;
  if (GPS.available() >= 16) {
    GPS.readBytes(x, 4);
    ubx_cls = x[0];
    ubx_id  = x[1];
    ubx_len = x[2] | (uint16_t)(x[3] << 8);
    if (ubx_cls == 0x01 && ubx_id == 0x02 && ubx_len == 28) UBX_msg = UBX_posllh;
    if (ubx_cls == 0x01 && ubx_id == 0x03 && ubx_len == 16) UBX_msg = UBX_status;
    if (ubx_cls == 0x01 && ubx_id == 0x06 && ubx_len == 52) UBX_msg = UBX_sol;
    if (ubx_cls == 0x01 && ubx_id == 0x21 && ubx_len == 20) UBX_msg = UBX_timeutc;

    GPS.readBytes(x + 4, ubx_len + 2);
    if (!check_ubx_ck(x + (ubx_len + 4), calc_ubx_ck(x, ubx_len + 4)))
      UBX_msg = UBX_none;
  }
  switch (UBX_msg) {
    case UBX_posllh:
      NAV_POSLLH.iTOW = ubxcp32(x + 4);
      NAV_POSLLH.lon = (int32_t)ubxcp32(x + 8);
      NAV_POSLLH.lat = (int32_t)ubxcp32(x + 12);
      NAV_POSLLH.height = (int32_t)ubxcp32(x + 16);
      NAV_POSLLH.hMSL = (int32_t)ubxcp32(x + 20);
      NAV_POSLLH.hAcc = ubxcp32(x + 24);
      NAV_POSLLH.vAcc = ubxcp32(x + 28);
      //debug_ubx_posllh();
      break;
    case UBX_status:
      NAV_STATUS.iTOW = ubxcp32(x + 4);
      NAV_STATUS.gpsFix = x[8];
      NAV_STATUS.flags = x[9];
      NAV_STATUS.fixStat = x[10];
      NAV_STATUS.flags2 = x[11];
      NAV_STATUS.ttff = ubxcp32(x + 12);
      NAV_STATUS.msss = ubxcp32(x + 16);
      //debug_ubx_status();
      break;
    case UBX_sol:
      NAV_SOL.iTOW = ubxcp32(x + 4);
      NAV_SOL.fTOW = (int32_t)ubxcp32(x + 8);
      NAV_SOL.week = (int16_t)ubxcp16(x + 12);
      NAV_SOL.gpsFix = x[14];
      NAV_SOL.flags = x[15];
      NAV_SOL.ecefX = (int32_t)ubxcp32(x + 16);
      NAV_SOL.ecefY = (int32_t)ubxcp32(x + 20);
      NAV_SOL.ecefZ = (int32_t)ubxcp32(x + 24);
      NAV_SOL.pAcc = ubxcp32(x + 28);
      NAV_SOL.ecefVX = (int32_t)ubxcp32(x + 32);
      NAV_SOL.ecefVY = (int32_t)ubxcp32(x + 36);
      NAV_SOL.ecefVZ = (int32_t)ubxcp32(x + 40);
      NAV_SOL.sAcc = ubxcp32(x + 44);
      NAV_SOL.pDOP = ubxcp16(x + 48);
      NAV_SOL.resv1 = x[50];
      NAV_SOL.numSV = x[51];
      NAV_SOL.resv2 = ubxcp32(x + 52);
      //debug_ubx_sol();
      break;
    case UBX_timeutc:
      NAV_TIMEUTC.iTOW = ubxcp32(x + 4);
      NAV_TIMEUTC.tAcc = ubxcp32(x + 8);
      NAV_TIMEUTC.nano = (int32_t)ubxcp32(x + 12);
      NAV_TIMEUTC.year = ubxcp16(x + 14);
      NAV_TIMEUTC.month = x[15];
      NAV_TIMEUTC.day = x[16];
      NAV_TIMEUTC.hour = x[17];
      NAV_TIMEUTC.min = x[18];
      NAV_TIMEUTC.sec = x[19];
      NAV_TIMEUTC.valid = x[20];
      //debug_ubx_timeutc();
      break;
    case UBX_none: break;
    default: break;
  }
}

void gps_config() {
  GPS.write(cfg_ubx_msg, sizeof(cfg_ubx_msg));
  GPS.write(cfg_prt, sizeof(cfg_prt));
  delay(300);
  GPS.begin(0, SERIAL_8N1, GPS_tx, GPS_rx, false, 5000UL);
  //GPS.write(cfg_nmea_msg, sizeof(cfg_nmea_msg));
  GPS.write(cfg_pm2, sizeof(cfg_pm2));
  GPS.write(cfg_rate, sizeof(cfg_rate));
  GPS.write(cfg_nav5, sizeof(cfg_nav5));
  GPS.write(cfg_rxm, sizeof(cfg_rxm));
  GPS.write(cfg_save, sizeof(cfg_save));
  GPS_status = GPS_ok;
  debug_gps();
}

void gps_reset_default() {
  GPS.write(cfg_clear, sizeof(cfg_clear));
  GPS.write(cfg_load, sizeof(cfg_load));
  GPS.write(cfg_save, sizeof(cfg_save));
}

void gps_wake() {
  pinMode(GPS_tx, OUTPUT);
  digitalWrite(GPS_tx, HIGH);
  delayMicroseconds(1);
  digitalWrite(GPS_tx, LOW);
}

bool check_ubx_ck (uint8_t* a, uint16_t b) {
  if ((a[0] == (b >> 8)) && (a[1] == (b & 0xFF))) return true;
  return false;
}

uint16_t calc_ubx_ck(uint8_t * buff, uint8_t x) {
  uint8_t ck_a = 0, ck_b = 0;
  for (int i = 0; i < x; i++)
  {
    ck_a = ck_a + buff[i];
    ck_b = ck_b + ck_a;
  }
  //  DBG.println(ck_a, HEX);
  //  DBG.println(ck_b, HEX);
  uint16_t ubx_ck = (uint16_t)(ck_a << 8) | ck_b;
  return ubx_ck;
}

uint32_t ubxcp32(uint8_t* buff) {
  return buff[3] << 24 | buff[2] << 16 | buff[1] << 8 | buff[0];
}

uint16_t ubxcp16(uint8_t* buff) {
  return buff[1] << 8 | buff[0];
}
