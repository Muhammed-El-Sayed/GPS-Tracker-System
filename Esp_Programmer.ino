#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
const char* ssid = "OPPO F11";    // name of your wifi network!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const char* password = "11111111";     // wifi pasword !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const char* host = "script.google.com";
const int httpsPort = 443;

WiFiClientSecure client;

const char* fingerprint = "46 B2 C3 44 9C 59 09 8B 01 B6 F8 BD 4C FB 00 74 91 2F EF F6";
String GAS_ID = "AKfycbwTvAesl9aZfMJg0QiMfdrCoXzB5Dz93vPKgny0I2tAoOT7Ph5Zmcy0TTNSRab67wV7gg";   // Replace by your GAS service id   

 //*...........................................................................*/
String string_longitude;
String string_latitude; 
int flag = 1;             // flag to check if thr reading has benn reached the server or not
char inChar;

int latitude_flag=0;
int longitude_flag=0;
 //*...........................................................................*/

 
void setup() 
{
Serial.begin(9600);   
WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   }
}


void loop() 
{
  if (Serial.available() > 0 && flag == 1)
  {
   inChar  = Serial.read();
   flag=0;
      if( inChar == ',')
      {
       //float_longitude = string_longitude.toFloat();
       // long longitude = (long) (float_longitude * 10000 ) ; 
        //longitude =  longitude / 100000;
        latitude_flag=1;
        longitude_flag=1;
        flag=1;
       }
      else if( latitude_flag==1 && !isWhitespace(inChar) )
      {
        string_latitude += inChar;
        flag=1;
      }
      else if(isWhitespace( inChar ))
      {
       //float_latitude = string_latitude.toFloat();
       //long latitude = (long) (float_longitude * 10000 ) ;         //long is 4 bytes
    //  latitude =  latitude / 100000;
          flag = 1;
        latitude_flag=0;
        delay(6000);
         if(longitude_flag==1 && latitude_flag==0)
         {
          sendData(string_longitude,string_latitude );
          flag=1;     
          string_longitude = "";
          string_latitude = "";
         } 
      }
      else
      {
         string_longitude += inChar ; 
         flag=1;
      }
  }
}


void sendData(String longtiude, String latitude )
{
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
  Serial.println("certificate matches");
  } else {
  Serial.println("certificate doesn't match");
  }
    String str_long =  longtiude; 
   String str_lat =  latitude; 
  String url = "/macros/s/" + GAS_ID + "/exec?field1=" + str_long + "&field2=" + str_lat;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
  String line = client.readStringUntil('\n');
  if (line == "\r") {
    Serial.println("headers received");
    break;
  }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
  Serial.println("esp8266/Arduino CI successfull!");
  } else {
  Serial.println("esp8266/Arduino CI has failed");
  }

} 
