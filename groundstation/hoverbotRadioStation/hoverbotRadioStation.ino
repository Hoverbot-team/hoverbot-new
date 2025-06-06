#include <SPI.h>
#include <LoRa.h>
#define SS 15
#define RST 16
#define DIO0 5

struct raspberry {
  int error;
} __attribute__((__packed__));
struct command {
  int command;
} __attribute__((__packed__));
raspberry received;
command send;
void setup() {
  Serial.begin(9600);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    while (1);
  }
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (LoRa.available()) {
    int packetSize = LoRa.parsePacket();
    if (packetSize == sizeof(raspberry))
      LoRa.readBytes((uint8_t *)&received, sizeof(raspberry));
      Serial.write((uint8_t *)&received, sizeof(raspberry));
  }
  while (Serial.available()) {
    Serial.readBytes((uint8_t *)&send, sizeof(send));
    LoRa.write((uint8_t *)&send, sizeof(send));
  }
}