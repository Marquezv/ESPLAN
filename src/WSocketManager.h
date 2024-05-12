#ifndef WSOCKET_MANAGER_H
#define WSOCKET_MANAGER_H
#include <Arduino.h>

class WSocketManager {
    public:
        WSocketManager();

        void setup();
        void broadcast();
        void unicast();

        void loop();

        const char **listSessions(); 
    private: 
        const char *topic_mqtt;
        const char *topic_server_mqtt;
        byte wsocket_port;

};
#endif