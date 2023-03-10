void oledInit() {
  Oled.begin();
  Oled.setBusClock(400000);
  Oled.enableUTF8Print();
  Oled.setFontMode(0);
  Oled.setDrawColor(1);
  Oled.setFont(u8g2_font_profont10_mf);
  Oled.clearBuffer();
  Oled.sendBuffer();
  baseOled();
}

void oledHandle() {
  if (Flag.NewPkg) oledUpdate();
}

void oledUpdate() {
  led(HIGH);
  oledPrint(0,  20,  Flag.Valid ? "VALID" : "INVALID");
  oledPrint(24, 30,  Col);
  oledPrint(24, 40,  Node);
  oledPrint(24, 50,  Lat/1E7);
  oledPrint(24, 60,  Lon/1E7);
  oledPrint(24, 70,  Rssi);
  oledPrint(24, 80,  Snr);
  oledPrint(24, 90,  Fei);
  oledPrint(24, 100, Dist);
  Oled.updateDisplay();
  led(LOW);
}


void baseOled() {
  oledPrint(0, 10,  "MICMAC RX");
  oledPrint(0, 30,  "COL");
  oledPrint(0, 40,  "NODE");
  oledPrint(0, 50,  "LAT");
  oledPrint(0, 60,  "LON");
  oledPrint(0, 70,  "RSSI");
  oledPrint(0, 80,  "SNR");
  oledPrint(0, 90,  "FEI");
  oledPrint(0, 100, "DIST");
  oledPrint(0, 110, "SF:");
  Oled.print(LORAsf);
  Oled.print("  CR:4/");
  Oled.print(LORAcr);
  oledPrint(0, 120, "BW:");
  Oled.print(LORAbw / 1000);
  Oled.print(" PWR:");
  Oled.print(LORApwr);
  Oled.updateDisplay();
}

void oledPrint(uint8_t x, uint8_t y, const char * m) {
  Oled.setCursor(x, y);
  Oled.print("          ");
  Oled.setCursor(x, y);
  Oled.print(m);
}

void oledPrint(uint8_t x, uint8_t y, uint32_t m) {
  Oled.setCursor(x, y);
  Oled.print("          ");
  Oled.setCursor(x, y);
  Oled.print(m);
}

void oledPrint(uint8_t x, uint8_t y, int32_t m) {
  Oled.setCursor(x, y);
  Oled.print("          ");
  Oled.setCursor(x, y);
  Oled.print(m);
}

void oledPrint(uint8_t x, uint8_t y, double m) {
  Oled.setCursor(x, y);
  Oled.print("          ");
  Oled.setCursor(x, y);
  Oled.print(m);
}
