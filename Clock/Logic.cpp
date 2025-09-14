#include "Logic.h"

bool TimerLogic::isFinish() {
    return(isZero ? true : false);
}
int TimerLogic::toTotalSec(int h, int m, int s) {
    return h * 3600 + m * 60 + s;
}

int TimerLogic::toSec(clock_t time) {
    return time / CLOCKS_PER_SEC;
}

clock_t TimerLogic::toCmpTime(int time) {
    return time * CLOCKS_PER_SEC;
}

clock_t TimerLogic::getCurCmpTime() {
    return clock();
}

void TimerLogic::startTimer(int InputHor, int InputMin, int InputSec, TimerMode Mode) {
    this->Mode = Mode;
    PauseSec = 0;
    isRunning = true;
    switch (this->Mode) {
    case COUNT_DOWN:
        TotalSec = toTotalSec(InputHor, InputMin, InputSec);
        StartTime = getCurCmpTime();
        EndTime = StartTime + toCmpTime(TotalSec);
        break;
    case COUNT_UP:
        StartTime = getCurCmpTime();
    default:
        break;
    }
}

void TimerLogic::stopResume() {
    if (!isRunning) return;
    if (Status == RUN) {
        ClockTime = getCurCmpTime();
        isPause = false;
        PauseSec = 0;
    }
    if (Status == STOP) {
        PauseSec = toSec(getCurCmpTime() - ClockTime);
        isPause = true;
    }
}

void TimerLogic::updateTimer() {
    if (!isRunning || isPause || Status == STOP) return;
    EndTime += PauseSec;
    if (TotalSec == 0) {
        TotalSec = 0;
        isZero = true;
        return;
    }
    TotalSec--;
}

void TimerLogic::getCurrentTime(int& hour, int& min, int& sec) {
    if (!isRunning) return;
    ClockTime = clock();
    hour = TotalSec / 3600;
    min = (TotalSec - (3600 * hour)) / 60;
    sec = TotalSec - 3600 * hour - 60 * min;
}

void TimerLogic::resetTimer() {
    isRunning = false;
    isPause = false;
    TotalSec = 0;
    PauseSec = 0;
    Status = START;
}
