// Otc 23 2020
// Author: Thuy Huy Nguyen

// inputs
#define PIN_IN_SIGNAL_POWER         11  // send power out for sensing
#define PIN_IN_SIGNAL_LEFT          10
#define PIN_IN_SIGNAL_RIGHT         12

// outputs
#define PIN_LED                     13 // D13: same as built in LED
#define PIN_OUT_SIGNAL_LEFT         4  // D4
#define PIN_OUT_SIGNAL_RIGHT        5  // D5
#define PIN_OUT_SIGNAL_BLINK        13 // 13


// blink without delay:
const long blinkInterval = 250;         // interval at which to blink (milliseconds)
unsigned long previousMillis = 0;       // will store last time LED was updated
int ledState = LOW;                     // ledState used to set the LED

unsigned long currentMillis = millis();

void setup() {
  pinMode(PIN_IN_SIGNAL_LEFT, INPUT);
  pinMode(PIN_IN_SIGNAL_RIGHT, INPUT);

  pinMode(PIN_IN_SIGNAL_POWER, OUTPUT);

  pinMode(PIN_OUT_SIGNAL_LEFT, OUTPUT);
  pinMode(PIN_OUT_SIGNAL_RIGHT, OUTPUT);
  pinMode(PIN_OUT_SIGNAL_BLINK, OUTPUT);

  Serial.begin(19200);
  delay(1000);
  Serial.println("xbike nano started !");
}

void loop() {
  digitalWrite(PIN_IN_SIGNAL_POWER, HIGH);

  blinkSignal();
}

void blinkSignal(){
  currentMillis = millis();

  if (currentMillis - previousMillis >= blinkInterval) {
    Serial.println("Timer checking...");
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    bool inLeft = digitalRead(PIN_IN_SIGNAL_LEFT);
    bool inRight = digitalRead(PIN_IN_SIGNAL_RIGHT);

    digitalWrite(PIN_OUT_SIGNAL_BLINK, ledState);

    if(inLeft){
      digitalWrite(PIN_OUT_SIGNAL_LEFT, ledState);
      Serial.println("LEFT activated: " + String(ledState));
    }
    else
      digitalWrite(PIN_OUT_SIGNAL_LEFT, LOW);

    if(inRight){
      digitalWrite(PIN_OUT_SIGNAL_RIGHT, ledState);
      Serial.println("RIGHT activated: " + String(ledState));
    }
    else
      digitalWrite(PIN_OUT_SIGNAL_RIGHT, LOW);
  }
}
