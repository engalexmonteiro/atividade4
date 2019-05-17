#include "smartemp.h"

#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include <DHT.h>
#include "cli.h"
#include "smartemp.h"
#include "configs.h"

//Parameters SmartTemp
float temp_min=16;
float temp_max=25;
float temp_current=0;

float hum_min=60;
float hum_max=80;
float hum_current;

unsigned int period=1000;

//Parameters Networking
String ip = "192.168.1.200";
String netmask = "255.255.255.0";
String gw = "192.168.1.1";
String dns = "8.8.8.8";


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
	    Serial.println("Failed to read from DHT");
	  }
	  else{

		temp_current = t;
		hum_current = h;

		if(temp_current<temp_min)
				Serial.println("ajustar T: "  + String(t) + "oC / H " + String(h));
   	    if(temp_current>temp_max)
				Serial.println("ligar ar "  + String(t) + "C / H " + String(h));

	  }

	  delay(period);
}


void setup(){



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
