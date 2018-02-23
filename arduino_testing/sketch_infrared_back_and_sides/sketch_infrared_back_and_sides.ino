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
