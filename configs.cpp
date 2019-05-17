
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

int configFile(){

	File myFile = SD.open("start.cf");

	String conf = "";

	if (myFile) {

		while (myFile.available()) {
				conf += (char)myFile.read();
				//Serial.println(conf);
	     }
		Serial.println(conf);


        // close the file:
	    myFile.close();

	    return 0;
	}else{
		Serial.println("error open");
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
