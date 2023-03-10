void eeprom_init() {
  EEPROM.begin(EEPROM_size);
  Col   = EEPROM.readUShort(EEPROM_id_colony_addr);
  Total = EEPROM.readUShort(EEPROM_total_node_addr);
}

void set_id_colony(uint16_t new_colony_id) {
  EEPROM.writeUShort(EEPROM_id_colony_addr,  new_colony_id);
  EEPROM.commit();
  Col = EEPROM.readUShort(EEPROM_id_colony_addr);
}

void set_total_node(uint16_t new_total_node) {
  EEPROM.writeUShort(EEPROM_total_node_addr,  new_total_node);
  EEPROM.commit();
  Total = EEPROM.readUShort(EEPROM_total_node_addr);
}
