#include "extend.h"
const int delay = 1 * CLOCKS_PER_SEC;
bool updated = false;
bool running = true;
enum InputState { HOR, MIN, SEC };
std::wstring end_word = L"END";
std::wstring tip = L"ENTER";
ExMessage msg;
int status;//0 regular 1 stop
int h, m, s = 0;

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
void Function();
void ioSys();
int main()
{
	Init();
	drawTimeC(0, 0, 0);
	HWND hwnd = GetHWnd();
	g_originWndProc = (WNDPROC)GetWindowLongPtr(hwnd, GWLP_WNDPROC);
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
	std::thread cl_f(Function);
	while (true)
	{
		if (running == false)
			break;
		if (updated == true)
		{
			BeginBatchDraw();
			drawTimeC(h, m, s);
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
	initgraph(WIDTH,HEIGHT,NULL);
	graphClean();
	fontInit();
	status = 0;
}
void Function()
{
	wchar_t input[10];
	ioSys();
	updated = true;
	graphClean();
	tip = L"Counting...";
	clock_t start = clock();
	for (;;)
	{
		start = clock();
		if (h * 3600 + m * 60 + s == 0)
		{
			running = false;
			break;
		}
		while (s >= 60)
		{
			s -= 60;
			m++;
		}
		while (m >= 60)
		{
			m -= 60;
			h++;
		}
		if (h != 0)
			if (m == 0)
			{
				m = 60;
				h--;
			}
		if (s == 0)
			if (m != 0)
			{
				s = 60;
				m--;
			}
			else
				break;
		s --;
		while (clock() - start <= delay);
	}
}
void ioSys()
{
	InputState input_state = HOR;
	std::string HORINPUT = "";
	std::string MININPUT = "";
	std::string SECINPUT = "";
	while (true)
	{
		if (peekmessage(&msg,EX_KEY))
		{
			if (msg.message == WM_KEYDOWN)
			{
				if (msg.vkcode >= '0' && msg.vkcode <= '9')
				{
					char num = (char)msg.vkcode;
					switch (input_state)
					{
					case HOR:
						if (HORINPUT.length() < 2)
						{
							HORINPUT += num;
							h = std::stoi(HORINPUT);
						}
						break;
					case MIN:
						if (MININPUT.length() < 2)
						{
							MININPUT += num;
							m = std::stoi(MININPUT);
						}
						break;
					case SEC:
						if (SECINPUT.length() < 2)
						{
							SECINPUT += num;
							s = std::stoi(SECINPUT);
						}
						break;
					}
				}
				if (msg.vkcode == VK_BACK)
				{
					switch (input_state)
					{
					case HOR:
						if (!HORINPUT.empty())
						{
							HORINPUT = "";
							h = 0;
						}
						break;
					case MIN:
						if (!MININPUT.empty())
						{
							MININPUT = "";
							m = 0;
						}
						break;
					case SEC:
						if (!SECINPUT.empty())
						{
							SECINPUT = "";
							s = 0;
						}
						break;
					}
				}
				if (msg.vkcode == VK_RIGHT)//->
					input_state = (InputState)((input_state + 1) % 3);
				if (msg.vkcode == VK_LEFT)
					input_state = (InputState)((input_state + 2) % 3);
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
				if (msg.vkcode == 13)
					return;
				if (input_state == SEC && SECINPUT.length() == 2)
					return;
			}
		}
		BeginBatchDraw();
		drawTimeC(h, m, s);
		drawTip(tip);
		EndBatchDraw();
		Sleep(10);
		FlushBatchDraw();
	}
}