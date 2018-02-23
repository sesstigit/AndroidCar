#include <AndroidCar.h>
#include <Servo.h>
#include <Wire.h>

const unsigned short ESC_PIN = 9; //the pin the esc will be connected to
const unsigned short SERVO_PIN = 8; //the pin the steering servo will be connected to

Car car(SERVO_PIN, ESC_PIN); //declare the car using the above pins

void setup() {
  car.begin(); //initialize the car
  Serial.begin(9600); //initialize serial input
  Serial.println("Carduino debug");
}

void loop() {
  handleInput();
}

void handleInput() { //handle serial input if there is any
  if (Serial.available()) { //if there's something available in the serial port
    char inChar = (char)Serial.read(); //read it
    switch (inChar) {
      case 'f':
        car.setSpeed(100); //start moving the wheels forward
        car.setAngle(0); //straighten the steering wheel
        Serial.println("f received");
        break;
      case 'b':
        car.setSpeed(-100); //start moving the wheels backward
        car.setAngle(0); //straighten the steering wheel
        Serial.println("b received");
        break;
      case 'l':
        car.setAngle(25); //put the steering wheel left
        Serial.println("l received");
        break;
      case 'r':
        car.setAngle(-25); //put the steering wheel right
        Serial.println("r received");
        break;
      default:
        car.setSpeed(0); //stop the motors
        car.setAngle(0); //straighten the steering wheel
        Serial.println("STOP received");
        break;
    }
  }
}
