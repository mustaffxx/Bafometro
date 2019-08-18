
#include <WiFi.h>
#include "FirebaseESP32.h"
#include <ArduinoJson.h>


#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxx"
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxxxxxxxxx"
const IPAddress IP = IPAddress(192,168,0,12);
const IPAddress GATEWAY = IPAddress(192,168,0,1);
const IPAddress SUBNET = IPAddress(255,255,255,0);
const IPAddress PRIMARY_DNS(8, 8, 8, 8);   
const IPAddress SECONDARY_DNS(8, 8, 4, 4); 

//Define Firebase Data object
FirebaseData firebaseData;
  
StaticJsonDocument<100> testDocument;
char buffer[100];

void setup()
{

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  if (!WiFi.config(IP, GATEWAY, SUBNET, PRIMARY_DNS, SECONDARY_DNS)) 
  {
    Serial.println("STA Failed to configure");
    while(1);
  }
 
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  testDocument["level"] = 25;
  testDocument["situation"] = "drunk";
  testDocument["estimateTime"] = "09h05min";

  serializeJson(testDocument, buffer);

  if (Firebase.pushJSON(firebaseData, "/registry/", buffer)) {

  Serial.println(firebaseData.dataPath());

  Serial.println(firebaseData.pushName());

  Serial.println(firebaseData.dataPath() + "/"+ firebaseData.pushName());

} else {
  Serial.println(firebaseData.errorReason());
}
 
}

void loop()
{
}
