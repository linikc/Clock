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
RECT tip_clean_rect = { 20, 20, 680, 100 };
RECT clock_recct = { 10,10,690,290 };
//converted rect
RECT hour_rect_convert = {0,0,0,0};
RECT HM_sprt_convert = { 0,0,0,0 };
RECT min_rect_convert = { 0,0,0,0 };
RECT MS_sprt_convert = { 0,0,0,0 };
RECT sec_rect_convert = { 0,0,0,0 };
RECT tip_rect_convert = { 0,0,0,0 };
RECT mode_rect_convert = { 0,0,0,0 };
RECT tip_clean_rect_convert = { 0,0,0,0 };
RECT clock_rect_convert = { 0,0,0,0 };



void TimerDrawer::toTipSize(LOGFONT F) {
    F.lfHeight = FTIP * RatioH;
    settextstyle(&F);
}

void TimerDrawer::toModeSize(LOGFONT F) {
    F.lfHeight = FTIP * RatioH;
    settextstyle(&F);
}

void TimerDrawer::toClockSize(LOGFONT F) {
    F.lfHeight = FHEIGHT * RatioH;
    settextstyle(&F);
}

RECT TimerDrawer::ConvertRect(RECT rect) {
    RatioH = WHeight / HEIGHT;
    RatioW = WWidth / WIDTH;
    rect.left = rect.left * RatioW;
    rect.right = rect.right * RatioW;
    rect.top = rect.top * RatioH;
    rect.bottom = rect.bottom * RatioH;
    return rect;
}

void TimerDrawer::DrawLandscape() {
    solidroundrect(clock_rect_convert.left, clock_rect_convert.top, clock_rect_convert.right, clock_rect_convert.bottom, OFFSET, OFFSET);
}

void TimerDrawer::CleanCanva() {
    solidroundrect(clock_rect_convert.left, clock_rect_convert.top, clock_rect_convert.right, clock_rect_convert.bottom, OFFSET, OFFSET);
    solidrectangle(tip_rect_convert.left, tip_rect_convert.top, tip_rect_convert.right, tip_rect_convert.bottom);
}

void TimerDrawer::CleanTip() {
    solidrectangle(tip_clean_rect_convert.left, tip_clean_rect_convert.top, tip_clean_rect_convert.right, tip_clean_rect_convert.bottom);
}

void TimerDrawer::CleanMode() {
    solidrectangle(mode_rect_convert.left, mode_rect_convert.top, mode_rect_convert.right, mode_rect_convert.bottom);
}

void TimerDrawer::DrawClock(int h, int m, int s) {
    std::wstring hw = L"";
    std::wstring mw = L"";
    std::wstring sw = L"";
    hw = std::to_wstring(h);
    mw = std::to_wstring(m);
    sw = std::to_wstring(s);
    toClockSize(F);
    drawtext(hw.c_str(), &hour_rect_convert, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T(":"), &HM_sprt_convert, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(mw.c_str(), &min_rect_convert, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T(":"), &MS_sprt_convert, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(sw.c_str(), &sec_rect_convert, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void TimerDrawer::DrawTip(std::wstring tip, LOGFONT F) {
    toTipSize(F);
    CleanTip();
    drawtext(tip.c_str(), &tip_rect_convert, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void TimerDrawer::DrawMode(std::wstring mode, LOGFONT F) {
    toModeSize(F);
    CleanMode();
    drawtext(mode.c_str(), &mode_rect_convert, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void TimerDrawer::toConvert() {
    hour_rect_convert = ConvertRect(hour_rect);
    HM_sprt_convert = ConvertRect(HM_sprt);
    min_rect_convert = ConvertRect(min_rect);
    MS_sprt_convert = ConvertRect(MS_sprt);
    sec_rect_convert = ConvertRect(sec_rect);
    tip_rect_convert = ConvertRect(tip_rect);
    mode_rect_convert = ConvertRect(mode_rect);
    tip_clean_rect_convert = ConvertRect(tip_clean_rect);
    clock_rect_convert = ConvertRect(clock_recct);
    printf("%d ",hour_rect_convert.right);
    printf("%f\n", RatioH);
}