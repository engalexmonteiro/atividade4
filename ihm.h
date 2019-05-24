/*
 * ihm.h
 *
 *  Created on: 18 de mai de 2019
 *      Author: alex
 */

#ifndef IHM_H_
#define IHM_H_


//Buttons
#define RIGHT  1
#define UP     2
#define DOWN   3
#define LEFT   4
#define SELECT 5

//States
#define S_LIST     0
#define S_MONITOR  1
#define S_SETTING  2
#define S_NETWORK  3

void ihm_Start();

void ihm_Service();


#endif /* IHM_H_ */
