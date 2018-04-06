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

Gyroscope gyro; //instantiate the gyroscope
unsigned long prevTime = 0;
unsigned long nowTime = 0;
const unsigned short INTERVAL = 1000;

const unsigned short GYRO_SAMPLING = 200; //to be optimized experimentally


void setup() {
  Serial.begin(9600);
  gyro.attach(); //initialize the gyroscope
  delay(1500); //wait to make sure it's ready
  Serial.println("Gyro Start measuring!");
  gyro.begin(GYRO_SAMPLING); //start measuring NOW
}

void loop() {
  nowTime = millis();
  Serial.print("Gyro:prevtime=");
  Serial.print(prevTime);
  Serial.print("Gyro:nowtime=");
  Serial.println(nowTime);
    
  if (nowTime - prevTime > INTERVAL){ //do this every INTERVAL
    Serial.print("About to update...");
    gyro.update();
    Serial.println("... finished gyro update");
    Serial.println(abs(gyro.getAngularDisplacement())); //print angular displacement since last begin()
    prevTime = nowTime;
      }
}

