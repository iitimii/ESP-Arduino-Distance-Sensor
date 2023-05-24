#include <SharpIR.h>
#include <ArduinoJson.h>

#define IR A0
#define model 1080

String message = "";
bool messageReady = false;

int dist;

//Create sensor object
SharpIR sharpir(IR, model);

void setup() {
  Serial.begin(115200);
}

void loop() {

   response();

}


void response(){
while(Serial.available()){
     message = Serial.readString();
     messageReady = true;
   }

   if (messageReady){
     DynamicJsonDocument doc(1024);
     DeserializationError error = deserializeJson(doc, message);
   
   if (error){
     Serial.print(F("deserializeJson() failed: "));
     Serial.println(error.c_str());
     messageReady = false;
     return;
   }

   if (doc["type"] == "request"){
     doc["type"] = "response";

     doc["distance"] = sharpir.distance();

     serializeJson(doc, Serial);
   }

   messageReady = false;
}
}
