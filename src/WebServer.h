#ifndef WEB_SERVER_H
#include <WiFiClient.h>
#define WEB_SERVER_H

class WebServer {
    public:
        WebServer();

        void setup();
        void handleClient();
        WiFiClient& setupClient();

    private:
        static void handleRoot();
        static void handleNotFound();
        static boolean captivePortal(String header);
        static boolean isIp(String str);
};     
#endif