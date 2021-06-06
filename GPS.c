 /******************************************************************************
 *
 * Module: Application _Gps tracker
 *
 * File Name: GPS.c
 *
 * Description: Source file for GPS.
 *
 ******************************************************************************/
#include "GPS.h"

/************************************************************************************
* Service Name: Return_Latitude_Direction
* Parameters (in): buffer
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to return N (North ) or E(East) in the buffer
************************************************************************************/
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


/************************************************************************************
* Service Name: Return_Latitude_Direction
* Parameters (in): buffer
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to return N (North ) or E(East) in the buffer
************************************************************************************/
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


/************************************************************************************
* Service Name: toRadians
* Parameters (in): degree 
* Parameters (inout): None
* Parameters (out): readings in radian	
* Return value: None
* Description: Function to convert reading from degree to radian
************************************************************************************/
float64 toRadians(const float64 degree)
{
	float64 one_deg = (float64)((3.14) / 180);
	return (one_deg * degree);
}


/************************************************************************************
* Service Name: calculate_Distance_between_2_Coordinates
* Parameters (in): lat1, long1, lat2, long2 
* Parameters (inout): None
* Parameters (out): Distance
* Return value: None
* Description: Functionm to calculate distance between 2 readings
************************************************************************************/
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


/************************************************************************************
* Service Name: Update_Latitude_In_String
* Parameters (in):buffer
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Update latitude array with the reading before conversion
************************************************************************************/
 void Update_Latitude_In_String (uint8 * buffer)
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
      if(buffer[i+1] == ' ')
      {
      }
      else if(buffer[i+1] != ',')
      {
        lat[l] = buffer[i+1]; //Degrees Minutes
        ++l;
      }
      else
        break;
    }
  }
}


/************************************************************************************
* Service Name: Update_Longitude_In_String
* Parameters (in):buffer
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Update Longtiude array with the reading before conversion
************************************************************************************/
void Update_Longitude_In_String (uint8 * buffer) 
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
      
      if(buffer[i+1] == ' ')
      {
      }
      else if(buffer[i+1] != ',')
      {
        lon[l] = buffer[i+1]; //Degrees Minutes
        ++l;
      }
      else
        break;

    }

  }

}


/************************************************************************************
* Service Name: Return_Latitude_or_Langitude_In_Degrees
* Parameters (in):Lat_or_Long_String
* Parameters (inout): None
* Parameters (out): Reading in degree
* Return value: None
* Description: Function to convert reading to deciaml form (degrees)
************************************************************************************/
float64 Return_Latitude_or_Langitude_In_Degrees (uint8 * Lat_or_Long_String)//Latitude or Longitude String DDDMM.MMMMM
{
  

	uint8 counter = 0;
	while(Lat_or_Long_String[counter] != '.')
	{
		counter++;

	}

   //Latitude
	float64 latitude_in_degrees =0;
	if(counter == 4) //2 numbers for degrees & 2 numbers for minutes
	latitude_in_degrees = (float64)((( (Lat_or_Long_String[0]-'0')*10)+((Lat_or_Long_String[1]-'0')))+ (((Lat_or_Long_String[2]-'0')*10) +((Lat_or_Long_String[3]-'0')))/60.0);

	if(counter == 5) //3 numbers for degrees & 2 numbers for minutes
	latitude_in_degrees = (float64)((((Lat_or_Long_String[0]-'0')*100)+((Lat_or_Long_String[1]-'0')*10)+ ((Lat_or_Long_String[2]-'0')))+ (((Lat_or_Long_String[3]-'0')*10) +((Lat_or_Long_String[4]-'0')))/60.0);

	uint8 counter2 =counter;


	while(Lat_or_Long_String[counter2] != '\0')
	{
		counter2++;

	}


	uint8 After_Decimal_Size = counter2-counter -1;
	float64 Min_After_Decimal=0;

        for(uint8 i=(counter+1),j=0; j< (counter2-counter-1);++j,++i)
        {
        	   After_Decimal_Size  = After_Decimal_Size -1;
        	   Min_After_Decimal+= (Lat_or_Long_String[i]-'0')*(pow(10,After_Decimal_Size));

        }

        Min_After_Decimal/=pow(10,counter2-counter-1);
	    Min_After_Decimal/=60.0;


        latitude_in_degrees+=Min_After_Decimal;

        return latitude_in_degrees;

}

