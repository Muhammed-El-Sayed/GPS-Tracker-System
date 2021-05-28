#ifndef GPS_H
#define GPS_H

#include "Common_Macros.h"
#include "Std_Types.h"
#include "tm4c123gh6pm_registers.h"
#include <math.h>



/*Functions*/
uint8 Return_Latitude_Direction(uint8 * buffer);
uint8 Return_Longitude_Direction(uint8 * buffer);
float64 Return_Latitude_In_Degrees (uint8 * buffer);
float64 Return_Longitude_In_Degrees (uint8 * buffer);
float64 toRadians(const float64 degree);
float64 calculate_Distance_between_2_Coordinates(float64 lat1, float64 long1,float64 lat2,float64 long2);



#endif
