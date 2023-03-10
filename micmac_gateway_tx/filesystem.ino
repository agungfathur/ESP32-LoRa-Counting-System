//void sdcardInit() {
//  pinMode(SDd0, INPUT_PULLUP);
//  pinMode(SDd1, INPUT_PULLUP);
//  pinMode(SDd3, INPUT_PULLUP);
//  if (!SD_MMC.begin()) {
//    INFO(("Card Mount Failed"));
//    return;
//  }
//  uint8_t cardType = SD_MMC.cardType();
//  if (cardType == CARD_NONE) {
//    INFO(("No SD_MMC card attached"));
//    return;
//  }
//  INFO(("SD_MMC Card Type: "));
//  if (cardType == CARD_MMC) {
//    INFO(("MMC"));
//  } else if (cardType == CARD_SD) {
//    INFO(("SDSC"));
//  } else if (cardType == CARD_SDHC) {
//    INFO(("SDHC"));
//  } else {
//    INFO(("UNKNOWN"));
//  }
//  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
//  INFO(("SD_MMC Card Size: %lluMB\n", cardSize));
//  listDir("/", 0);
//  INFO(("Total space: %lluMB\n", SD_MMC.totalBytes() / (1024 * 1024)));
//  INFO(("Used space: %lluMB\n", SD_MMC.usedBytes() / (1024 * 1024)));
//}
//
//void listDir(const char * dirname, uint8_t levels) {
//  INFO(("Listing directory: %s\n", dirname));
//  File root = SD_MMC.open(dirname);
//  if (!root) {
//    INFO(("Failed to open directory\n"));
//    return;
//  }
//  if (!root.isDirectory()) {
//    INFO(("Not a directory\n"));
//    return;
//  }
//
//  File file = root.openNextFile();
//  while (file) {
//    if (file.isDirectory()) {
//      INFO(("  DIR : "));
//      INFO(("%s\n", file.name()));
//      if (levels) {
//        listDir(file.name(), levels - 1);
//      }
//    } else {
//      INFO(("  FILE: "));
//      INFO((file.name()));
//      INFO(("  SIZE: "));
//      INFO(("%i\n", file.size()));
//    }
//    file = root.openNextFile();
//  }
//}
//
//void createDir(const char * path) {
//  INFO(("Creating Dir: %s\n", path));
//  if (SD_MMC.mkdir(path)) {
//    INFO(("Dir created\n"));
//  } else {
//    INFO(("mkdir failed\n"));
//  }
//}
//
//void removeDir(const char * path) {
//  INFO(("Removing Dir: %s\n", path));
//  if (SD_MMC.rmdir(path)) {
//    INFO(("Dir removed\n"));
//  } else {
//    INFO(("rmdir failed\n"));
//  }
//}
//
//void readFile(const char * path) {
//  INFO(("Reading file: %s\n", path));
//
//  File file = SD_MMC.open(path);
//  if (!file) {
//    INFO(("Failed to open file for reading\n"));
//    return;
//  }
//
//  INFO(("Read from file: \n"));
//  while (file.available()) {
//    PC.write(file.read());
//  }
//}
//
//void writeFile(const char * path, const char * message) {
//  INFO(("Writing file: %s\n", path));
//
//  File file = SD_MMC.open(path, FILE_WRITE);
//  if (!file) {
//    INFO(("Failed to open file for writing\n"));
//    return;
//  }
//  if (file.print(message)) {
//    INFO(("File written\n"));
//  } else {
//    INFO(("Write failed\n"));
//  }
//}
//
//void appendFile(const char * path, const char * message) {
//  INFO(("Appending to file: %s\n", path));
//
//  File file = SD_MMC.open(path, FILE_APPEND);
//  if (!file) {
//    INFO(("Failed to open file for appending\n"));
//    return;
//  }
//  if (file.print(message)) {
//    INFO(("Message appended\n"));
//  } else {
//    INFO(("Append failed\n"));
//  }
//}
//
//void renameFile(const char * path1, const char * path2) {
//  INFO(("Renaming file %s to %s\n", path1, path2));
//  if (SD_MMC.rename(path1, path2)) {
//    INFO(("File renamed\n"));
//  } else {
//    INFO(("Rename failed\n"));
//  }
//}
//
//void deleteFile(const char * path) {
//  INFO(("Deleting file: %s\n", path));
//  if (SD_MMC.remove(path)) {
//    INFO(("File deleted\n"));
//  } else {
//    INFO(("Delete failed\n"));
//  }
//}
