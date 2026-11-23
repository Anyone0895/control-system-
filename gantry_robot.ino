#include <Arduino.h> //базовый набор команд Arduino
//#include <FastAccelStepper.h> //библиотека для управления шаговыми двигателями

//безопасные (зеленые) выходы пинов для моторов
#define X_STEP 25 //шаг
#define X_DIR  26 //направление
#define Y_STEP 27
#define Y_DIR  13

const float shagi = ??? (80.0) //пересчет мм в шаги двигателя (тест)
int mm = 10; //расстояние (s), которое нужно будет проехать

//Текущие координаты робота
float activeX = 0;
float activeY = 0;
//Исходная точка (дом), куда всегда будет возвращаться робот
const float homeX = 0;
const float homeY = 0;
//Возврат к исходному углу
const int X_HOME_DIR = LOW;   //нужно будет проверить, как поедет робот (поменять HIGH - LOW)
const int Y_HOME_DIR = HIGH;

//FastAccelStepperEngine motorEngine = FastAccelStepperEngine(); //движок для управления моторами
//FastAccelStepper *motorX = NULL; //мотор оси Х (пока 0)
//FastAccelStepper *motorY = NULL; //мотор оси Y (пока 0)

void setup() //повторяется один раз при включении
{
//задаем пины мотора X как выходы
pinMode(X_STEP, OUTPUT);
pinMode(X_DIR, OUTPUT);
//задаем пины мотора Y как выходы
pinMode(Y_STEP, OUTPUT);
pinMode(Y_DIR, OUTPUT);
}

void loop() //повторяется бесконечно
{
//едем по оси X на s мм
digitalWrite(X_DIR, HIGH);
for (int i = 0; i < mm * shagi; i++) //цикл шагов
{
    digitalWrite(X_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(X_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
 }
    delay(2000); //пауза 2 секунды

//едем по оси Y вперед на s мм
  digitalWrite(Y_DIR, HIGH); //цикл шагов
  for (int i = 0; i < mm * shagi; i++)
  {
    digitalWrite(Y_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(Y_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
  }
    delay(2000); //пауза 2 секунды

//едем по оси X назад на s мм
  digitalWrite(X_DIR, LOW); //направление назад
  for (int i = 0; i < mm * shagi; i++) //цикл шагов
  {
    digitalWrite(X_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(X_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
  }
    delay(2000); //пауза 2 секунды

//едем по оси Y назад на s мм
  digitalWrite(Y_DIR, LOW); //направление назад
  for (int i = 0; i < mm * shagi; i++) //цикл шагов
  {
    digitalWrite(Y_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(Y_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
  }
    delay(2000); //пауза 2 секунды
}
