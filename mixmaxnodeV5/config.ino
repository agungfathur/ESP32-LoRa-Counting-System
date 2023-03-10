void config_node() {
  if (PC.available()) {
    if (PC.readString() == "config\n") {
      PC.printf("CONFIG MODE\n");
      PC.printf("COLONY: %i\n", ID_colony);
      PC.printf("NODE: %i\n", ID_node);
      PC.printf("TOTAL NODE: %i\n\n", TOTAL_node);
      for (;;) {
        if (PC.peek() == 'c') {
          PC.read();
          int _col = PC.parseInt();
          if (_col > 0 && _col <= 30) {
            set_id_colony((uint16_t)_col);
            PC.printf("NEW COLONY: %i\n", ID_colony);
          }
          else PC.printf("%i is invalid value, try again!\n", _col);
        }
        if (PC.peek() == 'n') {
          PC.read();
          int _node = PC.parseInt();
          if (_node > 0 && _node <= 300) {
            set_id_node((uint16_t)_node);
            PC.printf("NEW NODE: %i\n", ID_node);
          }
          else PC.printf("%i is invalid value, try again!\n", _node);
        }
        if (PC.peek() == 't') {
          PC.read();
          int _tot = PC.parseInt();
          if (_tot > 0 && _tot <= 300) {
            set_total_node((uint16_t)_tot);
            PC.printf("NEW TOTAL NODE: %i\n", TOTAL_node);
          }
          else PC.printf("%i is invalid value, try again!\n", _tot);
        }
        if (PC.peek() == '\n') {
          break;
        }
      }
      PC.printf("EXITING CONFIG MODE\n");
    }
  }
}


//void configGate(String _cfg) {
//  led(HIGH);
//  if (_cfg == "config colony\n")     config_id_colony();
//  if (_cfg == "config node\n")     config_id_node();
//  if (_cfg == "config total node\n") config_total_node();
//  led(LOW);
//}
//
//void config_id_colony() {
//  Serial.println("config colony: %i\n", Col);
//  while (1) {
//    if (PC.available()) {
//      int _Col = PC.parseInt();
//      flushPC();
//      if (_Col > 0 && _Col < 65535) {
//        setCol((uint16_t)_Col);
//        Serial.println("colony: %i\n", Col);
//        Serial.println("done\n");
//        break;
//      }
//      else Serial.println("%i is invalid value, try again!\n", _Col);
//    }
//  }
//}
//
//void config_id_node() {
//  Serial.println("config colony: %i\n", Col));
//  while (1) {
//    if (PC.available()) {
//      int _Col = PC.parseInt();
//      flushPC();
//      if (_Col > 0 && _Col < 65535) {
//        setCol((uint16_t)_Col);
//        Serial.println("colony: %i\n", Col);
//        Serial.println("done\n");
//        break;
//      }
//      else Serial.println("%i is invalid value, try again!\n", _Col);
//    }
//  }
//}
//
//void config_total_node() {
//  Serial.println("config total node: %i\n", Total);
//  while (1) {
//    if (PC.available() {
//      int _Total = PC.parseInt();
//      flushPC();
//      if (_Total > 0 && _Total < 65535) {
//        setTotal((uint16_t)_Total);
//        Serial.println("total node: %i\n", Total);
//        Serial.println("done\n");
//        break;
//      }
//      else Serial.println("%i is invalid value, try again!\n", _Total));
//    }
//  }
//}
