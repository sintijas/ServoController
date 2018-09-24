

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
 Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 
#define SERVOMINGRIPPER 200 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAXGRIPPER 500 // this is the 'maximum' pulse length count (out of 4096)
#define SERVOMINRIGHT 290 //movement to the back
#define SERVOMAXRIGHT 400
#define SERVOMINLEFT 560 //movement to the back
#define SERVOMAXLEFT 680
#define SERVOMINBASE 300 //movement to the back
#define SERVOMAXBASE 450

uint8_t servonum = 0;
uint8_t directionFlag = 0;

void setup() {
  Serial.begin(9600);

  pwm.begin();
  
  pwm.setPWMFreq(70);  // Analog servos run at ~60 Hz updates

  delay(10);
}


void loop() {
  // Drive each servo one at a time
  
  Serial.println(servonum);
  //Gripper on PIN0
  if (servonum == 0) {
    for (uint16_t pulselen = SERVOMINGRIPPER; pulselen < SERVOMAXGRIPPER; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(2);
    }
    for (uint16_t pulselen = SERVOMAXGRIPPER; pulselen > SERVOMINGRIPPER; pulselen--) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(2);
    }
    servonum=1;
  }
  //RIGHT SERVO ON PIN 1
  else if (servonum == 1 && directionFlag == 0) {
    for (uint16_t pulselen = SERVOMINRIGHT; pulselen < SERVOMAXRIGHT; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(6);
    }
    directionFlag=1;
  }
  else if (servonum == 1 && directionFlag == 1) {
    for (uint16_t pulselen = SERVOMAXRIGHT; pulselen > SERVOMINRIGHT; pulselen--) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(6);
    }
    directionFlag=0;
    servonum=2;
  }
  //LEFT SERVO ON PIN 2
  else if (servonum == 2 && directionFlag == 0) {
    for (uint16_t pulselen = SERVOMINLEFT; pulselen < SERVOMAXLEFT; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(5);
    }
    directionFlag=1;
  }
  else if (servonum == 2 && directionFlag == 1) {
    for (uint16_t pulselen = SERVOMAXLEFT; pulselen > SERVOMINLEFT; pulselen--) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(5);
    }
    directionFlag=0;
    servonum=3;
  }
  //BASE SERVO ON PIN 3
  else if (servonum == 3 && directionFlag == 0) {
    for (uint16_t pulselen = SERVOMINBASE; pulselen < SERVOMAXBASE; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(6);
    }
    directionFlag=1;
  }
  else if (servonum == 3 && directionFlag == 1) {
    for (uint16_t pulselen = SERVOMAXBASE; pulselen > SERVOMINBASE; pulselen--) {
      pwm.setPWM(servonum, 0, pulselen);
      delay(6);
    }
    directionFlag=0;
    servonum=0;
  }

  delay(3000);
}
