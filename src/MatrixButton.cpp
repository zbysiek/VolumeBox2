#include "MatrixButton.hpp"
#include "ButtonBox.hpp"

#include "Arduino.h"

MatrixButton::MatrixButton(int pinColumn, int pinRow){
    this->pinColumn = pinColumn;
    this->pinRow = pinRow;

    pinMode(pinColumn, INPUT);
    pinMode(pinRow, INPUT);
}

void MatrixButton::update(){
    pinMode(pinColumn, OUTPUT);
    pinMode(pinRow, INPUT_PULLUP);
    digitalWrite(pinColumn, LOW);

    raw_state = !digitalRead(pinRow);

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

    pinMode(pinColumn, INPUT);
    pinMode(pinRow, INPUT);
}

/*
void MatrixButton::print(){
    Serial.print(state);
    Serial.print(' ');
}
*/
