#include "CustomNetwork.h"
#include "config.h"
#include <WiFiManager.h>

CustomNetwork::CustomNetwork() : client(espClient) {}

// void CustomNetwork::connectWiFi()
// {
//     Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print(".");
//     }

//     Serial.println("\nWiFi connected!");
//     Serial.print("IP Address: ");
//     Serial.println(WiFi.localIP());
// }

void CustomNetwork::connectWiFi()
{
    Serial.println("Menghubungkan ke WiFi menggunakan WiFiManager...");

    // Buat instance WiFiManager
    // WiFiManager wifiManager;

    // (Opsional) Aktifkan debug output
    wifiManager.setDebugOutput(true);

    // Set callback AP (optional)
    wifiManager.setAPCallback(configModeCallback);

    // Jika autoConnect gagal dalam waktu tertentu, perangkat akan reboot
    if (!wifiManager.autoConnect("MAK Smart PSU", "12345678"))
    {
        Serial.println("Gagal terkoneksi ke WiFi, reboot...");
        delay(3000);
        ESP.restart();
        delay(5000);
    }

    // Jika autoConnect berhasil, WiFiManager sudah menyimpan konfigurasi di flash
    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Callback ketika konfigurasi berhasil (optional)
void CustomNetwork::configModeCallback(WiFiManager *myWiFiManager)
{
    myWiFiManager->setDarkMode(true);
    myWiFiManager->setTitle("Setup Connection");
    std::vector<const char *> menu = {"wifi", "exit"};
    // std::vector<const char *> menu = {"wifi", "setup", "sep", "info", "exit"};
    myWiFiManager->setMenu(menu);
    myWiFiManager->setHostname("mak-cms.com/smart-psu");
    myWiFiManager->setConfigPortalBlocking(true);
    myWiFiManager->setCountry("ID");

    Serial.println("Masuk ke Mode AP!");
    Serial.print("SSID AP: ");
    Serial.println(myWiFiManager->getConfigPortalSSID());
}

void CustomNetwork::connectMQTT()
{
    client.setServer(MQTT_BROKER, MQTT_PORT);
    reconnectMQTT();
}

void CustomNetwork::reconnectMQTT()
{
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT... ");
        if (client.connect("ESP32_Client"))
        {
            Serial.println("Connected!");
        }
        else
        {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void CustomNetwork::publishMessage(const char *message)
{
    client.publish(MQTT_TOPIC, message);
}

void CustomNetwork::loop()
{
    client.loop();
}

// Fungsi untuk reset konfigurasi WiFi dan reboot perangkat
void CustomNetwork::resetNetwork()
{
    Serial.println("Mereset konfigurasi WiFi...");
    // Buat instance WiFiManager untuk mengakses fungsi reset
    wifiManager.resetSettings(); // Hapus konfigurasi WiFi yang tersimpan
    Serial.println("Konfigurasi WiFi dihapus, perangkat akan reboot...");
    delay(2000);
    ESP.restart();
}