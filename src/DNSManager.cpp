#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include "SecretKeys.h"
#include "DNSManager.h"

DNSServer dnsServer;

DNSManager::DNSManager() {
    
    dns_port = 53;
    apIP = APIP;
    hostname = HOSTNAME;
}

void DNSManager::start() {

    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(dns_port, "*", apIP);
}

void DNSManager::processNextRequest() {

   dnsServer.processNextRequest();
}

void DNSManager::mdnsService() {
   
    if (!MDNS.begin(hostname)) {
        Serial.println("Error setting up MDNS responder!");
    } else {
        Serial.println("mDNS responder started");
        // Add service to MDNS-SD
        MDNS.addService("http", "tcp", 80);
    }
}

void DNSManager::mdnsUpdate() {
    MDNS.update();
}
