#include <Wire.h>
//--- Gyro Register Addresses
#define Gyro_gX0 0x28  
#define Gyro_gX1 0x29
#define Gyro_gY0 0x2A
#define Gyro_gY1 0x2B
#define Gyro_gZ0 0x2C  
#define Gyro_gZ1 0x2D
int Gyro = 0x69; //Device address in which is also included the 8th bit for selecting the mode, read in this case.
int gX0, gX1, gX_out;
int gY0, gY1, gY_out;
int gZ0, gZ1, gZ_out;
float Xg,Yg,Zg;
float angleX,angleY,angleZ,angleXc,angleYc,angleZc;
unsigned long start, finished, elapsed;
float dt=0.015;
void setup()
{
  Wire.begin();                
  Serial.begin(9600);    
  delay(100);
  
  Wire.beginTransmission(Gyro);
  Wire.write(0x20); // CTRL_REG1 - Power Mode
  Wire.write(15);   // Normal mode: 15d - 00001111b   
  Wire.endTransmission();
  
  Wire.beginTransmission(Gyro);
  Wire.write(0x23); // CTRL_REG4 - Sensitivity, Scale Selection
  Wire.write(48);   // 2000dps: 48d - 00110000b
  Wire.endTransmission();
}
void loop()
{
  start=millis(); 
  //---- X-Axis
  Wire.beginTransmission(Gyro); // transmit to device
  Wire.write(Gyro_gX0);
  Wire.endTransmission();
  Wire.requestFrom(Gyro,1); 
  if(Wire.available()<=1)   
  {
    gX0 = Wire.read();
  }
  Wire.beginTransmission(Gyro); // transmit to device
  Wire.write(Gyro_gX1);
  Wire.endTransmission();
  Wire.requestFrom(Gyro,1); 
  if(Wire.available()<=1)   
  {
    gX1 = Wire.read();
  }
  //---- Y-Axis
  Wire.beginTransmission(Gyro); // transmit to device
  Wire.write(Gyro_gY0);
  Wire.endTransmission();
  Wire.requestFrom(Gyro,1); 
  if(Wire.available()<=1)   
  {
    gY0 = Wire.read();
  }
  Wire.beginTransmission(Gyro); // transmit to device
  Wire.write(Gyro_gY1);
  Wire.endTransmission();
  Wire.requestFrom(Gyro,1); 
  if(Wire.available()<=1)   
  {
    gY1 = Wire.read();
  }
  
  //---- Z-Axis
  Wire.beginTransmission(Gyro); // transmit to device
  Wire.write(Gyro_gZ0);
  Wire.endTransmission();
  Wire.requestFrom(Gyro,1); 
  if(Wire.available()<=1)   
  {
    gZ0 = Wire.read();
  }
  Wire.beginTransmission(Gyro); // transmit to device
  Wire.write(Gyro_gZ1);
  Wire.endTransmission();
  Wire.requestFrom(Gyro,1); 
  if(Wire.available()<=1)   
  {
    gZ1 = Wire.read();
  }
  
  //---------- X - Axis
  
  // Raw Data
  gX1=gX1<<8;
  gX_out =gX0+gX1;
  
  // From the datasheet: 70 mdps/digit
  Xg=gX_out*0.07; // Angular rate
  // Angular_rate * dt = angle
  angleXc = Xg*dt;
  angleX = angleX + angleXc;
  //---------- Y - Axis
  gY1=gY1<<8;
  gY_out =gY0+gY1;
  Yg=gY_out*0.07;
  angleYc = Yg*dt;
  angleY = angleY + angleYc;
  
  //---------- Z - Axis
  gZ1=gZ1<<8;
  gZ_out =gZ0+gZ1;
  Zg=gZ_out*0.07;
  angleZc = Zg*dt;
  angleZ = angleZ + angleZc;
  
  // Prints the data on the Serial Monitor
  Serial.print("angleX= ");
  Serial.print(angleX);
  Serial.print("   angleY= ");
  Serial.print(angleY);
  Serial.print("   angleZ= ");
  Serial.println(angleZ);
  
  delay(10);
  // Calculating dt
  finished=millis();
  elapsed=finished-start;
  dt=elapsed/1000.0;
  start = elapsed = 0;
  
}
