#pragma once
#include "Timer.h"
extern enum TimerStatus Status;

class TimerDrawer {
private:
    //To change the font size of the EasyX
    void toTipSize(LOGFONT F);
    void toClockSize(LOGFONT F);
public:
    void DrawLandscape();
    void DrawClock(int h, int m, int s);
    void CleanCanva();
    void CleanTip();
    void DrawTip(std::wstring tip, LOGFONT F);
};