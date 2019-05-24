
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
#include "cli.h"


const char def_ip[] 		PROGMEM = "ip=192.168.1.200";
const char def_netmask[] 	PROGMEM = "netmask=255.255.255.0";
const char def_gw[] 		PROGMEM = "gateway=192.168.1.1";
const char def_dns[] 		PROGMEM = "dns=8.8.8.8";


int ipStringToByte(String address, byte ip[]){

  uint8_t i,pos,ints=0;

  for(i=0;i<4;i++){
    pos = address.indexOf(".",ints);
    ip[i] = address.substring(ints,pos).toInt();
    ints = pos+1;
  }

  return 0;
}

String ipByteToString(byte ip[]){
  String address;
  uint8_t i;
  for(i=0;i<4;i++){
    address+=ip[i];
    if(i<3)
      address+=".";
  }
  return address;
}

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

	File myFile = SD.open(STARTCONFIG);

	String conf = "";

	if (myFile) {

		while (myFile.available()) {
			conf += (char)myFile.read();
	    }

		//Sensor
		temp_min 	= readConfigFloat(conf,TEMPMIN);
		temp_max 	= readConfigFloat(conf,TEMPMAX);
		hum_min 	= readConfigFloat(conf,HUMMIN);
		hum_max 	= readConfigFloat(conf,HUMMAX);
		period 		= readConfigInt(conf,PERIOD);

		//Networking
		ipStringToByte(readConfigString(conf,IP),ip);
		ipStringToByte(readConfigString(conf,NETMASK),netmask);
		ipStringToByte(readConfigString(conf,GW),gw);
		ipStringToByte(readConfigString(conf,DNS),dns);

        // close the file:
	    myFile.close();

	    return 0;
	}else{
		//Serial.println("error open");
		return -1;
	}
}



/*int generateConfigFile(){

	SD.remove(STARTCONFIG);
	File myFile = SD.open(STARTCONFIG, FILE_WRITE);

	  // if the file opened okay, write to it:
	if (myFile) {
		Serial.print("Writing to ");
	    Serial.println(STARTCONFIG);

	    myFile.println("temp_min=16");
	    myFile.println("temp_max=22");
	    myFile.println("hum_min=60");
	    myFile.println("hum_max=70");
	    myFile.println("period=1000");
	    myFile.println("ip=192.168.1.1");
	    myFile.println("netmask=255.255.255.0");
	    myFile.println("gateway=192.168.1.1");
	    myFile.println("dns=8.8.8.8");

	    // close the file:
	    myFile.close();

	    Serial.println("done.");
	 } else {
	    // if the file didn't open, print an error:
	    Serial.println("error opening ");
	 }

	return 0;
}*/



void print_configs(){
	Serial.println(temp_min);
	Serial.println(temp_max);
	Serial.println(hum_min);
	Serial.println(hum_max);
	Serial.println(period);
	Serial.println(ipByteToString(ip));
	Serial.println(ipByteToString(netmask));
	Serial.println(ipByteToString(gw));
	Serial.println(ipByteToString(dns));
}


int load_configs(){

	//Serial.println("Initializing SD card...");

	if (!SD.begin(SD_PIN)){
	  // Serial.println("Initialization failed ... device is using EEPROM to save configs");
	   return 0;
	}

	if (SD.exists(STARTCONFIG)) {
			Serial.println("Loadings configurations");
			configFile();
	}else {
			Serial.println("Generating default and loading configuration file");
	//		generateConfigFile();
			configFile();
	 }

	return 0;
}
