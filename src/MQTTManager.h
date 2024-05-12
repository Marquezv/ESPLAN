#ifndef WSOCKET_MANAGER_H
#define WSOCKET_MANAGER_H
#include <Arduino.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

class MQTTManager {
    public:
        MQTTManager(WiFiClient& client);

        void setup();
        void subscribe();
        void publish();
    
        void loop();

    private:
        byte mqtt_port;
        const char *mqtt_host;
        const char *mqtt_password;
        PubSubClient mqttClient;
};
#endif