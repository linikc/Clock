#include "Timer.h"
#include "Display.h"
#include "Logic.h"
#include "Interaction.h"

TimerStatus Status = START;

//statement
TimerMode mode = COUNT_DOWN;
TimerLogic logic;
TimerDrawer draw;
Interaction inter;
LOGFONT F;
const int delay = 1 * CLOCKS_PER_SEC;
int h, m, s;
std::wstring tip = L"";
clock_t start_time = clock();
clock_t end_time = clock();
//handle exit
WNDPROC g_originWndProc = NULL;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT u_msg, WPARAM wParam, LPARAM lParam)
{
    if (u_msg == WM_CLOSE) {
        exit(0);
    }
    else {
        LRESULT result = CallWindowProc((WNDPROC)g_originWndProc, hwnd, u_msg, wParam, lParam);
        return result;
    }
}

//statement of function
void Init();
void Graphic(int h, int m, int s, std::wstring tip);
void Preparation();

int main() {
    Init();
    BeginBatchDraw();
    while (Status == START) {
        Preparation();
        logic.startTimer(h, m, s, mode);
        while (Status == RUN || Status == STOP) {
            start_time = clock();
            tip = L"";
            if (logic.isFinish())
                break;
            inter.GetInput();
            inter.HandleInputB();
            logic.updateTimer();
            logic.stopResume();
            if (Status == STOP)
                tip = L"Pause";
            if (Status == RESET)
            {
                tip = L"RESET";
                Graphic(h, m, s, tip);
                logic.resetTimer();
            }
            logic.getCurrentTime(h, m, s);
            Graphic(h, m, s, tip);
            FlushBatchDraw();
            printf("%d %d %d\n", h, m, s);
            end_time = clock();
            Sleep(delay - (end_time - start_time) > 0 ? delay - (end_time - start_time) : 0);
        }
    }
    Sleep(100);
    tip = L"Exiting...";
    Graphic(h, m, s, tip);
    printf("Exiting...");
    FlushBatchDraw();
    EndBatchDraw();
    Sleep(1000);
    return 0;
}

//definition of the function
void Init() {
    printf("Init...\n");
    initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
    gettextstyle(&F);
    F.lfHeight = FWIDTH;
    settextstyle(&F);
    HWND hwnd = GetHWnd();
    g_originWndProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
    draw.CleanCanva();
    draw.DrawLandscape();
}

void Graphic(int h,int m,int s, std::wstring tip) {
    draw.DrawLandscape();
    draw.DrawClock(h, m, s);
    draw.DrawTip(tip,F);
}

void Preparation() {
    h = 0, m = 0, s = 0;
    while (Status == START) {
        system("cls");
        inter.GetInput();
        inter.HandleInputA();
        if (Status == RUN)
            inter.ReturnInput(s);
        switch (inter.GetInputState()) {
        case HOR:
            printf("Hour "); if(h < 10)inter.ReturnInput(h); tip = L"HOR"; break;
        case MIN:
            printf("Min "); if(m < 10)inter.ReturnInput(m); tip = L"MIN"; break;
        case SEC:
            printf("Sec "); if(s < 10)inter.ReturnInput(s); tip = L"SEC"; break;
        }
        Graphic(h, m, s, tip);
        FlushBatchDraw();
        printf("%d\n", inter.GetInputState());
        printf("%d %d %d\n", h, m, s);
        Sleep(100);
    }
    tip = L"";
}
