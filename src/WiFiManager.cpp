#include <ESP8266WiFi.h>
#include "SecretKeys.h"
#include "WiFiManager.h"

WiFiManager::WiFiManager() {

    softAP_ssid = WIFI_SSID_AP;
    softAP_password = WIFI_PASSWORD_AP;
    server_ssid = WIFI_SSID_SERVER;
    server_password = WIFI_PASSWORD_SERVER;
    apIP = APIP;
    netMask = NETMASK;

}

void WiFiManager::start() {
    WiFi.softAPConfig(apIP, apIP, netMask);
    WiFi.softAP(softAP_ssid, softAP_password);
    delay(500);  // Without delay I've seen the IP address blank
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}

void WiFiManager::connect() {
    Serial.println("Connecting as wifi client...");
    // WiFi.disconnect();
    WiFi.begin(server_ssid, server_password);
    int connRes = WiFi.waitForConnectResult();
    Serial.print("connRes: ");
    Serial.println(connRes);  
}