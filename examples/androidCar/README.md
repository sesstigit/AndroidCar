#Sketch set up

******************
IMPORTANT NOTE: this is the sketch used by the original Android-Car-duino authors.  For the modified sketch for sesstigit, see ../../arduino_testing/sketch_android_car
******************

This sketch utilizes the Autonomous Car library and the [Netstrings library](https://github.com/platisd/Netstrings) in order to send data fetched from the on board sensors to an Android phone, while receiving driving instructions from it. The current system schematic can be found in the [../../diagrams](diagrams) folder, while various pin definitions are included in the [CarVariables.h](CarVariables.h)

The Android application that interpets the data sent via this sketch and sends the driving instructions, can be found in the [Android-Car-duino](https://github.com/sesstigit/Android-Car-duino/) repository.
