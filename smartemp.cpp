#include "smartemp.h"

#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include <DHT.h>
#include "cli.h"
#include "smartemp.h"
#include "configs.h"

//Parameters SmartTemp
float temp_min=10;
float temp_max=50;
float temp_current=0;

float hum_min=10;
float hum_max=200;
float hum_current=0;

unsigned int period=5000;

String ip="";
String netmask="";
String gw="";
String dns="";



//Thread instances
ThreadController controll = new ThreadController();
Thread *thread_Cli = new Thread();
Thread *thread_CheckTemp = new Thread();


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

		if(temp_current<temp_min)
				Serial.println("A-T: "  + String(t) + " ºC / H " + String(h));
   	    if(temp_current>temp_max)
				Serial.println("L-T "  + String(t) + " ºC / H " + String(h));

	  }

	  delay(period);
}


void setup(){


	Serial.flush();
	Serial.begin(9600);


	load_configs();

	dht.begin();

	pinMode(13,OUTPUT);


	thread_Cli->onRun(checktemp);
	thread_Cli->setInterval(0);

	thread_CheckTemp->onRun(cli_init);
	thread_CheckTemp->setInterval(0);

	controll.add(thread_Cli);
	controll.add(thread_CheckTemp);

}

void loop() {


	controll.run();



}
