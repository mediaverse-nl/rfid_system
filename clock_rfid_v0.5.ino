#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

//note moeten een tijd library inbouwen om het apparaat 
//resetten op een spesifieke moment van de day (02:00 bv.)
//RTC module moet gekocht worden om een time library te kunnen gebruiken

#define USE_SERIAL Serial

#define SSID "get your own wifi"
#define PASSWORD "hhaallooo"

#define THIS_VERSION "v0.0.5"
#define BOOT_AFTER_UPDATE true

//start setup 
void setup() {

  //start blink
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  USE_SERIAL.begin(115200);
  USE_SERIAL.setDebugOutput(false);
  
  USE_SERIAL.println(); 
  
  for(uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  USE_SERIAL.println("\nhttpUpdate");
  USE_SERIAL.println(THIS_VERSION);
  USE_SERIAL.println("start...");
  
  //trying to connect to wifi 
  WiFi.begin(SSID, PASSWORD);
 
  USE_SERIAL.println("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    USE_SERIAL.print(".");
    shortBlink();
    delay(1000);
  }

  //check for update
  spiffs();
}

//start loop
void loop() {  
   blinkLed();
   USE_SERIAL.println("doing shit");
   delay(5000);
}
