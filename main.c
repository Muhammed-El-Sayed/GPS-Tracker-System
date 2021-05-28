
#include"uart.h"

int main()
{
  uint8 string []= {'U','A','R','T','#','\0'};
  UART_Config Configuration1 ={UART_1_TX_PB1,DATA_LENGTH#include "GPS.h"
#include "uart.h"
#include "led.h"

/*Global Data Types*/
uint8 buffer[100];                //carries GPGGA data
uint8 index=0,stringRecieved=0;  //index is that iterates on GPGGA data characters, stringRecieved is a flag to determine if GPGGA data line is recieved or not
float64 Distance =0;            //Total distance between coordinates measured by GPS 



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
        float64 lat_In_Degrees = Return_Latitude_In_Degrees (buffer);
        float64 lon_In_Degrees = Return_Longitude_In_Degrees (buffer);
        
        //Display lat: 128.54 N
        //Display lon: 33.36  W
        
        
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
 
  
}
_8_BITS,ONE_STOP_BIT};
  
  UART_Init(&Configuration1);
  
  while(1)

   //UART_Send_Byte(0xA7, UART_1_TX_PB1);
   UART_sendString(string, UART_1_TX_PB1);

   //UART_Send_Byte(0xEE, UART_1_TX_PB1);
   
  return 0;
}
