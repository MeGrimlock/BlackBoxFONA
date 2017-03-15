void procesarComandoSerie(char command){
  switch (command) {
    /*
    case 'i': {
        //RSSI
        getRSSI();
        break;
      }
    case 'n': {
        //Network Status
        getNetStatus();
        break;
      }
    */
    /*** SMS ***/
    /*
    case 'N': {
      //Cantidad de sms
        getNumSMS();
        break;
      }
    case 'r': {
      //Leer un sms (en este caso 0)
        readSMS(0);
        break;
      }
    case 'R': {
        // read all SMS
        readALLSMS();
        break;
      }

    case 'd': {
        // delete an SMS en este caso 0
        deleteSMS(0);
        break;
      }

    case 's': {
        sendSMS("099479898","I'll be back ...");
        break;
      }
  */
    /*********************************** GPS (SIM808 only) */
  /*
    case 'o': {
        powerGPS(false);
        break;
      }
    case 'O': {
        // turn GPS on
        powerGPS(true);
        break;
      }
    case 'x': {
        getGPSfix();
        break;
      }

    case 'L': {
        getGPSLocation();//gpsdata);
        //Serial.println(gpsdata);
        break;
      }
    //Raw NMEA out (FONA808)
    case 'E': {
        flushSerial();
        if (type == FONA808_V1) {
          Serial.print(F("GPS NMEA output sentences (0 = off, 34 = RMC+GGA, 255 = all)"));
        } else {
          Serial.print(F("On (1) or Off (0)? "));
        }
        uint8_t nmeaout = readnumber();
        // turn on NMEA output
        fona.enableGPSNMEA(nmeaout);
        break;
      }
  */
    /*********************************** GPRS */

    case 'g': {
        // turn GPRS off
        if (!powerGPRS(false))
          Serial.println(F("Failed to turn off"));
        break;
      }
    case 'G': {
        // turn GPRS on
        if (!powerGPRS(true))
          Serial.println(F("Failed to turn on"));
        break;
      }
    /*
    case 'l': {
        // check for GSMLOC (requires GPRS)
        uint16_t returncode;

        if (!fona.getGSMLoc(&returncode, replybuffer, 250))
          Serial.println(F("Failed!"));
        if (returncode == 0) {
          Serial.println(replybuffer);
        } else {
          Serial.print(F("Fail code #")); Serial.println(returncode);
        }

        break;
      }
    */
    //case 'W': {
        // Post data to website
        //postURL();
     //   break;
     // }
    /*****************************************/
    default: {
        Serial.println(F("Unknown command"));
        //printMenu();
        break;
      }
  }
}
