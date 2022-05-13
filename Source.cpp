#include<graphics.h>
#include<conio.h>
#include<string>
using namespace std;
IMAGE stdimg;
LPCWSTR filename = L"";
bool recovery = 0;
int ileft,iright,itop,ibottom;
int main();
void editpicture() {
	saveimage(L"C:\\Users\\Public\\Pictures\\NaranjaTemp.jpg");
	initgraph(680, 480);
	loadimage(&stdimg, L"C:\\Users\\Public\\Pictures\\NaranjaTemp.jpg", 640, 480);
	putimage(0, 0, &stdimg);
}
string Lpcwstr2String(LPCWSTR lps) {
	//turn LPCWSTR to string
	int len = WideCharToMultiByte(CP_ACP, 0, lps, -1, NULL, 0, NULL, NULL);
	if (len <= 0) return "";
	else {
		char* dest = new char[len];
		WideCharToMultiByte(CP_ACP, 0, lps, -1, dest, len, NULL, NULL);
		dest[len - 1] = 0;
		string str(dest);
		delete[] dest;
		return str;
	}
}
LPCWSTR string2LPCWSTR(std::string orig){
	//turn string to LPCWSTR
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}
string get_path() {
	OPENFILENAME ofn;
	char szFile[300];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.lpstrFile[0] = '\0';
	LPTSTR        lpstrCustomFilter;
	DWORD         nMaxCustFilter;
	ofn.nFilterIndex = 1;
	LPTSTR        lpstrFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Pictures(*.jpg)\0*.jpg\0Pictures(*.png)\0*.png\0Pictures(*.jpeg)\0*.jpeg\0";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	string path_image = "";
	if (GetOpenFileName(&ofn)) {
		path_image = Lpcwstr2String(ofn.lpstrFile);
		return path_image;
	}
}
LPCWSTR collectfile() {
	//trim the inputted string to suit our needs
	string path = get_path();
	for (size_t i = 0; i < path.size(); i++)
		if (path[i] == '\\') {
			path.insert(i, string("\\"));
			i++;
		}
	return string2LPCWSTR(path);
}
void night() {
	//night mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for(int cntleft=0;cntleft<=640;cntleft++)
		for (int cntbottom=0; cntbottom <= 480; cntbottom++) {
			COLORREF pixcolor = getpixel(cntleft, cntbottom);
			pixcolor = RGB(255 - GetRValue(pixcolor), 255 - GetGValue(pixcolor), 255 - GetBValue(pixcolor));
			putpixel(cntleft, cntbottom,pixcolor);
		}
	editpicture();
}
void sunny() {
	//sunny mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 0; cntleft <= 640; cntleft++)
		for (int cntbottom=0; cntbottom <= 480; cntbottom++) {
			COLORREF pixcolor = getpixel(cntleft, cntbottom);
			pixcolor = RGB(GetRValue(pixcolor)*3, GetGValue(pixcolor)*3, GetBValue(pixcolor)*3);
			putpixel(cntleft, cntbottom, pixcolor);
		}
	editpicture();
}
void gold() {
	//gold mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 0; cntleft <= 640; cntleft++)
		for (int cntbottom = 0; cntbottom <= 480; cntbottom++) {
			COLORREF pixcolor = getpixel(cntleft, cntbottom);
			pixcolor = RGB(GetRValue(pixcolor) , GetGValue(pixcolor) * 0.8, 0);
			putpixel(cntleft, cntbottom, pixcolor);
		}
	editpicture();
}
void green() {
	//green mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 0; cntleft <= 640; cntleft++)
		for (int cntbottom = 0; cntbottom <= 480; cntbottom++) {
			COLORREF pixcolor = getpixel(cntleft, cntbottom);
			pixcolor = RGB(GetRValue(pixcolor), GetGValue(pixcolor) * 3, GetBValue(pixcolor));
			putpixel(cntleft, cntbottom, pixcolor);
		}
	editpicture();
}
void blue() {
	//blue mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 0; cntleft <= 640; cntleft++)
		for (int cntbottom = 0; cntbottom <= 480; cntbottom++) {
			COLORREF pixcolor = getpixel(cntleft, cntbottom);
			pixcolor = RGB(GetRValue(pixcolor), GetGValue(pixcolor), GetBValue(pixcolor)*3);
			putpixel(cntleft, cntbottom, pixcolor);
		}
	editpicture();
}
void average() {
	//average mode
	/*
		Convolution Core:
		0.2 0,2 0.2
		0.2 0.2 0.2
		0.2 0.2 0.2
	*/
	int convcore[3][3] = {
		0.2,2,0.2,
		2,0.2,2,
		0.2,2,0.2
	};
	cleardevice();
	loadimage(&stdimg, filename, 640, 480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 1; cntleft < 640; cntleft ++)
		for (int cntbottom = 1; cntbottom < 480; cntbottom ++) {
			int totalR = 0, totalG = 0, totalB = 0;
			for (int cntsq1 = cntleft; cntsq1 <= cntleft + 3; cntsq1++)
				for (int cntsq2 = cntbottom; cntsq2 <= cntbottom + 3; cntsq2++) {
					COLORREF pixcolor = getpixel(cntsq1, cntsq2);
					totalR += GetRValue(pixcolor) * convcore[cntsq1 - cntleft][cntsq2 - cntbottom];
					totalG += GetGValue(pixcolor) * convcore[cntsq1 - cntleft][cntsq2 - cntbottom];
					totalB += GetBValue(pixcolor) * convcore[cntsq1 - cntleft][cntsq2 - cntbottom];
				}
			COLORREF convcolor = RGB(totalR, totalG, totalB);
			putpixel(cntleft + 1, cntbottom + 1, convcolor);
		}
	editpicture();
}
void blanca() {
	//blanca mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 0; cntleft <= 640; cntleft++)
		for (int cntbottom = 0; cntbottom <= 480; cntbottom++) {
			COLORREF pixcolor = getpixel(cntleft, cntbottom);
			pixcolor = RGB(GetRValue(pixcolor) * 2, GetGValue(pixcolor) * 3, GetBValue(pixcolor) * 4);
			putpixel(cntleft, cntbottom, pixcolor);
		}
	editpicture();
}
void red() {
	//negro mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 0; cntleft <= 640; cntleft++)
		for (int cntbottom = 0; cntbottom <= 480; cntbottom++) {
			COLORREF pixcolor = getpixel(cntleft, cntbottom);
			pixcolor = RGB(GetRValue(pixcolor) * 10, GetGValue(pixcolor) * 4, GetBValue(pixcolor) * 2);
			putpixel(cntleft, cntbottom, pixcolor);
		}
	editpicture();
}
void sharp() {
	//sharp mode
	/*
		Convolution Core:
		0 -0.1 0,
		-0.1 0.5 -0.1
		0 -0.1 0
	*/
	int convcore[3][3] = {
		0,-0.1,0,
		-0.1,0.5,-0.1,
		0,-0.1,0
	};
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	for (int cntleft = 1; cntleft < 640; cntleft++)
		for (int cntbottom = 1; cntbottom < 480; cntbottom ++) {
			int totalR = 0, totalG = 0, totalB = 0;
			for (int cntsq1 = cntleft; cntsq1 <= cntleft + 3; cntsq1++)
				for (int cntsq2 = cntbottom; cntsq2 <= cntbottom + 3; cntsq2++) {
					COLORREF pixcolor = getpixel(cntsq1, cntsq2);
					totalR += GetRValue(pixcolor) * convcore[cntsq1 - cntleft][cntsq2 - cntbottom];
					totalG += GetGValue(pixcolor) * convcore[cntsq1 - cntleft][cntsq2 - cntbottom];
					totalB += GetBValue(pixcolor) * convcore[cntsq1 - cntleft][cntsq2 - cntbottom];
				}
			COLORREF convcolor = RGB(totalR, totalG, totalB);
			putpixel(cntleft + 1, cntbottom + 1, convcolor);
		}
	editpicture();
}
void original() {
	//original mode
	cleardevice();
	loadimage(&stdimg, filename,640,480);
	putimage(0, 0, &stdimg);
	editpicture();
}
void dirrclick() {
	//dirrect the users to the mode they want
	choose:
	MOUSEMSG msg;
	do msg = GetMouseMsg();
	while (msg.uMsg!=WM_LBUTTONDOWN);
	if (msg.y > 370 && msg.y < 400) {
		recovery = 1;
		filename = L"C:\\Users\\Public\\Pictures\\NaranjaTemp.jpg";
		main();
	}
	if(!recovery)filename = collectfile();
	if (filename == L"")main();
	if (msg.y > 100 && msg.y < 130)night();
	else if (msg.y > 100 && msg.y < 130)sunny();
	else if (msg.y > 130 && msg.y < 160)gold();
	else if (msg.y > 160 && msg.y < 190)green();
	else if (msg.y > 190 && msg.y < 220)blanca();
	else if (msg.y > 220 && msg.y < 250)red();
	else if (msg.y > 250 && msg.y < 280)blue();
	else if (msg.y > 280 && msg.y < 310)average();
	else if (msg.y > 310 && msg.y < 340)sharp();
	else if (msg.y > 340 && msg.y < 370)original();
	else goto choose;
}
int main() {
	//starting point
	initgraph(640, 480);
	setbkmode(TRANSPARENT);
	for (int cnt = 0; cnt < 6; cnt++) {
		setfillcolor(RGB(0, 0, cnt * 40 + 55));
		solidrectangle(0, cnt * 80, 640, cnt * 80 + 80);
	}
	settextstyle(70, 0, L"Lucida Calligraphy");
	settextcolor(CYAN);
	outtextxy(20, 0, L"Foto Naranja 2.0");
	settextcolor(GREEN);
	settextstyle(20, 0, L"Copper Black");
	outtextxy(20, 80, L"(C)Conejito Software");
	settextcolor(BROWN);
	settextstyle(30, 0, L"Copper Black",0,0,0,0,1,0);
	outtextxy(20, 100, L"1.NIGHT");
	outtextxy(20, 130, L"2.SUNNY");
	outtextxy(20, 160, L"3.GOLD");
	outtextxy(20, 190, L"4.GREEN");
	outtextxy(20, 220, L"5.RED");
	outtextxy(20, 250, L"6.BLUE");
	outtextxy(20, 280, L"7.AVERAGE(CV)");
	outtextxy(20, 310, L"8.SHARP(CV)");
	outtextxy(20, 340, L"9.ORIGINAL");
	if(!recovery)outtextxy(20, 370, L"Recover Last File");
	dirrclick();
	Sleep(5000);
	if (MessageBox(GetHWnd(), L"Do you want to save the new picture", L"Asure", MB_YESNO | MB_ICONQUESTION) == 6) {
		saveimage(collectfile());
		MessageBox(GetHWnd(), L"Saved", L"Success", MB_OK);
	}
	if (MessageBox(GetHWnd(), L"Do you want to go to the home page", L"Asure", MB_YESNO | MB_ICONQUESTION) == 6) {
		recovery = 0;
		main();
	}
	while (_getch() != 27);
	closegraph();
	return 0;
}