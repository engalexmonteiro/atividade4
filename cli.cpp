/*
 * cli.cpp
 *
 *  Created on: 14 de mai de 2019
 *      Author: alex
 */

#include <Arduino.h>
#include "cli.h"
#include "configs.h"



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
				Serial.print(ipByteToString(ip));
				return 0;
	}

	strcpy_P(buffer, (char *)NETMASK);
	if(command.equals(String(buffer) + '\r')){
				Serial.print(ipByteToString(netmask));
				return 0;
	}

	strcpy_P(buffer, (char *)GW);
	if(command.equals(String(buffer) + '\r')){
				Serial.print(ipByteToString(gw));
				return 0;
	}

	strcpy_P(buffer, (char *)DNS);
	if(command.equals(String(buffer) + '\r')){
				Serial.print(ipByteToString(dns));
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
			String temp = command.substring(command.indexOf('=')+1);
			ipStringToByte(temp,ip);
			Serial.print(ipByteToString(ip));
			return 0;
	}


	strcpy_P(buffer, (char *)NETMASK);
	if(command.startsWith(String(buffer) + "=")){
			String temp = command.substring(command.indexOf('=')+1);
			ipStringToByte(temp,netmask);
			Serial.print(ipByteToString(netmask));
			return 0;
	}

	strcpy_P(buffer, (char *)GW);
	if(command.startsWith(String(buffer) + "=")){
					String temp = command.substring(command.indexOf('=')+1);
					ipStringToByte(temp,gw);
					Serial.print(ipByteToString(gw));
				return 0;
	}

	strcpy_P(buffer, (char *)DNS);
	if(command.startsWith(String(buffer) + "=")){
				String temp = command.substring(command.indexOf('=')+1);
				ipStringToByte(temp,dns);
				Serial.print(ipByteToString(dns));
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


