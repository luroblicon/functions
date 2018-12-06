
#pragma once
#include <Stepper.h>

int PIN1=A0;
int PIN2=A2;
int PIN3=47;
int PIN4=48;
int stepsLeft = 0;

Stepper motor(200,PIN1,PIN2,PIN3,PIN4);
bool resetFlag = false;
bool resetMotor = false;
bool movMotor = false;
int cloudResetFunction(String Command);
int motorSpeed(String stepp);
int disablePin(String command);

void setup(){
  Particle.function("reset",cloudResetFunction);
  Particle.function("Speed",motorSpeed);
  Particle.function("Disable",disablePin);
  motor.setSpeed(255);// value of 50 works
  Serial.begin(9600);
  Serial.println("Start");
 }

void loop() {
    if(resetMotor){
    if(stepsLeft<2500){
      motor.step(1);
      stepsLeft++;
      Serial.println(stepsLeft);
    }
    if(stepsLeft == 2500){
      resetMotor = false;
      stepsLeft = 0;
      Serial.println("Stop");
    }
  }        
 if(resetFlag)
     System.reset();
}//end of main loop()

int cloudResetFunction(String Command){
  resetFlag = true;
  return 1;
}

int motorSpeed(String stepp){
  uint8_t velocidad = stepp.toInt();
  motor.setSpeed(velocidad);
  resetMotor = true;
  return 1;
 }
 
 int disablePin(String command){
      if(command.equals("on")){
        digitalWrite(PIN1,HIGH);
        digitalWrite(PIN2,HIGH);
        digitalWrite(PIN3,HIGH);
        digitalWrite(PIN4,HIGH);
      }

      if(command.equals("off")){
        digitalWrite(PIN1,LOW);
        digitalWrite(PIN2,LOW);
        digitalWrite(PIN3,LOW);
        digitalWrite(PIN4,LOW);
      }
      stepsLeft = 0;
      resetMotor = false;
      return 1;
 }