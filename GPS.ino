boolean powerGPS(boolean power){
  return fona.enableGPS(power);  
}

int8_t getGPSfix(){
  int8_t stat;
  // check GPS fix
  stat = fona.GPSstatus();
  /*if (stat < 0)
    Serial.println(F("Failed to query"));
  if (stat == 0) Serial.println(F("GPS off"));
  if (stat == 1) Serial.println(F("No fix"));
  if (stat == 2) Serial.println(F("2D fix"));
  if (stat == 3) Serial.println(F("3D fix"));*/
  return stat;
}

boolean getGPSLocation(){//char *gpsdata){
  // check for GPS location
  boolean gps_success = fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude); 
  /*Reply in format: mode,fixstatus,utctime(yyyymmddHHMMSS),
   * 
   latitude,longitude,altitude,speed,course,
   fixmode,reserved1,HDOP,PDOP,VDOP,
   reserved2,view_satellites,used_satellites,reserved3,C/N0max,
   HPA,VPA
   */
  fona.getGPS(0, gpsdata, 120);
  
  if (gps_success) {
    printGPS();
  }else{
    fona.getGPS(0, gpsdata, 120);
    if (type == FONA808_V1)
      Serial.println(F("Reply in format: mode,longitude,latitude,altitude,utctime(yyyymmddHHMMSS),ttff,satellites,speed,course"));
    else 
      Serial.println(F("Reply in format: mode,fixstatus,utctime(yyyymmddHHMMSS),latitude,longitude,altitude,speed,course,fixmode,reserved1,HDOP,PDOP,VDOP,reserved2,view_satellites,used_satellites,reserved3,C/N0max,HPA,VPA"));
    //Serial.println(gpsdata);
  }
  return gps_success;
}
void printGPS(){
  Serial.print("GPS lat:");
  Serial.print(latitude, 6);
  Serial.print(" long:");
  Serial.print(longitude, 6);
  Serial.print(" speed KPH:");
  Serial.print(speed_kph);;
  Serial.print(" heading:");
  Serial.print(heading);
  Serial.print(" altitude:");
  Serial.println(altitude);  
}
