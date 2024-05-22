# GPS troubleshooting

The goal of this project is figure out:
- Why the new [Adafruit Ultimate GPS FeatherWing](https://www.adafruit.com/product/3133) modules don't work with the Mikal Hart's [TinyGPS](https://github.com/mikalhart/TinyGPS) library
- Find a solution to make the modules work with the library.

I have a project that uses the Mikal Hart's [TinyGPS](https://github.com/mikalhart/TinyGPS) library to parse data from [Adafruit Ultimate GPS FeatherWing](https://www.adafruit.com/product/3133) modules. The featherwing modules is the same module as the [Adafruit Ultimate GPS Breakout](https://www.adafruit.com/product/746), just in the Adafruit Feather layout. 

From the [Adafruit Ultimate GPS Breakout](https://www.adafruit.com/product/746) product page: *As of Sept 2021, the original "Ultimate GPS" module we used was discontinued by the vendor. We found and are using a nearly identical version of the module with the same functionality. The commands for querying the antenna have changed slightly so existing projects may need to update their firmware.*

![test equipment](/docs/img/adafruit_GPS_testing.png)

[MTK3329/MTK3339 command set sheet](https://cdn-shop.adafruit.com/datasheets/PMTK_A11.pdf)

## Testing

Default serial output from [GPS_HardwareSerial_Parsing.ino](https://github.com/adafruit/Adafruit_GPS/blob/master/examples/GPS_HardwareSerial_Parsing/GPS_HardwareSerial_Parsing.ino)


### PA1616D

```
Time: 19:50:10.000
Date: 11/4/2024
Fix: 1 quality: 2
Location: 3906.2783N, 9625.8213W
Speed (knots): 0.01
Angle: 0.00
Altitude: 360.90
Satellites: 18
Antenna status: 0
$GNGGA,195011.000,3906.2783,N,09625.8213,W,2,18,0.59,360.9,M,-28.2,M,,*40
$GNRMC,195011.000,A,3906.2783,N,09625.8213,W,0.01,0.00,110424,,,D*6B
$GNGGA,195012.000,3906.2783,N,09625.8213,W,2,18,0.59,360.9,M,-28.2,M,,*43
$GNRMC,195012.000,A,3906.2783,N,09625.8213,W,0.00,0.00,110424,,,D*69
```


### PA6H

```
Time: 19:50:51.981
Date: 11/4/2024
Fix: 1 quality: 1
Location: 3906.2754N, 9625.8223W
Speed (knots): 0.07
Angle: 227.56
Altitude: 346.70
Satellites: 9
Antenna status: 0
$GPGGA,195052.982,3906.2759,N,09625.8222,W,1,09,0.88,347.2,M,-28.2,M,,*5E
$GPGSA,A,3,06,20,22,24,25,11,19,12,17,,,,1.20,0.88,0.82*03
$GPRMC,195052.982,A,3906.2759,N,09625.8222,W,0.09,189.42,110424,,,A*7F
$GPVTG,189.42,T,,M,0.09,N,0.16,K,A*35
$GPGGA,195053.982,3906.2762,N,09625.8222,W,1,09,0.88,347.3,M,-28.2,M,,*56
$GPGSA,A,3,06,20,22,24,25,11,19,12,17,,,,1.20,0.88,0.82*03
$GPRMC,195053.982,A,3906.2762,N,09625.8222,W,0.07,65.46,110424,,,A*4F
$GPVTG,65.46,T,,M,0.07,N,0.14,K,A*0E
```

------------------------

In [GPS_HardwareSerial_Parsing.ino](https://github.com/adafruit/Adafruit_GPS/blob/master/examples/GPS_HardwareSerial_Parsing/GPS_HardwareSerial_Parsing.ino), comment out 
```c++
GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
```

from [Adafruit_GPS/srs/Adafruit_PMTK.h](https://github.com/adafruit/Adafruit_GPS/blob/master/src/Adafruit_PMTK.h):

```c++
#define PMTK_SET_NMEA_OUTPUT_RMCGGA                                            \
  "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28" ///< turn on GPRMC and
                                                      ///< GPGGA
```

From [Adafruit_GPS.cpp](https://github.com/adafruit/Adafruit_GPS/blob/master/src/Adafruit_GPS.cpp) `sendCommand()`:

```c++
void Adafruit_GPS::sendCommand(const char *str) { println(str); }
```


### PA6H

```
Time: 20:13:00.000
Date: 11/4/2024
Fix: 1 quality: 2
Location: 3906.2776N, 9625.8213W
Speed (knots): 0.01
Angle: 197.37
Altitude: 345.50
Satellites: 10
Antenna status: 3
$PGTOP,11,3*6F
$GPGGA,201301.000,3906.2777,N,09625.8209,W,2,10,0.89,345.5,M,-28.2,M,0000,0000*5C
$GPGSA,A,3,06,20,05,22,24,25,11,19,12,17,,,1.62,0.89,1.36*0F
$GPRMC,201301.000,A,3906.2777,N,09625.8209,W,0.02,183.70,110424,,,D*77
$GPVTG,183.70,T,,M,0.02,N,0.04,K,D*33
$PGTOP,11,3*6F
$GPGGA,201302.000,3906.2777,N,09625.8209,W,2,10,0.88,345.5,M,-28.2,M,0000,0000*5E
$GPGSA,A,3,06,20,05,22,24,25,11,19,12,17,,,1.62,0.88,1.36*0E
$GPRMC,201302.000,A,3906.2777,N,09625.8209,W,0.01,213.39,110424,,,D*70
$GPVTG,213.39,T,,M,0.01,N,0.02,K,D*31
```

#### PA1616

```
Time: 23:59:56.303
Date: 5/1/2080
Fix: 0 quality: 0
$GPGSV,2,1,08,06,,,48,11,,,50,05,,,38,20,,,48*7D
$GPGSV,2,2,08,19,,,42,25,,,46,24,,,42,12,,,49*74
$GLGSV,2,1,08,75,,,,84,,,,65,,,,82,,,*69
$GLGSV,2,2,08,73,,,,76,,,,85,,,,83,,,*6E
$GNRMC,235956.303,V,,,,,0.00,0.00,050180,,,N*51
$GNVTG,0.00,T,,M,0.00,N,0.00,K,N*2C
$GNGGA,201508.201,,,,,0,0,,,M,,M,,*5B
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GLGSA,A,1,,,,,,,,,,,,,,,*02
$GNRMC,201508.201,V,,,,,0.00,0.00,100180,,,N*56
$GNVTG,0.00,T,,M,0.00,N,0.00,K,N*2C
$GNGGA,201509.201,,,,,0,0,,,M,,M,,*5A
$GPGSA,A,1,,,,,,,,,,,,,,,*1E
$GLGSA,A,1,,,,,,,,,,,,,,,*02
```

SOLUTION:
`git clone --branch dpwe_gns_fix https://github.com/dpwe/TinyGPS.git`
