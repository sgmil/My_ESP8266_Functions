/*
	ESP8266_Functions.h - Personal library with useful 
	files for ESP8266.
	Library functions
	1. 	connect ESP8266 to riverrun 
  		wifi with static IP address, as wifi STAtion. 
	2. 	tweet string through ThingTweet
	Created By Stephen Milheim, December 14, 2019
*/


#ifndef LED_PIN
#define LED_PIN  5 // Thing's onboard, green LED
#endif

#ifndef connectWiFi_h
#define connectWiFi_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class MyWiFi
{
	public:
		//when instantiating class object, pass a unique 
		//device name and last three digits of static IP
		MyWiFi(String deviceName,int lastThreeIP);
		void connectWiFi();
		void myTweet(String tweet);
	
	private:
		//////////////////////
		// WiFi Definitions //
		//////////////////////
		const char* const _WiFiSSID = "riverrun";
		const char* const _WiFiPSK = "";
		//ThingTweet API KEY
		const String _API_KEY = "SWSPZGZN1CBMD2E3";
		String _deviceName;
		int _lastThreeIP;
		
};

#endif
