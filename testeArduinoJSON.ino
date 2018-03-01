/**
 * StreamHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

void setup() {

    USE_SERIAL.begin(115200);
    // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("PROJETOS", "info@132");

}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");

        // configure server and url
        http.begin("http://www.mocky.io/v2/5a987c2f2e0000890f553369");
        //http.begin("192.168.1.12", 80, "/test.html");

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                // get tcp stream
                WiFiClient * stream = http.getStreamPtr();
                StaticJsonBuffer<300> jsonBuffer;
                JsonObject& root = jsonBuffer.parseObject(*stream);
                //root.printTo(USE_SERIAL);
                USE_SERIAL.println(root["pergunta"]);
                USE_SERIAL.println(root["alternativas"][0]);

                USE_SERIAL.println();
                USE_SERIAL.print("[HTTP] connection closed or file end.\n");

            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(2000);
}

