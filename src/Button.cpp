#include "Button.hpp"
#include "ButtonBox.hpp"

#include "Arduino.h"

Button::Button(int pin){
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

void Button::update(){
    raw_state = !digitalRead(pin);

    if(state != raw_state){
        unsigned long toggle_dtime = millis() - toggle_time;
        if(
            raw_state ||
            (toggle_dtime > DEBOUNCE_TIME)
        ){
            state = raw_state;
        }
        toggle_time = millis();
    }

}

/*
void Button::print(){
    Serial.print(state);
    Serial.print(' ');
}
*/