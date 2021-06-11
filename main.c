 /******************************************************************************
 *
 * Module: Application _Gps tracker
 *
 * File Name: main.c
 *
 * Description: Source file for Application Tasks.
 *
 ******************************************************************************/

#include "GPS.h"
#include "uart.h"
#include "led.h"
#include "systickTimer.h"
#include "port.h"
#include "dio.h"
#include "lcd.h"
#include "eeprom.h"


/*Global Data Types*/
uint8 buffer[100];                //carries GPGGA data
uint8 index=0,stringRecieved=0;  //index is that iterates on GPGGA data characters, stringRecieved is a flag to determine if GPGGA data line is recieved or not
float64 Distance =0;            //Total distance between coordinates measured by GPS 

//Current Point recieved by GPS
uint8 lat[13] ={'\0'};
uint8 lon[13] ={'\0'};

//No of words in eeprom
  uint32 wordCount =0;
  

/*Application Handler on recieving UART2 a byte*/
void Latitude_Longitude_String_Recieved (void) //fills buffer by the recieved GPGGA data & sets stringRecieved flag after recieving GPGGA full info.
{
    uint8 GPGGA[]={'$','G','P','G','G','A'}; 
    
    uint8 data_Recieved_Character =0;
    data_Recieved_Character = *(volatile uint32 *)((volatile uint8 *)UART2_BASE_ADDRESS + UARTDR_OFFSET);
     
     buffer[index]=data_Recieved_Character;
     index++;
     if(index<7)
     {
           if(buffer[index-1] != GPGGA[index-1])  // $GPGGA
                index=0;
     }
     if(index>=50)
     {
       stringRecieved=1;
     }
  
}


/*Application Handler on recieving UART3 a command from PC*/
void PC_To_Uart_Read_EEPROM(void)  // c6 Recieve Pin  ,  c5 Send Pin  Pc to UART
{
     uint8 data_Recieved_Character =0;
    data_Recieved_Character = *(volatile uint32 *)((volatile uint8 *)UART3_BASE_ADDRESS + UARTDR_OFFSET);  
    
   if( data_Recieved_Character == 'U')
   {
    //LED_setOn();
   // UART_sendString("32.4567,22.44567",UART_4_TX);
    int count=0;  
    REG num2;
    
    EEPROM_read(&wordCount,508,4);
    
  while(count < wordCount)
 {
   EEPROM_read(& num2.word_32_bit, count*4,4);
   UART_Send_Byte(num2.character_8_bit.d,UART_4_TX);
   UART_Send_Byte(num2.character_8_bit.c,UART_4_TX);
   UART_Send_Byte(num2.character_8_bit.b,UART_4_TX);
   UART_Send_Byte(num2.character_8_bit.a,UART_4_TX);
   count++;
 }
  
   }

      
}
 
   //   Application Code
int main()
{  


  
  Port_Init(&Port_Configuration);
  Dio_Init(&Dio_Configuration);
  LCD_init();

  EEPROM_Init();

 
  UART_Config Configuration3 ={UART_4_TX,DATA_LENGTH_8_BITS,ONE_STOP_BIT}; 
  UART_Init(&Configuration3);
  UART_Config Configuration4 ={UART_5_TX,DATA_LENGTH_8_BITS,ONE_STOP_BIT};
  UART_Init(&Configuration4);
  UART_Config Configuration2 ={UART_3_RX,DATA_LENGTH_8_BITS,ONE_STOP_BIT};
  UART_Init(&Configuration2);
  //Enable_UART_3_RX_INTERRUPT();
  //UART_3_RX_setCallBack(PC_To_Uart_Read_EEPROM);
  
  
  
  UART_Config Configuration ={UART_2_RX,DATA_LENGTH_8_BITS,ONE_STOP_BIT};
  UART_Init(&Configuration);
  Enable_UART_2_RX_INTERRUPT();
    
  
  UART_2_RX_setCallBack(Latitude_Longitude_String_Recieved);
  
  //These local data are used to store the previous latitude & longitude
  uint8 flag =0;
  float64 lat1,lon1;    //eeprom
  float64 lat11,lon11;   //wifi
      
    
  while(1)
  {
    
    
    if(stringRecieved == 1) //GPGGA data is recieved
    {
      Disable_Interrupts();
      index =0,stringRecieved=0; 
      
      //Extract latitude & longitude Info.
      uint8 lat_Dir = Return_Latitude_Direction(buffer);
      uint8 lon_Dir = Return_Longitude_Direction(buffer);
      //Update strings
      Update_Latitude_In_String(buffer);
      Update_Longitude_In_String(buffer);
      
      //lat , lon are latitude & longitude strings Before Conversion
      // Double lat_In_Degrees , lon_In_Degrees are latitude & longitude in degrees After Conversion
      float64 lat_In_Degrees = Return_Latitude_or_Langitude_In_Degrees (lat); 
      float64 lon_In_Degrees = Return_Latitude_or_Langitude_In_Degrees (lon);
      
      // String lat_In_Degrees_Str , lon_In_Degrees_Str are latitude & longitude in string After Conversion
      char lat_In_Degrees_Str[16] = {'\0'};
      char lon_In_Degrees_Str[16] = {'\0'};
      sprintf((char*)lat_In_Degrees_Str,"%0.5lf", lat_In_Degrees);
      sprintf((char*)lon_In_Degrees_Str,"%0.5lf", lon_In_Degrees);
      
      
      
      //Display lat: 128.54 N  -->lat_In_Degrees lat_Dir
      LCD_clearScreen();
     // LCD_displayString("latt.:");
      LCD_doubleToString(lat_In_Degrees);
       LCD_displayCharacter(' ');
       LCD_displayCharacter(lat_Dir);
       LCD_displayCharacter(',');
       
      //Display lon: 33.36  W  -->lon_In_Degrees lon_Dir
	 
    // LCD_displayString("long.:");
       LCD_doubleToString(lon_In_Degrees);
       LCD_displayCharacter(' ');
       LCD_displayCharacter(lon_Dir);
	LCD_goToRowColoumn(0,0);
	  
     //Concatenating the GPS Point 'latitude,longitude '
      uint8 str_info[30]={'\0'};

	uint8 * ptr_char  ;
	uint8 * ptr_char2  ;
	ptr_char = lat_In_Degrees_Str; 
	uint8 i=0;
  
	while( *ptr_char != '\0')
	{
	 
	    str_info[i] =lat_In_Degrees_Str[i];
	    ptr_char++;
	    i++;
	}
	str_info[i]=',';
	i++;
	ptr_char2 = lon_In_Degrees_Str;
	uint8 j=0;
	while( *ptr_char2 != '\0')
	{
	 
	  str_info[i] =lon_In_Degrees_Str[j];
	     ptr_char2++;
	  j++;
	  i++;
	}    
        str_info[i]=' ';
	     

        
      

       //calculating Distance FVC
      //Initializing lat1 with the first latitude & lon1 with the first longitude
      if(flag == 0)
      { 
	flag =1;
	lat1 =lat_In_Degrees;
	lon1 =lon_In_Degrees;
        
        lat11 = lat_In_Degrees;
        lon11 = lon_In_Degrees;

          wordCount = EEPROM_writeBytes(str_info,wordCount);
        
          //send to wifi  --> 'lat,lon ' string after conversion
    	 // D7 will send to wifi
         
 	  UART_sendString(str_info,UART_5_TX);
      }
	 //Calibration
      
      
       //write in eeprom
      if(calculate_Distance_between_2_Coordinates(lat1,lon1,lat_In_Degrees,lon_In_Degrees) >= 0.0005 )
      { 
        wordCount = EEPROM_writeBytes(str_info,wordCount);
        
      
       //lat_In_Degrees is the new latitude (lat2) & lon_In_Degrees is the new longitude (lon2)
      //lon_In_Degrees if( (lat1 != lat_In_Degrees)  || (lon1 != lon_In_Degrees) )
       Distance += calculate_Distance_between_2_Coordinates(lat1,lon1,lat_In_Degrees,lon_In_Degrees);
       
        //Storing previous latitude & longitude
       lat1=lat_In_Degrees;
       lon1=lon_In_Degrees;
       
      }
      
      //write in wifi
      if(calculate_Distance_between_2_Coordinates(lat11,lon11,lat_In_Degrees,lon_In_Degrees) >= 0.005 )
      { 
       
        
          //send to wifi  --> 'lat,lon ' string after conversion
    	 // D7 will send to wifi
         
 	  UART_sendString(str_info,UART_5_TX);
       
        //Storing previous latitude & longitude
       lat11=lat_In_Degrees;
       lon11=lon_In_Degrees;
       
      }
     

       //Display Distance
       LCD_goToRowColoumn(1,0);
       LCD_displayString("Dis: ");

      LCD_doubleToString(Distance);
      LCD_displayString(" Km");
       if(Distance >=0.1) //0.1 km = 100 m
       {
	 //Turn led on Using PORT & DIO
	 LED_setOn();
       EEPROM_write( &wordCount, 508, 4);
	 break;
       }
	SysTick_Delay_ms(250);
       Enable_Interrupts();
       


    }
      
 }

   
//MC will stuck in this loop after distance reach 100m so that MC will not receive 
while(1)
{  if( UART_Recieve_Byte(UART_3_RX) == 'U')
   {
    //LED_setOn();
   // UART_sendString("32.4567,22.44567",UART_4_TX);
    int count=0;  
    REG num2;
    
    EEPROM_read(&wordCount,508,4);
    
  while(count < wordCount)
 {
   EEPROM_read(& num2.word_32_bit, count*4,4);
   UART_Send_Byte(num2.character_8_bit.d,UART_4_TX);
   UART_Send_Byte(num2.character_8_bit.c,UART_4_TX);
   UART_Send_Byte(num2.character_8_bit.b,UART_4_TX);
   UART_Send_Byte(num2.character_8_bit.a,UART_4_TX);
   count++;
 }
  
   }
}





}
