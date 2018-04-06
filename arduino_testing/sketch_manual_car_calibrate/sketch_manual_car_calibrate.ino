/**
*    This file is part of AndroidCar.
*
*    AndroidCar is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    AndroidCar is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with AndroidCar.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <Servo.h>
#include <Wire.h>

// This is a self-contained test of manual mode, without requiring the AndroidCar library.  Hence all the calibration parameters
// are controllable from this sketch, the main ones being that speed is 1500+-500, and steering is 90 degrees +- 50 degrees.

//Note: RC cars have a non-intuitive mode of operating.  The accelerator is a trigger lever.  Releasing the trigger sets the accelerator to zero.
// But to decelerate (brake) you need to push the trigger outwards once.  Only after the trigger returns to neutral position can you then push the 
// trigger outwards again to put the car into reverse.

// This makes the manual mode here a bit more complicated.  Forward and then backward won't necessarily result in going into reverse.
// Hence add some special code to enable reverse.

const unsigned short ESC_PIN = 9; //the pin the esc will be connected to.  This can override the DEFAULT_ESC_PIN in the Car class.
const unsigned short SERVO_PIN = 8; //the pin the steering servo will be connected to. This can override the DEFAULT_SERVO_PIN in the Car class.



const int IDLE_SPEED = 1500;
const int MAX_FRONT_SPEED = 2000; //can go to 1800, was 1590
const int MAX_BACK_SPEED = 1000; //can go to 1200, was 1200
const int STRAIGHT_WHEELS = 90;  //was 97
const int MAX_RIGHT_DEGREES = 40;  //was 122
const int MAX_LEFT_DEGREES = 140;  //was 72

class Car {
  public:
    Car(unsigned short steeringWheelPin = DEFAULT_SERVO_PIN, unsigned short escPin = DEFAULT_ESC_PIN);
    void begin();
    void setSpeed(int speed);
    void setAngle(int degrees);
    int getSpeed();
    int getAngle();
    int modSpeed(int modAmount);
    int modAngle(int modAmount);
  private:
    void setSteeringWheelPin(unsigned short steeringWheelPin);
    void setESCPin(unsigned short escPin);
    unsigned short _steeringWheelPin, _escPin;
    Servo motor, steeringWheel;
    int _speed, _angle;
    static const unsigned short DEFAULT_SERVO_PIN = 8;
    static const unsigned short DEFAULT_ESC_PIN = 9;
};

Car::Car(unsigned short steeringWheelPin, unsigned short escPin){
  setSteeringWheelPin(steeringWheelPin);
  setESCPin(escPin);
}

void Car::begin(){
  motor.attach(_escPin);
  steeringWheel.attach(_steeringWheelPin);
  setSpeed(0);
  setAngle(0);
}

void Car::setSteeringWheelPin(unsigned short steeringWheelPin){
  _steeringWheelPin = steeringWheelPin;
}

void Car::setESCPin(unsigned short escPin){
  _escPin = escPin;
}

void Car::setSpeed(int speed){
  _speed = constrain(IDLE_SPEED + speed, MAX_BACK_SPEED, MAX_FRONT_SPEED);
  motor.write(_speed);
}

void Car::setAngle(int degrees){
  _angle = constrain(STRAIGHT_WHEELS + degrees, MAX_RIGHT_DEGREES, MAX_LEFT_DEGREES);
  steeringWheel.write(_angle);
}

int Car::getSpeed(){
  return _speed - IDLE_SPEED;
}

int Car::getAngle(){
  return _angle - STRAIGHT_WHEELS;
}

int Car::modSpeed(int modAmount){
  int initialSpeed = getSpeed();
  setSpeed(initialSpeed + modAmount);
  int finalSpeed = getSpeed();
  // Check whether we have passed from positive to negative speed.
  if ((finalSpeed < 0) && initialSpeed >= 0)) {
    // now in braking mode.  Change to reverse mode by setting speed back to zero, and then to the negative speed.
    setSpeed(0);
    setSpeed(finalSpeed);
  }
}

int Car::modAngle(int modAmount){
  int newDegrees = getAngle() + modAmount;
  setAngle(newDegrees);
  return getAngle();
}

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
  int rSpeed = 0; //speed returned by call to car method
  int rAngle = 0; //angle returned by call to car method
  if (Serial.available()) { //if there's something available in the serial port
    char inChar = (char)Serial.read(); //read it
    switch (inChar) {
      case 'f':
        rSpeed = car.modSpeed(10); //start moving the wheels forward
        car.setAngle(0); //straighten the steering wheel
        Serial.print("f received: ");
        break;
      case 'b':
        //car.setSpeed(-100); //start moving the wheels backward
        rSpeed = car.modSpeed(-10); //start moving the wheels backward
        car.setAngle(0); //straighten the steering wheel
        Serial.print("b received: ");
        break;
      case 'l':
        rAngle = car.modAngle(5); //put the steering wheel left
        Serial.print("l received: ");
        break;
      case 'r':
        rAngle = car.modAngle(-5); //put the steering wheel right
        Serial.print("r received: ");
        break;
      // Following lines are commented out because they are dangerous.  Sets the car to highest speed forward or reverse.
      //case 'm':
      //  // set minimum speed
      //  car.setSpeed(MAX_BACK_SPEED - IDLE_SPEED);
      //  Serial.print("m received: ");
      //  break;
      //case 'M':
      //  // set maximum speed
      //  car.setSpeed(MAX_FRONT_SPEED - IDLE_SPEED);
      //  Serial.print("M received: ");
      //  break;
      default:
        car.setSpeed(0); //stop the motors
        car.setAngle(0); //straighten the steering wheel
        Serial.print("STOP received: ");
        break;
    }
    rSpeed = car.getSpeed();
    rAngle = car.getAngle();
     Serial.print(rSpeed); Serial.print("; "); Serial.println(rAngle);
  }
}
