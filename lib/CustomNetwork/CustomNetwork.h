#ifndef CUSTOM_NETWORK_H
#define CUSTOM_NETWORK_H

#include <Arduino.h>
// #include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>

class CustomNetwork
{
public:
    CustomNetwork();
    void connectWiFi();
    void connectMQTT();
    void publishMessage(const char *message);
    void loop();
    // Fungsi untuk mereset konfigurasi WiFi dan reboot perangkat
    void resetNetwork();

private:
    WiFiClient espClient;
    PubSubClient client;
    WiFiManager wifiManager;
    void reconnectMQTT();
    static void configModeCallback(WiFiManager *myWiFiManager);
};

#endif
