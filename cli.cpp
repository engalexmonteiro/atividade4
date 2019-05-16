/*
 * cli.cpp
 *
 *  Created on: 14 de mai de 2019
 *      Author: alex
 */

#include <Arduino.h>
#include "cli.h"
#include "smartemp.h"

int command_cli(String command){

	Serial.println(command);

	if(command.equals("LED13\r")){
			digitalWrite(13,!digitalRead(13));
			Serial.print("LED13=");
			Serial.print(digitalRead(13));
			return 0;
	}

	if(command.equals("TEMP\r")){
			Serial.print(temp_current);
			return 0;
	}

	if(command.equals("TEMPMIN\r")){
			Serial.print(temp_min);
			return 0;
	}

	if(command.startsWith("TEMPMIN=")){
				temp_max = command.substring(command.indexOf('=')+1).toFloat();
				Serial.print(temp_max);
				return 0;
	}


	if(command.equals("TEMPMAX\r")){
				Serial.print(temp_max);
				return 0;
	}

	if(command.startsWith("TEMPMAX=")){
				temp_max = command.substring(command.indexOf('=')+1).toFloat();
				Serial.print(temp_max);
				return 0;
	}

	Serial.print("unknow command: " + command);

	return 0;
}


int cli_init(){

	String command;

	if(Serial.available()){
		command = Serial.readStringUntil('\n');

		command_cli(command);

		Serial.print("\r\nsmarTemp> ");
	}

	return 0;
}


