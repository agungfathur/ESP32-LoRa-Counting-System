void config_gateway() {
  if (PC.available()) {
    if (PC.readString() == "config\n") {
      PC.printf("CONFIG MODE\n");
      PC.printf("COLONY: %i\n", Col);
      PC.printf("TOTAL NODE: %i\n\n", Total);
      for (;;) {
        if (PC.peek() == 'c') {
          PC.read();
          int _col = PC.parseInt();
          if (_col > 0 && _col <= 30) {
            set_id_colony((uint16_t)_col);
            PC.printf("NEW COLONY: %i\n", Col);
          }
          else PC.printf("%i is invalid value, try again!\n", _col);
        }
        if (PC.peek() == 't') {
          PC.read();
          int _tot = PC.parseInt();
          if (_tot > 0 && _tot <= 300) {
            set_total_node((uint16_t)_tot);
            PC.printf("NEW TOTAL NODE: %i\n", Total);
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
