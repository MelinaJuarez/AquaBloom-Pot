#include "ServoMotor.h"
#include <Servo.h> 

Servo servo;

boolean state;

ServoMotor::ServoMotor(){}

void ServoMotor::StartServo() {
  servo.attach(SERVO);
  servo.write(0);  // Posición inicial del servo (0 grados)
  state = false;
}

bool ServoMotor::check_state(){
  return state;
}

void ServoMotor::open() {
  servo.write(180);
  delay(15); // 15ms para alcanzar la posición
  state = true;
}

void ServoMotor::close(){
  servo.write(0);
  delay(15); // 15ms para alcanzar la posición
  state = false;
}


