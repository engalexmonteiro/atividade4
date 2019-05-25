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

		delay(DELAY);
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

void editConfigAddr(byte address[]){
			uint8_t temp, button,pos;
			STATES s_temp;
			byte temp_addr[4];

			memcpy(temp_addr, address, sizeof(byte)*4);

			oldState=state;
			state = S_EDIT;

			while(state == S_EDIT){

				button = readButton();

				if(temp != button){
					switch(button){
						case UP: temp_addr[pos]+=1;
								 break;
						case DOWN:
								temp_addr[pos]-=1;
								 break;
						case RIGHT: pos+=1;
									pos = pos%4;
									break;
						case LEFT:
								s_temp = state;
								state = oldState;
								oldState= s_temp;
								break;
						case SELECT:
								memcpy(address,temp_addr, sizeof(byte)*4);
								s_temp = state;
								state = oldState;
								oldState= s_temp;
								break;
					}

					lcd.setCursor(0,1);
					lcd.print(ipByteToString(temp_addr));
				}

				delay(DELAY);
			}

}

float editConfigFloat(float value, float inc){

		uint8_t temp, button;
		STATES s_temp;
		float oldValue = value;

		oldState=state;
		state = S_EDIT;

		while(state == S_EDIT){

			button = readButton();

			if(temp != button){
				switch(button){
					case UP: value+=inc;
							 break;
					case DOWN:
							 value-=inc;
							 break;
					case LEFT:
							s_temp = state;
							state = oldState;
							oldState= s_temp;
							return oldValue;
							break;
					case SELECT:
							s_temp = state;
							state = oldState;
							oldState= s_temp;
							return value;
							break;
				}

				lcd.setCursor(0,1);
				lcd.print(value);
			}

			delay(DELAY);
		}

		return oldValue;
}

void settingSelect(uint8_t x){
	lcd.clear();
	switch (x){
	case 0:
			lcd.setCursor(0,0);
			lcd.print("--->Temp Min");
			lcd.setCursor(0,1);
			lcd.print(String(temp_min) + "*C");
			temp_min = editConfigFloat(temp_min, 0.5);
			break;
	case 1:
			lcd.setCursor(0,0);
			lcd.print("--->Temp Max");
			lcd.setCursor(0,1);
			lcd.print(String(temp_max) + "*C");
			temp_max = editConfigFloat(temp_max, 0.5);
			break;
	case 2:
			lcd.setCursor(0,0);
			lcd.print("--->Hum Min");
			lcd.setCursor(0,1);
			lcd.print(String(hum_min) + "%");
			hum_min = editConfigFloat(hum_min, 0.5);
			break;
	case 3:
			lcd.setCursor(0,0);
			lcd.print("--->Hum Max");
			lcd.setCursor(0,1);
			lcd.print(String(hum_max) + "%");
			hum_max = editConfigFloat(hum_max, 0.5);
			break;
	case 4:
				lcd.setCursor(0,0);
				lcd.print("--->Period");
				lcd.setCursor(0,1);
				lcd.print(String(period) + "ms");
				period = editConfigFloat(period,100);
				break;
	}
}

void networkSelect(uint8_t x){
	lcd.clear();
	switch (x){
	case 0:
			lcd.setCursor(0,0);
			lcd.print("--->IP");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(ip));
			editConfigAddr(ip);
			break;
	case 1:
			lcd.setCursor(0,0);
			lcd.print("--->Netmask");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(netmask));
			editConfigAddr(netmask);
			break;
	case 2:
			lcd.setCursor(0,0);
			lcd.print("--->Gateway");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(gw));
			editConfigAddr(gw);
			break;
	case 3:
			lcd.setCursor(0,0);
			lcd.print("--->DNS");
			lcd.setCursor(0,1);
			lcd.print(ipByteToString(dns));
			editConfigAddr(dns);
			break;
	}
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


void ihm_Start(){
	lcd.begin(16, 2); // Estabelece caracteres do display
	clearPrintTitle();
	tempc=temp_current;
	humic = hum_current;
}

int settingsMenu(int x) {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("->Settings");
	lcd.setCursor(0,1);
	switch (x) {
	case 0:
		lcd.print("Temp Min"); // Imprime na tela opção escolhida
		break;
	case 1:
		lcd.print("Temp Max"); // Imprime na tela opção escolhida
		break;
	case 2:
		lcd.print("Hum Min"); // Imprime na tela opção escolhida
		break;
	case 3:
		lcd.print("Hum Max"); // Imprime na tela opção escolhida
		break;
	case 4:
		lcd.print("Period"); // Imprime na tela opção escolhida
		break;
	}
	return x;
}


void listState(){
		uint8_t button = 0;
		state_selected = S_SETTING;
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("SmartTemp");
		lcd.setCursor(0,1);
		lcd.print("-->Settings");

		oldState = state;

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
			else if(button == LEFT){
					state = S_MONITOR;
			}

			delay(DELAY);
		}


}

void settingState(){

	int8_t menu=0,temp,button = 0;
	STATES s_temp = oldState;

	while(state == S_SETTING){

		if(s_temp != state){
			settingsMenu(menu);
			s_temp = state;
		}

		temp = readButton();

		if(temp != button){
			button = temp;


			switch(button){
				case UP:   	menu--;
							if(menu < 0) menu = 4;
							settingsMenu(menu);
							break;
				case DOWN:  menu++;
							if(menu > 4) menu = 0;
							settingsMenu(menu);
					   	   	break;
				case RIGHT: s_temp=S_EDIT;
							settingSelect(menu);
						    break;
				case SELECT:s_temp=S_EDIT;
							settingSelect(menu);
							break;
				case LEFT:	oldState=state;
							state = S_LIST;
					 	 	break;
			}
		}

		Serial.println(menu);

		delay(DELAY);
	}
}

void networkState(){

	int8_t menu=0,temp,button = 0;
	STATES s_temp = oldState;

	while(state == S_NETWORK){

		if(s_temp != state){
				networkMenu(menu);
				s_temp = state;
		}

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
				case RIGHT: s_temp=S_EDIT;
							networkSelect(menu);
						    break;
				case SELECT:s_temp=S_EDIT;
							networkSelect(menu);
							break;
				case LEFT:	oldState = state;
							state = S_LIST;
					 	 	break;
			}
		}

		Serial.println(menu);

		delay(DELAY);
	}
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


	delay(DELAY);
}
