#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int panPin = 5;   // Pin for pan servo
const int tiltPin = 6; // Pin for tilt servo

typedef struct {
  uint8_t joyx1;
  uint8_t joyy1;
  uint8_t joyx2;
  uint8_t joyy2;
  uint8_t pot;
  uint8_t but1;
  uint8_t but2;
}packet;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(panPin, OUTPUT);
  pinMode(tiltPin, OUTPUT);

  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    while(radio.available()){
      packet packet1;
      radio.read(&packet1, sizeof(packet1));
      if(packet1.but1){
        digitalWrite(2, HIGH);
      }
      else{
        digitalWrite(2,LOW);
      }

      analogWrite(3, packet1.pot);
      writeServoAngle(panPin, packet1.joyx2);
      writeServoAngle(tiltPin, packet1.joyy2);
      
      Serial.println(packet1.joyx2);
      Serial.println(packet1.joyy2);
      Serial.println(packet1.pot);
      Serial.println(packet1.but1);
      Serial.println(packet1.but2);
      Serial.println("         ");
     
      Serial.println("\n");
    }
  }
}


void writeServoAngle(int servoPin, int angle) {
  int pulseWidth = map(angle, 0, 180, 1000, 2000);  // Convert angle to pulse width
  digitalWrite(servoPin, HIGH);  // Set pin high
  delayMicroseconds(pulseWidth);  // Wait for the desired pulse width
  digitalWrite(servoPin, LOW);   // Set pin low
  delay(20);                      // Add a small delay between servo pulses
}
