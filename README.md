# AndroidCar Arduino Library

## Description
This library is used as part of an Autonomous Vehicle which can follow lanes, park and overtake vehicles.  The brains of the car is a separate Andoid app (which runs on a mobile phone mounted on the car).  It controls the car motor and steering by sending commands over bluetooth.

This library is middleware.  It sits in the middle, between the Android App and the car hardware, and runs on a small computer called an Arduino.  After cabling an RC car's sensors and bluethooth module to a physical Arduino board, the job of this library is to fetch sensor data and transmit it over bluetooth to the Android App controller.  The library also receives driving commands from the Android App controller and passes them to the ESC (for acceleration) and to a servo motor (for steering).

The arduino sketch which supports running the vehicle in autonomous mode is in [arduino_testing/sketch_android_car/]

## Documentation
More details about installation, setup and debugging are on the AndroidCar [Wiki](https://github.com/sesstigit/AndroidCar/wiki)

## Dependencies
* Arduino Integrated Development Environment (IDE) [Software](https://www.arduino.cc/en/Main/Software).  Install to Windows PC.
* Arduino board: tested on Arduino Mega 2560 (should already be installed in RC car)
* Sensors: only a limited set of sensors for the RC car are supported.  See the [Wiki](https://github.com/sesstigit/AndroidCar/wiki) for details.
* If the aim is an autonomous car, then additional controller software must be used such as the [Carduino App](https://github.com/sesstigit/Android-Car-duino).
  * However, casic testing of the Arduino and car sensors does not require the Carduino App.  The App is only used for autonomous mode.
* Arduino IDE add the [Wire library](http://arduino.cc/en/reference/Wire) for getting data from the gyroscope, via I2C
* Arduino IDE add the [Servo library](http://www.arduino.cc/en/Reference/Servo) for controlling the ESC and the steering wheel

## Diagram
![Alt text](car_architecture_arduino.png?raw=true "You are now looking at the arduino library")

## History
This repository was cloned from [here](https://github.com/platisd/AndroidCar), before customisation.

### License
GPLv3
