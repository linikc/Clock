#pragma once
#include "Display.h"

RECT hour_rect = { 0,0,280,300 };
//posistion of the division between Hour and Minute
RECT HM_sprt = { 0,0,500,300 };
RECT min_rect = { 0,0,720,300 };
RECT MS_sprt = { 0,0,920,300 };
RECT sec_rect = { 0,0,1120,300 };
//position of the tip in the center
RECT tip_rect = { 20,200,680,280 };
RECT mode_rect = { 500,20,680,100 };
RECT tip_clean = { 20, 20, 680, 100 };

void TimerDrawer::toTipSize(LOGFONT F) {
    F.lfHeight = FFWIDTH;
    settextstyle(&F);
}

void TimerDrawer::toModeSize(LOGFONT F) {
    F.lfHeight = FFWIDTH;
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
    solidrectangle(tip_rect.left, tip_rect.top, tip_rect.right, tip_rect.bottom);
}

void TimerDrawer::CleanTip() {
    solidrectangle(tip_clean.left, tip_clean.top, tip_clean.right, tip_clean.bottom);
}

void TimerDrawer::CleanMode() {
    solidrectangle(mode_rect.left, mode_rect.top, mode_rect.right, mode_rect.bottom);
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

void TimerDrawer::DrawMode(std::wstring mode, LOGFONT F) {
    toModeSize(F);
    CleanMode();
    drawtext(mode.c_str(), &mode_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}