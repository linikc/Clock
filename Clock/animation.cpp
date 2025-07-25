#include "extend.h"
RECT hour_rect = { 0,0,280,300 };//position of Hour
RECT HM_sprt = { 0,0,500,300 };//posistion of the division between Hour and Minute
RECT min_rect = { 0,0,720,300 };
RECT MS_sprt = { 0,0,920,300 };
RECT sec_rect = { 0,0,1120,300 };
RECT tip_rect = { 0,0,700,500 };//position of the tip in the center
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
	solidroundrect(OFFSET, OFFSET, 690, 290, OFFSET, OFFSET);//round rectangle to clean the canvas
	std::wstring hw = L"";
	std::wstring mw = L"";
	std::wstring sw = L"";
	hw = std::to_wstring(h);
	mw = std::to_wstring(m);
	sw = std::to_wstring(s);
	drawtext(hw.c_str(), &hour_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &HM_sprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(mw.c_str(), &min_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &MS_sprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(sw.c_str(), &sec_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
};
void drawTimeT(std::wstring h, std::wstring m, std::wstring s)
{
	drawtext(h.c_str(), &hour_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &HM_sprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(m.c_str(), &min_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(":"), &MS_sprt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(s.c_str(), &sec_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void graphClean()
{
	solidroundrect(OFFSET, OFFSET, 690, 290, OFFSET, OFFSET);//WIDTH-OFFSET and HEIGHT-OFFSET
}
void drawTip(std::wstring tip)
{
	F.lfHeight = 50;
	settextstyle(&F);
	solidrectangle(20,400,600,600);
	drawtext(tip.c_str(), &tip_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	F.lfHeight = FWIDTH;
	settextstyle(&F);
}
void fontInit()
{
	gettextstyle(&F);
	F.lfHeight = FWIDTH;
	settextstyle(&F);
}
