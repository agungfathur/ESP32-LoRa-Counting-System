void debugPkg() {
#ifdef DBG
  DBG(("Pkg:   "));
  for (uint8_t i = 0; i < PkgSize; i++) DBG(("%i ", Pkg[i]));
  DBG(("\n"));
#endif
}

void debugMsg() {
#ifdef DBG
  DBG(("Msg:   "));
  for (uint8_t i = 0; i < MsgSize; i++) DBG(("%i ", Msg[i]));
  DBG(("\n"));
#endif
}
