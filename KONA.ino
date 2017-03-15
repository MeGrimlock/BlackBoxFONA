boolean getKONA(char *url){
  // read website URL
  uint16_t statuscode;
  int16_t length;

  char bufferGET[120];
  sprintf(bufferGET,"%sid=Device1&decibels=%i",url,value);
  
  Serial.println(F("\n****"));
  Serial.println(bufferGET);
  
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
