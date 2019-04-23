#define PIN_PHOTO_SENSOR_DIGITAL D5

int koef = 5000; // Количество вспышек на 1 кВт

volatile unsigned long impulseCounter = 0; // Счетчик импульсов
volatile unsigned long prevTime = 0; // Время предыдущей вспышки
volatile unsigned long currTime = 0; // Время текущей вспышки
volatile float freq = 0;             // Частота вспышек
volatile float currPower = 0;        // Мгновенная мощность
float power = 0;                     // Общее энергопотребление до перезагрузки

void setup() {
  Serial.begin(9600);
  pinMode(PIN_PHOTO_SENSOR_DIGITAL, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt (PIN_PHOTO_SENSOR_DIGITAL), blink, RISING);
}

void loop() {
  
  if ((millis() - prevTime) > 3000) { // Если не было миганий больше 3 секунд, то мощность = 0
    freq = 0;         // Частота мигания = 0
    currPower = 0;    // Получим значеение мгновенной мощности в кВт = 0
    }
  Serial.print(impulseCounter);Serial.print("  ");Serial.print(freq,3); Serial.print("  "); Serial.print(currPower,3); Serial.print("  "); Serial.println((float)impulseCounter/koef,3);
  delay(1000); // Статус 1 раз в секунду
}

void blink()
{  
  prevTime = currTime;
  currTime = millis();  
  if ((currTime - prevTime) > 10)
  {
    impulseCounter++;
    freq = (float)1000/(currTime-prevTime); // Частота мигания
    currPower = (float)(freq*3600/koef);    // Получим значеение мгновенной мощности в кВт
    };
}
