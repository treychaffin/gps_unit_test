#include "gps_functions.hpp"
// #include "globals.hpp"
#include <RTClib.h>
// #include "logging.hpp"

//******** GPS Vars ********
TinyGPS gps;
time_t prevDisplay = 0; // when the digital clock was displayed
FLOAT_BYTES lat;
FLOAT_BYTES lon;

/*****************************
      GPS Time Functions
******************************/

void initGPS() {
  SerialGPS.begin(9600);
  SET_NMEA_OUTPUT_RMCONLY();
}

void SET_NMEA_OUTPUT_GLLONLY() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_GLLONLY);
}

void SET_NMEA_OUTPUT_RMCONLY() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_RMCONLY);
}

void SET_NMEA_OUTPUT_VTGONLY() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_VTGONLY);
}

void SET_NMEA_OUTPUT_GGAONLY() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_GGAONLY);
}

void SET_NMEA_OUTPUT_GSAONLY() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_GSAONLY);
}

void SET_NMEA_OUTPUT_GSVONLY() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_GSVONLY);
}

void SET_NMEA_OUTPUT_RMCGGA() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_RMCGGA);
}

void SET_NMEA_OUTPUT_RMCGGAGSA() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_RMCGGAGSA);
}

void SET_NMEA_OUTPUT_ALLDATA() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_ALLDATA);
}

void SET_NMEA_OUTPUT_OFF() {
  SerialGPS.println(PMTK_SET_NMEA_OUTPUT_OFF);
}


void updateGPSTime() {
  while (SerialGPS.available()) {
    char GPSmessage = SerialGPS.read();
    Serial.print(GPSmessage);
    if (gps.encode(GPSmessage)) { // process gps messages
      // when TinyGPS reports new data...
      unsigned long age;      
      int Year;
      byte Month, Day, Hour, Minute, Second;
      gps.crack_datetime( & Year, & Month, & Day, & Hour, & Minute, & Second, NULL, & age);
      if (age < 500) {
        // // set the time to the latest GPS reading
        // setTime(Hour, Minute, Second, Day, Month, Year);
				// // If the RTC is out of sync, update it with the latest GPS time
				// DateTime now = rtc.now();
				// if (
        //   abs(now.second() - Second) > 1 ||
        //   now.minute() != Minute ||
        //   now.hour() != Hour ||
        //   now.day() != Day ||
        //   now.month() != Month ||
        //   now.year() != Year
        //   ) {
        //   logMsg("Syncing RTC with GPS - RTC sec: " + String(now.second()) + " GPS sec: " + String(Second));
				// 	rtc.adjust(DateTime(Year, Month, Day, Hour, Minute, Second));        
				// }
        gps.f_get_position(&lat.val, &lon.val, &age);
      }
    }
  }
}

DateTime getGPSDateTime() {
  unsigned long age;      
  int Year;
  byte Month, Day, Hour, Minute, Second;
  gps.crack_datetime( & Year, & Month, & Day, & Hour, & Minute, & Second, NULL, & age);
  return DateTime(Year, Month, Day, Hour, Minute, Second);
}

void digitalClockDisplay() {
  // digital clock display of the time
  DateTime now = getGPSDateTime();
  Serial.println(); Serial.println();
  Serial.print("GPS Time: ");
  Serial.print(now.year());
  Serial.print(" ");
  Serial.print(now.month());
  Serial.print(" ");
  Serial.print(now.day());
  Serial.print(" ");
  Serial.print(now.hour());
  printDigits(now.minute());
  printDigits(now.second());
  Serial.println(); 

  // Serial.print("RTC Time: ");
  // Serial.print(rtc.now().year());
  // Serial.print(" ");
  // Serial.print(rtc.now().month());
  // Serial.print(" ");
  // Serial.print(rtc.now().day());
  // Serial.print(" ");
  // Serial.print(rtc.now().hour());
  // printDigits(rtc.now().minute());
  // printDigits(rtc.now().second());
  // Serial.println();

  Serial.print("GPS coordinates: ");
  printFloat(lat.val, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  printFloat(lon.val, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  Serial.println();Serial.println();
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void printFloat(float val, float invalid, int len, int prec) {
  if (val == invalid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
}