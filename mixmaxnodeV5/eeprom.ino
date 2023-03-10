void eeprom_init() {
  EEPROM.begin(EEPROM_size);
  EEPROM.readUShort(EEPROM_id_node_addr);
  ID_colony  = EEPROM.readUShort(EEPROM_id_colony_addr);
  ID_node    = EEPROM.readUShort(EEPROM_id_node_addr);
  TOTAL_node = EEPROM.readUShort(EEPROM_total_node_addr);
}

void set_id_colony(uint16_t new_colony_id) {
  EEPROM.writeUShort(EEPROM_id_colony_addr,  new_colony_id);
  EEPROM.commit();
  ID_colony = EEPROM.readUShort(EEPROM_id_colony_addr);
}

void set_id_node(uint16_t new_node_id) {
  EEPROM.writeUShort(EEPROM_id_node_addr,  new_node_id);
  EEPROM.commit();
  ID_node = EEPROM.readUShort(EEPROM_id_node_addr);
}

void set_total_node(uint16_t new_total_node) {
  EEPROM.writeUShort(EEPROM_total_node_addr,  new_total_node);
  EEPROM.commit();
  TOTAL_node = EEPROM.readUShort(EEPROM_total_node_addr);
}
