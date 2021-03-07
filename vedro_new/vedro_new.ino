/*
  Created 2016
  by AlexGyver
  AlexGyver Home Labs Inc.
*/

#include <Servo.h>   //используем библиотеку для работы с сервоприводом
Servo servo;     //объявляем переменную servo типа Servo
int trigPin = 6;    //Триггер
int echoPin = 7;    //Эхо
long duration, dist, average;   //переменные
int flag = 0; //флажок для кнопки
long aver[3];   //массив для расчёта среднего арифметического

void setup() {
  servo.attach(5);  //серво на 5 порту
  pinMode(3, INPUT_PULLUP); //кнопка
  pinMode(trigPin, OUTPUT);  //пин триггера в режиме выхода
  pinMode(echoPin, INPUT);  //пин эхо в режиме входа
  servo.write(180);         //при подключении питания поставить крышку открытой
}

void measure() {  //блок, измеряющий расстояние
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1;  //получаем расстояние с датчика
}

void loop() {

  if (!digitalRead(3) == 1 && flag == 0) { //если нажимаем кнопку
    servo.write(180);  //открыть крышку
    delay(1000);       //подождать 3.5  секунды
    flag = 1;           //ставим флажок, что кнопка нажата
  }

  if (!digitalRead(3) == 0 && flag == 1) {
    servo.write(3);    //закрыть крышку
    delay(1000);      //подождать секунду
    flag = 0;         //снимаем флажок
  }

  if (flag == 0) {
    for (int i = 0; i <= 2; i++) { //заполняем массив тремя измерениями
      measure();               //измерить расстояние, получаем dist
      aver[i] = dist;          //присваиваем значение dist элементу массива с номером i
      delay(50);              //рекомендуемая задержка между измерениями
    }
    dist = (aver[0] + aver[1] + aver[2]) / 3; //расчёт среднего арифметического с 3-х измерений
  }

  if (dist > 10 && dist < 30 && flag == 0) { //если рука от 10 до 30 см, кнопка не нажата
    servo.write(180);  //открыть крышку
    delay(10000);       //подождать 10  секунд
    servo.write(3);    //закрыть крышку
    delay(1000);      //подождать секунду
  }

  if (dist > 30 && dist < 60 && flag == 0) { //если рука от 30 до 60 см, кнопка не нажата
    servo.write(180);  //открыть крышку
    delay(2500);       //подождать 2,5  секунды
    servo.write(3);    //закрыть крышку
    delay(1000);      //подождать секунду
  }

}
