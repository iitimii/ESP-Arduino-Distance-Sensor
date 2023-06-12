#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "ThingSpeak.h"
#include <ArduinoJson.h>
#include <WiFiClient.h>

#define RXp2 16
#define TXp2 17 

const char* ssid = "WiFi Network name here...."; 
const char* password = "enter password here....";

WiFiClient  client;

unsigned long ChannelNumber = 2;
const char * WriteAPIKey = "B7WRSN34R3AJMF91";

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int distance;
int button=15;
int button_state=1;
int post = 0;


void setup(){
  //Initialize serial
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2); //Talk to the Sharp Sensor

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();


  pinMode(button, INPUT_PULLUP);

  //Set wifi mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status()!=WL_CONNECTED){
    Serial.println("");
    lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("Connecting");
    lcd.setCursor(0, 1);
    lcd.print("to WiFi...");
    delay(500);
    }
    
    Serial.println("");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    lcd.clear();
  lcd.setCursor(0, 0);
    lcd.print("IP Address:");
  lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
  delay(2000);

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initialization");
  lcd.setCursor(0, 1);
  lcd.print("Successful");
  delay(1000);
}

void loop(){

  // Connect or reconnect to WiFi if connection is lost

    if(WiFi.status() != WL_CONNECTED){
      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting");
  lcd.setCursor(0, 1);
  lcd.print("to WiFi...");
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(1000);     
      } 
      Serial.println("\nConnected.");

      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected");
  delay(1000);
  lcd.clear();
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button");
  lcd.setCursor(0, 1);
   lcd.print("to measure");


  // //Get distance from Arduino
  while(button_state!=0){
  button_state = digitalRead(button);}

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");

  distance = request();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  
  Serial.print("\n Distance from ESP: ");
  Serial.println(distance);

  // Write to ThingSpeak
   lcd.setCursor(0, 1);
  lcd.print("Uploading...");
  int x = ThingSpeak.writeField(ChannelNumber, 1, distance, WriteAPIKey);

   if(x == 200){
      Serial.println("Channel update successful.");
      lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Post Successful");
  post = 1;
  delay(1000);

    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Post error");
  delay(1000);

  while (post==0){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Retrying...");

  int x = ThingSpeak.writeField(ChannelNumber, 1, distance, WriteAPIKey); //Get response code from the request to Thingsspeak
  
  if(x == 200){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Post Successful");
  post = 1;
  delay(1000);
  }
  }

  }

  button_state = 1;
  post = 0;
// }
}


int request(){
  DynamicJsonDocument doc(1024);

  distance = 0;

  //Sending Request
  doc["type"] = "request";
  serializeJson(doc, Serial2);

  // Reading Request
  bool messageReady = false;
  String message = "";

  while(messageReady == false){
    if (Serial2.available()){
      message = Serial2.readString();
      messageReady = true;
    }
  }
// Deserialize JSON formatted message
  DeserializationError error = deserializeJson(doc, message);
   if (error){
     Serial.print(F("deserializeJson() failed: "));
     Serial.println(error.c_str());
     return 0;
   }

   distance = doc["distance"];

  return distance;
}
