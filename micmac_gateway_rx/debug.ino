void debugFlag() {
#ifdef DBG
  DBG(("Flag:  RxPkg:%i RxMsg:%i Crc:%i Head:%i Col:%i Valid:%i NewPkg:%i NewMsg:%i BleOk:%i FileOk:%i LoraOk:%i\n",
       Flag.RxPkg, Flag.RxMsg, Flag.Crc, Flag.Head, Flag.Col, Flag.Valid, Flag.NewPkg, Flag.NewMsg, Flag.BleOk, Flag.FileOk, Flag.LoraOk));
#endif
}

void debugPkg(uint8_t * Buf, uint8_t x) {
#ifdef DBG
  DBG(("Pkg:   "));
  for (uint8_t i = 0; i < x; i++) DBG(("%i ", Buf[i]));
  DBG(("\n"));
#endif
}

void debugRssi() {
#ifdef DBG
  DBG(("Rssi:  %i\n", LoRa.packetRssi()));
#endif
}

void debugSnr() {
#ifdef DBG
  DBG(("Snr:   %.3f\n", LoRa.packetSnr()));
#endif
}

void debugFei() {
#ifdef DBG
  DBG(("Fei:   %i\n", LoRa.packetFrequencyError()));
#endif
}
