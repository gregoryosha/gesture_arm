#include <Servo.h>
//Servo set up
Servo servoC;
Servo servoE;
Servo servoS;
Servo servoB;
int angle_c = 0;
int angle_e = 0;
int angle_s = 0;
int angle_b = 0;

int setAngle_c = 90;
int setAngle_e = 45;
int setAngle_s = 90;
int setAngle_b = 90;


int timeCount = 0;

const int MaxChars = 13;
char strValue[MaxChars + 1];
int index = 0;

int count = 0;

int setPoint = 55;

void setup() {
  Serial.begin(9600);
  servoC.attach(10);
  servoE.attach(9);
  servoS.attach(6);
  servoB.attach(5);

  //reset mode:
  servoC.write(110);
  servoE.write(45);
  servoS.write(90);
  servoB.write(90);

}

void loop()
{
  while (!Serial.available())
  {
  }
  // Serial read section
  while (Serial.available())
  {
    char r = Serial.read();
    if (index < MaxChars && isDigit(r)) {
      strValue[index] = r;
      index++;
    }
    else if (r == 'c') {
      strValue[index] = 0;
      angle_c = atoi(strValue);
      strValue;
      index = 0;
    }
    else if (r == 'e') {
      strValue[index] = 0;
      angle_e = atoi(strValue);
      strValue;
      index = 0;
    }
    else if (r == 's') {
      strValue[index] = 0;
      angle_s = atoi(strValue);
      strValue;
      index = 0;
    }

    else {
      strValue[index] = 0;
      angle_b = atoi(strValue);

      if (angle_c > 0) {
        Serial.print("Claw: ");
        Serial.println(angle_c);
        servoC.write(angle_c);
      }
      if (angle_e > 0) {
        Serial.print("Elbow: ");
        Serial.println(angle_e);
        servoE.write(angle_e);
      }
      if (angle_s > 0) {
        Serial.print("Shoulder: ");
        Serial.println(angle_s);
        servoS.write(angle_s);
      }
      if (angle_b > 0) {
        Serial.print("Base: ");
        Serial.println(angle_b);
        servoB.write(angle_b);
      }
      //Serial.flush();

      strValue;
      index = 0;

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


