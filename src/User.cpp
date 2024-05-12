#include <ESP8266WiFi.h>
#include "SecretKeys.h"
#include "User.h"

User::User(IPAddress ip, uint8_t num, String sessionId, uint8_t *mac) {
    ip = ip;
    num = num;
    sessionId = sessionId;
    mac = mac;
}

void User::send() {}

void User::receive() {}