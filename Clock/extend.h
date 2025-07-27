#include <graphics.h>
#include <string>
#include <stdio.h>
#include <ctime>
#include <Windows.h>
#include <thread>
#ifdef EXTEND_H
#define EXTEND_H

#endif // EXTEND_H
#define REGULAR       0
#define STOP          2
#define FAIL        404
#define RUNNING       1
#define WIDTH       700
#define HEIGHT      300
#define FWIDTH      100
#define FHEIGHT      20
#define OFFSET       10
void drawTime(LPCTSTR h, LPCTSTR m, LPCTSTR s, RECT hourRect, RECT HMSprt, RECT minRect, RECT MSSprt, RECT secRect);
void drawTimeC(int h, int m, int s);
void drawTimeT(std::wstring h, std::wstring m, std::wstring s);
void drawTip(std::wstring tip);

void graphClean();
void fontInit();
