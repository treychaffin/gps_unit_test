#include <Arduino.h>
#include "gps_functions.hpp"

/**********************
     Core Functions
***********************/

void setup() {
  Serial.begin(115200);
  delay(5000);
  initGPS();
  // SET_NMEA_OUTPUT_GLLONLY();
  // SET_NMEA_OUTPUT_RMCONLY();
  // SET_NMEA_OUTPUT_VTGONLY();
  // SET_NMEA_OUTPUT_GGAONLY();
  // SET_NMEA_OUTPUT_GSAONLY();
  // SET_NMEA_OUTPUT_GSVONLY();
  // SET_NMEA_OUTPUT_RMCGGA();
  // SET_NMEA_OUTPUT_RMCGGAGSA();
  // SET_NMEA_OUTPUT_ALLDATA();
  // SET_NMEA_OUTPUT_OFF();
}

void loop() {
  updateGPSTime();
  digitalClockDisplay();
  delay(1000);
}