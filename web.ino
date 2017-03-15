boolean getURL(char *url){
  // read website URL
  uint16_t statuscode;
  int16_t length;
  Serial.println(F("\n****"));
  Serial.println(url);
  if (!fona.HTTP_GET_start(url, &statuscode, (uint16_t *)&length)) {
    Serial.println("Failed!");
    return false;
  }
  while (length > 0) {
    while (fona.available()) {
      char c = fona.read();
      // Serial.write is too slow, we'll write directly to Serial register!
  #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
      loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
      UDR0 = c;
  #else
      Serial.write(c);
  #endif
      length--;
      if (! length) break;
    }
  }
  Serial.println(F("\n****"));
  fona.HTTP_GET_end();  
  return true;
}

boolean sendGPS(){
  // read website URL
  uint16_t statuscode;
  int16_t length;
  Serial.println(F("\n****"));
  //Send URL with parameters: float latitude, longitude, speed_kph, heading, speed_mph, altitude
  flushSerial();
  char bufferGET[120];
  
  dtostrf(latitude,10,6,tempLat);
  dtostrf(longitude,10,6,tempLon);
  dtostrf(speed_kph,5,2,tempSpd);
  sprintf(bufferGET,"%slat=%s&lng=%s&spd=%s",url,tempLat,tempLon,tempSpd);
  
  Serial.println("Parameters for link: "+String(bufferGET));
  if (!fona.HTTP_GET_start(bufferGET, &statuscode, (uint16_t *)&length)) {
    Serial.println("Failed!");
    return false;
  }
  while (length > 0) {
    while (fona.available()) {
      char c = fona.read();
      // Serial.write is too slow, we'll write directly to Serial register!
  #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
      loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
      UDR0 = c;
  #else
      Serial.write(c);
  #endif
      length--;
      if (! length) break;
    }
  }
  Serial.println(F("\n****"));
  fona.HTTP_GET_end();  
  return true;
}

