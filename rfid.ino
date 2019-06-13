

void rfid(){
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    //delay(50);
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    //delay(50);
    return;
  }
  
  // Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID:"));
  const String ID = dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println("New tag read: " + ID);
  Serial.println();


  HTTPClient http; //Declare an object of class HTTPClient
    http.begin("http://jsonplaceholder.typicode.com/users/1"); //Specify request destination
    int httpCode = http.GET(); //Send the request
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString(); //Get the request response payload
      Serial.println(payload); //Print the response payload
    }
    http.end(); //Close connection
  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  delay(100);
}


String dump_byte_array(byte *buffer, byte bufferSize) {
  String out = "";
  for (byte i = 0; i < bufferSize; i++) {
      out += String(buffer[i] < 0x10 ? " 0" : " ") + String(buffer[i], HEX);
  }
  out.toUpperCase();
  out.replace(" ", "");
   
  return out;
}


void printArray(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
