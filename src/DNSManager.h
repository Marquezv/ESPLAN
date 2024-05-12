#ifndef DNS_MANAGER_H
#define DNS_MANAGER_H

#include <Arduino.h>

class DNSManager {
    public:
        DNSManager();

        void start();
        void processNextRequest();
        void mdnsService();
        void mdnsUpdate();

    private: 
        byte dns_port;
        IPAddress apIP;
        IPAddress netMask;
        const char * hostname;
};
#endif