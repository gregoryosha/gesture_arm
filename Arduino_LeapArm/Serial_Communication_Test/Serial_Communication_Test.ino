#include <Servo.h>
//Servo set up
Servo myservo;
int angle = 0;
int newAngle = 0;
const int MaxChars = 4;
char strValue[MaxChars + 1];
int index = 0;

int setPoint = 55;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  angle = 90;
}

void loop()
{
  while (!Serial.available())
  {

  }
  // Serial read section
  while (Serial.available())
  {
    char c = Serial.read();
    if (index < MaxChars && isDigit(c)) {
      strValue[index++] = c;
    }
    else {
      strValue[index] = 0;
      angle = atoi(strValue);
      //newAngle = (angle/10) * 20;
      newAngle = angle;
      delay(10);

      if (newAngle > 0)
      {
        Serial.print("Arduino received (int): ");
        Serial.println(angle);
        Serial.print("Arduino received (str): ");
        Serial.println(strValue);
        myservo.write(newAngle);
        delay(10);
      }
      strValue;
      index = 0;

      Serial.print("Arduino sends: ");
      Serial.println('1');
      Serial.print("\n");
      Serial.flush();
    }
  }


  /* if(newAngle > 0 && newAngle < 180){
         if(newAngle < angle){
           for(; angle > newAngle; angle -=1) {
             myservo.write(angle);
           }
         }
         else {
           for(; angle < newAngle; angle +=1){
             myservo.write(angle);
           }
         }
       }
  */


}


