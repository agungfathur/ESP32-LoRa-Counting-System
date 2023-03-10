//class AdvDevCallBack: public BLEAdvertisedDeviceCallbacks {
//    void onResult(BLEAdvertisedDevice x) {
//      if (x.haveServiceUUID() && x.getServiceUUID().equals(UUIDsrvComm)) {
//        INFO(("BLE server found\n"));
//        INFO(("BLE server address %s\n", x.getAddress().toString().c_str()));
//        pAdDev = new BLEAdvertisedDevice(x);
//        x.getScan()->stop();
//      }
//    }
//};
//
//static void notifyCallBack(
//  BLERemoteCharacteristic* pX,
//  uint8_t* pBuf,
//  size_t Size,
//  bool isNotify) {
//  Serial.println(pX->getUUID().toString().c_str());
//}
//
//void bleInit() {
//  Flag.BleOk = false;
//  BLE.init("");
//  pSc = BLE.getScan();
//  pSc->setAdvertisedDeviceCallbacks(new AdvDevCallBack());
//  pSc->setActiveScan(true);
//  INFO(("BLE start scanning\n"));
//  pSc->start(BLEscanTime);
//}
//
//void bleHandle() {
//  if (!Flag.BleOk) {
//    bleConnect();
//    if (Flag.BleOk) return;
//    WARN(("BLE not connected, trying to connect\n"));
//    return;
//  }
//  bleReport();
//}
//
//void bleReport() {
//  if (!Flag.Valid || !Flag.NewPkg) return;
//  pRmChrTx->writeValue(Pkg, PkgSize);
//  INFO(("BLE report new package\n"));
//}
//
//void bleConnect() {
//  if (!checkAdDev()) return;
//  createCl();
//  if (!getRmSrv()) return;
//  if (!getRmChr()) return;
//  Flag.BleOk = true;
//  INFO(("BLE connected\n"));
//}
//
//void createCl() {
//  pCl = BLE.createClient();
//  INFO(("BLE connect to %s\n", pAdDev->getAddress().toString().c_str()));
//  pCl->connect(pAdDev->getAddress());
//}
//
//bool checkAdDev() {
//  if (pAdDev == nullptr) {
//    WARN(("BLE server not found, try to scan\n"));
//    pSc->start(BLEscanTime);
//    return false;
//  }
//  return true;
//}
//
//bool getRmSrv() {
//  pRmSrvComm = pCl->getService(UUIDsrvComm);
//  if (pRmSrvComm == nullptr) {
//    pCl->disconnect();
//    WARN(("BLE service not found, disconnecting\n"));
//    return false;
//  }
//  INFO(("BLE service found\n"));
//  return true;
//}
//
//bool getRmChr() {
//  pRmChrRx = pRmSrvComm->getCharacteristic(UUIDchrRx);
//  if (pRmChrRx == nullptr) {
//    pCl->disconnect();
//    WARN(("BLE RX not found, disconnecting\n"));
//    return false;
//  }
//  if (pRmChrRx->canRead())
//    INFO(("BLE RX can read\n"));
//  else {
//    pCl->disconnect();
//    WARN(("BLE RX can't read, disconnecting\n"));
//    return false;
//  }
//  if (pRmChrRx->canNotify()) {
//    pRmChrRx->registerForNotify(notifyCallBack);
//    INFO(("BLE registered for notification\n"));
//  }
//  else {
//    pCl->disconnect();
//    WARN(("BLE RX can't notify, disconnecting\n"));
//    return false;
//  }
//  pRmChrTx = pRmSrvComm->getCharacteristic(UUIDchrTx);
//  if (pRmChrTx == nullptr) {
//    pCl->disconnect();
//    WARN(("BLE TX not found, disconnecting\n"));
//    return false;
//  }
//  if (pRmChrTx->canWrite())
//    INFO(("BLE TX can write\n"));
//  else {
//    pCl->disconnect();
//    WARN(("BLE TX can't write, disconnecting\n"));
//    return false;
//  }
//  return true;
//}
