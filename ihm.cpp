/*
 * ihm.cpp
 *
 *  Created on: 18 de mai de 2019
 *      Author: alex
 */
#include <Arduino.h>
#include "ihm.h"
#include "configs.h"
#include <LiquidCrystal.h> // Inclui biblioteca "LiquidCristal.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Define Pinos do Display

int Menu = 0;                    // Inicializa valores para Menu
STATES state = S_MONITOR;      // Inicializa valores para estado
STATES oldState = S_MONITOR;
STATES state_selected = S_MONITOR;
int tempc=0;
int humic=0;

uint8_t readButton(){

	uint16_t x = analogRead(A0);

	uint8_t button = 0;

	if (x < 10) { // Define valores máximos para UP em ValEstado = 1
		button = RIGHT;
	}
	else if (x < 200) { // Define valores máximos para UP em ValEstado = 1
		button = UP;
	}
	else if (x < 300) {
		button = DOWN;
	}
	else if (x < 600){ // Define ação nula para Left
		button = LEFT;
	}
	else if (x < 800){ // Define valores máximos para Select em ValEstado = 3
		button = SELECT;
	}
	return button;
}

void clearPrintTitle() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("smartTemp ");
	lcd.setCursor(0,1);
}

void monitorState(){

	uint16_t button = readButton();
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("SmartTemp->Monitor");
	lcd.setCursor(0,1);
	lcd.print("T:" + String(temp_current).substring(0,2) +  "C/HUM:" + String(hum_current).substring(0,2) + "%");

	while(state == S_MONITOR){

		button = readButton();
		if(button == UP || button == DOWN){
			state = S_LIST;
			clearPrintTitle();
			break;
		}

		if(tempc != temp_current || humic != hum_current){
			clearPrintTitle();
			lcd.setCursor(3,1);
			lcd.print(String(temp_current).substring(0,2));
			lcd.print("C/HUM:");
			lcd.print(String(hum_current).substring(0,2));
			lcd.print("%");
			tempc=temp_current;
			humic=hum_current;
		}
		lcd.setCursor(0,1);
	}

}



void mainMenu(int x) {

	switch (x){

	case S_MONITOR:
		clearPrintTitle();
		lcd.print("--->Monitor<---"); // Imprime na tela a opção do Menu
		break;
	case S_SETTING:
		clearPrintTitle();
		lcd.print("--->Settings<---"); // Imprime na tela a opção do Menu
		break;
	case S_NETWORK:
		clearPrintTitle();
		lcd.print("--->Networking<---"); // Imprime na tela a opção do Menu
		break;
	}

}

void settingMenu(int x) {
	switch (x) {
	lcd.clear();
	lcd.setCursor(0,0);
	case 1:
		lcd.print("sett --> temp min"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(ip));
		break;
	case 2:
		lcd.print("sett --> temp max"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(netmask));
		break;
	case 3:
		lcd.print("sett --> hum min"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(gw));
		break;
	case 4:
		lcd.print("sett --> hum max"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(dns));
		break;
	case 5:
		lcd.print("sett --> inteval"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(dns));
		break;
	}
}

void networkSelect(uint8_t x){
	lcd.clear();
	switch (x){
	case 0:
			lcd.setCursor(0,0);
			lcd.print("--->ip");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(ip));
			break;
	case 1:
			lcd.setCursor(0,0);
			lcd.print("--->netmask");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(netmask));
			break;
	case 2:
			lcd.setCursor(0,0);
			lcd.print("--->gateway");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(gw));
			break;
	case 3:
			lcd.setCursor(0,0);
			lcd.print("--->DNS");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(dns));
			break;
	}
	/*
	lcd.setCursor(0,1);
			lcd.print(ipByteToString(netmask));

			lcd.setCursor(0,1);
					lcd.print(ipByteToString(gw));

					lcd.setCursor(0,1);
							lcd.print(ipByteToString(dns));*/
}

int networkMenu(int x) {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("->Networking");
	lcd.setCursor(0,1);
	switch (x) {
	case 0:
		lcd.print("ip"); // Imprime na tela opção escolhida
		break;
	case 1:
		lcd.print("netmask"); // Imprime na tela opção escolhida

		break;
	case 2:
		lcd.print("gateway"); // Imprime na tela opção escolhida
		break;
	case 3:
		lcd.print("DNS"); // Imprime na tela opção escolhida
		break;
	}
	return x;
}

void selectMenu(int x) {

	switch (x) {
	case S_MONITOR:
		monitorState();
	case S_NETWORK:
		networkMenu(0);
		break;
	case S_SETTING:
		settingMenu(0);
		break;
	}
}

void ihm_Start(){
	lcd.begin(16, 2); // Estabelece caracteres do display
	clearPrintTitle();
	tempc=temp_current;
	humic = hum_current;
}

void listState(){
		uint8_t button = 0;
		state_selected = S_SETTING;
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("SmartTemp");
		lcd.setCursor(0,1);
		lcd.print("-->Settings");

		while(state == S_LIST){

			button = readButton();

			if(button == UP){
				state_selected = S_SETTING;
				lcd.setCursor(0,1);
				lcd.print("-->Settings  ");
			}
			else if(button == DOWN){
				lcd.setCursor(0,1);
				lcd.print("-->Networking");
				state_selected = S_NETWORK;
			}else if(button == RIGHT || button == SELECT)
					state = state_selected;
			else if(button == LEFT)
					state = S_MONITOR;
		}


}

void networkState(){

	int8_t menu,temp,button = 0;
	networkMenu(menu);

	while(state == S_NETWORK){


		temp = readButton();

		if(temp != button){
			button = temp;


			switch(button){
				case UP:   	menu--;
							if(menu < 0) menu = 3;
							networkMenu(menu);
							break;
				case DOWN:  menu++;
							if(menu > 3) menu = 0;
					   	   	networkMenu(menu);
					   	   	break;
				case RIGHT: networkSelect(menu);
						    break;
				case SELECT:
							networkSelect(menu);
							break;
				case LEFT:	state = S_LIST;
					 	 	break;
			}
		}

		Serial.println(menu);

		delay(5);
	}
}

void settingState(){

}


void ihm_Service() {

	switch(state){
		case S_MONITOR:	monitorState();
						break;
		case S_LIST:  	listState();
						break;
		case S_NETWORK: networkState();
						break;
		case S_SETTING: settingState();
						break;
	}

	Serial.print(state);
	Serial.println(" | ");


	delay(5);
}
