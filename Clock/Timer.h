#pragma once
#include <graphics.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <ctime>

#define WIDTH       700
#define HEIGHT      300
#define FWIDTH      100
#define FHEIGHT      20
#define OFFSET       10
#define CLEAN       233
//position of Hour
extern RECT hour_rect;
//posistion of the division between Hour and Minute
extern RECT HM_sprt;
extern RECT min_rect;
extern RECT MS_sprt;
extern RECT sec_rect;
//position of the tip in the center
extern RECT tip_rect;
extern RECT tip_clean;
extern LOGFONT F;

class TimerLogic;
class TimerDrawer;
class Interaction;

//Timer State
enum TimerMode {
    COUNT_UP, COUNT_DOWN
};

enum TimerStatus {
    START, RUN,
    STOP, WAIT,
    SLEEP, RESET
};

enum InputState {
    HOR, MIN, SEC
};
