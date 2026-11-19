#include <Servo.h>          // Include servo library

//초음파센서 핀
#define trig 4
#define echo 5

Servo servoLeft;         
Servo servoRight;

int speed = 200; // 자동차 기본 속도
int headlight=4;
int lightPin=0;
int light;

void setup() {
  // put your setup code here, to run once:
  servoLeft.attach(13);      // Attach left signal to pin 13
  servoRight.attach(12);

  //초음파센서 핀모드 설정
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  //헤드라이트
  pinMode(headlight,OUTPUT);   
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, inches, cm;
  light=analogRead(lightPin); //조도

  digitalWrite(trig, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH, 30000);  //돌아오는 시간 측정, 타임아웃 시간
  cm = microsecondsToCentimeters(duration);
  
  delay(100); //short delay for faster response to light.

  int targetSpeed = 200; //거리에 따른 속도

  //앞차와 거리에 따른 속도
  if(cm>=35 || duration == 0){
    targetSpeed == 200;
  }
  else if(cm>15&&cm<35){ 
    targetSpeed = 100;
  }
  else{
    targetSpeed = 0;
  }

  // 현재 speed를 targetSpeed에 맞춰 10씩 조절
  if (speed < targetSpeed) {
    speed = min(speed + 10, targetSpeed);
  } else if (speed > targetSpeed) {
    speed = max(speed - 10, targetSpeed);
  }
  maneuver(speed, speed, 100);

  //조도가 낮을시 헤드라이트 on
  if(light<750){
    analogWrite(headlight,analogRead(lightPin)/4);
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