#include <SoftwareSerial.h>
#define ERROR_LED_PIN 3
class extension{
  struct ext_conf {
    bool is_using_pins = false;
  };
  public:
    ext_conf Config;
};


bool is_configured = false;
String input = ""; 
SoftwareSerial module (10,11);
extension Extension;
void setup() {
  // put your setup code here, to run once:
  module.begin(115200);
  Serial.begin(115200);
  
  
}

void loop() {
  if(Serial.available() > 0){
      input = Serial.readString();
      Serial.print(input);
      if(input.startsWith("$c ")){
        Serial.print("starting the configuration");
        configure(input.substring(3));

      }
  } 
}
void configure(String args){
  bool failed = false;
  if(args.length() <= 3){
    failed = true;
  }
  else{
    if(args[4] = '1'){
      Extension.Config.is_using_pins = true;
      Serial.println("pins configured");
    }
  }




  if(failed){
    digitalWrite(ERROR_LED_PIN, 1);
  }
}
