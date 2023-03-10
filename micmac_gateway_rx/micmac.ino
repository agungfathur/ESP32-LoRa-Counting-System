void systemInit() {
  PC.begin(PCbaud);
  pinMode(LED, OUTPUT);
}

void flushPC() {
  while (PC.available()) PC.read();
}

void led(bool State) {
  digitalWrite(LED, State);
}

bool checkCrc(uint8_t * Buf, uint8_t x) {
  if (calcCrc(Buf, x) == 0) return true;
  return false;
}

uint8_t calcCrc(uint8_t * Buf, uint8_t Size) {
  uint8_t Crc = 0;
  for (uint8_t i = 0; i < Size; i++) {
    uint8_t a = Buf[i];
    for (uint8_t j = 0; j < 8; j++) {
      uint8_t b = (Crc ^ a) & 0x01;
      Crc >>= 1;
      if (b)
        Crc ^= 0x8C;
      a >>= 1;
    }
  }
  return Crc;
}

uint16_t memcpy16(uint8_t* Buf) {
  return (uint16_t)Buf[0] << 8 | Buf[1];
}

uint16_t memcpy16(uint16_t* x, uint8_t* Buf) {
  *x = (uint16_t)Buf[0] << 8 | Buf[1];
}

uint32_t memcpy32(uint8_t* Buf) {
  return (uint32_t)Buf[0] << 24 | Buf[1] << 16 | Buf[2] << 8 | Buf[3];
}

bool memcmp16(uint8_t * Buf, uint16_t x, uint8_t y) {
  if (Buf[y] == (x >> 8) && Buf[y + 1] == (x & 0xFF)) return true;
  else return false;
}

uint16_t bswp16 (uint16_t x) {
  return ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8));
}

uint32_t bswp32 (uint32_t x) {
  return ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |
          (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24));
}
