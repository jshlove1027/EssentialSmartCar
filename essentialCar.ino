#include <Servo.h>          // Include servo library
Servo servoLeft;         
Servo servoRight;

void setup() {
  // put your setup code here, to run once:
  servoLeft.attach(13);      // Attach left signal to pin 13
  servoRight.attach(12);   
}

void loop() {
  // put your main code here, to run repeatedly:

  maneuver(200,200,1000);
}

//drive car
void maneuver(int speedLeft, int speedRight, int msTime)
{ // speedLeft, speedRight ranges: Backward Linear Stop Linear Forward
  // -200 -100......0......100 200
  servoLeft.writeMicroseconds(1500+speedLeft); // Set Left servo speed
  servoRight.writeMicroseconds(1500-speedRight);//Set right servo speed
  if(msTime==-1){ 
    servoLeft.detach(); // Stop servo signals
    servoRight.detach(); 
  }
  delay(msTime); // Delay for msTime
}
