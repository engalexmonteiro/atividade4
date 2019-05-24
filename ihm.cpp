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
uint8_t state = S_MONITOR;      // Inicializa valores para estado
uint8_t oldState = S_MONITOR;
uint8_t state_selected = S_MONITOR;
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

void monitorState() {

	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("--> Monitoring");
	lcd.setCursor(0,1);
	lcd.print("T:" + String(temp_current).substring(0,2) +  "C/HUM:" + String(hum_current).substring(0,2) + "%");

	while(state_selected == S_MONITOR){

		if(readButton() == LEFT){
			state_selected = oldState;
			Menu = oldState;
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

void networkMenu(int x) {
	switch (x) {
	lcd.clear();
	lcd.setCursor(0,0);
	case 1:
		lcd.print("net --> iP"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(ip));
		break;
	case 2:
		lcd.print("net --> netmask"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(netmask));
		break;
	case 3:
		lcd.print("net --> gateway"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(gw));
		break;
	case 4:
		lcd.print("net --> DNS"); // Imprime na tela opção escolhida
		lcd.setCursor(0,1);
		lcd.print(ipByteToString(dns));
		break;

	}
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





void ihm_Service() {

	uint8_t temp =0;

	uint8_t button = readButton();

	lcd.setCursor(0,0); // Posiciona Cursor

	if (Menu < 0 || Menu > 3)
		Menu = 0;

	if (button != state) {

		switch(button){
				case RIGHT:
						oldState = state_selected;
						state_selected = Menu;
						selectMenu(state_selected);
						break;
				case UP:
						Menu = Menu - 1;
						mainMenu(Menu);
						break;
				case DOWN:
						Menu = Menu + 1;
						mainMenu(Menu);
						break;
				case LEFT:
						temp = state;
						state = oldState;
						oldState = temp;
						break;
				case SELECT:
						oldState = state_selected;
						state_selected = Menu;
						selectMenu(state_selected);
						break;
		}

			state = button;
	}

	Serial.print(state);
	Serial.print(" | ");
	Serial.print(button);
	Serial.print(" | ");
	Serial.println(Menu);

	delay(5);
}
