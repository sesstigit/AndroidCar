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
/*
*	MouseSensor.cpp - Reads data from MouseSensor
*	Author: Dimitris Platis (based on the Smartcar project by Team Pegasus)
* 	License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
*/
#include "AndroidCar.h"

MouseSensor::MouseSensor(){
}

void MouseSensor::attach(HardwareSerial *mouseSerial){
	_serial = mouseSerial;
	_serial->begin(115200);
	_serial->setTimeout(50);
}

boolean MouseSensor::available(){
	return _serial->available();
}

String MouseSensor::readLine(){
	if (available()){
		return readRawSerialLine();
	}else{
		return "error";	
	}
}

/* read whatever is in the buffer untill you reach the last available line and return it */
String MouseSensor::readLastLine(){
	if (available()){
		String input = "";
		while (available()) input = readRawSerialLine();
		return input;
	}else{
		return "error";
	}
}

int MouseSensor::getX(String mouseInput){
	String x = mouseInput.substring(mouseInput.indexOf(':') + 1,mouseInput.indexOf(' '));
	int out = x.toInt();
	if (out || x.equals("0")){
		return out;
	}else{
		return -9999;
	}
}

int MouseSensor::getY(String mouseInput){
	mouseInput.trim();
	String y = mouseInput.substring(mouseInput.lastIndexOf(':') + 1);
	int out = y.toInt();
	if (out || y.equals("0")){
		return out;
	}else{
		return -9999;
	} 
}


String MouseSensor::readRawSerialLine(){
	return _serial->readStringUntil('\n');
}

void MouseSensor::clear(){
	_serial->print("c");
}
