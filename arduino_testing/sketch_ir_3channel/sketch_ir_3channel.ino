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

#define LEFT_IR_ARRAY_L A8
#define LEFT_IR_ARRAY_R A9
#define RIGHT_IR_ARRAY_L A10
#define RIGHT_IR_ARRAY_R A11
#define WHITE 1
#define BLACK 0
const unsigned short LINE = WHITE; //define the color of the street lines
unsigned long prevInfraTime = 0;
const unsigned short IR_INTERVAL = 500;

void setup() {
  pinMode(LEFT_IR_ARRAY_L,INPUT);
  pinMode(LEFT_IR_ARRAY_R,INPUT);
  pinMode(RIGHT_IR_ARRAY_L,INPUT);
  pinMode(RIGHT_IR_ARRAY_R,INPUT);

  setupChangeInterrupt(LEFT_IR_ARRAY_L);
  setupChangeInterrupt(LEFT_IR_ARRAY_R);
  setupChangeInterrupt(RIGHT_IR_ARRAY_L);
  setupChangeInterrupt(RIGHT_IR_ARRAY_R);
  Serial.begin(9600);
  Serial.println("Infrared funduino tcrt5000 3-channel IR Test script");
}
void setupChangeInterrupt(unsigned short pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

void loop() {
  delay(1500);
  Serial.println("loop");
}
//the interrupt service routine for pins A8 until A15 on Arduino mega
ISR (PCINT2_vect) {
  //if either of the IR arrays have detected a line
  unsigned short leftArrayL = digitalRead(LEFT_IR_ARRAY_L);
  unsigned short leftArrayR = digitalRead(LEFT_IR_ARRAY_R);
  unsigned short rightArrayL = digitalRead(RIGHT_IR_ARRAY_L);
  unsigned short rightArrayR = digitalRead(RIGHT_IR_ARRAY_R);
  if ((leftArrayL == LINE) || (leftArrayR == LINE) || (rightArrayL == LINE) || (rightArrayR == LINE)){
    unsigned long currentTime = millis();
    //if we have NOT detected the line "lately"
    if (currentTime - prevInfraTime > IR_INTERVAL){
      if ((leftArrayL == LINE) || (leftArrayR == LINE)) Serial.println("lineL..........................."); //send that we have detected the left line
      if ((rightArrayL == LINE) || (rightArrayR == LINE)) Serial.println("..........................lineR"); //send that we have detected the right line
      prevInfraTime = currentTime; //save the time that we transmitted the line detection
    }
  }
}

