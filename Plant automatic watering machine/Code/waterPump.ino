// 12C Communication Wire libary
#include <Wire.h>
// RTC libary
#include <RTClib.h>

// RTC Declare
RTC_DS1307 RTC;

// A motor
int A_1A = 11;
int A_2A = 12;

// B motor
int B_1A = 9;
int B_2A = 10;

// Start Time
int startHour;
int startMin;
int startSec;

// PlayTime
int firstPlayTime;
int secondPlayTime;
int thirdPlayTime;

void setup() {
  // Debug Serial Number
  Serial.begin(9600);
  
  Wire.begin();
  
  // RTC(Real Time Clock) module
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));

  // PinMode Set
  pinMode(A_1A, OUTPUT);
  pinMode(A_2A, OUTPUT);

  pinMode(B_1A, OUTPUT);
  pinMode(B_2A, OUTPUT);
  
  // Start Time set
  DateTime startTime = RTC.now();
  startHour = startTime.hour();
  startMin = startTime.minute();
  startSec = startTime.second();

  // Play Time set
  firstPlayTime = startHour + 8;
  if (firstPlayTime > 24){
    firstPlayTime = firstPlayTime - 24;
  }
  secondPlayTime = firstPlayTime + 8;
  if (secondPlayTime > 24){
    secondPlayTime = secondPlayTime - 24;
  }
  thirdPlayTime = secondPlayTime + 8;
  if (thirdPlayTime > 24){
    thirdPlayTime = thirdPlayTime - 24;
  }
}

void loop() {
  // RTC Set
  DateTime now = RTC.now();

  if ((firstPlayTime == now.hour()) and (now.minute() == 0) and (now.second() >= 0 and now.second() < 15)){
    pump();
    }
  else if((secondPlayTime == now.hour()) and (now.minute() == 0) and (now.second() >= 0 and now.second() < 15)){
    pump();
    }
  else if((thirdPlayTime == now.hour()) and (now.minute() == 0) and (now.second() >= 0 and now.second() < 15)){
    pump();
    } else{
      stop();
    }
    
  // Time Serial  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.hour(), DEC);
  Serial.print('/');
  Serial.print(now.minute(), DEC);
  Serial.print('/');
  Serial.print(now.second(), DEC);
  Serial.print('\n');

  // 1sec delay
  delay(1000);
}

void pump(){
  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;

  digitalWrite(A_1A, inPin1);
  digitalWrite(A_2A, inPin2);
}

void stop(){
  digitalWrite(A_1A, LOW);
  digitalWrite(A_2A, LOW);
}
