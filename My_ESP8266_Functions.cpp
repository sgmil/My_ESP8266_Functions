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

MyWiFi::MyWiFi(String deviceName, int lastThreeIP)
{
    _deviceName = deviceName;
    _lastThreeIP = lastThreeIP;
    pinMode(LED_PIN, OUTPUT); 
     
}
void MyWiFi::connectWiFi()
{	
	Serial.begin(115200);
	byte ledStatus = LOW;	
	Serial.println();
	Serial.println("Connecting to: " + String(_WiFiSSID));
	WiFi.hostname(_deviceName);
	IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
	IPAddress subnet(255, 255, 255, 0);  //Subnet mask
	IPAddress dns(8, 8, 8, 8);  //DNS
	IPAddress staticIP(192,168,0,_lastThreeIP); //ESP static ip 
	WiFi.config(staticIP,gateway,subnet,dns);
	// Set WiFi mode to station (as opposed to AP or AP_STA)
	WiFi.mode(WIFI_STA);
	// WiFI.begin([ssid], [passkey]) initiates a WiFI connection
	// to the stated [ssid], using the [passkey] as a WPA, WPA2,
	// or WEP passphrase.
	WiFi.begin(_WiFiSSID, _WiFiPSK);
	// Use the WiFi.status() function to check if the ESP8266
	// is connected to a WiFi network.
	while (WiFi.status() != WL_CONNECTED)
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
	Serial.println(WiFi.localIP());
	digitalWrite(LED_PIN, HIGH);
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
