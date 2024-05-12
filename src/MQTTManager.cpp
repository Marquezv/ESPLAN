#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SecretKeys.h"
#include "MQTTManager.h"

MQTTManager::MQTTManager(WiFiClient& client){

    mqtt_host = MQTT_HOST;
    mqtt_password = MQTT_PASSWORD;
    PubSubClient mqttClient(client);
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // webSocket.broadcastTXT(payload);
}

void MQTTManager::setup() {
    Serial.println("Connected to Wi-Fi");
    mqttClient.setServer("192.168.12.1", 1883);
    if (mqttClient.connect("ESP8266_001", "ESP8266_01", "ESP8266_01" )) {
        Serial.println("Connected to MQTT broker");
        mqttClient.setCallback(callback);
    } else {
        delay(500);
        Serial.print(".");
    }
}

// void MQTTManager::messageOverMqtt(const char *topic, const char *payload) {
//     mqttClient.connect("ESP8266_001", "ESP8266_01", "" );
//     mqttClient.publish(topic, payload);
//     Serial.printf("Send message on %s", topic);
//     Serial.println();
//     // mqttClient.disconnect();
// }
