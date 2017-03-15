int8_t getNumSMS(){
// read the number of SMS's!
  return fona.getNumSMS();
}

void readSMS(int8_t smsn){
  dtostrf(latitude,10,6,tempLat);
  dtostrf(longitude,10,6,tempLon);
  // Retrieve SMS sender address/phone number.
  if (! fona.getSMSSender(smsn, replybuffer, 250)) {
    Serial.println("Failed!");
    return;
  }
  Serial.print(F("FROM: ")); Serial.println(replybuffer);
  //Guardo el telefono que me envio el SMS
  strncpy(sendto, replybuffer, 21);
  // Retrieve SMS value.
  uint16_t smslen;
  if (! fona.readSMS(smsn, replybuffer, 250, &smslen)) { // pass in buffer and max len!
    Serial.println("Failed!");
    return;
  }
  Serial.print(F("***** SMS #")); Serial.print(smsn);
  Serial.print(" ("); Serial.print(smslen); Serial.println(F(") bytes *****"));
  Serial.println(replybuffer);
  if (strcmp(replybuffer,"GPS")==0){
    sprintf(message,"http://maps.google.com/?q=%s,%s",tempLat,tempLon);
    Serial.println(message);
    sendSMS(sendto,message);  
  }
  Serial.println(F("*****")); 
  //deleteSMS(smsn); 
}

void readALLSMS(){
  int8_t smsnum = fona.getNumSMS();
  uint16_t smslen;
  int8_t smsn;

  if ( (type == FONA3G_A) || (type == FONA3G_E) ) {
    smsn = 0; // zero indexed
    smsnum--;
  } else {
    smsn = 1;  // 1 indexed
  }
  for ( ; smsn <= smsnum; smsn++) {
    readSMS(smsn);
  }  
}

void deleteSMS(uint8_t smsn){
  Serial.print(F("\n\rDeleting SMS #")); Serial.println(smsn);
  if (fona.deleteSMS(smsn)) {
    Serial.println(F("OK!"));
  } else {
    Serial.println(F("Couldn't delete"));
  }  
}

void sendSMS(char *sendto,char *menssage){  
  if (!fona.sendSMS(sendto, message)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Sent!"));
  }
}
