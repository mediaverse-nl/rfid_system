#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <SPI.h>
#include <MFRC522.h>

//note #1
//watchdog timer moet ook geinstalleert worden 
//voor het checken van de status van het appraart 
//zodat we weten of het apparaat nog goed werkt

//note #2
//moeten een tijd library inbouwen om het apparaat 
//resetten op een spesifieke moment van de day (02:00 bv.)
//RTC module moet gekocht worden om een time library te kunnen gebruiken

#define USE_SERIAL Serial

#define SSID "get your own wifi"
#define PASSWORD "hhaallooo"

#define THIS_VERSION "v0.0.8"
#define BOOT_AFTER_UPDATE true

constexpr uint8_t RST_PIN =  0;          // Configurable, see typical pin layout above 18
constexpr uint8_t SS_PIN =  15;         // Configurable, see typical pin layout above  16

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

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

  USE_SERIAL.println("Setup");
  
  while (!USE_SERIAL);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  USE_SERIAL.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  USE_SERIAL.println("Setup done");
}

//start loop
void loop() {  
  rfid();
//   blinkLed();
//   USE_SERIAL.println("doing shit");
   delay(200);
}
