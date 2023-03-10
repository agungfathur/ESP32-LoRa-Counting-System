void mixmax_sleep() {
  switch (SYS_mode) {
    case NORMAL_mode: normal_sleep(); break;
    case GPS_mode:    gps_sleep();    break;
    case WIFI_mode:   wifi_sleep();   break;
    case BLE_mode:    ble_sleep();    break;
    default: break;
  }
  DBG.println("SLEEP");
  esp_deep_sleep_start();
}

void normal_sleep() {
  if (flag.wait_ || flag.ping_) {
    LoRa.sleep();
    DBG.println(TIME_sleep);
    esp_sleep_enable_timer_wakeup(TIME_sleep);
  }
  else {
    pinMode(LORA_irq, INPUT);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, HIGH);
  }
}

void gps_sleep() {
  GPS_retry++;
  if (flag.gps_fix_ && !flag.gps_valid_) {
    GPS_wake_cause = GPS_timer;
    esp_sleep_enable_timer_wakeup(10000000);
  }
  else {
    GPS_wake_cause = GPS_interrupt;
    pinMode(GPS_pps, INPUT);
    esp_sleep_enable_timer_wakeup(TIME_gps * 1000000);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_12, HIGH);
  }
}

void wifi_sleep() {
  WIFI_retry++;
  esp_sleep_enable_timer_wakeup(10000000);
}

void ble_sleep() {

}
