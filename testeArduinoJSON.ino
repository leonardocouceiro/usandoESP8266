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

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {2, 0, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 14}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
void setup() {

    USE_SERIAL.begin(115200);
    pinMode(16, OUTPUT);
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
    
char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }
  switch (key) {
    case '9':
      digitalWrite(16, HIGH);
      break;
    case '8':
      digitalWrite(16, LOW);
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
                const char* textoPergunta = root["pergunta"];
                USE_SERIAL.println(textoPergunta);
                const char* primeiraAlternativa = root["alternativas"][0];
                USE_SERIAL.println(primeiraAlternativa);

                USE_SERIAL.println();
                USE_SERIAL.print("[HTTP] connection closed or file end.\n");

            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    
      
      break;
  }
  
    delay(1000);
}

void mandarResposta(char alternativa) {
//  http.begin("");
//  String resposta = "{\"idRespondente\":1, \"idQuestao\":1, \"alternativa\": \"a\"}";
//  int codigoResposta = http.POST(resposta);
}

