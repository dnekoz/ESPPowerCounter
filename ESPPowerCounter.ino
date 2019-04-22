#define PIN_PHOTO_SENSOR_DIGITAL D5
int koef = 5000; // Количество вспышек на 1 кВт

volatile unsigned long impulseCounter = 0;
volatile unsigned long prevTime = 0;
volatile unsigned long currTime = 0;
volatile float currPower = 0;
volatile float power = 0;
volatile int state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_PHOTO_SENSOR_DIGITAL, INPUT);
  attachInterrupt (digitalPinToInterrupt (PIN_PHOTO_SENSOR_DIGITAL), blink, FALLING);
}

void loop() {
  Serial.print(impulseCounter); Serial.print("  ");
  Serial.println(currPower);
  delay(20);
}
void blink()
{
  prevTime = currTime;
  currTime = millis();
  if ((currTime - prevTime) > 75)
  {
    impulseCounter++;
    currPower = (60 * 60) / (1000 * (currTime - prevTime) / koef);
    };
}
