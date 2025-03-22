#ifndef MQTT_H
#define MQTT_H

typedef enum tipoMensagemMQTT
{
    Posicao_X=0,
    Posicao_Y=1,
    Controle_P=2,
    Controle_I=3,
    Controle_D=4,
    Velocidade=5
};

void connectToBroker();
void reconnect();
void sendMessageToBroker(float value, tipoMensagemMQTT type);

#endif