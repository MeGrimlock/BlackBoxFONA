/*Codgio funcional SIM808, FONA - ProMini
  -Los comandos estan implementados como funciones.
  -Tiene interfaz serie (no automatica)
*/
//----------------------------------------------------------------------------------------------------------------------------------
#include "Adafruit_FONA.h"

#define FONA_RX 11
#define FONA_TX 10
#define FONA_RST 4

#define debug false
#define pwrON true
#define pwrOFF false

// this is a large buffer for replies
char replybuffer[255];
char *url="https://dweet.io/dweet/for/cloudstat1?"; 

#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

uint8_t type;
char gpsdata[120];

float latitude, longitude, speed_kph, heading, speed_mph, altitude;
char sendto[21], message[141];

char tempSpd[7]; 
char tempLat[11];
char tempLon[11];

//-----------------------------------------------------------------------------------------------------------------------------------

 // Define hardware connections
#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
#define PIN_LED_OUT 13
#define PIN_ANALOG_IN A0

//-----------------------------------------------------------------------------------------------------------------------------------
void setup() {
  while (!Serial);

  Serial.begin(115200);
  Serial.println(F("IMM - Ruidos Molestos V.0.9"));
  Serial.println(F("Initializing....(May take 3 seconds)"));
  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Modem 3G no responde."));
    while (1);
  }
  type = fona.type();
  Serial.println(F("SIM808 is OK"));  
  // Print module IMEI number.
  char imei[15] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("IMEI: "); Serial.println(imei);
  }
  fona.setGPRSNetworkSettings(F("prepago.ancel"), F("bam"), F("bam"));
  fona.setHTTPSRedirect(false);
  //printMenu();
  Serial.println("Testing Net Status and RSSI");
  getNetStatus();
  getRSSI();
  fona.setHTTPSRedirect(true);
  while(getURL("https://dweet.io/get/dweets/for/cloudstat1")==false){
    powerGPRS(pwrON);
    delay(10000);
  }
  fona.setHTTPSRedirect(false);
  delay(2000);
  //while(getGPSfix()<=0)
  //    powerGPS(pwrON);
  //-----------------------------------------------------------------------------------------
  //  Configure LED pin as output
  pinMode(PIN_LED_OUT, OUTPUT);
  // Display status
  Serial.println("Inicializacion lista.\n\n");
}

int value; //Valor del sensor de sonido.

void loop() {
  Serial.print(F("IMM - Ruidos Molestos > "));
  //Si no se recibio el comando serie del usuario, leer la uart del SIM
  while (! Serial.available() ) {
    if (fona.available()) {
      //Serial.write(fona.read());
      delay(10);
    }else{/*
      if (getGPSLocation()==true){
        sendGPS();
        delay(30000);
      }else
        Serial.println("GPS data not good (yet)");
      printGPS();
      //readALLSMS();*/
      
      // Check the envelope input
      value = analogRead(PIN_ANALOG_IN);
      Serial.print("Valor del sensor = "+String(value)+"dB ");
      // Convert envelope value into a message
      Serial.print("Estado: ");
      if(value <= 20) {
        Serial.println("0. Super tranquilo.");
      }
      else if( (value > 20) && ( value <= 35) ){
        Serial.println("1. Tranquilo.");
      }
      else if( (value > 35) && ( value <= 70)) {
        Serial.println("2. Conversacion.");
      }else{
        Serial.println("3. Ruidoso.");  
      }
      getKONA("http://noise.dev.konabackend.com/events/add?");
      delay(500);
    }
  }

  char command = Serial.read(); 
  Serial.println(command);
  procesarComandoSerie(command);
  flushSerial();

  if (debug==true){
    while (fona.available()) {
      Serial.write(fona.read());
    }
  }
}




