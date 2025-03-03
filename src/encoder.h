#ifndef ENCODER_H
#define ENCODER_H

void changeLeftCalback(void (*leftCallback)(void));
void changeRightCalback(void (*rightCallback)(void));
void changePressCalback(void (*pressCallback)(void));

void setupEncoder();
#endif