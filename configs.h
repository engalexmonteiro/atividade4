/*
 * configs.h
 *
 *  Created on: 16 de mai de 2019
 *      Author: aluno
 */

#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <Arduino.h>

#define SD_PIN 4
#define STARTCONFIG "start.cf"

#define TEMP_MIN 19.00
#define TEMP_MAX 22.00
#define HUM_MIN 60.00
#define HUM_MAX 80.00
#define PERIODI 5000

#define DHTPIN  A1
#define DHTTYPE DHT11

//Parameters

extern float temp_min;
extern float temp_max;

extern float hum_min;
extern float hum_max;

//
extern float temp_current;
extern float hum_current;

extern String ip;
extern String netmask;
extern String gw;
extern String dns;

extern unsigned int period;

int load_configs();

void print_configs();
//Parameters Networking


#endif /* CONFIGS_H_ */
