#include <SoftwareSerial.h>
#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성

//모터 핀번호
#define M1A  10
#define M1B  9
#define M2A  5
#define M2B  3


//왼쪽 초음파 센서 
#define left_TRIG 12
#define left_ECHO 11
//오른쪽 초음파 센서
#define right_TRIG 8
#define right_ECHO 7

int left_duration;
int left_distance;
int right_duration;
int right_distance;
  
void setup(){
  Serial.begin(9600);
  
  servo.attach(6);
  
  //초음파센서들 세팅
  pinMode(left_TRIG, OUTPUT);
  pinMode(left_ECHO, INPUT);
  pinMode(right_TRIG, OUTPUT);
  pinMode(right_ECHO, INPUT);
  
  //모터 세팅
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);

  
  servo.write(90);

}

void loop(){  //초음파센서들을 사용하면서 주행
  left_ultrasonic();
  right_ultrasonic();

  autorun();
} 

void left_ultrasonic(){
        digitalWrite(left_TRIG,LOW);
        digitalWrite(left_ECHO,LOW);
        delay(2);
        digitalWrite(left_TRIG,HIGH);
        delay(10);
        digitalWrite(left_TRIG,LOW);


        left_duration = pulseIn(left_ECHO,HIGH);
        left_distance =  left_duration / 29.0/ 2.0; //340 * duration * 0.001 / 2;
}

void right_ultrasonic(){
        digitalWrite(right_TRIG,LOW);
        digitalWrite(right_ECHO,LOW);
        delay(2);
        digitalWrite(right_TRIG,HIGH);
        delay(10);
        digitalWrite(right_TRIG,LOW);

       
        right_duration = pulseIn(right_ECHO,HIGH);
        right_distance =  right_duration / 29.0/ 2.0; //340 * duration * 0.001 / 2;

}


void Foward(int spd) {
  servo.write(90);
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, spd);
  analogWrite(M2B, 0);
//전진
  }

void Back (int spd){
  servo.write(90);
  analogWrite(M1A, 0);
  analogWrite(M1B, spd);
  analogWrite(M2A, 0);
  analogWrite(M2B, spd);
  delay(300);
//후진
}

void Left(int spd) {
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, spd);
  analogWrite(M2B, 0);
  servo.write(45);
//좌로 회전
}

void Right(int spd) {
  servo.write(135);
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, spd);
  analogWrite(M2B, 0);
//우로 회전
}


void Stop() {
  analogWrite(M1A, 0);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, 0);
//멈춤
}

void random_turning()  //난수를 사용하여 랜덤으로 회전
{
  int Random=random(0,2);
  if(Random==1)
  {
    Right(255);
    delay(150);
  }
  else
  {
    Left(255);
    delay(150);
  }
}

void autorun(){
  if(right_distance<23){
    if(left_distance<23)
    {
      Back(255);
      delay(500);
      random_turning();
      delay(300);
    }
    else{
      Left(255);
      delay(300);
    }
  }
  else if(left_distance<20){
    Right(255);
    delay(300);
  }
  else
  {
    Foward(255);
  }
}
