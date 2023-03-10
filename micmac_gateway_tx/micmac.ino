void systemInit() {
  PC.begin(PCbaud);
  pinMode(LED, OUTPUT);
}

void led(bool State) {
  digitalWrite(LED, State);
}
