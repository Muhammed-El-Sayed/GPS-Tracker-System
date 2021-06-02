#include "GPS.h"
#include "uart.h"
#include "led.h"
#include "systickTimer.h"
#include "port.h"
#include "dio.h"
#include "lcd.h"
/*Global Data Types*/
uint8 buffer[100];                //carries GPGGA data
uint8 index=0,stringRecieved=0;  //index is that iterates on GPGGA data characters, stringRecieved is a flag to determine if GPGGA data line is recieved or not
float64 Distance =0;            //Total distance between coordinates measured by GPS 

//Current Point recieved by GPS
uint8 lat[13] ={'\0'};
uint8 lon[13] ={'\0'};


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

void led_on(void)
{
     uint8 data_Recieved_Character =0;
     data_Recieved_Character = *(volatile uint32 *)((volatile uint8 *)UART2_BASE_ADDRESS + UARTDR_OFFSET);
     
    if(data_Recieved_Character == 'A')
       GPIO_PORTF_DATA_REG  |= 1<<1;
}


int main()
{  
  Port_Init(&Port_Configuration);
  Dio_Init(&Dio_Configuration);
  LCD_init();
   //   Application Code
    UART_Config Configuration ={UART_2_RX,DATA_LENGTH_8_BITS,ONE_STOP_BIT};
    UART_Init(&Configuration);
    Enable_UART_2_RX_INTERRUPT();
    Led_Red_Init();
  
    UART_2_RX_setCallBack(Latitude_Longitude_String_Recieved);
    
    //These local data are used to store the previous latitude & longitude
    uint8 flag =0;
    float64 lat1,lon1;
      
    while(1)
    {
      if(stringRecieved == 1) //GPGGA data is recieved
      {
        Disable_Interrupts();
        index =0,stringRecieved=0; 
        
        //Extract latitude & longitude Info.
        uint8 lat_Dir = Return_Latitude_Direction(buffer);
        uint8 lon_Dir = Return_Longitude_Direction(buffer);
        Update_Latitude_In_String(buffer);
        Update_Longitude_In_String(buffer);
        
        //lat , lon are latitude & longitude strings
        //lat_In_Degrees , lon_In_Degrees are latitude & longitude in degrees
        float64 lat_In_Degrees = Return_Latitude_or_Langitude_In_Degrees (lat);
        float64 lon_In_Degrees = Return_Latitude_or_Langitude_In_Degrees (lon);
        
        //Display lat: 128.54 N  -->lat_In_Degrees lat_Dir
        LCD_displayString("latt.:");
        LCD_doubleToString(lat_In_Degrees);
         LCD_displayCharacter(' ');
         LCD_displayCharacter(lat_Dir);
           LCD_goToRowColoumn(1,0);
        //Display lon: 33.36  W  -->lon_In_Degrees lon_Dir
           
           LCD_displayString("long.:");
             LCD_doubleToString(lon_In_Degrees);
             LCD_displayCharacter(' ');
             LCD_displayCharacter(lon_Dir);
             LCD_clearScreen();
              LCD_goToRowColoumn(0,0);
               
         
        
        
        //send to wifi  --> lat & lon strings
        //write in eeprom 
        
         //calculating Distance 
        //Initializing lat1 with the first latitude & lon1 with the first longitude
        if(flag == 0)
        { 
          flag =1;
          lat1 =lat_In_Degrees;
          lon1 =lon_In_Degrees;
        }
        //lat_In_Degrees is the new latitude (lat2) & lon_In_Degrees is the new longitude (lon2)
         Distance += calculate_Distance_between_2_Coordinates(lat1,lon1,lat_In_Degrees,lon_In_Degrees);
         //Storing previous latitude & longitude
         lat1=lat_In_Degrees;
         lon1=lon_In_Degrees;
         
         //Display Distance
         
         if(Distance >=100)
         {
           //Turn led on Using PORT & DIO
         }
        
        Enable_Interrupts();
      }
        
    }
 
  /*
   
  
    UART_Config Configuration ={UART_2_RX,DATA_LENGTH_8_BITS,ONE_STOP_BIT};
    UART_Init(&Configuration);
    Enable_UART_2_RX_INTERRUPT();
    Led_Red_Init();
    UART_2_RX_setCallBack(led_on);
   
    
    
    
      
    while(1)
    {
         
  
      
    }
  
  */
  
  
  
}
