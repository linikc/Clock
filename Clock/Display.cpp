#pragma once
#include "Display.h"

RECT hour_rect = { 0,0,280,300 };
//posistion of the division between Hour and Minute
RECT HM_sprt = { 0,0,500,300 };
RECT min_rect = { 0,0,720,300 };
RECT MS_sprt = { 0,0,920,300 };
RECT sec_rect = { 0,0,1120,300 };
//position of the tip in the center
RECT tip_rect = { 0,0,700,500 };
RECT tip_clean = { 20, 400, 600, 600 };

void TimerDrawer::toTipSize(LOGFONT F) {
    F.lfHeight = 50;
    settextstyle(&F);
}

void TimerDrawer::toClockSize(LOGFONT F) {
    F.lfHeight = FWIDTH;
    settextstyle(&F);
}

void TimerDrawer::DrawLandscape() {
    solidroundrect(OFFSET, OFFSET, 690, 290, OFFSET, OFFSET);
}

void TimerDrawer::CleanCanva() {
    solidroundrect(OFFSET, OFFSET, 690, 290, OFFSET, OFFSET);
    solidrectangle(tip_rect.left, tip_rect.right, tip_rect.top, tip_rect.bottom);
}

void TimerDrawer::CleanTip() {
    solidrectangle(tip_clean.left, tip_clean.right, tip_clean.top, tip_clean.bottom);
}

void TimerDrawer::DrawClock(int h, int m, int s) {
    std::wstring hw = L"";
    std::wstring mw = L"";
    std::wstring sw = L"";
    hw = std::to_wstring(h);
    mw = std::to_wstring(m);
    sw = std::to_wstring(s);
    toClockSize(F);
    drawtext(hw.c_str(), &hour_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T(":"), &HM_sprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(mw.c_str(), &min_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T(":"), &MS_sprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(sw.c_str(), &sec_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void TimerDrawer::DrawTip(std::wstring tip, LOGFONT F) {
    toTipSize(F);
    CleanTip();
    drawtext(tip.c_str(), &tip_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}