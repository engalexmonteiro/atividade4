/*
 * ihm.h
 *
 *  Created on: 18 de mai de 2019
 *      Author: alex
 */

#ifndef IHM_H_
#define IHM_H_


//Buttons
#define DELAY  70
#define RIGHT  1
#define UP     2
#define DOWN   3
#define LEFT   4
#define SELECT 5

//States
enum STATES{S_MONITOR,S_LIST,S_SETTING,S_NETWORK,S_EDIT};

void ihm_Start();

void ihm_Service();


#endif /* IHM_H_ */
