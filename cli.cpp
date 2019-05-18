/*
 * cli.cpp
 *
 *  Created on: 14 de mai de 2019
 *      Author: alex
 */

#include <Arduino.h>
#include "cli.h"
#include "configs.h"

const char SMARTTEMP[] PROGMEM = "\r\nsmarTemp> ";
const char LED13[] PROGMEM = "led13";
const char TEMP[] PROGMEM = "temp_current";
const char TEMPMIN[] PROGMEM = "temp_min";
const char TEMPMAX[] PROGMEM = "temp_max";
const char HUM[] PROGMEM = "hum_current";
const char HUMMIN[] PROGMEM = "hum_min";
const char HUMMAX[] PROGMEM = "hum_max";
const char PERIOD[] PROGMEM = "period";
const char UNKN[] PROGMEM = "unknow command: ";
const char IP[] PROGMEM = "ip";
const char NETMASK[] PROGMEM = "netmask";
const char GW[] PROGMEM = "gateway";
const char DNS[] PROGMEM = "dns";
const char *const cmd_table[] PROGMEM = {TEMPMIN,TEMPMAX,HUMMIN,HUMMAX,PERIOD,IP,NETMASK,GW,DNS,UNKN};



int command_cli(String command){

	char buffer[30];

	strcpy_P(buffer, (char *)LED13);
	if(command.equals(String(buffer) + '\r')){
			digitalWrite(13,!digitalRead(13));
			return 0;
	}

	strcpy_P(buffer, (char *)TEMP);
	if(command.equals(String(buffer) + '\r')){
			Serial.print(temp_current);
			return 0;
	}

	strcpy_P(buffer, (char *)TEMPMIN);
	if(command.equals(String(buffer) + '\r')){
			Serial.print(temp_min);
			return 0;
	}

	strcpy_P(buffer, (char *)TEMPMAX);
	if(command.equals(String(buffer) + '\r')){
			Serial.print(temp_max);
			return 0;
	}

	strcpy_P(buffer, (char *)IP);
	if(command.equals(String(buffer) + '\r')){
				Serial.print(ip);
				return 0;
	}

	strcpy_P(buffer, (char *)NETMASK);
	if(command.equals(String(buffer) + '\r')){
				Serial.print(netmask);
				return 0;
	}

	strcpy_P(buffer, (char *)GW);
	if(command.equals(String(buffer) + '\r')){
				Serial.print(gw);
				return 0;
	}

	strcpy_P(buffer, (char *)DNS);
	if(command.equals(String(buffer) + '\r')){
				Serial.print(dns);
				return 0;
	}

	strcpy_P(buffer, (char *)PERIOD);
		if(command.equals(String(buffer) + '\r')){
					Serial.print(period);
					return 0;
		}

		strcpy_P(buffer, (char *)PERIOD);
		if(command.startsWith(String(buffer) + "=")){
					period = command.substring(command.indexOf('=')+1).toInt();
					Serial.print(period);
					return 0;
		}


	strcpy_P(buffer, (char *)TEMPMAX);
	if(command.startsWith(String(buffer) + "=")){
				temp_max = command.substring(command.indexOf('=')+1).toFloat();
				Serial.print(temp_max);
				return 0;
	}

	strcpy_P(buffer, (char *)TEMPMIN);
	if(command.startsWith(String(buffer) + "=")){
				temp_min = command.substring(command.indexOf('=')+1).toFloat();
				Serial.print(temp_min);
				return 0;
	}

	strcpy_P(buffer, (char *)IP);
	if(command.startsWith(String(buffer) + "=")){
			ip= command.substring(command.indexOf('=')+1);
			Serial.print(ip);
			return 0;
	}


	strcpy_P(buffer, (char *)NETMASK);
	if(command.startsWith(String(buffer) + "=")){
			netmask= command.substring(command.indexOf('=')+1);
			Serial.print(netmask);
			return 0;
	}

	strcpy_P(buffer, (char *)GW);
	if(command.startsWith(String(buffer) + "=")){
				gw = command.substring(command.indexOf('=')+1);
				Serial.print(gw);
				return 0;
	}

	strcpy_P(buffer, (char *)DNS);
	if(command.startsWith(String(buffer) + "=")){
				dns = command.substring(command.indexOf('=')+1);
				Serial.print(dns);
				return 0;
	}

	strcpy_P(buffer, (char *)UNKN);
	Serial.print(String(buffer) + command);

	return -1;
}


int cli_init(){

	String command;

	if(Serial.available()){
		command = Serial.readStringUntil('\n');

		command_cli(command);

		char buffer[30];
		strcpy_P(buffer, (char *)SMARTTEMP);
		Serial.print(buffer);

	}

	return 0;
}


