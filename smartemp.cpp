#include "configs.h"
#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include <DHT.h>
#include "cli.h"
#include "ihm.h"


//Parameters SmartTemp
float temp_min=TEMP_MIN;
float temp_max=TEMP_MAX;
float temp_current=-1;

float hum_min=TEMP_MIN;
float hum_max=TEMP_MAX;
float hum_current=-1;

unsigned int period=PERIODI;

byte ip[]={192,168,1,250};
byte netmask[]={255,255,255,255};
byte gw[]={192,168,1,1};
byte dns[]={192.168,1,1};

//Thread instances
ThreadController controll = new ThreadController();
Thread *thread_Cli = new Thread();
Thread *thread_CheckTemp = new Thread();
Thread *thread_IHM = new Thread();


//SmartTemp objects
DHT dht(DHTPIN, DHTTYPE);

void checktemp(){

	  float h = dht.readHumidity();
	  float t = dht.readTemperature();

	  // testa se retorno é valido, caso contrário algo está errado.
	  if (isnan(t) || isnan(h))
	  {
	    //Serial.println("Failed to read from DHT");
	  }
	  else{

		temp_current = t;
		hum_current = h;

/*
		if(temp_current<temp_min)
				Serial.println("A-T: "  + String(t) + " ºC / H " + String(h));
   	    if(temp_current>temp_max)
				Serial.println("L-T "  + String(t) + " ºC / H " + String(h));
*/

	  }

	  delay(period);
}


void setup(){


	Serial.begin(9600);
	pinMode(A1,OUTPUT);
	pinMode(A4,OUTPUT);
	digitalWrite(A1,HIGH);
	digitalWrite(A4,LOW);

	Serial.flush();
	Serial.begin(9600);

	load_configs();

	dht.begin();

	pinMode(13,OUTPUT);


	thread_Cli->onRun(checktemp);
	thread_Cli->setInterval(0);

	/*	thread_CheckTemp->onRun(cli_init);
	thread_CheckTemp->setInterval(0);*/

	thread_CheckTemp->onRun(ihm_Service);
	thread_CheckTemp->setInterval(0);

	//controll.add(thread_Cli);
	controll.add(thread_CheckTemp);
	controll.add(thread_IHM);

	ihm_Start();

}

void loop() {

	controll.run();
//	ihm_Service();

}
