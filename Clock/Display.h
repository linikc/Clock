#pragma once
#include "Timer.h"
extern enum TimerStatus Status;

class TimerDrawer {
private:
    //To change the font size of the EasyX
    void toTipSize(LOGFONT F);
    void toClockSize(LOGFONT F);
    void toModeSize(LOGFONT F);
    RECT ConvertRect(RECT rect, float WHeight, float WWidth);
    float RatioW = 1;
    float RatioH = 1;
public:
    void DrawLandscape();
    void DrawClock(int h, int m, int s);
    void CleanCanva();
    void CleanTip();
    void CleanMode();
    void DrawTip(std::wstring tip, LOGFONT F);
    void DrawMode(std::wstring mode, LOGFONT);
    void toConvert(float width, float height);
};