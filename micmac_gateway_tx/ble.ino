
class SrCallBack: public BLEServerCallbacks {
    void onConnect(BLEServer * pX) {
      //      deviceConnected = true;
      //      Serial.println("Connected");
    };
    void onDisconnect(BLEServer * pX) {
      //      deviceConnected = false;
      //      Serial.println("Disonnected");
    }
};

class ChrRxCallBack: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic * pX) {
      pValRx->setValue(pX->getValue());
    }
};

void bleInit() {
  BLE.init("MICRO-MACHINA");

  pSr = BLE.createServer();
  pSr->setCallbacks(new SrCallBack());

  pSrvComm = pSr->createService(UUIDsrvComm);
  pChrTx = pSrvComm->createCharacteristic(UUIDchrTx, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pChrTx->addDescriptor(new BLE2902());
  pChrRx = pSrvComm->createCharacteristic(UUIDchrRx, BLECharacteristic::PROPERTY_WRITE);
  pChrRx->setCallbacks(new ChrRxCallBack());
  pSrvComm->start();

  pSrvInfo = pSr->createService(UUIDsrvInfo);
  pChrStat = pSrvInfo->createCharacteristic(UUIDchrStat, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pChrStat->addDescriptor(new BLE2902());
  pChrDate = pSrvInfo->createCharacteristic(UUIDchrDate, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pChrDate->addDescriptor(new BLE2902());
  pChrTime = pSrvInfo->createCharacteristic(UUIDchrTime, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pChrTime->addDescriptor(new BLE2902());
  pChrLoc  = pSrvInfo->createCharacteristic(UUIDchrLoc,  BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pChrLoc ->addDescriptor(new BLE2902());
  pSrvInfo->start();

  pSrvConf = pSr->createService(UUIDsrvConf);
  pChrCol  = pSrvConf->createCharacteristic(UUIDchrCol,  BLECharacteristic::PROPERTY_READ);
  pChrCol->setValue(String(Col).c_str());
  pChrTot  = pSrvConf->createCharacteristic(UUIDchrTot,  BLECharacteristic::PROPERTY_READ);
  pChrTot->setValue(String(Total).c_str());
  pSrvConf->start();

  bleInitValue();

  pSr->getAdvertising()->addServiceUUID(UUIDsrvComm);
  pSr->getAdvertising()->addServiceUUID(UUIDsrvInfo);
  pSr->getAdvertising()->addServiceUUID(UUIDsrvConf);
  pSr->getAdvertising()->setScanResponse(true);
  pSr->getAdvertising()->start();
}

void bleInitValue() {
  updateStat("IDLE");
  updateDate(Day, Month, Year);
  updateTime(Hour, Minute);
  updateLoc(GateLat, GateLon);
}

void updateStat(String _Status) {
  Status = _Status;
  pChrStat->setValue(Status.c_str());
  pChrStat->notify();
}

void updateDate(uint8_t _Day, uint8_t _Month, uint8_t _Year) {
  Day   = _Day;
  Month = _Month;
  Year  = _Year;
  Date = String(Day) + " - " +
         String(Month) + " - " +
         String(Year);
  pChrDate->setValue(Date.c_str());
  pChrDate->notify();
}

void updateTime(uint8_t _Hour, uint8_t _Minute) {
  Hour   = _Hour;
  Minute = _Minute;
  Time = String(Hour) + " : " +
         String(Minute);
  pChrTime->setValue(Time.c_str());
  pChrTime->notify();
}

void updateLoc(int32_t _Lat, int32_t _Lon) {
  GateLat = _Lat;
  GateLon = _Lon;
  Loc = String((double)(GateLat / 1E7), 6) + " , " +
        String((double)(GateLon / 1E7), 6);
  pChrLoc->setValue(Loc.c_str());
  pChrLoc->notify();
}
