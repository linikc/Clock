#include "extend.h"
const int delay = 1 * CLOCKS_PER_SEC;
bool updated = false;
bool running = true;
enum InputState { HOR, MIN, SEC };
std::wstring end_word = L"END";
std::wstring tip = L"ENTER";
ExMessage msg;
char key;
int status;//0 regular 1 stop
int hr, mn, sc = 0;
int hr_buffer, mn_buffer, sc_buffer = 0;
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
void Init();
void Countdown();
void Countup();
void ioSys(char key);
int main()
{
	Init();
	drawTimeC(0, 0, 0);
	printf("waiting!\n");
	std::thread cl_f(Countdown);
	while (true)
	{
		if (running == false)
			break;
		if (updated == true)
		{
			BeginBatchDraw();
			drawTimeC(hr, mn, sc);
			drawTip(tip);
			EndBatchDraw();
			Sleep(400);
			FlushBatchDraw();
		}
	}
	cl_f.join();
	drawTimeT(end_word, end_word, end_word);
	Sleep(1000);
	closegraph();
	return 0;
}
void Init()
{
	initgraph(WIDTH,HEIGHT,SHOWCONSOLE);
	HWND hwnd = GetHWnd();
	g_originWndProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
	graphClean();
	fontInit();
	status = 0;
}
void Countdown()
{
	wchar_t input[10];
	printf("Start input\n");
	ioSys(key);
	updated = true;
	graphClean();
	tip = L"Counting...";
	clock_t start = clock();
	for (;;)
	{
		start = clock();
		if (hr * 3600 + mn * 60 + sc == 0)
		{
			running = false;
			break;
		}
		while (sc >= 60)
		{
			sc -= 60;
			mn++;
		}
		while (mn >= 60)
		{
			mn -= 60;
			hr++;
		}
		if (hr != 0)
			if (mn == 0)
			{
				mn = 60;
				hr--;
			}
		if (sc == 0)
			if (mn != 0)
			{
				sc = 60;
				mn--;
			}
			else
				break;
		sc --;
		while (clock() - start <= delay);
	}
	printf("\n%d %d %d t1 finished\n", hr, mn, sc);
}
void Countup()
{

}
void ioSys(char key)
{
	InputState input_state = HOR;
	std::string HORINPUT = "";
	std::string MININPUT = "";
	std::string SECINPUT = "";
	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();
			if (key >= '0' && key <= '9' || key == 8)
			{
				char num = (char)key;
				switch (input_state)
				{
				case HOR:
					if (HORINPUT.length() < 2)
					{
						HORINPUT += num;
						hr = std::stoi(HORINPUT);
					}
					break;
				case MIN:
					if (MININPUT.length() < 2)
					{
						MININPUT += num;
						mn = std::stoi(MININPUT);
					}
					break;
				case SEC:
					if (SECINPUT.length() < 2)
					{
						SECINPUT += num;
						sc = std::stoi(SECINPUT);
					}
					break;
				}
			}
			if (key == 8)
			{
				switch (input_state)
				{
				case HOR:
					if (!HORINPUT.empty())
					{
						HORINPUT = "";
						hr = 0;
					}
					break;
				case MIN:
					if (!MININPUT.empty())
					{
						MININPUT = "";
						mn = 0;
					}
					break;
				case SEC:
					if (!SECINPUT.empty())
					{
						SECINPUT = "";
						sc = 0;
					}
					break;
				}
			}
			if (key == 'd' || key == 77)//->
			{
				input_state = (InputState)((input_state + 1) % 3);
				printf("->\n");
			}
			if (key == 'a' || key == 75)//<-
			{
				input_state = (InputState)((input_state + 2) % 3);
				printf("<-\n");
			}
			switch (input_state)
			{
			case HOR:
				tip = L"HOR";
				break;
			case MIN:
				tip = L"MIN";
				break;
			case SEC:
				tip = L"SEC";
				break;
			}
			if (key == 13)
				return;
			if (input_state == SEC && SECINPUT.length() == 2)
				return;
		}
		BeginBatchDraw();
		drawTimeC(hr, mn, sc);
		drawTip(tip);
		EndBatchDraw();
		FlushBatchDraw();
		Sleep(10);
	}
	hr_buffer = hr;
	mn_buffer = mn;
	sc_buffer = sc;
}