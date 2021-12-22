#define LOW 0
#define HIGH 1
#include <Servo.h> // Servo library 
int arrow =0;
// PID controller
float Kp=25;
float Ki=2;
float Kd=1;
float error=0, P=0, I=0, D=0, PIDvalue=0;
float previousError=0, previousI=0;
const int power = 500;
const int iniMotorPower = 250;
const int adj = 1;
float adjTurn = 8;
Servo leftServo;
Servo rightServo;
void setup() {
leftServo.attach(5);
rightServo.attach(3);
pinMode(11,INPUT);
pinMode(12,INPUT);
pinMode(13,INPUT);
}
void loop() {
// pembacaan sensor pada pin 12 dan 13
int lsensor=digitalRead(11);
int msensor=digitalRead(12);
int rsensor=digitalRead(13);
//logika robot menggunakan prinsip AND
if((lsensor== 0 )&&(msensor== 0 )&&(rsensor== 1 )) error = 2;
else if((lsensor== 0 )&&(msensor== 1 )&&(rsensor== 1 )) error = 1; 
else if((lsensor== 0 )&&(msensor== 1 )&&(rsensor== 0 )) error = 0;
else if((lsensor== 1 )&&(msensor== 1 )&&(rsensor== 0 )) error = -1;
else if((lsensor== 1 )&&(msensor== 0 )&&(rsensor== 0 )) error = -2;
}
void calculatePID()
{
 P = error;
 I = I + error;
 D = error-previousError;
 PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
 previousError = error;
}
void motorPIDcontrol()
{
 int leftMotorSpeed = 1500 - iniMotorPower - PIDvalue;
 int rightMotorSpeed = 1500 + iniMotorPower - PIDvalue;
 
 leftServo.writeMicroseconds(leftMotorSpeed);
 rightServo.writeMicroseconds(rightMotorSpeed);
