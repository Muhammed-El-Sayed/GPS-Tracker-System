
#include "GPS.h"

uint16 Return_Latitude_In_Degrees (void) //returns latitude in degrees (including converting minutes to degrees) & fill lat[] array with degrees & minutes
{
  uint8 counter=0,l=0;
  for(uint8 i=0;i<100;++i)
  {
    if(buffer[i]==',')
    {
      counter++;
    }
    if(counter == 2)
    {
      if(buffer[i+1] != '.')
      {
        lat[l] = buffer[i+1]; //Degrees Minutes
        ++l; 
      } 
      else
        break;
      
    }
    
  }
  uint16 latitude_in_degrees =0;
  if(l == 4) //2 numbers for degrees & 2 numbers for minutes 
  latitude_in_degrees = (( (lat[0]-'0')*10)+((lat[1]-'0')))+ (((lat[2]-'0')*10) +((lat[3]-'0')))/60;
    
  if(l == 5) //3 numbers for degrees & 2 numbers for minutes   
  latitude_in_degrees = (((lat[0]-'0')*100)+((lat[1]-'0')*10)+ ((lat[2]-'0')))+ (((lat[3]-'0')*10) +((lat[4]-'0')))/60;
  
  return latitude_in_degrees;
}

uint16 Return_Longitude_In_Degrees (void) //returns longitude in degrees (including converting minutes to degrees) & fill lon[] array with degrees & minutes
{
  uint8 counter=0,l=0;
  for(uint8 i=0;i<100;++i)
  {
    if(buffer[i]==',')
    {
      counter++;
    }
    if(counter == 4)
    {
      if(buffer[i+1] != '.')
      {
        lon[l] = buffer[i+1]; //Degrees Minutes
        ++l; 
      } 
      else
        break;
      
    }
    
  }
  uint16 longitude_in_degrees =0;
  if(l == 4) //2 numbers for degrees & 2 numbers for minutes 
  longitude_in_degrees = (( (lon[0]-'0')*10)+((lon[1]-'0')))+ (((lon[2]-'0')*10) +((lon[3]-'0')))/60;
    
  if(l == 5) //3 numbers for degrees & 2 numbers for minutes   
  longitude_in_degrees = (((lon[0]-'0')*100)+((lon[1]-'0')*10)+ ((lon[2]-'0')))+ (((lon[3]-'0')*10) +((lon[4]-'0')))/60;
  
  return longitude_in_degrees;
}

sint32 toRadians(const sint32 degree)  
{   
	sint32 one_deg = (sint32)((3.14) / 180);  
	return (one_deg * degree);  
}  
 
sint32 calculate_Distance_between_2_Coordinates(uint16 lat1, uint16 long1,uint16 lat2,uint16 long2) //latitude & longitude in degrees  
{  
	// Convert the latitudes and longitudes from degree to radians.  
	lat1 = toRadians(lat1);  
	long1 = toRadians(long1);  
	lat2 = toRadians(lat2);  
	long2 = toRadians(long2);  
	 
	// Haversine Formula  
	sint32 dlong = long2 - long1;  
	sint32 dlat = lat2 - lat1;  
 
	sint32 ans = (sint32)(pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2));  
	ans = (sint32)(2 * asin(sqrt(ans)));  
        
	//Radius of Earth in Kilometers, R = 6371  
	// Use R = 3956 for miles  
	sint32 R = 6371;  
	 
	// Calculate the result  
	ans = ans * R;  
 
	return ans;  
}  
