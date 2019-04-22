#define PIN_PHOTO_SENSOR_DIGITAL D5
#define PIN_PHOTO_SENSOR_ANALOG A0

int koef = 5000; // Количество вспышек на 1 кВт
int val = 0;

volatile unsigned long impulseCounter = 0;
volatile unsigned long prevTime = 0;
volatile unsigned long currTime = 0;
volatile float currPower = 0;
volatile float power = 0;
volatile int state = 0;
volatile int currVal = 0;
volatile int prevVal = 0;

void setup() {
  Serial.begin(9600);
//  pinMode(PIN_PHOTO_SENSOR_DIGITAL, INPUT_PULLUP);
  pinMode(PIN_PHOTO_SENSOR_ANALOG, INPUT_PULLUP);
//  attachInterrupt (digitalPinToInterrupt (PIN_PHOTO_SENSOR_DIGITAL), blink, CHANGE);
}

void loop() {
  val = analogRead(PIN_PHOTO_SENSOR_ANALOG);
//  Serial.println(val);

  if ((val < 500) && (state == 0))
  {
    state = 1;
    impulseCounter++;
    prevTime = currTime;
    currTime = millis();
    };
  if ((val < 500) && (state == 0))
  {
    state = 1;
    impulseCounter++;
    }    
  if ((val > 500) && (state == 1))
  {
    state = 0;
    };


    
//  Serial.print(prevTime); Serial.print("   "); Serial.print(currTime); Serial.println("delta: "+(currTime-prevTime));
//  Serial.print(prevVal); Serial.print("   "); Serial.print(currVal); Serial.println("  "+state);
    Serial.println(impulseCounter);

  delay(20);
}
void blink()
{  
  prevTime = currTime;
  currTime = millis();
  
  if ((currTime - prevTime) > 150)
  {
    impulseCounter++;
//    currPower = (60 * 60) / (1000 * (currTime - prevTime) / koef);    
    };
}
