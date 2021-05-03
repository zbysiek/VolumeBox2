#pragma once

class MatrixButton{
private:
    int pinRow;
    int pinColumn;

    bool raw_state;
    unsigned long toggle_time;
public:
    bool state;

    MatrixButton(int pinColumn, int pinRow);

    void update();
    void print();
};