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
        if (abs(setAngle_c - angle_c) > 5){
          if((setAngle_c - angle_c) > 0){
            setAngle_c -= 4;
          }
          else {
            setAngle_c += 4;
          }
        }
        Serial.print("Claw: ");
        Serial.println(setAngle_c);
        servoC.write(setAngle_c);
      }
      if (angle_e > 0) {
        if (abs(setAngle_e - angle_e) > 3){
          if((setAngle_e - angle_e) > 0){
            setAngle_e -= 4;
          }
          else {
            setAngle_e += 4;
          }
        }
        Serial.print("Elbow: ");
        Serial.println(setAngle_e);
        servoE.write(setAngle_e);
      }
      if (angle_s > 0) {
        if (abs(setAngle_s - angle_s) > 3){
          if((setAngle_s - angle_s) > 0){
            setAngle_s -= 4;
          }
          else {
            setAngle_s += 4;
          }
        }
        Serial.print("Shoulder: ");
        Serial.println(setAngle_s);
        servoS.write(setAngle_s);
      }
      if (angle_b > 0) {
        if (abs(setAngle_b - angle_b) > 3){
          if((setAngle_b - angle_b) > 0){
            setAngle_b -= 4;
          }
          else {
            setAngle_b += 4;
          }
        }
        Serial.print("Base: ");
        Serial.println(setAngle_b);
        servoB.write(setAngle_b);
      }
      Serial.flush();

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


