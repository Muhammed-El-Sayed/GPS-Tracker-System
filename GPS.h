#ifndef GPS_H
#define GPS_H

#include "Common_Macros.h"
#include "Std_Types.h"
#include "tm4c123gh6pm_registers.h"
#include <math.h>

//Current Point recieved by GPS
extern uint8 lat[13];
extern uint8 lon[13];

/*Functions*/
float64 Return_Latitude_or_Langitude_In_Degrees (uint8 * Lat_or_Long_String);
uint8 Return_Latitude_Direction(uint8 * buffer);
uint8 Return_Longitude_Direction(uint8 * buffer);
float64 toRadians(const float64 degree);
float64 calculate_Distance_between_2_Coordinates(float64 lat1, float64 long1,float64 lat2,float64 long2);
void Update_Latitude_In_String (uint8 * buffer); 
void Update_Longitude_In_String (uint8 * buffer);



#endif
