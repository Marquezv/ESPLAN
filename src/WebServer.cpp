#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "LittleFS.h" 
#include "SecretKeys.h"
#include "WebServer.h"

ESP8266WebServer server(80);
HTTPClient http;
WiFiClient wifiClient;

WebServer::WebServer() {}

/** Is this an IP? */
boolean WebServer::isIp(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) { return false; }
  }
  return true;
}

boolean WebServer::captivePortal(String header) {
    Serial.println(server.hostHeader());
    if (!isIp(header) && server.hostHeader() != (String(HOSTNAME) + ".net")) {
        Serial.println("Request redirected to captive portal");
        server.sendHeader("Location", String("http://") + (String(HOSTNAME) + ".net"), true);
        server.send(302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
        server.client().stop();              // Stop is needed because we sent no content length
        return true;
    }
    return false;
}

void WebServer::handleRoot() {
    String payload = "<h1>Reconetando</h1>";
    if (captivePortal(server.hostHeader())) {
        return;
    }
    server.sendHeader("Cache-Control", "public");
    // server.sendHeader("Pragma", "no-cache");
    // server.sendHeader("Expires", "-1");
    http.begin(wifiClient, "http://cardinalwave.net");
    int httpCode = http.GET();
    if(httpCode > 0 || httpCode != -1) {
        payload = http.getString();
        server.send(200, "text/html", payload);
    }
    server.send(200, "text/html", payload);

}

void WebServer::handleNotFound() {
    if (captivePortal(server.hostHeader())) {  // If caprive portal redirect instead of displaying the error page.
        return;
    }
    String message = F("File Not Found\n\n");
    message += F("URI: ");
    message += server.uri();
    message += F("\nMethod: ");
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += F("\nArguments: ");
    message += server.args();
    message += F("\n");

    for (uint8_t i = 0; i < server.args(); i++) { message += String(F(" ")) + server.argName(i) + F(": ") + server.arg(i) + F("\n"); }
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.send(404, "text/plain", message);
}

void WebServer::setup() {
    String payload;
    http.begin(wifiClient, "http://cardinalwave.net");
    int httpCode = http.GET();
    if(httpCode > 0 || httpCode != -1) {
        payload = http.getString();
        server.send(200, "text/html", payload);
    }
    server.on("/", handleRoot);
    server.onNotFound(handleNotFound); 
    server.begin();  // Web server start
}

WiFiClient& WebServer::setupClient() {
    return wifiClient;
}

void WebServer::handleClient() {
    server.handleClient();
}