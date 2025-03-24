#ifndef MQTT_H
#define MQTT_H

typedef enum tipoMensagemMQTT
{
    Posicao_X=0,
    Posicao_Y=1,
    ContribuicaoP_X=2,
    ContribuicaoI_X=3,
    ContribuicaoD_X=4,
    ContribuicaoP_Y=5,
    ContribuicaoI_Y=6,
    ContribuicaoD_Y=7,
    Velocidade_X=8,
    Velocidade_Y=9
};

void connectToBroker();
void reconnect();
void sendMessageToBroker(float value, tipoMensagemMQTT type);

#endif