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
#include <AndroidCar.h>
#include <Servo.h>
#include <Wire.h>

Sharp_IR backIR; //instantiate the infra red sensor
const int backIR_pin = A2; //set the pin that the infra red sensor will be providing data to
Sharp_IR sidefrontIR; //instantiate the infra red sensor
const int sidefrontIR_pin = A0; //set the pin that the infra red sensor will be providing data to
Sharp_IR sidebackIR; //instantiate the infra red sensor
const int sidebackIR_pin = A1; //set the pin that the infra red sensor will be providing data to


void setup() {
  backIR.attach(backIR_pin); //attach (initialize) the sensor at the appropriate pin
  sidefrontIR.attach(sidefrontIR_pin);
  sidebackIR.attach(sidebackIR_pin);
  Serial.begin(9600); //start the serial
  Serial.println("Infrared back and side sensors debugging");
}

void loop() {
  delay(100); //run the following every 100 ms
  Serial.print("BACK cm = "); Serial.print(backIR.getDistance()); //print the distance in cm
  Serial.print("; SIDEFRONT cm = "); Serial.print(sidefrontIR.getDistance()); //print the distance in cm
  Serial.print("; SIDEBACK cm = "); Serial.println(sidebackIR.getDistance()); //print the distance in cm

}
