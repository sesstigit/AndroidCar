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
/*
*	Car.cpp
*/
#include "AndroidCar.h"
/* --- CAR --- */

const unsigned short Car::DEFAULT_SERVO_PIN = 8;
const unsigned short Car::DEFAULT_ESC_PIN = 9;

const int IDLE_SPEED = 1500;
const int MAX_FRONT_SPEED = 2000; //can go to 1800, was 1590
const int MAX_BACK_SPEED = 1000; //can go to 1200, was 1200
const int STRAIGHT_WHEELS = 90;  //was 97
const int MAX_RIGHT_DEGREES = 40;  //was 122
const int MAX_LEFT_DEGREES = 140;  //was 72

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
  if ((finalSpeed < 0) && (initialSpeed >= 0)) {
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
