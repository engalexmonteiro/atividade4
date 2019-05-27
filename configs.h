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

#define DHTPIN  A2
#define DHTTYPE DHT11

//Parameters

extern float temp_min;
extern float temp_max;

extern float hum_min;
extern float hum_max;

//
extern float temp_current;
extern float hum_current;

extern byte ip[];
extern byte netmask[];
extern byte gw[];
extern byte dns[];

extern const char nameDevice[];
extern const char SMARTTEMP[];
extern const char LED13[];
extern const char TEMP[];
extern const char TEMPMIN[];
extern const char TEMPMAX[];
extern const char HUMMIN[];
extern const char HUMMAX[];
extern const char PERIOD[];
extern const char UNKN[];

extern const char IP[];
extern const char NETMASK[];
extern const char GW[];
extern const char DNS[];
extern const char *const cmd_table[];

extern unsigned int period;

int load_configs();

void print_configs();

String readStringMEM(char WORD[]);
//Parameters Networking
String ipByteToString(byte ip[]);

int ipStringToByte(String address, byte ip[]);

#endif /* CONFIGS_H_ */
