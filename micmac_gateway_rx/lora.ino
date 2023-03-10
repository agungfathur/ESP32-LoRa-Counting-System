void loraInit() {
  SPI.begin(LORAsck, LORAmiso,  LORAmosi, LORAcs);
  SPI.setFrequency(LORAspif);
  LoRa.setPins(LORAcs, LORArst, LORAirq);
  Flag.LoraOk = LoRa.begin(LORAfrq);
  if (!Flag.LoraOk) {
    WARN(("Lora failed\n"));
    return;
  }
  INFO(("Lora Initialized\n"));
  LoRa.setSpreadingFactor(LORAsf);
  LoRa.setSignalBandwidth(LORAbw);
  LoRa.setCodingRate4(LORAcr);
  LoRa.setTxPower(LORApwr);
  LoRa.onReceive(loraOnRx);
  LoRa.receive();
}

void loraHandle() {
  if (Flag.NewPkg) Flag.NewPkg = false;
  if (Flag.RxPkg) parsePkg(Pkg);
}

void loraOnRx(int Size) {
  if (Size == PkgSize) {
    Flag.RxPkg = true;
    for (uint8_t i = 0; i < PkgSize; i++) Pkg[i] = LoRa.read();
  }
  else {
    LoRa.flush();
  }
}

void parsePkg(uint8_t * Buf) {
  Flag.RxPkg  = false;
  Flag.NewPkg = true;
  Flag.Crc    = checkCrc(Buf, PkgSize);
  Flag.Head   = memcmp(&Head, Buf + PKGhead, 2) == 0 ? true : false;
  Flag.Col    = memcmp(&Col,  Buf + PKGcol,  2) == 0 ? true : false;
  Flag.Valid  = Flag.Crc & Flag.Head & Flag.Col;
  if (Flag.Valid)  {
    memcpy(&Col,  Pkg + PKGcol , 2);
    memcpy(&Node, Pkg + PKGnode, 2);
    memcpy(&Lat,  Pkg + PKGlat,  4);
    memcpy(&Lon,  Pkg + PKGlon,  4);
  }
  Rssi = LoRa.packetRssi();
  Snr  = LoRa.packetSnr();
  Fei  = LoRa.packetFrequencyError();
  debugFlag();
  debugPkg(Buf, PkgSize);
  debugRssi();
  debugSnr();
  debugFei();
}

void assignPkg() {
  memcpy(Pkg,           &Head, 2);
  memcpy(Pkg + PKGcol,  &Col,  2);
  memcpy(Pkg + PKGnode, &Node, 2);
  memcpy(Pkg + PKGlat,  &Lat,  4);
  memcpy(Pkg + PKGlon,  &Lon,  4);
  Pkg[PKGcrc] = calcCrc(Pkg, PkgSize - 1);
}
