#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H


class WiFiManager {
    public:
        WiFiManager();

        void start();
        void connect();
    private: 
        const char *softAP_ssid;
        const char *softAP_password;

        const char *server_ssid;
        const char *server_password;

        IPAddress apIP;
        IPAddress netMask;
};
#endif