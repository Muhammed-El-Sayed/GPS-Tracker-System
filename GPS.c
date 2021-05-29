#include "GPS.h"

uint8 Return_Latitude_Direction(uint8 * buffer)
{
	  uint8 counter=0;
	  for(uint8 i=0;i<100;++i)
	  {
	    if(buffer[i]==',')
	    {
	      counter++;
	    }
	    if(counter == 3)
	    {

            return buffer[i+1];
	    }

	  }
          return '!'; //# is returned when Dir. is not found

}

uint8 Return_Longitude_Direction(uint8 * buffer)
{
	  uint8 counter=0;
	  for(uint8 i=0;i<100;++i)
	  {
	    if(buffer[i]==',')
	    {
	      counter++;
	    }
	    if(counter == 5)
	    {

            return buffer[i+1];
	    }

	  }

          return '!'; //# is returned when Dir. is not found
}

 float64 Return_Latitude_In_Degrees (uint8 * buffer) //returns latitude in degrees (including converting minutes to degrees) & fill lat[] array with degrees & minutes
{
  uint8 counter=0,l=0;
  uint8 lat[13];
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
  float64 latitude_in_degrees =0;
  if(l == 4) //2 numbers for degrees & 2 numbers for minutes
  latitude_in_degrees = (float64)((( (lat[0]-'0')*10)+((lat[1]-'0')))+ (((lat[2]-'0')*10) +((lat[3]-'0')))/60.0);

  if(l == 5) //3 numbers for degrees & 2 numbers for minutes
  latitude_in_degrees = (float64)((((lat[0]-'0')*100)+((lat[1]-'0')*10)+ ((lat[2]-'0')))+ (((lat[3]-'0')*10) +((lat[4]-'0')))/60.0);

  return latitude_in_degrees;
}

float64 Return_Longitude_In_Degrees (uint8 * buffer) //returns longitude in degrees (including converting minutes to degrees) & fill lon[] array with degrees & minutes
{
  uint8 counter=0,l=0;
  uint8 lon[13];
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
  float64 longitude_in_degrees =0;
  if(l == 4) //2 numbers for degrees & 2 numbers for minutes
  longitude_in_degrees = (float64)((( (lon[0]-'0')*10)+((lon[1]-'0')))+ (((lon[2]-'0')*10) +((lon[3]-'0')))/60.0);

  if(l == 5) //3 numbers for degrees & 2 numbers for minutes
  longitude_in_degrees = (float64)((((lon[0]-'0')*100)+((lon[1]-'0')*10)+ ((lon[2]-'0')))+ (((lon[3]-'0')*10) +((lon[4]-'0')))/60.0);

  return longitude_in_degrees;
}

float64 toRadians(const float64 degree)
{
	float64 one_deg = (float64)((3.14) / 180);
	return (one_deg * degree);
}

float64 calculate_Distance_between_2_Coordinates(float64 lat1, float64 long1,float64 lat2,float64 long2) //latitude & longitude in degrees
{
	// Convert the latitudes and longitudes from degree to radians.
	lat1 = toRadians(lat1);
	long1 = toRadians(long1);
	lat2 = toRadians(lat2);
	long2 = toRadians(long2);

	// Haversine Formula
	float64 dlong = long2 - long1;
	float64 dlat = lat2 - lat1;

	float64 ans = (float64)(pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2));
	ans = (float64)(2 * asin(sqrt(ans)));

	//Radius of Earth in Kilometers, R = 6371
	// Use R = 3956 for miles
	float64 R = 6371;

	// Calculate the result
	ans = ans * R;

	return ans;
}
