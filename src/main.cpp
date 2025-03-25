#include <Arduino.h>
#include "menu.h"
#include "camera.h"
#include "display.h"
#include "servoControl.h"
#include "PIDControl.h"
#include "mqttConnect.h"
#include <freertos/FreeRTOS.h>

SemaphoreHandle_t PIDX_mutex = xSemaphoreCreateMutex();

SemaphoreHandle_t PIDY_mutex = xSemaphoreCreateMutex();

SemaphoreHandle_t ballX_mutex = xSemaphoreCreateMutex();

SemaphoreHandle_t ballY_mutex = xSemaphoreCreateMutex();


void parallelTask(void* pvParameters){
  TickType_t time;
  const TickType_t freq = 1000;
  time = xTaskGetTickCount();

  int velX;
  int velY;
  int posX;
  int posY;
  int PX;
  int PY;
  int IX;
  int IY;
  int DX;
  int DY;

  while (1)
  {  
    xSemaphoreTake( ballX_mutex, 10 );
    posX = ballX;
    xSemaphoreGive( ballX_mutex );
    sendMessageToBroker(posX, Posicao_X);
    
    xSemaphoreTake( PIDX_mutex, 10 );
    velX = getVel(&PIDX);
    xSemaphoreGive( PIDX_mutex );
    sendMessageToBroker(velX, Velocidade_X);
    
    xSemaphoreTake( PIDX_mutex, 10 );
    PX = getPVal(&PIDX);
    xSemaphoreGive( PIDX_mutex );
    sendMessageToBroker(PX, ContribuicaoP_X);
    
    xSemaphoreTake( PIDX_mutex, 10 );
    IX = getIVal(&PIDX);
    xSemaphoreGive( PIDX_mutex );
    sendMessageToBroker(IX, ContribuicaoI_X);
    
    xSemaphoreTake( PIDX_mutex, 10 );
    DX = getDVal(&PIDX);
    xSemaphoreGive( PIDX_mutex );
    sendMessageToBroker(DX, ContribuicaoD_X);
    
    xSemaphoreTake( ballY_mutex, 10 );
    posY = ballY;
    xSemaphoreGive( ballY_mutex );
    sendMessageToBroker(posY, Posicao_Y);
    
    xSemaphoreTake( PIDY_mutex, 10 );
    velY = getVel(&PIDY);
    xSemaphoreGive( PIDY_mutex );
    sendMessageToBroker(velY, Velocidade_Y);
    
    xSemaphoreTake( PIDY_mutex, 10 );
    PY = getPVal(&PIDY);
    xSemaphoreGive( PIDY_mutex );
    sendMessageToBroker(PY, ContribuicaoP_Y);
    
    xSemaphoreTake( PIDY_mutex, 10 );
    IY = getIVal(&PIDY);
    xSemaphoreGive( PIDY_mutex );
    sendMessageToBroker(IY, ContribuicaoI_Y);
    
    xSemaphoreTake( PIDY_mutex, 10 );
    DY = getDVal(&PIDY);
    xSemaphoreGive( PIDY_mutex );
    sendMessageToBroker(DY, ContribuicaoD_Y);

    xTaskDelayUntil(&time, freq);
  }
}

//int lastErrorsX [3];
//int lastErrorsY [3];

void setup() {
  delay(500);
  setupServos();

  Serial.begin(9600);
  Serial.println("Serial begun");
  setupMainMenu();
  setupCamera();

  connectToBroker();

  setupLCD();

  xTaskCreatePinnedToCore( parallelTask,"parallelTask",50000,NULL,    1,    NULL,    1  );

// int i = 0;
// for (i=0; i<3; i++)
// {
//   lastErrorsX[i] = 0;
//   lastErrorsY[i] = 0;
// }

  sei();
}

int setPointX = 156;//160
int setPointY = 116;//120

void loop() {
  static unsigned short int errorIdx = 0;
  int errorX;
  int valX;
  int errorY;
  int valY;

  switch(updateBallPosition())
  {
    case REQUEST_FAIL:
      Serial.println("Failed to request object data");
      Serial.println("Check camera connection");
      //displayDebugText(L1, "REQUEST FAIL");
      break;

    case NOT_LEARNED:
      Serial.println("Camera has not learned an object");
      Serial.println("Learn an object first");
      //displayDebugText(L1, "NOT LEARNED");
      break;

    case NO_OBJECT:
      Serial.println("No object found");
      //updateServo(&servoX, INI_ANG_MS);
      //updateServo(&servoY, INI_ANG_MS);
      //displayDebugText(L1, "NO OBJECT");
      break;

    case UPDATE_SUCCESS:
    {
      Serial.print("X:");
      Serial.print(ballX);
      Serial.print(" Y:");
      Serial.println(ballY);

      //xSemaphoreTake( ballX_mutex, 10 );
      //lastErrorsX[errorIdx] = setPointX - ballX;
      errorX = -1*( setPointX - ballX );
      xSemaphoreGive( ballX_mutex );
  
      xSemaphoreTake( PIDX_mutex, 1 );
      calcPID(&PIDX, errorX);
      xSemaphoreGive( PIDX_mutex );
      
      xSemaphoreTake( PIDX_mutex, 1 );
      valX = remapPID(&PIDX, MIN_ANG_MS+X_BIAS, MAX_ANG_MS+X_BIAS);
      xSemaphoreGive( PIDX_mutex );

      xSemaphoreTake( ballY_mutex, 10 );
      //lastErrorsY[errorIdx] = setPointY - ballY;
      //errorIdx = (errorIdx+1)%3;
      errorY = setPointY - ballY;
      xSemaphoreGive( ballY_mutex );  
  
      xSemaphoreTake( PIDY_mutex, 1 );
      calcPID(&PIDY, errorY);
      xSemaphoreGive( PIDY_mutex );
      
      xSemaphoreTake( PIDY_mutex, 1 );
      valY = remapPID(&PIDY, MIN_ANG_MS+Y_BIAS, MAX_ANG_MS+Y_BIAS);
      xSemaphoreGive( PIDY_mutex );
      
      updateServo(&servoX, valX);
      updateServo(&servoY, valY);

      
      Serial.print("P:");
      Serial.print(getPVal(&PIDX));
      Serial.print("   I:");
      Serial.print(getIVal(&PIDX));
      Serial.print("   D:");
      Serial.println(getDVal(&PIDX));
      Serial.print("PIDval:");
      Serial.println(getPIDVal(&PIDX));
      Serial.print("Convertion:");
      Serial.println(valX);
      
      break;
    }
    default:
    {
      // Serial.println("Unknown error!");  
    }
  }
  reconnect();
  
}
