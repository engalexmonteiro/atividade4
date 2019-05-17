
/*
 * configs.c
 *
 *  Created on: 16 de mai de 2019
 *      Author: aluno
 */


#include "configs.h"
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "smartemp.h"
#include "cli.h"

const char def_ip[] PROGMEM = "192.168.1.200";
const char def_netmask[] PROGMEM = "255.255.255.0";
const char def_gw[] PROGMEM = "192.168.1.1";
const char def_dns[] PROGMEM = "8.8.8.8";


float readConfigFloat(String conf,const char* param){

	char buffer[30];

	strcpy_P(buffer, (char *)param);

	//Serial.println(buffer);

	uint16_t position = conf.indexOf(buffer);

	if(position != -1){

		position = conf.indexOf("=",position);


		uint16_t finalp = conf.indexOf('\n',position);


		String temp = conf.substring(position+1,finalp);



		return temp.toFloat();
	}

	return position;
};

int readConfigInt(String conf,const char* param){

	char buffer[30];

	strcpy_P(buffer, (char *)param);

	uint16_t position = conf.indexOf(buffer);

	if(position != -1){

	position = conf.indexOf("=",position);

	uint16_t finalp = conf.indexOf('\n',position);

	String temp = conf.substring(position+1,finalp);


	return temp.toInt();

	}

	return position;
};

String readConfigString(String conf,const char* param){

		char buffer[30];

		strcpy_P(buffer, (char *)param);

		uint16_t position = conf.indexOf(buffer);

		if(position != -1){

			position = conf.indexOf("=",position);

			uint16_t finalp = conf.indexOf('\n',position);

			return conf.substring(position+1,finalp);

		}


		return "";
};


int configFile(){

	File myFile = SD.open("start.cf");

	String conf = "";

	if (myFile) {

		while (myFile.available()) {
				conf += (char)myFile.read();
	     }


	temp_min = readConfigFloat(conf,TEMPMIN);
	temp_max =readConfigFloat(conf,TEMPMAX);
	hum_min = readConfigFloat(conf,HUMMIN);
	hum_max = readConfigFloat(conf,HUMMAX);
	period = readConfigInt(conf,PERIOD);
	ip = readConfigString(conf,IP);
	netmask = readConfigString(conf,NETMASK);
	gw = readConfigString(conf,GW);
	dns = readConfigString(conf,DNS);

        // close the file:
	    myFile.close();

	    return 0;
	}else{
		//Serial.println("error open");
		return -1;
	}
}


/*
int generateConfigFile(){

	File myFile = SD.open("start.cf", FILE_WRITE);

	  // if the file opened okay, write to it:
	if (myFile) {
	    Serial.println("Writing to start.conf");
	    myFile.println("temp_min=16");
	    myFile.println("temp_max=22");
	    myFile.println("hum_min=60");
	    myFile.println("hum_min=70");
	    myFile.println("period=1000");
	    myFile.println("ip=192.168.1.1");
	    myFile.println("netmask=255.255.255.0");
	    myFile.println("gateway=192.168.1.1");
	    myFile.println("dns=8.8.8.8.");

	    // close the file:
	    myFile.close();

	    Serial.println("done.");
	 } else {
	    // if the file didn't open, print an error:
	    Serial.println("error opening ");
	 }




	return 0;
}
*/



int load_configs(){

	//Serial.println("Initializing SD card...");

	if (!SD.begin(SD_PIN)){
	  // Serial.println("Initialization failed ... device is using EEPROM to save configs");
	   return 0;
	}

	if (SD.exists(STARTCONFIG)) {
		//	Serial.println("Loadings configurations");
			configFile();
	}else {
		//	Serial.println("Generating default and loading configuration file");
			//generateConfigFile();
			configFile();
	 }

	return 0;
}
