// TRANSMITTER CODE

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

typedef struct {
  uint8_t joyx1;
  uint8_t joyy1;
  uint8_t joyx2;
  uint8_t joyy2;
  uint8_t pot;
  uint8_t but1;
  uint8_t but2;
}packet;

RF24 radio(10, 9); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  packet packet1 = 
  {
    (uint8_t) map(analogRead(A0), 0, 1023, 0, 180),
    (uint8_t) map(analogRead(A1), 0, 1023, 0, 180),
    (uint8_t) map(analogRead(A2), 0, 1023, 0, 180),
    (uint8_t) map(analogRead(A3), 0, 1023, 0, 180),
    (uint8_t) map(analogRead(A4), 0, 1023, 0, 255),
    (uint8_t) digitalRead(2),
    (uint8_t) digitalRead(6)
  };
  radio.write(&packet1, sizeof(packet1));
  delay(10);
}
