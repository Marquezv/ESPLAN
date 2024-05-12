#ifndef SECRET_KEYS_H
#define SECRET_KEYS_H
#include <Arduino.h>

#define WIFI_SSID_SERVER "CardinalWaveSV"
#define WIFI_PASSWORD_SERVER "serverPassword"

#define WIFI_SSID_AP "CardinalWaveAP"
#define WIFI_PASSWORD_AP "password"

#define APIP IPAddress(172, 217, 28, 1);
#define NETMASK IPAddress(255, 255, 255, 0);

#define HOSTNAME "cardialwave"
#define MQTT_HOST "192.168.12.1";
#define MQTT_PORT 1883;
#define MQTT_CLIENT_ID "ESP8266_001";
#define MQTT_USER "ESP8266_01";
#define MQTT_PASSWORD "";
#define TOPIC "esp8266_01"
#define TOPIC_SERVER "server"

#endif // SECRET_KEYS_H
