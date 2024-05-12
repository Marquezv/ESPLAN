#ifndef USER_H
#define USER_H
#include <ESP8266WiFi.h>
#include <Arduino.h>

class User {
    public:
        User(IPAddress ip, uint8_t num, String sessionId, uint8_t *mac);

        void setup();
        void send();
        void receive();

    private: 
        IPAddress ip;
        uint8_t num;
        String sessionId;
};
#endif