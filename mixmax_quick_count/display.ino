void oled_init() {
  oled.begin();
  oled.setBusClock(400000);
  oled.enableUTF8Print();
  oled.setFontMode(0);
  oled.setDrawColor(1);
  oled.setFont(u8g2_font_profont17_mf);
  const char* _text_1 = "Micro-Machina";
  const char* _text_2 = "Counter";
  oled.setCursor(((128 - (oled.getUTF8Width(_text_1))) / 2), 17);
  oled.print(_text_1);
  oled.setCursor(((128 - (oled.getUTF8Width(_text_2))) / 2), 34);
  oled.print(_text_2);
  oled.drawFrame(22, 40, 82, 23);
  oled.drawFrame(21, 39, 84, 25);
  oled.updateDisplay();
  oled.setFont(u8g2_font_profont29_mf);
}

void oled_update() {
  COW_new=false;
  uint8_t _digit=1;
  if(COW_count>9)_digit=2;
  if(COW_count>99)_digit=3;
  if(COW_count>999)_digit=4;
  if(COW_count>9999)_digit=5;
  uint8_t _offset = _digit*oled.getUTF8Width("X");
  oled.setCursor((128 - _offset)/2, 61);
  oled.print(COW_count);
  oled.drawFrame(22, 40, 82, 23);
  oled.drawFrame(21, 39, 84, 25);
  oled.updateDisplay();
}
