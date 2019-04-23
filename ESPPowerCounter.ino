#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Библиотека отсюда https://github.com/johnrickman/LiquidCrystal_I2C/archive/master.zip


#define PIN_PHOTO_SENSOR_DIGITAL D5 // Пин куда подключен цифровой выход датчика света

int koef = 5000; // Количество вспышек на 1 кВт

volatile unsigned long impulseCounter = 0; // Счетчик импульсов
volatile unsigned long prevTime = 0;       // Время предыдущей вспышки
volatile unsigned long currTime = 0;       // Время текущей вспышки
volatile float freq = 0;                   // Частота вспышек
volatile float currPower = 0;              // Мгновенная мощность
float power = 0;                           // Общее энергопотребление до перезагрузки

/* Подключение дисплея:
ESP (NodeMCU)| LCD 1602
-------------|-----------
     VU      | VCC
     GND     | GND
     SDA     | D2
     SDL     | D1
*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(PIN_PHOTO_SENSOR_DIGITAL, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt (PIN_PHOTO_SENSOR_DIGITAL), blink, FALLING);
}

void loop() {
  
  if ((millis() - prevTime) > 3000) { // Если не было миганий больше 3 секунд, то мощность = 0
    freq = 0;         // Частота мигания = 0
    currPower = 0;    // Получим значеение мгновенной мощности в кВт = 0
    }
  Serial.print(impulseCounter);Serial.print("  ");Serial.print(freq,3); Serial.print("  "); Serial.print(currPower,3); Serial.print("  "); Serial.println((float)impulseCounter/koef,3);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(impulseCounter);
  lcd.setCursor(0, 1);
  lcd.print(impulseCounter/koef);
  
  delay(1000); // Статус 1 раз в секунду
}

void blink()
{  
  prevTime = currTime;
  currTime = millis();  
  if ((currTime - prevTime) > 10) // Чуть избавимся от "дрожания"
  {
    impulseCounter++;
    freq = (float)1000/(currTime-prevTime); // Частота мигания
    currPower = (float)(freq*3600/koef);    // Получим значеение мгновенной мощности в кВт
    };
}
