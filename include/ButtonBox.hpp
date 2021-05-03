#pragma once

const int DEBOUNCE_TIME = 20;
const int ANALOG_WINDOW = 3;
const int ANALOG_MIN = 1023 - ANALOG_WINDOW;
const int ANALOG_MAX = 0 + ANALOG_WINDOW;

#include "Button.hpp"
#include "MatrixButton.hpp"
#include "Analog.hpp"