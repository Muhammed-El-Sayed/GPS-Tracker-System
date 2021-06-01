#include <ESP8266WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "WE_EA58F4";   // your network SSID (name) 
char pass[] = "jbv10284";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 1402622;
const char * myWriteAPIKey = "8V94ZE82Y1QHS8NG";

int lang = -1;
int lat = -1; 
int distance = -1 ;
int flag = 0;
int count = -1 ;
int value  =0 ; 
void setup() {
  Serial.begin(9600);  // Initialize serial

  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    //Serial.print("Attempting to connect to SSID: ");
    //Serial.println("WE_EA58F4");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      //Serial.print(".");
      delay(5000);     
    } 
   // Serial.println("\nConnected.");
  }

  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.

/********************************************************************************************************/

      
  if(count == 0 )
  {
    lang = value ;
    int x = ThingSpeak.writeField(myChannelNumber, 1, lang, myWriteAPIKey);
    if(x == 200){
      flag = 1;
     count = (count + 1 ) %  2; 
      }
  }
  else if(count == 1 )
  {
    lat = value ;
    int x = ThingSpeak.writeField(myChannelNumber, 2, lat, myWriteAPIKey);
    if(x == 200){
    flag = 1;
    count = (count + 1 ) %  2;
        }
  }
  else
  {
    ThingSpeak.setField(1, lang);
    ThingSpeak.setField(2, lat);
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200)
     {
        count = (count + 1 ) %  2;
       flag = 1;
     }
  }


/******************************************************************************************/

  // change the value
  if (Serial.available() > 0 && flag == 1)
  {
      value  = Serial.read();
      flag = 0;
  }
/*  if(number > 99){
    number = 0;
  } -1  */
  
  delay(20000); // Wait 20 seconds to update the channel again
}
