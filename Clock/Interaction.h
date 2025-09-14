#pragma once
#include "Timer.h"
extern enum TimerStatus Status;

class Interaction {
private:
    ExMessage Key;
    char Num;
    int Time = 0;
    int hi, mi, si;
    std::string Input = "";
    InputState input_state = HOR;
public:
    void GetInput(ExMessage msg);
    void HandleInputA();
    void HandleInputB();
    InputState GetInputState();
    void ReturnInput(int& time);
};