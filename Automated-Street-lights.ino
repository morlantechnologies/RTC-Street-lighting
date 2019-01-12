/*
 * mornah hermann anglania
 * morlantech.com/anglania
 */

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define block1_lamps 9
#define block2_lamps 10
#define block3_lamps 11
#define block4_lamps 6

#define PIR1 4
#define PIR2 3
#define PIR3 2
#define PIR4 5

#define LDR0 A3
#define LDR1 A2
#define LDR2 A1
#define LDR3 A0
#define LDR4 7

void setup () {

  Serial.begin(9600);
  
  pinMode(block1_lamps, OUTPUT);
  pinMode(block2_lamps, OUTPUT);
  pinMode(block3_lamps, OUTPUT);
  pinMode(block4_lamps, OUTPUT);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.println();
    void light_action();
    delay(3000);
}

void light_action(){
  const uint8_t block_lamps[4] = { 6, 9, 10, 11 };
  DateTime now = rtc.now();
  for (uint8_t i = 0; i < 4; i++){
  while (now.hour()== 12 && now.minute()== 0 && now.second()== 0){
    if (digitalRead(LDR0) == HIGH){
    digitalWrite(block_lamps[i], HIGH);

    if (now.hour()== 12 && now.minute()== 4 && now.second()== 0){
      analogWrite(block_lamps[i], 127.5);
      }
      else {
        if (digitalRead(LDR1) == HIGH || digitalRead(PIR0) == HIGH){
          analogWrite(block1_lamps, 255);
          Serial.println("block 1 on");
          }
        else if (digitalRead(LDR2) == HIGH || digitalRead(PIR1) == HIGH){
          analogWrite(block2_lamps, 255);
          Serial.println("block 2 on");
          }
        else if (digitalRead(LDR3) == HIGH || digitalRead(PIR2) == HIGH){
          analogWrite(block3_lamps, 255);
          Serial.println("block 3 on");
          }
        else if (digitalRead(LDR4) == HIGH || digitalRead(PIR3) == HIGH){
          analogWrite(block4_lamps, 255);
          Serial.println("block 4 on");
          }
        }

      }  
    }
  while (now.hour()== 12 && now.minute()== 5 && now.second()== 0){
    digitalWrite(block_lamps[i], LOW);
    }
  }
  }
