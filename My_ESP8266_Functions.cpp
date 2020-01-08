/*
 *	ESP8266_Functions.cpp - Library functions
 * 1. 	connect ESP8266 to riverrun 
 * 		wifi with static IP address, as wifi STAtion. 
 * 2. 	tweet string through ThingTweet
 */
 
#include <Arduino.h>
#include "My_ESP8266_Functions.h"
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoOTA.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

MyWiFi::MyWiFi(String deviceName, String IPaddress)
{
    //_deviceName = devicename;
    _IPaddress = IPaddress.c_str(); //to strip IP String need c++ string::
    pinMode(LED_PIN, OUTPUT); 
    ArduinoOTAClass myOTA;
    ESP8266WiFiClass wf;
}
void MyWiFi::connectWiFi()
{	
	Serial.begin(115200);
	byte ledStatus = LOW;	
	Serial.println();
	Serial.println("Connecting to: " + String(_WiFiSSID));
	wf.hostname(_deviceName);
	IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
	IPAddress subnet(255, 255, 255, 0);  //Subnet mask
	IPAddress dns(8, 8, 8, 8);  //DNS
    int *IParray = MyWiFi::IPstringtodigits(_IPaddress);
    //for (int i=0;i<4;i++) {
        //Serial.println(IParray[i]);
    //}
	IPAddress staticIP(IParray[0],IParray[1],IParray[2],IParray[3]); //ESP static ip 
	wf.config(staticIP,gateway,subnet,dns);
	// Set WiFi mode to station (as opposed to AP or AP_STA)
	wf.mode(WIFI_STA);
	// WiFI.begin([ssid], [passkey]) initiates a WiFI connection
	// to the stated [ssid], using the [passkey] as a WPA, WPA2,
	// or WEP passphrase.
	wf.begin(_WiFiSSID, _WiFiPSK);
	// Use the WiFi.status() function to check if the ESP8266
	// is connected to a WiFi network.
	while (wf.status() != WL_CONNECTED)
	{
	// Blink the LED
	digitalWrite(LED_PIN, ledStatus); // Write LED high/low
	ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
	Serial.print(".");
	// Delays allow the ESP8266 to perform critical tasks
	// defined outside of the sketch. These tasks include
	// setting up, and maintaining, a WiFi connection.
	delay(100);
	// Potentially infinite loops are generally dangerous.
	// Add delays -- allowing the processor to perform other
	// tasks -- wherever possible.
	}
	Serial.println("WiFi connected");  
	Serial.println("IP address: ");
	Serial.println(wf.localIP());
	digitalWrite(LED_PIN, HIGH);
}
void MyWiFi::wifiRenew()
{
    if (wf.status() !=WL_CONNECTED)
    {
        ESP.restart();
    }
}
void MyWiFi::myTweet(String tweet)	//no spaces in string, must use "+" (eg tweet="Hello+World!")
{
	WiFiClient client; 
	if (client.connect("184.106.153.149", 80))
	{ 
		String getLine = "api_key="+_API_KEY+"&status="+tweet;
		client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
		client.print("Host: api.thingspeak.com\n");
		client.print("Connection: close\n");
		client.print("Content-Type: application/x-www-form-urlencoded\n");
		client.print("Content-Length: ");
		client.print(getLine.length());
		client.print("\n\n");
		client.print(getLine);
		client.stop();
		Serial.print("We tweeted:  ");
		Serial.println(tweet);
	}
}
void MyWiFi::myOTAsetup() {
    
  myOTA.setHostname("ESP8266");
  myOTA.setPassword("");

  myOTA.onStart([]() {
    Serial.println("Start");
  });
  myOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  myOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  myOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  myOTA.begin();
  Serial.println("OTA ready");
}
void MyWiFi::myOTAhandle() {
   myOTA.handle();
}
int * MyWiFi::IPstringtodigits(string IPaddress) {
    static int IPdigits[4];
    //for (int b=0;b<IPaddress.length();b++)
    //{
        //Serial.print(IPaddress[b]);
    //}
    replace( IPaddress.begin(), IPaddress.end(),'.',' ' );
    stringstream t(IPaddress);
    //Serial.print("We're converting string to digits ");
    //Serial.println(IPaddress);
    //Serial.println(t);
    for (int c=0; c<4; c++)
    {
        t >> IPdigits[c];
        //Serial.println(IPdigits[c]);
    }
    return IPdigits;
}
