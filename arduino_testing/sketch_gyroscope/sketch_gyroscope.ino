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

