#include <SoftwareSerial.h>
#define ERROR_LED_PIN 3
class extension{
  struct ext_conf {
    bool is_using_pins = false;
    int (*out_data[3])(void); 
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
      if(input.startsWith("$c ")){
        configure(input.substring(3));

      }
  } 
}
void configure(String args){
  args.trim();
  int input_length = args.length();
  bool failed = false;
  if(args[4] == '1'){
    Extension.Config.is_using_pins = true;
  }
  else if (args[4] == '0') {
    Extension.Config.is_using_pins = false;
  }else{
    failed = true;
  }
  if(args.indexOf("gyro") != -1){
    Extension.Config.out_data[0] = gyro;
  }
  if(args.indexOf("distance") != 0){
    Extension.Config.out_data[0] = distance;
  }





  if(failed){
    digitalWrite(ERROR_LED_PIN, 1);
    Serial.print("err");
    module.print("err");
  }
}
//placeholder
int gyro(){

}
//placeholder
int distance(){

}
