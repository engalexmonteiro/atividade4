
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

#include <SDConfigfile.h>
#include "smartemp.h"


boolean load_startconfig() {

   /* Length of the longest line expected in the config file.
   * The larger this number, the more memory is used
   * to read the file.
   * You probably won't need to change this number.*/

  const uint8_t CONFIG_LINE_LENGTH = 127;

  // The open configuration file.
  SDConfigFile cfg;

  // Open the configuration file.
  if (!cfg.begin(STARTCONFIG, CONFIG_LINE_LENGTH)) {
    Serial.print("Failed to open configuration file: ");
    Serial.println(STARTCONFIG);
    return false;
  }

  // Read each setting from the file.
  while (cfg.readNextSetting()) {

    // Put a nameIs() block here for each setting you have.

    if (cfg.nameIs("temp_min")) {

    temp_min = cfg.getIntValue();
    Serial.print("temp_min: ");
    Serial.println(temp_min);

    }else if (cfg.nameIs("temp_max")) {

    temp_max = cfg.getIntValue();
    Serial.print("temp_max: ");
    Serial.println(temp_max);

    }else if (cfg.nameIs("hum_min")) {

    temp_max = cfg.getIntValue();
    Serial.print("temp_min: ");
    Serial.println(hum_min);


    }else if (cfg.nameIs("hum_max")) {

    hum_max = cfg.getIntValue();
    Serial.print("hum_max: ");
    Serial.println(hum_max);

    // waitMs integer
    } else if (cfg.nameIs("period")) {

      period = cfg.getIntValue();
      Serial.print("period: ");
      Serial.println(period);

    // hello string (char *)
    } else if (cfg.nameIs("ip")) {

      // Dynamically allocate a copy of the string.
      ip = cfg.copyValue();
      Serial.print("ip address: ");
      Serial.println(ip);

    } else if (cfg.nameIs("netmask")) {

      // Dynamically allocate a copy of the string.
      netmask= cfg.copyValue();
      Serial.print("netmask: ");
      Serial.println(netmask);

    } else if (cfg.nameIs("gateway")) {

      // Dynamically allocate a copy of the string.
      gw = cfg.copyValue();
      Serial.print("gateway: ");
      Serial.println(gw);

    } else if (cfg.nameIs("dns")) {

      // Dynamically allocate a copy of the string.
      dns = cfg.copyValue();
      Serial.print("dns: ");
      Serial.println(ip);

    } else {
      // report unrecognized names.
      Serial.print("Unknown name in config: ");
      Serial.println(cfg.getName());
    }
  }

  // clean up
  cfg.end();

  return true;
}


int load_configs(){

	Serial.println("Initializing SD card...");

	if (!SD.begin(SD_PIN)){
	   Serial.println("Initialization failed ... device is using EEPROM to save configs");
	   return 0;
	}
	else{
		Serial.println("Loadings configurations");

		if (SD.exists(STARTCONFIG)) {
			Serial.println("Loadings configurations");
		//    load_startconfig();
		} else {
			Serial.println("Generating default configuration file");
	 }
	}
	return 0;

}

