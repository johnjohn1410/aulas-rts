#include <Arduino.h>

static const int LED_PIN = 2;
static const int BTN_PIN = 4;

// Estado do â€œmodoâ€ (muda a velocidade da tarefa do LED)
static bool fastMode = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
}

// â€œTaskâ€ A: LED periÃ³dico (200ms ou 80ms)
void led_timing(bool mode, unsigned long now) {
  static unsigned long lastLed = 0;
  unsigned long ledPeriod = mode ? 80 : 200;

  if(now - lastLed >= ledPeriod){
    lastLed = now; 
    digitalWrite(LED_PIN,!digitalRead(LED_PIN));
  } 
}

// â€œTaskâ€ B: log a cada 1000ms
void log_alive(unsigned long now) {
  static unsigned long lastLog = 0;
  if(now - lastLog >= 1000){
    lastLog = now;
    Serial.printf("[loop] modo = %s, \n", fastMode ? "fast":"normal");
  
}
}

// â€œTaskâ€ C: polling do botÃ£o (com debounce)
void button_press() {
  if (digitalRead(BTN_PIN) == LOW) {   // apertou
    delay(50);
    if (digitalRead(BTN_PIN) == LOW) {
        fastMode = !fastMode;
        Serial.printf("[btn] modo = %s, \n", fastMode ? "fast":"normal");
        while(digitalRead(BTN_PIN) == LOW){}
      }
    delay(50);
  }
}

void loop() {
  unsigned long now = millis();

  button_press();
  led_timing(fastMode, now);
  log_alive(now);
}
