/*
	ESP8266_Functions.h - Personal library with useful 
	files for ESP8266.
	Library functions
	1. 	connect ESP8266 to riverrun 
  		wifi with static IP address, as wifi STAtion. 
	2. 	tweet string through ThingTweet
    3.  can add OTA programming to sketch
	Created By Stephen Milheim, December 14, 2019
*/


#ifndef LED_PIN
#define LED_PIN  5 // Thing's onboard, green LED
#endif

#ifndef connectWiFi_h
#define connectWiFi_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <string>
#include <bits/stdc++.h>
using namespace std;

class MyWiFi
{
	public:
        ArduinoOTAClass myOTA;
        ESP8266WiFiClass wf;
		//when instantiating class object, pass a unique 
		//device name and last three digits of static IP
		MyWiFi(String deviceName,string IPaddress);
		void connectWiFi();
		void myTweet(String tweet);
        void myOTAsetup();
        void myOTAhandle();
	private:
		//////////////////////
		// WiFi Definitions //
		//////////////////////
		const char* const _WiFiSSID = "riverrun";
		const char* const _WiFiPSK = "";
		//ThingTweet API KEY
		const String _API_KEY = "SWSPZGZN1CBMD2E3";
		String _deviceName = "ESP8266";
		string _IPaddress;
        int * IPstringtodigits(string IPaddress);
		void wifiRenew();
};

#endif
