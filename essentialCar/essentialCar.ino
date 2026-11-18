#include <Servo.h>          // Include servo library

//초음파센서 핀
#define trig 4
#define echo 5

Servo servoLeft;         
Servo servoRight;

void setup() {
  // put your setup code here, to run once:
  servoLeft.attach(13);      // Attach left signal to pin 13
  servoRight.attach(12);

  //초음파센서 핀모드 설정
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);   
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, inches, cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  //돌아오는 시간 측정
  cm = microsecondsToCentimeters(duration);

  //앞차와 거리에 따른 속도
  if(cm>=35){
    maneuver(200,200,1000);
  }
  else if(cm>15&&cd<35){
    maneuver(100,100,1000);
  }
  else{
    maneuver(0,0,1000);
  }
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


//초음파센서로 앞 차와 거리 계산
long microsecondsToCentimeters(long microseconds)
{
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    
    return microseconds / 29 / 2;
}

