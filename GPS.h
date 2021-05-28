#ifndef GPS_H
#define GPS_H

#include "Common_Macros.h"
#include "Std_Types.h"
#include "tm4c123gh6pm_registers.h"
#include <math.h>


/*Data Types*/
 extern uint8 buffer[];
 extern uint8 lat[];
 extern uint8 lon[];


/*Functions*/
float64 Return_Latitude_In_Degrees (void);
float64 Return_Longitude_In_Degrees (void);
float64 toRadians(const float64 degree);
float64 calculate_Distance_between_2_Coordinates(float64 lat1, float64 long1,float64 lat2,float64 long2);


#endif
