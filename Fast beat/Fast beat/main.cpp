#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
//#include <thread>
#include <windows.h>
using namespace std;
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
const int MAX_LINE_LEN = 50;
int width = 400;
int height = 350;
wchar_t* char2wchar(char* cchar)
{
	wchar_t* m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}
class Spectrum
{
public:

};
class Player
{
public:
	void draw_s(COLORREF color_f, int txt_s, bool z)
	{
		settextcolor(color_f);
		char txt_n[10];
		_itoa_s(txt_s, txt_n, 10);
		wchar_t* txt = char2wchar(txt_n);
		int x = width / 2;
		int y = height / 10;
		setfillcolor(BLACK);
		solidrectangle(x - textwidth(L"COMBO") / 2, y - textheight(txt), x + textwidth(L"COMBO") / 2, y + textheight(txt));
		outtextxy(x - textwidth(L"COMBO") / 2, y - textheight(txt), L"COMBO");
		if (z) 
		{
			setfillcolor(BLACK);
			solidrectangle(x - textwidth(L"COMBO") / 2, y - textheight(txt), x + textwidth(L"COMBO"), y);
			outtextxy(x - textwidth(L"MISS") / 2, y - textheight(txt), L"MISS");
		}
		outtextxy(x - textwidth(txt) / 2, y, txt);
	}
	int score = 0;
};
void draw_txt(COLORREF color_t, COLORREF color_x, char* txt_n, bool n = 0, bool m = 1, int x = 80,int y = 50)
{
	settextcolor(color_t);
	setlinecolor(color_x);
	wchar_t* txt = char2wchar(txt_n);
	int c_wid = 10; //英文间隙
	int c_hei = 15;
	if(n)
	{
	c_wid = 16; //中文间隙
	c_hei = 20;
	}
	int width_d = width - 2 * x;
	int height_d = ceil(_tcslen(txt) / ceil((width_d - 10 * 2) / c_wid)) * c_hei + 5 * 2;
	int txt_size = _tcslen(txt);
	if (find(txt, txt + _tcslen(txt),'/')!=txt + _tcslen(txt))
	{
		int a = 0;
		for (int i = 0; i < txt_size; i++)
		{
			if (txt[i] == '/') { a++; }
		}
		height_d = c_hei * a + c_hei * 2;
	}
	int left_m = x;
	int top_m = y;
	int right_m = x + width_d;
	int bottom_m = y + height_d;
	fillrectangle(left_m, top_m, right_m, bottom_m);
	int t_size = 2;
	int t_x = x;
	int t_y = y + 7;
	int mac = (width_d - c_wid * 2) + x;
	for (int num = 0; num < txt_size; num++)
	{
		if (t_x == mac)
		{
			t_y += c_hei;
			t_x = x;
		}
		if (txt[num] == '/')
		{
			t_y += c_hei;
			t_x = x;
			for (int i = num; i < txt_size; i++) { txt[i] = txt[i + 1]; }
			txt_size--;
		}
		t_x += c_wid;
		//mciSendString("play 1.mp3 from 0", NULL, 0, NULL);
		//char txt_l[] = { '!','@','#','$','%','^','&','*' };
		//for (int i = 0; i < 8; i++)
		//{
		//	outtextxy(t_x, t_y, txt_l[i]);
		//	Sleep(10);
		//	//setfillcolor(BLACK);
		//	solidrectangle(t_x, t_y, t_x + c_wid, t_y + c_hei);
		//}
		outtextxy(t_x, t_y, txt[num]);
		if(m){ Sleep(50); }
	}
}
class Draw_y
{
public:
	void draw_y_k()
	{
		BeginBatchDraw();
		for(int i = 0; i < 300; i += 10)
		{
			setlinecolor(WHITE);
			for(int o = 0; o < 50; o++) { circle(width / 2, height / 2, i + o); }
			FlushBatchDraw();
			//Sleep(2);
			setlinecolor(BLACK);
			//for(int o = 0; o < 50; o++) { circle(width / 2, height / 2, i + o); }
			cleardevice();
		}
		//cleardevice();
		EndBatchDraw();
	}
};
int main()
{
	initgraph(width, height);	// 创建绘图窗口，大小为 400x350 像素
	LOGFONT f;
	gettextstyle(&f);
	_tcscpy_s(f.lfFaceName, _T("宋体"));
	//f.lfWeight = FW_THIN;
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	setbkcolor(BLACK);
	setfillcolor(BLACK);

	char txt[] = "请稍后....../ /";
	char txt_1[] = "海内存知己，/天涯若比邻。";
	char txt_2[] = "按任意键开始....../ /";
	draw_txt(WHITE, WHITE, txt, 1);
	Sleep(200);
	cleardevice();
	draw_txt(WHITE, WHITE, txt_1, 1);
	Sleep(200);
	cleardevice();
	draw_txt(WHITE, WHITE, txt_2, 1);
	if(_getch()!=NULL)
	{
		cleardevice();
		Sleep(200);
		draw_txt(WHITE, WHITE, txt_2, 1, 0);
		Sleep(200);
		cleardevice();
		Sleep(200);
		draw_txt(WHITE, WHITE, txt_2, 1, 0);
		Sleep(200);
		cleardevice();
		Sleep(200);
		draw_txt(WHITE, WHITE, txt_2, 1, 0);
		Sleep(300);
		cleardevice();
	}
	Draw_y y;
	Player p;

	//p.draw_s(WHITE, 114, 0);
	//p.draw_s(WHITE, 514, 1);
	while (1)
	{
		p.draw_s(WHITE, p.score, 0);
		if (_getch() != NULL)
		{
			//thread (&Draw_y::draw_y_k, y).detach(); //使用前请#include <thread>
			p.score++;
			y.draw_y_k();
		}
	}


	//cleardevice();
	//ifstream readFile;
	//readFile.open("旧日之箓.txt", ios::in);
	//if (readFile.is_open())
	//{
	//	string str;
	//	while (getline(readFile, str))
	//	{
	//		/*cout << str << endl;*/
	//		draw(BLACK, WHITE, 80, 50, (char*)str.c_str(), 1);
	//		Sleep(100);
	//		cleardevice();
	//		Sleep(100);
	//	}
	//}

	
	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}