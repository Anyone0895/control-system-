#include <Arduino.h> //базовый набор команд Arduino
//#include <FastAccelStepper.h> //библиотека для управления шаговыми двигателями

//безопасные (зеленые) выходы пинов для моторов
#define X_STEP 25 //шаг
#define X_DIR  26 //направление
#define Y_STEP 27
#define Y_DIR  13

//такие же пины для концевиков
#define X_LIMIT 18 //концевик оси X
#define Y_LIMIT 19 //концевик оси Y

//пины датчиков только на вход
#define DIRT_PIN  34 //датчик влажности почвы
#define WATER_PIN 35 //датчик уровня воды в баке
#define PUMP_PIN  23 //реле насоса (зеленый пин)
#define ALARM_LED 2 //встроенный светодиод для сигнала аварии

const float shagi = ??? (80.0) //пересчет мм в шаги двигателя (тест)
int mmX = 10; //столько-то проехать по х 
int mmY = 10; //столько-то проехать по y

//пороги срабатывания датчиков (надо будет проверить значения)
int suho = 2500;  //если БОЛЬШЕ — земля сухая
int mokro = 1000; //если БОЛЬШЕ  — вода в баке есть

//Текущие координаты робота
float activeX = 0;
float activeY = 0;
//Исходная точка (дом), куда всегда будет возвращаться робот
const float homeX = 0;
const float homeY = 0;
//Возврат к исходному углу
const int X_HOME_DIR = LOW;   //нужно будет проверить, как поедет робот (поменять HIGH - LOW)
const int Y_HOME_DIR = LOW;

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

//задаем пины концевиков как входы с подтяжкой(не нажата HIGH, нажата LOW)
pinMode(X_LIMIT, INPUT_PULLUP);
pinMode(Y_LIMIT, INPUT_PULLUP);

//задаем пины датчиков как входы
pinMode(DIRT_PIN, INPUT);
pinMode(WATER_PIN, INPUT);

//задаем пин насоса как выход и выключаем его
pinMode(PUMP_PIN, OUTPUT);
digitalWrite(PUMP_PIN, LOW);

//задаем пин светодиода как выход (ошибка - воды в баке нет)
pinMode(ALARM_LED, OUTPUT);
digitalWrite(ALARM_LED, LOW); //при старте выключаем

//поиск исходного угла при включении
//едем по X в угол, пока кнопка не нажмется
  digitalWrite(X_DIR, X_HOME_DIR); //направление домой
  while (digitalRead(X_LIMIT) == HIGH) //пока кнопка X НЕ нажата
  {
    digitalWrite(X_STEP, HIGH);
    delayMicroseconds(500); 
    digitalWrite(X_STEP, LOW);
    delayMicroseconds(500);
  }
  activeX = homeX; //запоминаем, что мы в 0
  
//едем по Y в угол, пока кнопка не нажмется
  digitalWrite(Y_DIR, Y_HOME_DIR);
  while (digitalRead(Y_LIMIT) == HIGH) //пока кнопка Y НЕ нажата
  {
    digitalWrite(Y_STEP, HIGH);
    delayMicroseconds(500); 
    digitalWrite(Y_STEP, LOW);
    delayMicroseconds(500);
  }
  activeY = homeY; //запоминаем, что мы в 0
  delay(2000);
}

void loop() //повторяется бесконечно
{
//едем по оси X на s мм
digitalWrite(X_DIR, HIGH);
for (int i = 0; i < mmX * shagi; i++) //цикл шагов
{
    digitalWrite(X_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(X_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
 }
 activeX = activeX + mmX; //запомнили координату Х
    delay(2000); //пауза 2 секунды

//едем по оси Y вперед на s мм
  digitalWrite(Y_DIR, HIGH); //цикл шагов
  for (int i = 0; i < mmY * shagi; i++)
  {
    digitalWrite(Y_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(Y_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
  }
    activeY = activeY + mmY; //запомнили координату Y
    delay(2000); //пауза 2 секунды

//проверка датчиков и полив
int dirtValue = analogRead(DIRT_PIN);   //читаем влажность почвы
int waterValue = analogRead(WATER_PIN); //читаем уровень воды
if (waterValue > mokro && dirtValue > suho) //если вода есть И земля сухая
{
  digitalWrite(PUMP_PIN, HIGH); //включаем насос
  delay(4000); //поливаем 4 секунды
  digitalWrite(PUMP_PIN, LOW); //выключаем насос
}
  delay(2000); //пауза перед возвратом домой

//едем по оси X назад на s мм
  digitalWrite(X_DIR, X_HOME_DIR); //направление домой
  for (int i = 0; i < activeX * shagi; i++) //едем в точку дома по X
  {
    digitalWrite(X_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(X_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
  }
    activeX = homeX; //сбросили координату X в 0
    delay(2000); //пауза 2 секунды

//едем по оси Y назад на s мм
  digitalWrite(Y_DIR, Y_HOME_DIR); 
  for (int i = 0; i < activeY * shagi; i++) //едем в точку дома по Y
  {
    digitalWrite(Y_STEP, HIGH);
    delayMicroseconds(500); //скорость (тест скорость)
    digitalWrite(Y_STEP, LOW);
    delayMicroseconds(500); //(тест скорость)
  }
    activeY = homeY; //сбросили координату Y в 0
    delay(2000); //пауза 2 секунды
}
