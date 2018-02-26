# AndroidCar Arduino Library

## Description
An Arduino library, based on the Team Pegasus autonomous car [code](https://github.com/platisd/AndroidCar). The arduino must be cabled to a model car's sensors and bluethooth module.  Then, this library fetches sensor data and transmits it via bluetooth.  It also receives driving commands from the Android App to control an ESC (acceleration) and a servo motor (steering).

This library provides a simple interface to the car's sensors.  The aim is to use the library to build an Autonomous Vehicle which can follow lanes, park and overtake vehicles.  An Andoid app (running on a mobile phone mounted on the car) would control the vehicle over bluetooth using this library.

The arduino sketch which supports running the vehicle in autonomous mode is in [arduino_testing/sketch_android_car/]

## Documentation
- AndroidCar [Wiki](https://github.com/sesstigit/AndroidCar/wiki)

## Dependencies
* Arduino board: tested on Arduino Mega 2560
* Sensors: only a limited set of sensors are supported.  See the [Wiki](https://github.com/sesstigit/AndroidCar/wiki) for details.
* To drive the car autonomously, the [Carduino App](https://github.com/sesstigit/Android-Car-duino) must be installed on an Android device.
* [Wire library](http://arduino.cc/en/reference/Wire) used for getting data from the gyroscope, via I2C
* [Servo library](http://www.arduino.cc/en/Reference/Servo) used for controlling the ESC and the steering wheel

## Diagram
![Alt text](car_architecture_arduino.png?raw=true "You are now looking at the arduino library")

## History
Repository cloned, then adapted from [this project](https://github.com/platisd/AndroidCar).

### License
GPLv3
