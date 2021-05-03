#pragma once

#include <stdint.h>

class Analog{
private:
    int pin;
public:
    int16_t value;

    Analog(int pin);

    void update();
    void print();
};