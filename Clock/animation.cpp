#include "extend.h"
RECT hourRect = { 0,0,280,300 };
RECT HMSprt = { 0,0,500,300 };
RECT minRect = { 0,0,720,300 };
RECT MSSprt = { 0,0,920,300 };
RECT secRect = { 0,0,1120,300 };
RECT tipRect = { 0,0,700,500 };
LOGFONT F;
void drawTime(LPCTSTR h,LPCTSTR m,LPCTSTR s,RECT hourRect,RECT HMSprt,RECT minRect,RECT MSSprt,RECT secRect)
{
	drawtext(h, &hourRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &HMSprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(m, &minRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &MSSprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s, &secRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
};
void drawTimeC(int h, int m, int s)
{
	solidroundrect(OFFSET, OFFSET, WIDTH - OFFSET, HEIGHT - OFFSET, OFFSET, OFFSET);
	std::wstring hw = L"";
	std::wstring mw = L"";
	std::wstring sw = L"";
	hw = std::to_wstring(h);
	mw = std::to_wstring(m);
	sw = std::to_wstring(s);
	drawtext(hw.c_str(), &hourRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &HMSprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(mw.c_str(), &minRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &MSSprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(sw.c_str(), &secRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
};
void drawTimeT(std::wstring h, std::wstring m, std::wstring s)
{
	drawtext(h.c_str(), &hourRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &HMSprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(m.c_str(), &minRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &MSSprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s.c_str(), &secRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void graphClean()
{
	solidroundrect(OFFSET, OFFSET, WIDTH - OFFSET, HEIGHT - OFFSET, OFFSET, OFFSET);
}
void drawTip(std::wstring tip)
{
	F.lfHeight = 50;
	settextstyle(&F);
	solidrectangle(20,400,600,600);
	drawtext(tip.c_str(), &tipRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	F.lfHeight = FWIDTH;
	settextstyle(&F);
}
void fontInit()
{
	gettextstyle(&F);
	F.lfHeight = FWIDTH;
	settextstyle(&F);
}