/*
 * cli.h
 *
 *  Created on: 14 de mai de 2019
 *      Author: alex
 */

#ifndef CLI_H_
#define CLI_H_

#include <Arduino.h>

int cli_init();

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


#endif /* CLI_H_ */
