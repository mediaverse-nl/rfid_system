#define DEBUG ESP_HTTP_UPDATE

#define REMOTE_SERVER "http://clock-on.nl/firmware-wemos"
#define SKETCH_BIN "/wemos.bin"

void spiffs(){
  WiFi.macAddress(mac); 
  clientMac += macToStr(mac);
  
  USE_SERIAL.println("connected");  
  
  USE_SERIAL.println("--------- hier ---------");
  USE_SERIAL.print("\nhttpUpdate: ");
  USE_SERIAL.println(THIS_VERSION);
  USE_SERIAL.println(clientMac);
  USE_SERIAL.println("--------- hier ---------");

  String url = REMOTE_SERVER; 
    url += SKETCH_BIN;
    url += String("?v=") + THIS_VERSION + String("&mac=") + clientMac;
    
  USE_SERIAL.print("url: ");USE_SERIAL.println(url);
  USE_SERIAL.print("REMOTE_SERVER: ");USE_SERIAL.println(REMOTE_SERVER);
  USE_SERIAL.print("SKETCH_BIN: ");USE_SERIAL.println(SKETCH_BIN);
   
  ESPhttpUpdate.rebootOnUpdate(BOOT_AFTER_UPDATE);
  
  t_httpUpdate_return ret = ESPhttpUpdate.update(url);
 
  USE_SERIAL.print("ret ");
  USE_SERIAL.println(ret); 
  
  switch(ret) {
     case HTTP_UPDATE_FAILED:
         USE_SERIAL.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
         break;
     case HTTP_UPDATE_NO_UPDATES:
         USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
         break;
     case HTTP_UPDATE_OK:
         USE_SERIAL.println("HTTP_UPDATE_OK");
         break;
     default:
         USE_SERIAL.print("Undefined HTTP_UPDATE Code: ");USE_SERIAL.println(ret);
  }         
}
