#ifdef MC_WEB
void webserver_handler() {
  webserver.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmac.html");
  });
  webserver.on("/micmac.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmac.css", "text/css");
  });
  webserver.on("/micmacico.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmacico.png", "image/png");
  });
  webserver.on("/micmac.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmac.png", "image/png");
  });
  webserver.on("/micmac.ttf", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmac.ttf", "font/ttf");
  });
  webserver.on("/micmac.woff", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmac.woff", "font/woff");
  });
  webserver.on("/micmac.woff2", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmac.woff2", "font/woff2");
  });
  webserver.on("/micmac.eot", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/micmac.eot", "font/eot");
  });
  webserver.on("/cowcount", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", (String)COW_count);
  });
  webserver.on("/cowlist", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", COW_list);
  });
}
#endif
void webserver_update(uint16_t x) {
  if (x < 65535) {
    if (COW_check[x] == 0) {
      COW_check[x] = 1;
      COW_count++;
      COW_new = true;
#ifdef MC_WEB
      COW_list = "\n\n";
      for (uint16_t i = 1; i < 65535; i++) {
        if (COW_check[i] == 1)
          COW_list = COW_list + "Node " + String(i) + "\n";
      }
#endif
    }
  }
}
