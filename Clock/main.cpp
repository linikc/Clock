#include "Timer.h"
#include "Display.h"
#include "Logic.h"
#include "Interaction.h"
TimerStatus Status = START;

//statement
TimerMode Mode = COUNT_DOWN;
TimerLogic logic;
TimerDrawer draw;
Interaction inter;
LOGFONT F;
ExMessage msg;
const int delay = 1 * CLOCKS_PER_SEC;
int h, m, s;
std::wstring tip = L"";
std::wstring mode = L"DOWN";
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

#if DEBUG
int main();
#else
int WinMain(HINSTANCE hInstace, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#endif // DEBUG

int main()
{
    Init();
    BeginBatchDraw();
    while (Status == START) {
        Preparation();
        logic.startTimer(h, m, s, Mode);
        while (Status == RUN || Status == STOP) {
            start_time = clock();
            tip = L"";
            if (logic.isFinish())
                break;
            inter.GetInput(msg);
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
int WinMain(HINSTANCE hInstace, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Init();
    BeginBatchDraw();
    while (Status != EXIT) {
        Preparation();
        logic.startTimer(h, m, s, Mode);
        if (Status == RESET)
            Status = START;
        while (Status == RUN || Status == STOP) {
            start_time = clock();
            tip = L"";
            inter.GetInput(msg);
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
                FlushBatchDraw();
                Sleep(200);
            }
            logic.getCurrentTime(h, m, s);
            Graphic(h, m, s, tip);
            FlushBatchDraw();
            end_time = clock();
            if(Status == RUN)
                Sleep(delay - (end_time - start_time) > 0 ? delay - (end_time - start_time) : 0);
        }
    }
    Sleep(100);
    tip = L"Exiting...";
    Graphic(h, m, s, tip);
    FlushBatchDraw();
    EndBatchDraw();
    Sleep(1000);
    return 0;
}
//definition of the function
void Init() {
    printf("Init...\n");
#if DEBUG
    initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
#else 
    initgraph(WIDTH, HEIGHT);
#endif
    gettextstyle(&F);
    F.lfHeight = FWIDTH;
    settextstyle(&F);
    HWND hwnd = GetHWnd();
    g_originWndProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
    SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
    draw.CleanCanva();
    draw.DrawLandscape();
}

void Graphic(int h, int m, int s, std::wstring tip) {
    draw.DrawLandscape();
    draw.DrawClock(h, m, s);
    draw.DrawTip(tip, F);
    draw.DrawMode(mode, F);
}

void Preparation() {
    h = 0, m = 0, s = 0;
    while (Status == START) {
        inter.GetInput(msg);
        inter.HandleModeChange();
        inter.HandleInputA();
        inter.HandleInputB();
        if (Mode == COUNT_UP)
            mode = L"UP";
        if (Mode == COUNT_DOWN)
            mode = L"DOWN";
        if (Status == RUN) {
            inter.ReturnInput(s);
            break;
        }
        switch (inter.GetInputState()) {
        case HOR:
            inter.ReturnInput(h); tip = L"HOR"; break;
        case MIN:
            inter.ReturnInput(m); tip = L"MIN"; break;
        case SEC:
            inter.ReturnInput(s); tip = L"SEC"; break;
        }
        Graphic(h, m, s, tip);
        FlushBatchDraw();
        Sleep(100);
    }
    tip = L"";
}
