#include <Arduino.h> //базовый набор команд Arduino
#include <FastAccelStepper.h> //библиотека для управления шаговыми двигателями

//безопасные (зеленые) выходы пинов для моторов
#define X_STEP 25 
#define X_DIR  26
#define Y_STEP 27
#define Y_DIR  13

float shagi = ??? (80.0) //пересчет мм в шаши двигателя (тест)

FastAccelStepperEngine motorEngine = FastAccelStepperEngine(); //движок для управления моторами
FastAccelStepper *motorX = NULL; //мотор оси Х (пока 0)
FastAccelStepper *motorY = NULL; //мотор оси Y (пока 0)
