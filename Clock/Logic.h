#pragma once
#include "Timer.h"
extern enum TimerStatus Status;

class TimerLogic {
private:
    TimerMode Mode = COUNT_DOWN;
    int TotalSec = 0;
    int PauseSec = 0;
    int elapseSec = 0;
    int Interval = -1;
    //storage the current time when pause
    clock_t ClockTime = clock();
    clock_t StartTime = clock();
    clock_t EndTime = clock();
    bool isRunning = false;
    bool isPause = false;
    bool isZero = false;
    int toTotalSec(int h, int m, int s);
    int toSec(clock_t time);
    clock_t toCmpTime(int time);
    clock_t getCurCmpTime();
public:
    void startTimer(int InputHor, int InputMin, int InputSec, TimerMode Mode);
    void stopResume();
    void updateTimer();
    void getCurrentTime(int& hour, int& min, int& sec);
    void resetTimer();
    bool isFinish();
};