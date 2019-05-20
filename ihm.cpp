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

int Menu = 0; // Inicializa valores para Menu
int estado = 0; // Inicializa valores para estado
int AntEstado = 0;
int tempc=0;
int humic=0;

void clearPrintTitle() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("smartTemp ");
	lcd.setCursor(0,1);
}

void mainPrintTitle() {
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



void displayMenu(int x) {
	switch (x) {
	case 0:
		clearPrintTitle();
		lcd.print("T:" + String(temp_current).substring(0,2) + "*C/H:" + String(hum_current).substring(0,2) + "%"); // Imprime na tela a opção do Menu
		break;
	case 1:
		clearPrintTitle();
		lcd.print("--->Monitoring<---"); // Imprime na tela a opção do Menu
		break;
	case 2:
		clearPrintTitle();
		lcd.print("--->Settings<---"); // Imprime na tela a opção do Menu
		break;
	}
}

void selectMenu(int x) {
	switch (x) {
	case 1:
		clearPrintTitle();
		lcd.print("Monitoring"); // Imprime na tela opção escolhida
		break;
	case 2:
		clearPrintTitle();
		lcd.print("Settings"); // Imprime na tela opção escolhida
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

	int ValEstado = 0; // Inicializa valores para ValEstado
	int x = analogRead (0);


	lcd.setCursor(0,0); // Posiciona Cursor

	if (x < 80) { // Define valores máximos para UP em ValEstado = 1
	}
	else if (x < 200) {
		ValEstado = 1;
	}
	else if (x < 400){ // Define valores máximos para Down em ValEstado = 2
		ValEstado = 2;
	}
	else if (x < 600){ // Define ação nula para Left
	}
	else if (x < 800){ // Define valores máximos para Select em ValEstado = 3
		ValEstado = 3;
	}

	if (Menu < 0 || Menu > 4) {
		Menu = 0;
	}

	if(Menu == 0)
		mainPrintTitle();

	if (ValEstado != estado) {

		if (ValEstado == 1) {
			Menu = Menu - 1;
			displayMenu(Menu);
		} else if (ValEstado == 2) {
			Menu = Menu + 1;
			displayMenu(Menu);
		} else if (ValEstado == 3) {
			selectMenu(Menu);
		}
		estado = ValEstado;
	}

	Serial.print(estado);
	Serial.print(" | ");
	Serial.print(ValEstado);
	Serial.print(" | ");
	Serial.println(Menu);

	delay(5);
}
