#include "mqttConnect.h"
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

using namespace std;

static WiFiClient espClient;
static PubSubClient client(espClient);
static const char *mqtt_server = "172.21.30.66"; // local host IP of this machine.
static const char *port = "1883";                // port in which mqtt broker is being hosted.

void connectToBroker()
{
    const char *ssid = "REPLACE-WTIH-SSID";      // ssid used to connect to desired wifi network
    const char *psswd = "REPLACE-WITH-PASSWORD"; // password used to connect to desired wifi network

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, psswd);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_server, 1883);
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client"))
        {
            Serial.println("connected");
            // Subscribe
            client.subscribe("ESP32/TopicoMesa");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void sendMessageToBroker(float value, tipoMensagemMQTT type)
{
    // Convert the value to a char array
    char valueString[8];
    dtostrf(value, 1, 2, valueString);

    if(type == Posicao_X)
    {   
        client.publish("ESP32Mesa/PosicaoX",valueString);
    }
    else if(type == Posicao_Y)
    {
        client.publish("ESP32Mesa/PosicaoY",valueString);
    }
    else if(type == Controle_P)
    {
        client.publish("ESP32Mesa/ControleP",valueString);
    }
    else if(type == Controle_I)
    {
        client.publish("ESP32Mesa/ControleI",valueString);
    }
    else if(type == Controle_D)
    {
        client.publish("ESP32Mesa/ControleD",valueString);
    }
    else
    {
        client.publish("ESP32Mesa/Velocidade",valueString);
    }
}