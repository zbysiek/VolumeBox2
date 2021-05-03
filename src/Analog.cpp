#include "Analog.hpp"
#include "ButtonBox.hpp"
#include "Arduino.h"

Analog::Analog(int pin){
    this->pin = pin;
    this->value = ANALOG_WINDOW;
    pinMode(pin, INPUT);
}

void Analog::update(){
    int raw_value = analogRead(pin);

    int window_up = value + ANALOG_WINDOW;
    int window_down = value - ANALOG_WINDOW;

    if(raw_value > window_up){
        value = raw_value - ANALOG_WINDOW;
    }else if (raw_value < window_down){
        value = raw_value + ANALOG_WINDOW;
    }
}

/*
void Analog::print(){
    Serial.print(value);
    Serial.print(' ');
}
*/