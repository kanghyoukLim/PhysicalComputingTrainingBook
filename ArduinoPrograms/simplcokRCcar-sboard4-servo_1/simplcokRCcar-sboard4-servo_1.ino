#include <SoftwareSerial.h>
#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성

SoftwareSerial BT(2, 4);
//모터 핀 번호
#define M1A  7
#define M1B  8
#define M2A  3
#define M2B  5
#define M3A  11
#define M3B  10
#define LED_L 7
#define LED_R 8
#define pz 13  //피에조

char character;
int count = 1;

void setup() {
  Serial.begin(9600);

  servo.attach(10);
   
  BT.begin(9600);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M3A, OUTPUT);
  pinMode(M3B, OUTPUT);
  pinMode(LED_L, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(pz, OUTPUT);
//모터4개와 블루투스 세팅

  servo.write(87);
}

void loop() {
  while(BT.available()) {
    character = BT.read(); //블루투스 통신을 통해 메시지를 받아서 변수에 저장

    if(character == 'Y') {
      ledSwitch();
      count = count + 1;
    }

    if(character == 'X') {
      left_LED();
    }

    if(character == 'Z') {
      right_LED();
    }

    if(character =='C') {
      Piezo();
    }
    
    switch(character){  //받은 변수에 따라 동작
      case 'F':
      Forward(255);
      break;

      case 'B':
      Back(255);
      break;

      case 'L':
      Left(255);
      break;

      case 'R':
      Right(255);
      break;

      case 'G':
      F_Left(255);
      break;

      case 'I':
      F_Right(255);
      break;

      case 'J':
      B_Left(255);
      break;

      case 'H':
      B_Right(255);
      break;

      case 'S':
      Stop();
    } 
  }
}

//spd는 속도를 나타냄. 최소 0, 최대 255
void Forward(int spd) { 
  servo.write(87);
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, spd);
//앞으로 전진
  }

void Back (int spd){
  servo.write(87);
  analogWrite(M1A, 0);
  analogWrite(M1B, spd);
  analogWrite(M2A, spd);
  analogWrite(M2B, 0);
//뒤로 후진
}

void F_Right(int spd) {

  servo.write(105);
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, spd);
//우회전(전진하면서)
}

void F_Left(int spd) {
  servo.write(65);
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, spd);
//좌회전(전진하면서)
}


void Left(int spd) {
  servo.write(45);
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, spd);
//좌로 회전
}

void Right(int spd) {
  servo.write(125);
  analogWrite(M1A, spd);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, spd);
//우로 회전
}

void B_Left(int spd){
  servo.write(52);
  analogWrite(M1A, 0);
  analogWrite(M1B, spd);
  analogWrite(M2A, spd);
  analogWrite(M2B, 0);
//좌후진(후진하면서)
}

void B_Right(int spd){
  servo.write(125);
  analogWrite(M1A, 0);
  analogWrite(M1B, spd);
  analogWrite(M2A, spd);
  analogWrite(M2B, 0);
//우후진(후진하면서)
}

void Stop() {
  analogWrite(M1A, 0);
  analogWrite(M1B, 0);
  analogWrite(M2A, 0);
  analogWrite(M2B, 0);
//정지
}

void ledSwitch() {
  if(count % 2 == 1) {
    digitalWrite(LED_L, HIGH);
    digitalWrite(LED_R, HIGH);
  }
  else {
    digitalWrite(LED_L, LOW);
    digitalWrite(LED_R, LOW);
  }
} //LED 온오프

void left_LED() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_L, HIGH);
    delay(200);
    digitalWrite(LED_L, LOW);
    delay(200);
  }
} //좌깜빡이

void right_LED() {
  for(int i = 0; i < 3; i++) {
    digitalWrite(LED_R, HIGH);
    delay(200);
    digitalWrite(LED_R, LOW);
    delay(200);
  }
} //우깜빡이

void Piezo() {
  tone(pz, 440, 250);
} //피에조 클락션
