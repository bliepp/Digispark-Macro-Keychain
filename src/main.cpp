#include <Arduino.h>
#include <DigiKeyboard.h>


bool last_state;
long last_time;


void btn_pressed(){
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  DigiKeyboard.sendKeyStroke(0);

  // ALT + ESC switches between previous window and current window
  // CHANGES HERE
  DigiKeyboard.sendKeyStroke(KEY_ESC, MOD_ALT_LEFT);
}


void setup() {
  last_state = false;
  last_time = 0;

  pinMode(2, INPUT_PULLUP);
}

void loop() {
  // manual debounce
  long new_time = millis();
  if (new_time - last_time > 100){
    bool new_state = !digitalRead(2);
    if (!last_state && new_state){
      btn_pressed();
    }
    last_state = new_state;
    last_time = new_time;
  }
}
