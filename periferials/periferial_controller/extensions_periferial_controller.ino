#include <SoftwareSerial.h>

bool is_configured = false;

SoftwareSerial module (10,11);
void setup() {
  // put your setup code here, to run once:
  module.begin(115200);
  Serial.begin(115200);
  
}

void loop() {
  if(Serial.available()){
      String input = Serial.readString();
      Serial.write(input)
      if(input[0] == "$" && input[1] == "c"){
        Serial.write("starting the configuration");
      }
  } 
}
