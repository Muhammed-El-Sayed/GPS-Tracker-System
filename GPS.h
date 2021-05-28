
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
uint16 Return_Latitude_In_Degrees (void);
uint16 Return_Longitude_In_Degrees (void);
sint32 toRadians(const sint32 degree);
sint32 calculate_Distance_between_2_Coordinates(uint16 lat1, uint16 long1,uint16 lat2,uint16 long2);


#endif
