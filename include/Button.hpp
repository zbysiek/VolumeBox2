#pragma once

class Button{
private:
    int pin;

    bool raw_state;
    unsigned long toggle_time;
public:
    bool state;

    Button(int pin);

    void update();
    void print();
};