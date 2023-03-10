//void fileInit() {
//  Flag.FileOk = FFat.begin();
//  if (FILEformatRetry == 0 && !Flag.FileOk) {
//    WARN(("Filesystem failed, not retrying to format\n"));
//    INFO(("Please change Partition Scheme to No OTA 2MB App 2MB FFAT\n"));
//    INFO(("Tools->Partition Scheme\n"));
//    return;
//  }
//  for (int i = 0; i < FILEformatRetry; i++) {
//    if (Flag.FileOk) {
//      INFO(("Filesystem Initialized\n"));
//      return;
//    }
//    WARN(("Filesystem failed, trying to format #%i\n", i));
//    FFat.format();
//    Flag.FileOk = FFat.begin();
//  }
//  INFO(("Filesystem free space: %10u\n", FFat.freeBytes()));
//}
//
//void fileHandle() {
//  if (!Flag.Valid || !Flag.NewPkg) return;
//  assignLog();
//  writeLog();
//}
//
//void assignLog() {
//  memcpy(Log + LOGnode, Pkg + PKGnode, 2);
//  memcpy(Log + LOGlat,  Pkg + PKGlat,  4);
//  memcpy(Log + LOGlon,  Pkg + PKGlon,  4);
//  Log[LOGcrc] = calcCrc(Log, LogSize - 1);
//}
//
//void writeLog() {
//  fileWrite(Log, LogSize);
//}
//
//void fileWrite(uint8_t * Buf, uint8_t Size) {
//  INFO(("Writing Log File: %s\n", LogName.c_str()));
//  LogFile = FFat.open(LogName, FILE_APPEND);
//  if (!LogFile) {
//    WARN(("Failed to open Log File for writing"));
//    return;
//  }
//  if (LogFile.write(Buf, Size)) INFO(("Log File written"));
//  else WARN(("Log File write failed"));
//  LogFile.close();
//}
//
//void fileRead(String Path) {
//  INFO(("Reading Log File: %s\n", Path.c_str()));
//  LogFile = FFat.open(Path);
//  if (!LogFile || LogFile.isDirectory()) {
//    WARN(("Failed to open Log File for reading"));
//    return;
//  }
//  INFO(("Read from file:"));
//  while (LogFile.available()) {
//    PC.write(LogFile.read());
//  }
//  LogFile.close();
//}
