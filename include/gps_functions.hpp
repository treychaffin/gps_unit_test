// #ifndef BCD57B92_43D3_4A71_81DE_7D26B7B5A6B2
// #define BCD57B92_43D3_4A71_81DE_7D26B7B5A6B2

// #include <TimeLib.h>
#include <TinyGPS.h>       // http://arduiniana.org/libraries/TinyGPS/
#include <RTClib.h>
// TinyGPS and SoftwareSerial libraries are the work of Mikal Hart

#define SerialGPS Serial1 // User SerialGPS name for clarity

#define PMTK_SET_NMEA_OUTPUT_GLLONLY                                           \
  "$PMTK314,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29" ///< turn on only the
                                                      ///< GPGLL sentence
#define PMTK_SET_NMEA_OUTPUT_RMCONLY                                           \
  "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29" ///< turn on only the
                                                      ///< GPRMC sentence
#define PMTK_SET_NMEA_OUTPUT_VTGONLY                                           \
  "$PMTK314,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29" ///< turn on only the
                                                      ///< GPVTG
#define PMTK_SET_NMEA_OUTPUT_GGAONLY                                           \
  "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29" ///< turn on just the
                                                      ///< GPGGA
#define PMTK_SET_NMEA_OUTPUT_GSAONLY                                           \
  "$PMTK314,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29" ///< turn on just the
                                                      ///< GPGSA
#define PMTK_SET_NMEA_OUTPUT_GSVONLY                                           \
  "$PMTK314,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0*29" ///< turn on just the
                                                      ///< GPGSV
#define PMTK_SET_NMEA_OUTPUT_RMCGGA                                            \
  "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28" ///< turn on GPRMC and
                                                      ///< GPGGA
#define PMTK_SET_NMEA_OUTPUT_RMCGGAGSA                                         \
  "$PMTK314,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29" ///< turn on GPRMC, GPGGA
                                                      ///< and GPGSA
#define PMTK_SET_NMEA_OUTPUT_ALLDATA                                           \
  "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28" ///< turn on ALL THE DATA
#define PMTK_SET_NMEA_OUTPUT_OFF                                               \
  "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28" ///< turn off output

/**********************
      Data Types
***********************/

typedef union _float_bytes{
 float val;
 byte bytes[sizeof(float)];
} FLOAT_BYTES;

//******** GPS Vars ********
extern TinyGPS gps;
extern FLOAT_BYTES lat;
extern FLOAT_BYTES lon;

/*****************************
      GPS Time Functions
******************************/

void initGPS();
void SET_NMEA_OUTPUT_GLLONLY();
void SET_NMEA_OUTPUT_RMCONLY();
void SET_NMEA_OUTPUT_VTGONLY();
void SET_NMEA_OUTPUT_GGAONLY();
void SET_NMEA_OUTPUT_GSAONLY();
void SET_NMEA_OUTPUT_GSVONLY();
void SET_NMEA_OUTPUT_RMCGGA();
void SET_NMEA_OUTPUT_RMCGGAGSA();
void SET_NMEA_OUTPUT_ALLDATA();
void SET_NMEA_OUTPUT_OFF();
void updateGPSTime();
void digitalClockDisplay();
void printDigits(int digits);
void printFloat(float val, float invalid, int len, int prec);
DateTime getGPSDateTime();

// #endif /* BCD57B92_43D3_4A71_81DE_7D26B7B5A6B2 */
