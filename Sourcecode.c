 /*
  * MQ135 Sensor data sended to Firebase using ESP 8266 Microcontroller
  * Name : Manojkumar Saravanan
  * Linked id :www.linkedin.com/in/manojkumarsaravanan2002 
 */


      
#include <WiFi.h>
#include <ESP8266WiFi.h>                 
#include <FirebaseArduino.h>

        /*Firebase  credentials*/
#define FIREBASE_AUTH ""        // Enter your Firebase API
#define FIREBASE_HOST ""        // Enter your Firebase Host link

         /*Wi-Fi credentials*/
const char* ssid = "PASSWORD";  // Enter your WiFi Network's SSID
const char* pass = "12345678";  // Enter your WiFi Network's Password
WiFiClient client;

        /* Define the MQ135 sensor pin and store the data */
#define MQ135_PIN A0  
MQ135 gasSensor = MQ135(A0);

void setup()
{
  Serial.begin(115200);
  Serial.println("Connecting to Wifi");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED)       // checking WI-FI is connected or Not           
  {
    delay(100);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop()
{
  float air_quality = gasSensor.getPPM();                        // Read a value from sensor
  Serial.print("Air Quality: ");                                 // Serial print the Value from sensor
  Serial.print(air_quality);
  Serial.println("  PPM");   
  Serial.println();
  Firebase.pushFloat("/sensor_data/air_quality", air_quality);   // Upload data to Firebase
  delay(5000);                                                   
}
