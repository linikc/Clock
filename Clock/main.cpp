#include "extend.h"
const int delay = 1 * CLOCKS_PER_SEC;
bool updated = false;
bool running = true;
enum InputState { HOR, MIN, SEC };
std::wstring endWord = L"END";
std::wstring Tip = L"ENTER";
ExMessage msg;
char key;
int status;//0 regular 1 stop
int h, m, s = 0;
void Init();
void Function();
void iosys(char key);
int main()
{
	Init();
	drawTimeC(0, 0, 0);
	printf("waiting!\n");
	std::thread clF(Function);
	while (true)
	{
		//std::unique_lock<std::mutex> lock(mtx);
		//cv.wait(lock, [&] {return updated; });
		if (running == false)
			break;
		if (updated == true)
		{
			BeginBatchDraw();
			drawTimeC(h, m, s);
			drawTip(Tip);
			EndBatchDraw();
			Sleep(400);
			FlushBatchDraw();
			//printf("Done!\n");
		}
	}
	clF.join();
	drawTimeT(endWord, endWord, endWord);
	Sleep(1000);
	closegraph();
	//system("pause");
	return 0;
}
void Init()
{
	initgraph(WIDTH,HEIGHT,0);
	graphClean();
	fontInit();
	status = 0;
}
void Function()
{
	wchar_t input[10];
	/*InputBox(input, 10, L"Hour(s)");
	h = _wtoi(input);
	InputBox(input, 10, L"Minute(s)");
	m = _wtoi(input);
	InputBox(input, 10, L"Seconde(s)");
	s = _wtoi(input);*/
	printf("Start input\n");
	iosys(key);
	updated = true;
	graphClean();
	Tip = L"Counting...";
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
		//printf("%d\n",h * 3600 + m * 60 + s);
		//printf("%d %d %d\n", h, m, s);
		//Sleep(1000)
		while (clock() - start <= delay);
	}
	printf("\n%d %d %d t1 finished\n", h, m, s);
}
void iosys(char key)
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
					Tip = L"HOUR";
					if (HORINPUT.length() < 2)
					{
						HORINPUT += num;
						h = std::stoi(HORINPUT);
					}
					if (key == 8)
					{
						HORINPUT = "";
						h = 0;
					}
					break;
				case MIN:
					Tip = L"MIN";
					if (MININPUT.length() < 2)
					{
						MININPUT += num;
						m = std::stoi(MININPUT);
					}
					if (key == 8)
					{
						MININPUT = "";
						h = 0;
					}
					break;
				case SEC:
					Tip = L"SEC";
					if (SECINPUT.length() < 2)
					{
						SECINPUT += num;
						s = std::stoi(SECINPUT);
					}
					if (key == 8)
					{
						SECINPUT = "";
						h = 0;
					}
					break;
				}
			}
			else if (key == 'd' || key == 'D')//->
			{
				printf("->\n");
				input_state = (InputState)((input_state + 1) % 3);
			}
			if (key == 'a' || key == 'A')
			{
				printf("<-\n");
				input_state = (InputState)((input_state - 1) % 3);
			}
			if (key == 13)
				return;
			if (input_state == SEC && SECINPUT.length() == 2) {
				return;
			}
			drawTimeC(h, m, s);
		}
		drawTip(Tip);
	}
}