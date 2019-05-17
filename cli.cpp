/*
 * cli.cpp
 *
 *  Created on: 14 de mai de 2019
 *      Author: alex
 */

#include <Arduino.h>
#include "cli.h"
#include "smartemp.h"

const char SMARTTEMP[] PROGMEM = "\r\nsmarTemp> ";
const char LED13[] PROGMEM = "led13\r";
const char TEMP[] PROGMEM = "temp";
const char TEMPMIN[] PROGMEM = "temp_min";
const char TEMPMAX[] PROGMEM = "temp_max";
const char HUM[] PROGMEM = "hum";
const char HUMMIN[] PROGMEM = "hum_min";
const char HUMMAX[] PROGMEM = "hum_max";
const char PERIOD[] PROGMEM = "period";
const char UNKN[] PROGMEM = "unknow command: ";

const char IP[] PROGMEM = "ip";
const char NETMASK[] PROGMEM = "netmask";
const char GW[] PROGMEM = "gateway";
const char DNS[] PROGMEM = "dns";

int command_cli(String command){

	Serial.println(command);

	if(command.equals(LED13)){
			digitalWrite(13,!digitalRead(13));
			return 0;
	}

	if(command.equals(String(TEMP) + "\r")){
			Serial.print(temp_current);
			return 0;
	}

	if(command.equals(String(TEMPMIN) + "\r")){
			Serial.print(temp_min);
			return 0;
	}

	if(command.startsWith(String(TEMPMAX) + "=")){
				temp_max = command.substring(command.indexOf('=')+1).toFloat();
				Serial.print(temp_max);
				return 0;
	}


	if(command.equals(String(TEMPMAX) + "\r")){
				Serial.print(temp_max);
				return 0;
	}

	if(command.startsWith("TEMPMAX=")){
				temp_max = command.substring(command.indexOf('=')+1).toFloat();
				Serial.print(temp_max);
				return 0;
	}

	Serial.print(String(UNKN) + command);

	return 0;
}


int cli_init(){

	String command;

	if(Serial.available()){
		command = Serial.readStringUntil('\n');

		command_cli(command);

		Serial.print(SMARTTEMP);
	}

	return 0;
}


