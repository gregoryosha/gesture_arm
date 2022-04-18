#include <Servo.h>

Servo myservo;
char serialData;
int pin=10;

void setup(){
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
  myservo.attach(10);
}

void loop() {
  if (Serial.available() > 0){
    serialData = Serial.read();
    Serial.println(serialData);

    if(serialData == '1'){
      myservo.write(80);
      Serial.println("ON");
    }
    else if (serialData == '0'){
      myservo.write(10);
      Serial.println("OFF");
    }
  }
}

