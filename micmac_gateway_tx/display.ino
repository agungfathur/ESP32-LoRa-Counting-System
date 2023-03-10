void oledInit() {
  oled.begin();
  oled.setBusClock(400000);
  oled.enableUTF8Print();
  oled.setFontMode(0);
  oled.setDrawColor(1);
  oled.setFont(u8g2_font_profont10_mf);
  oled.clearBuffer();
  oled.sendBuffer();
  baseOled();
}

void updateOled() {
  printOled(24, 30, Col);
  printOled(24, 40, Node);
  oled.updateDisplay();
}

void printOled(uint8_t x, uint8_t y, const char * m) {
  oled.setCursor(x, y);
  oled.print("          ");
  oled.setCursor(x, y);
  oled.print(m);
}

void printOled(uint8_t x, uint8_t y, uint32_t m) {
  oled.setCursor(x, y);
  oled.print("          ");
  oled.setCursor(x, y);
  oled.print(m);
}

void printOled(uint8_t x, uint8_t y, int32_t m) {
  oled.setCursor(x, y);
  oled.print("          ");
  oled.setCursor(x, y);
  oled.print(m);
}

void printOled(uint8_t x, uint8_t y, double m) {
  oled.setCursor(x, y);
  oled.print("          ");
  oled.setCursor(x, y);
  oled.print(m);
}

void baseOled() {
  oled.setCursor(0, 10);
  oled.print("MICMAC TX");
  oled.setCursor(0, 30);
  oled.print("COL");
  oled.setCursor(0, 40);
  oled.print("NODE");
  oled.setCursor(0, 60);
  oled.print("SF:  ");
  oled.print(LORAsf);
  oled.setCursor(0, 70);
  oled.print("CR:  4/");
  oled.print(LORAcr);
  oled.setCursor(0, 80);
  oled.print("BW:  ");
  oled.print(LORAbw / 1000);
  oled.setCursor(0, 90);
  oled.print("PWR: ");
  oled.print(LORApwr);
  oled.updateDisplay();
}
