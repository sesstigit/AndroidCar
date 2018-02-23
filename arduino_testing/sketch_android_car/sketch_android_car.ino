/* The running arduino sketch on the Android Autonomous Vehicle by Team Pegasus
*
* Description: The vehicle is based on an Arduino Mega, that is connected to various sensors
* (infrared, ultrasound, speed encoder, gyroscope and 9DOF IMU) and receives driving instructions
* from an Android phone, via Bluetooth, that is attached on the top of the vehicle. The vehicle
* can follow street lanes, park and overtake obstacles, using image processing on the Android phone.
*
*  Author: Dimitris Platis
*  Note: modifications have been made for STIGIT car, e.g. Razorboard and Odometer not yet included
*        All changes labelled STIGIT
*/
#include <AndroidCar.h>
#include <Servo.h>
#include <Netstrings.h>
#include <Wire.h>
#include "CarVariables.h"

Car car(SERVO_PIN, ESC_PIN); //steering, esc
//STIGIT//Sonar frontSonar, frontRightSonar, rearSonar;
Sharp_IR sideFrontIR, sideRearIR, rearIR;
//STIGIT//Odometer encoder;
//STIGIT//Gyroscope gyro;
//STIGIT//Razorboard razor;

const unsigned short COM_FREQ = 100;
unsigned long previousTransmission = 0;

const unsigned short OVERRIDE_TIMEOUT = 3000;
unsigned long overrideRelease = 0;
boolean overrideTriggered = false;

unsigned long prevCheck = 0;
const unsigned short LEDrefreshRate = 200;

const unsigned short GYRO_SAMPLING = 90; //to be optimized experimentally

const unsigned short LINE = WHITE; //define the color of the street lines
unsigned long prevInfraTime = 0;
const unsigned short IR_INTERVAL = 500;

void setup() {
  car.begin();
  //STIGIT//frontSonar.attach(FRONT_US_TRIG_PIN, FRONT_US_ECHO_PIN);
  //STIGIT//frontRightSonar.attach(FRONT_RIGHT_US_TRIG_PIN, FRONT_RIGHT_US_ECHO_PIN);
  //STIGIT//rearSonar.attach(REAR_US_TRIG_PIN, REAR_US_ECHO_PIN);
  sideFrontIR.attach(SIDE_FRONT_IR_PIN);
  sideRearIR.attach(SIDE_REAR_IR_PIN);
  rearIR.attach(REAR_IR_PIN);
  //STIGIT//encoder.attach(ENCODER_DIG_PIN);
  //STIGIT//encoder.begin(); //start counting
  //STIGIT//gyro.attach();
  //STIGIT//gyro.begin(GYRO_SAMPLING); //start measuring
  //STIGIT//razor.attach(&Serial3);
  pinMode(BT_STATE_PIN, INPUT);  //STIGIT added
  pinMode(LEFT_IR_ARRAY_L,INPUT); //STIGIT added
  pinMode(LEFT_IR_ARRAY_R,INPUT); //STIGIT added
  pinMode(RIGHT_IR_ARRAY_L,INPUT); //STIGIT added
  pinMode(RIGHT_IR_ARRAY_R,INPUT); //STIGIT added
  setupChangeInterrupt(LEFT_IR_ARRAY_L); //STIGIT added
  setupChangeInterrupt(LEFT_IR_ARRAY_R); //STIGIT added
  setupChangeInterrupt(RIGHT_IR_ARRAY_L); //STIGIT added
  setupChangeInterrupt(RIGHT_IR_ARRAY_R); //STIGIT added
  //STIGIT//pinMode(LEFT_IR_ARRAY,INPUT);
  //STIGIT//pinMode(RIGHT_IR_ARRAY,INPUT);
  //STIGIT//setupChangeInterrupt(LEFT_IR_ARRAY);
  //STIGIT//setupChangeInterrupt(RIGHT_IR_ARRAY);
  Serial2.begin(9600);
  Serial2.setTimeout(200);
}

void loop() {
  //STIGIT//handleOverride(); //look for an override signal and if it exists disable bluetooth input
  handleInput(); //look for a serial input if override is not triggered and act accordingly
  //STIGIT//updateLEDs(); //update LEDs depending on the mode we are currently in
  //STIGIT//gyro.update(); //integrate gyroscope's readings
  transmitSensorData(); //fetch and transmit the sensor data in the correct intervals if bluetooth is connected
}

void updateLEDs() {
  if (millis() - prevCheck > LEDrefreshRate) {
    if (overrideTriggered) { //if override is triggered
      Serial3.print('m');
    } else {  //if override is NOT triggered
      if (!car.getSpeed()) { //if car is immobilized
        Serial3.print('s');
      } else { //if car is running
        if (car.getAngle() > 0) { //if car turns right
          Serial3.print('r');
        } else if (car.getAngle() < 0) { //if car turns left
          Serial3.print('l');
        } else { //if car goes straight
          Serial3.print('i');
        }
      }
    }
    prevCheck = millis();
  }
}

void handleOverride() {
  if (int override = pulseIn(OVERRIDE_SIGNAL_PIN, HIGH, MAX_WAVELENGTH)) {
    overrideRelease = millis() + OVERRIDE_TIMEOUT; //time to re-enable Serial communication
    overrideTriggered = true;
  }
}

void transmitSensorData() {
  if (bluetoothConnected && (millis() - previousTransmission > COM_FREQ)) {
    String out;
    //STIGIT//out = "US1-";
    //STIGIT//out += frontSonar.getDistance();
    //STIGIT//Serial2.println(encodedNetstring(out));
    //STIGIT//out = "US2-";
    //STIGIT//out += frontRightSonar.getDistance();
    //STIGIT//Serial2.println(encodedNetstring(out));
    //STIGIT//out = "US3-";
    //STIGIT//out += rearSonar.getDistance();
    //STIGIT//Serial2.println(encodedNetstring(out));
    out = "IR1-";
    out += sideFrontIR.getDistance();
    Serial2.println(encodedNetstring(out));
    out = "IR2-";
    out += sideRearIR.getDistance();
    Serial2.println(encodedNetstring(out));
    out = "IR3-";
    out += rearIR.getDistance();
    Serial2.println(encodedNetstring(out));
    //STIGIT//out = "EN-";
    //STIGIT//out += encoder.getDistance();
    //STIGIT//Serial2.println(encodedNetstring(out));
    //STIGIT//out = "HE-";
    //STIGIT//out += abs(gyro.getAngularDisplacement());
    //STIGIT//Serial2.println(encodedNetstring(out));
    //STIGIT//out = "RZR-";
    //STIGIT//out += razor.getLatestHeading();
    //STIGIT//Serial2.println(encodedNetstring(out));
    previousTransmission = millis();
  }

}

void handleInput() {
  if (!overrideTriggered || (millis() > overrideRelease)) {
    if (overrideTriggered) { //this state is only entered when the OVERRIDE_TIMEOUT is over
      overrideTriggered = false;
      //after going out of the override mode, set speed and steering to initial position
      car.setSpeed(0);
      car.setAngle(0);
    }
    if (Serial2.available()) {
      String input = decodedNetstring(Serial2.readStringUntil(','));
      if (input.startsWith("m")) {
        int throttle = input.substring(1).toInt();
        car.setSpeed(throttle);
      } else if (input.startsWith("t")) {
        int degrees = input.substring(1).toInt();
        car.setAngle(degrees);
      } else if (input.startsWith("h")) {
        //STIGIT//gyro.begin(GYRO_SAMPLING);
      } else {
        Serial2.println(encodedNetstring("Bad input"));
      }
    }
  } else { //override mode
    unsigned short servoFreq = pulseIn(OVERRIDE_SERVO_PIN, HIGH, MAX_STEERING_WAVELENGTH);
    unsigned short throttleFreq = pulseIn(OVERRIDE_THROTTLE_PIN, HIGH, MAX_STEERING_WAVELENGTH);
    //handle override servo
    if (servoFreq) { //if you get 0, ignore it as it is between the pulses
      short diff = servoFreq - NEUTRAL_FREQUENCY;
      if (abs(diff) < OVERRIDE_FREQ_TOLERANCE) {
        car.setAngle(0);
      } else {
        if (servoFreq > NEUTRAL_FREQUENCY) {
          car.setAngle(OVERRIDE_STEER_RIGHT);
        } else {
          car.setAngle(OVERRIDE_STEER_LEFT);
        }
      }
    }
    //handle override throttle
    if (throttleFreq) {
      short diff = throttleFreq - NEUTRAL_FREQUENCY;
      if (abs(diff) < OVERRIDE_FREQ_TOLERANCE) {
        car.setSpeed(0);
      } else {
        if (throttleFreq > NEUTRAL_FREQUENCY) {
          car.setSpeed(OVERRIDE_FORWARD_SPEED);
        } else {
          car.setSpeed(OVERRIDE_BACKWARD_SPEED);
        }
      }
    }
    while (Serial2.read() != -1); //discard incoming data while on override
  }
}

void setupChangeInterrupt(unsigned short pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

//the interrupt service routine for pins A8 until A15 on Arduino mega
ISR (PCINT2_vect) {
  //if either of the IR arrays have detected a line
  //STIGIT//unsigned short leftArray = digitalRead(LEFT_IR_ARRAY);
  //STIGIT//unsigned short rightArray = digitalRead(RIGHT_IR_ARRAY);
  unsigned short leftArrayL = digitalRead(LEFT_IR_ARRAY_L); //STIGIT added
  unsigned short leftArrayR = digitalRead(LEFT_IR_ARRAY_R); //STIGIT added
  unsigned short rightArrayL = digitalRead(RIGHT_IR_ARRAY_L); //STIGIT added
  unsigned short rightArrayR = digitalRead(RIGHT_IR_ARRAY_R); //STIGIT added
  if ((leftArrayL == LINE) || (leftArrayR == LINE) || (rightArrayL == LINE) || (rightArrayR == LINE)){  //STIGIT added
  //STIGIT//if ((leftArray == LINE) || (rightArray == LINE)){
    unsigned long currentTime = millis();
    //if we have NOT detected the line "lately"
    if (currentTime - prevInfraTime > IR_INTERVAL){
      //STIGIT//if (leftArray == LINE) Serial2.println(encodedNetstring("lineL")); //send that we have detected the left line
      if ((leftArrayL == LINE) || (leftArrayR == LINE)) Serial2.println(encodedNetstring("lineL")); //STIGIT added
      //STIGIT//if (rightArray == LINE) Serial2.println(encodedNetstring("lineR")); //send that we have detected the right line
      if ((rightArrayL == LINE) || (rightArrayR == LINE)) Serial2.println(encodedNetstring("lineR")); //STIGIT added
      prevInfraTime = currentTime; //save the time that we transmitted the line detection
    }
  }
}
