#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <uri/UriGlob.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "WiFIManager.h"
#include "DNSManager.h"
#include "WebServer.h"
#include "WSocketManager.h"

#ifndef APSSID
#define APSSID "CardinalWaveAP"
#define APPSK "password"
#endif

const char *softAP_ssid = APSSID;
const char *softAP_password = APPSK;

const char *myHostname = "cardinalwave";

char ssid[33] = "CardinalWaveSV";
char password[65] = "serverPassword";

#define BEGIN_OF_PAD 0

// WiFi Manager
WiFiManager wiFiManager;

// DNS Manager
DNSManager dnsManager;

// Web server
WebServer webServer;

WiFiClient client = webServer.setupClient();
PubSubClient mqttClient(client);

// WebSocket Manager
WSocketManager socketManager;

/** Should I connect to WLAN asap? */
boolean connect;

/** Last time I tried to connect to WLAN */
unsigned long lastConnectTry = 0;

/** Current WLAN status */
unsigned int status = WL_IDLE_STATUS;

void createUser() {
  unsigned char number_client;
  unsigned char channel;
  struct station_info *stat_info;
  
  struct ip4_addr *IPaddress;
  IPAddress address;
  int cnt=1;
  
  number_client = wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();
  channel = wifi_get_channel();

  Serial.print("Connected clients: ");
  Serial.println(number_client);

  Serial.print("Channel: ");
  Serial.println(channel);

  Serial.print("DHCP - STATUS: ");
  Serial.println(wifi_station_dhcpc_status());
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Configuring access point...");

  wiFiManager.start();
  dnsManager.start();
  // socketManager.setup();
  // webServer.setup();
  Serial.println("HTTP server started");
}

void loop() {
  if (connect) {
    Serial.println("Connect requested");
    connect = false;
    wiFiManager.connect();
    lastConnectTry = millis();
  }
  {
    unsigned int s = WiFi.status();
    if (s == 0 && millis() > (lastConnectTry + 60000)) {
      /* If WLAN disconnected and idle try to connect */
      /* Don't set retry time too low as retry interfere the softAP operation */
      connect = true;
    }
    if (status != s) {  // WLAN status change
      Serial.print("Status: ");
      Serial.println(s);
      status = s;
      if (s == WL_CONNECTED) {
        /* Just connected to WLAN */
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    
        while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
        }

        Serial.println("Connected to Wi-Fi");
        // mqttClient.setServer(MQTT_HOST, MQTT_PORT);

        dnsManager.mdnsService();

      } else if (s == WL_NO_SSID_AVAIL) {
        WiFi.disconnect();
      }
    }
    if (s == WL_CONNECTED) { dnsManager.mdnsUpdate();  }
  }
  createUser();
  // // DNS
  dnsManager.processNextRequest();
  // HTTP
  webServer.handleClient();
  // WebSocket
  // socketManager.loop();
  // // MQTT
  // mqttClient.loop();
  
}