#include <windows.h>    
#include "resource.h"
#include "GL.h"  

HDC         hDC = NULL;
HGLRC       hRC = NULL;
HWND        hWnd = NULL;
HINSTANCE   hInstance;


GLuint  arialbig;
GLuint arialsm;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int listH(900), listW(1600), mineW(30), mineH(16), minecount(99), indexb(44), Fontbig(30), Fontsm(17), help_g(0);
bool end(0), Gnew(1), win(0), Seti(0), mous(1), menu(0), EN(1);
Colornum Butcolor = DeepSkyBlue;
Colornum Background = White;
Colornum Textcol = Black;
Colornum Window = White;
//*///////
char tet[2][22][25] = { "New Game", "Game Over!", "Restart", "Exit", "Setting", "Full", "Height", "Width",
"Mine", "Beginner", "Intermediate", "Advanced", "Color", "Reset", "OK", "You Win!", "Close", "Opening", "Text", "Background", "РУ", "Author Gagik Pogosyan",
"Новая игра", "Конец Игры!", "Заного", "Выход", "Опции", "Полный", "Высота", "Ширина",
"Мины", "Новичок", "Любитель", "Профи", "Цвет", "Сброс", "ОК", "Вы Выигривали!",  "Закрытый","Открытый", "Текст", "Фон", "EN", "Автор Гагик Погосян" };

//////*////
Label Win;
Label** P;
Label mes[13];
Label Col_but[48];
Textbox Te[3];

void Newdas();
void dasavor(int = 0);
void make(int, int);
void endofgame(int = 100);
void restart();
void bum(int nx, int ny);
void bac(int ny, int nx, int = 0);
void Wingame(int = 0);
void InitWnd();
void anim(int n = 5, int Ny = -1, int Nx = 0, int Ny2 = 0, int Nx2 = 0, int Ay = -1, int Ax = 0, int Ay2 = 0, int Ax2 = 0);
int save();
int open();


void Display()
{
	int ind(0);
	int qanak(0);
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	Win.Init();

	if (help_g) {
		mes[0].Init();
		mes[4].Init();
		mes[5].Init();
		mes[9].Init();
		mes[10].Init();
		mes[12].Init();

		glutSwapBuffers();
		return;

	}

	for (int i = 0; i < mineH; i++)
		for (int j = 0; j < mineW; j++)
		{
			ind = P[i][j].Init(end);
			if (!(!end && !win && !Seti && !Gnew))
				continue;
			if (ind == 1)	bum(i, j);
			if (ind == 2) { endofgame(); P[i][j].G_end = true; mes[2].Enabled = true; mes[0] = tet[EN][1]; win = 0; mes[3] = tet[EN][3]; mes[1] = tet[EN][0]; mes[2] = tet[EN][2]; }
			if (ind == 3 || ind == 1)	qanak++;
		}

	if (qanak == mineW * mineH - minecount && !Gnew)
	{
		mes[0] = tet[EN][15];
		mes[3] = tet[EN][3];
		Gnew = 1;
		mes[2].Enabled = false;
		Wingame();
	}

	if (end || win)
		for (int i = 0; i < 4; i++)
		{
			mes[i].Init();
		}

	mes[4].Init();
	mes[5].Init();
	mes[9].Init();
	mes[10].Init();
	mes[12].Init();


	if (Seti)
	{
		mes[0] = "\0";
		mes[0].Init();

		Te[0].Init();
		Te[1].Init();
		Te[2].Init();
		mes[3].Init();
		mes[2].Init();
		mes[1].Init();
		mes[6].Init();
		mes[7].Init();
		mes[8].Init();
		mes[11].Init();
	}
	if (menu && Seti)
	{

		for (int i = 44; i < 48; i++)
			Col_but[i].Color = Background;

		Col_but[indexb].Color = Butcolor;

		for (int i = 0; i < 48; i++)
			Col_but[i].Init();

	}

	glutSwapBuffers();



}

void timer1(int)
{

	if (!end && !Gnew && !Seti && !help_g)
		mes[5] += 1;
	glutTimerFunc(1000, timer1, 0);

}

void timer(int)
{
	glutPostRedisplay();//ej@ obnavit

	glutTimerFunc(100, timer, 0);
}


void Reshop(int aw, int ah)
{


	if (ah < 500 || aw < 600)
		return;

	listH = ah;
	listW = aw;

	glViewport(0, 0, aw, ah);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, listW, 0, listH);

	dasavor(1);
	save();

	glMatrixMode(GL_MODELVIEW);

}

void keys(unsigned char key, int x, int y)
{
	if (Seti)
	{
		Te[0].Keys(key);
		Te[1].Keys(key);
		Te[2].Keys(key);
	}
	if (key == 'p' || key == 'P')
	{
		if (!end && !win && !Seti)
			//help ?
			if (help_g) {
				help_g = 0;
				mes[0].Top = Up;
				mes[0].Transporent = true;
				mes[0].Textsize = Small;
				mes[0].textposition = Right;
			}
			else {
				mes[0].Textsize = Big;
				mes[0].Transporent = false;
				mes[0].Top = Center;
				mes[0] = tet[EN][21];
				mes[0].textposition = Left;
				help_g = 1;
			}
	}
	if (help_g)
		return;
	switch (key)
	{
	case'r':
		restart();
		break;
	case'f':
		glutFullScreenToggle();
		break;
	case 27:
		glutLeaveFullScreen();
		break;
	case's':
		Te[0] = mineH;
		Te[1] = mineW;
		Te[2] = minecount;

		if (Seti) {
			Seti = 0;

			//	mes[1].Color = Green;
			//	mes[1].Textcolor = Black;
			mes[3] = tet[EN][3];
			mes[1] = tet[EN][0];
			mes[2] = tet[EN][2];

			if (win) {
				mes[0] = tet[EN][15];
			}
			else {
				mes[0] = tet[EN][1];
			}
		}
		else {
			mes[2] = tet[EN][13];
			mes[3] = tet[EN][14];
			//	mes[1].Color = Butcolor;
			//	mes[1].Textcolor = Textcol;
			mes[1] = tet[EN][12];
			Seti = 1;
			menu = 0;
		}
		break;
	}




}

/*
void keys(int key, int x, int y)
{


switch (key)
{
case :
//glRotatef(1, 0, 0, 1);//frcnel
break;
default:

break;
}

}
//*/

void mouse(int ax, int ay)
{
	if (end || win || Seti)
		if (mes[0].Mouse(ax, listH - ay))
		{
			InitWnd();
		}
}

/*
void mouse(int state, int ax, int ay)
{
char Text[10];

sprintf_s(Text, "%d", ax);
glutSetWindowTitle(Text);


}
//*/

void mouse(int button, int state, int ax, int ay)
{

	if (!mous) return;
	if (!end && !win && !Seti)
		if (mes[12].Mouse(button, state, ax, listH - ay)) { //help ?
			if (help_g) {
				help_g = 0;
				mes[0].Top = Up;
				mes[0].Transporent = true;
				mes[0].Textsize = Small;
				mes[0].textposition = Right;

			}
			else {
				mes[0].Textsize = Big;
				mes[0].Transporent = false;
				mes[0].Top = Center;
				mes[0] = tet[EN][21];
				mes[0].textposition = Left;
				help_g = 1;
			}
		}
	if (help_g) return;

	if (menu && Seti)//color button
		for (int i = 0; i < 48; i++)
			if (Col_but[i].Mouse(button, state, ax, listH - ay))
			{
				if (i >= 44)
				{
					indexb = i;
				}
				else {

					switch (indexb)
					{
					case 44:
						Butcolor = (Colornum)i;
						break;
					case 45:
						Background = (Colornum)i;
						break;
					case 46:
						Textcol = (Colornum)i;
						break;
					case 47:
						Window = (Colornum)i;
						break;
					default:
						break;
					}

					dasavor(2);
					return;
				}
			}


	if (state)mes[0].is_klick = 0;



	if (end || win || Seti)
		mes[0].Mouse(button, state, ax, listH - ay);


	if (1 == mes[9].Mouse(button, state, ax, listH - ay)) {
		Te[0] = mineH;
		Te[1] = mineW;
		Te[2] = minecount;

		if (Seti) {
			Seti = 0;
			mes[2] = tet[EN][2];
			mes[3] = tet[EN][3];
			mes[1] = tet[EN][0];
			if (win)
				mes[0] = tet[EN][15];
			else mes[0] = tet[EN][1];
		}
		else {
			mes[2] = tet[EN][13];
			mes[3] = tet[EN][14];
			mes[1] = tet[EN][12];
			Seti = 1;
			menu = 0;

		}

	}

	if (1 == mes[10].Mouse(button, state, ax, listH - ay)) { glutFullScreenToggle(); }


	int Numx(0), Numy(0);

	if (Seti) {
		///okno


		if (button != 0 || state != 1)	return;
		Te[0].Mouse(button, state, ax, listH - ay);
		Te[1].Mouse(button, state, ax, listH - ay);
		Te[2].Mouse(button, state, ax, listH - ay);

		if (mes[6].Mouse(button, state, ax, listH - ay)) { Te[0] = 9; Te[1] = 9; Te[2] = 10; }
		if (mes[7].Mouse(button, state, ax, listH - ay)) { Te[0] = 16; Te[1] = 16; Te[2] = 40; }
		if (mes[8].Mouse(button, state, ax, listH - ay)) { Te[0] = 16; Te[1] = 30; Te[2] = 99; }
		if (mes[11].Mouse(button, state, ax, listH - ay)) {
			if (EN)EN = 0; else EN = 1; dasavor(0);	mes[1] = tet[EN][12];	mes[2] = tet[EN][13]; 	mes[3] = tet[EN][14];
		}
		if (mes[3].Mouse(button, state, ax, listH - ay))
		{

			Te[0].Color = Silver;
			Te[1].Color = Silver;
			Te[2].Color = Silver;

			if (Te[0].Count >= 9 && Te[0].Count <= 30)
				if (Te[1].Count >= 9 && Te[1].Count <= 50)
					if (Te[2].Count >= 10 && Te[2].Count < Te[0].Count * Te[1].Count - 10)
					{
						for (int i = 0; i < mineH; i++)
						{
							delete[] P[i];
						}
						delete[] P;

						mineH = Te[0].Count;
						mineW = Te[1].Count;
						minecount = Te[2].Count;
						Newdas();
						dasavor(0);
						Seti = 0;
						Gnew = 1;
						end = 0;
						win = 0;
						mes[5] = 0;
						save();

					}
					else Te[2].Color = Red;
				else Te[1].Color = Red;
			else Te[0].Color = Red;
		}
		///reset
		if (mes[2].Mouse(button, state, ax, listH - ay)) {
			for (int i = 0; i < mineH; i++)
			{
				delete[] P[i];
			}
			delete[] P;


			mineW = 30; mineH = 16; minecount = 99;
			Butcolor = DeepSkyBlue;
			Background = White;
			Textcol = Black;
			Window = White;


			Newdas();
			EN = 1;
			Seti = 0;
			Gnew = 1;
			end = 0;
			win = 0;
			mes[5] = 0;
			menu = 0;
			dasavor(1);
			save();
		}

		if (mes[1].Mouse(button, state, ax, listH - ay))
			if (menu)
				menu = 0;
			else {
				//	make(5, 5);
				menu = 1;/////////////////////////////////////////
			}
		return;
	}

	if (state == 1) {

		//*poisk
		for (int i = 0; i < mineW; i++)
			if (P[0][Numx].X < ax && P[0][Numx].X + P[0][0].H > ax)
				break;
			else	  Numx++;

		for (int i = 0; i < mineH; i++)
			if (P[Numy][0].Y < (listH - ay) && P[Numy][0].Y + P[0][0].H >(listH - ay))
				break;
			else	  Numy++;

		if (Numx >= mineW || Numx < 0)
			return;
		if (Numy >= mineH || Numy < 0)
			return;
		//*/
		switch (button)
		{
		case 0://lkm
			if (!end) {
				if (Gnew) {
					make(Numy, Numx);
				}
				if (!P[Numy][Numx].drosh) {
					bac(Numy, Numx);
				}
			}
			else {
				//new game
				if (mes[1].Mouse(button, state, ax, listH - ay) == 1)
				{
					restart();
				}
				///restart
				if (mes[4].Enabled && !win)
					if (mes[2].Mouse(button, state, ax, listH - ay))
					{
						for (int i = 0; i < mineH; i++)
							for (int j = 0; j < mineW; j++)
							{
								P[i][j].Bp = 0;
								P[i][j].drosh = 0;
								P[i][j].G_end = false;

							}
						mes[5] = 0;
						mes[4] = minecount;

						end = 0;
					}
				//exit
				if (mes[3].Mouse(button, state, ax, listH - ay))
				{
					ExitProcess(0);
				}
			}
			break;
		case 2://rkm
			if (!end && !Gnew) {
				if (P[Numy][Numx].drosh)
				{
					P[Numy][Numx].drosh = 0;
					mes[4] += 1;
				}
				else	if (P[Numy][Numx].Bp == 0)
				{
					P[Numy][Numx].drosh = 1;
					mes[4] -= 1;
				}
				if (P[Numy][Numx].Bp) { bac(Numy, Numx); }
			}

			break;
			/*//////// porc
			case 1://ckm
			if (!end&&!Gnew){
			P[Numy][Numx]= 11;
			for (int k = Numy - 1; k <= Numy + 1; k++)
			for (int j = Numx - 1; j <= Numx + 1; j++)
			{
			if (k < 0 || j < 0 || k >= mineH || j >= mineW)
			continue;
			P[k][j] += 1;
			}


			}

			break;
			//////*/
		}




	}



}


int main(int argc, char* argv[])
{
	open();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(listW, listH);
	glutCreateWindow("Minesweeper 1.3");

	hWnd = FindWindowA(0, "Minesweeper 1.3");
	hDC = GetDC(hWnd);


	//HANDLE icon = LoadImage(GetModuleHandle(NULL), ("Minesweeper_icon.ico"), IMAGE_ICON, 32, 32, LR_LOADFROMFILE | LR_COLOR);

	HANDLE icon = LoadImage(GetModuleHandle("Minesweeper.exe"), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, LR_COLOR);
	SendMessage(hWnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)icon);

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, listW, 0, listH);

	glMatrixMode(GL_MODELVIEW);



	Newdas();
	dasavor();


	glutKeyboardFunc(keys);//char/klaviatura
	//glutSpecialFunc(keys);//int/klaviatura

	glutMotionFunc(mouse);//////////////MUK
	//glutMultiPassiveFunc(mouse);
	glutMouseFunc(mouse);///////////////

	glutReshapeFunc(Reshop);

	//glutSetWindowTitle("ert");//zagalovki poxel

	glutTimerFunc(100, timer, 0);
	glutTimerFunc(1000, timer1, 0);
	glutDisplayFunc(Display);


	InitMat();


	glutMainLoop();
	return 0;
}


void Newdas()
{
	P = new Label * [mineH];
	for (int i = 0; i < mineH; i++)
	{
		P[i] = new Label[mineW];
	}

}

void dasavor(int gorc)
{
	float h;
	if (listW / mineW < listH / mineH)
		h = (float)(listW / (mineW + 1)) - 5;
	else h = (float)(listH / (mineH + 1)) - 5;

	Fontbig = h * 0.7;

	arialsm = BuildFont(Fontsm, "Arial");
	arialbig = BuildFont(Fontbig, "Arial");

	for (int i = 0; i < 11; i++)
	{
		mes[i].Size_font = Fontsm;

	}

	mes[0].H = 200;
	mes[0].W = 400;
	mes[0].Y = (listH - mes[0].H) / 2;
	mes[0].X = (listW - mes[0].W) / 2;
	mes[0].Color = Window;
	mes[0].Textcolor = Textcol;
	mes[0].butt = 1;
	if (!gorc)
		mes[0] = tet[EN][1];
	if (!help_g)
		mes[0].Top = Up;
	mes[0].Enabled = true;
	mes[0].textposition = Centery;
	mes[0].Textsize = Small;

	for (int i = 0; i < mineH; i++)
		for (int j = 0; j < mineW; j++)
		{
			P[i][j].H = h;
			P[i][j].W = h;
			P[i][j].X = j * h + j + (listW - mineW * (h + 1)) / 2;
			P[i][j].Y = (float)i * h + i + (listH - mineH * (h + 1)) / 2 + listH * 0.03f;
			P[i][j].Textsize = Big;
			P[i][j].Color = Butcolor;
			P[i][j].Textcolor = Textcol;
			P[i][j].Coloropen = Background;
			P[i][j].Size_font = Fontbig;

		}


	InitWnd();





	mes[1].H = 40;
	mes[1].W = 100;
	mes[1].Color = Butcolor;
	mes[1].Textcolor = Textcol;
	mes[1].butt = 1;
	if (!gorc)
		mes[1] = tet[EN][0];
	mes[1].Textsize = Small;
	mes[1].Enabled = true;

	mes[2].H = 40;
	mes[2].W = 100;
	mes[2].Color = Butcolor;
	mes[2].Textcolor = Textcol;
	mes[2].butt = 1;
	if (!gorc)
		mes[2] = tet[EN][2];
	mes[2].Textsize = Small;
	mes[2].Enabled = true;

	mes[3].H = 40;
	mes[3].W = 100;
	mes[3].Color = Butcolor;
	mes[3].Textcolor = Textcol;
	mes[3].butt = 1;
	if (!gorc)
		mes[3] = tet[EN][3];
	mes[3].Textsize = Small;
	mes[3].Enabled = true;

	mes[4].H = 40;
	mes[4].W = 100;
	mes[4].Y = 20;
	mes[4].X = 20;
	mes[4].Color = Butcolor;
	mes[4].Textcolor = Textcol;
	mes[4].butt = 1;
	if (gorc != 2)
		mes[4] = minecount;
	mes[4].Textsize = Big;
	mes[4].Autosize = true;

	mes[5].H = 40;
	mes[5].W = 10;
	mes[5].Y = 20;
	mes[5].X = (float)listW - 100;
	mes[5].Color = Butcolor;
	mes[5].Textcolor = Textcol;
	mes[5].butt = 1;
	mes[5].Textsize = Big;
	mes[5].Autosize = true;

	mes[6].H = 30;
	mes[6].W = 120;
	mes[6].Color = Butcolor;
	mes[6].Textcolor = Textcol;
	mes[6].butt = 1;
	mes[6] = tet[EN][9];
	mes[6].Textsize = Small;
	mes[6].Enabled = true;

	mes[7].H = 30;
	mes[7].W = 120;
	mes[7].Color = Butcolor;
	mes[7].Textcolor = Textcol;
	mes[7].butt = 1;
	mes[7] = tet[EN][10];
	mes[7].Textsize = Small;
	mes[7].Enabled = true;

	mes[8].H = 30;
	mes[8].W = 120;
	mes[8].Color = Butcolor;
	mes[8].Textcolor = Textcol;
	mes[8].butt = 1;
	mes[8] = tet[EN][11];
	mes[8].Textsize = Small;
	mes[8].Enabled = true;
	mes[4].Transporent = false;
	mes[5].Transporent = false;



	mes[9].H = 40;
	mes[9].W = 70;
	mes[9].Y = listH - mes[9].H - 10;
	mes[9].X = 10;
	mes[9].Color = Butcolor;
	mes[9].Textcolor = Textcol;
	mes[9].butt = 1;
	mes[9].Textsize = Small;
	mes[9].Autosize = true;
	mes[9] = tet[EN][4];

	mes[10].H = 40;
	mes[10].W = 70;
	mes[10].Y = listH - mes[9].H - 10;
	mes[10].X = listW - mes[10].W - 60;
	mes[10].Color = Butcolor;
	mes[10].Textcolor = Textcol;
	mes[10].butt = 1;
	mes[10] = tet[EN][5];
	mes[10].Textsize = Small;
	mes[10].Autosize = true;



	mes[11].H = 40;
	mes[11].W = 40;
	mes[11].Color = Butcolor;
	mes[11].Textcolor = Textcol;
	mes[11].butt = 1;
	if (!gorc)
		mes[11] = tet[EN][20];
	mes[11].Textsize = Small;
	mes[11].Enabled = true;

	mes[12].H = 30;
	mes[12].W = 30;
	mes[12].X = 10;
	mes[12].Y = listH - 90.0f;
	mes[12].Color = Butcolor;
	mes[12].Textcolor = Textcol;
	mes[12].butt = 1;
	mes[12] = "   | |";
	mes[12].Textsize = Small;
	mes[12].Enabled = true;
	//		mes[12].Top = Up;
	//mes[12].Transporent = false;

	Te[0].Caption = tet[EN][6];
	Te[1].Caption = tet[EN][7];
	Te[2].Caption = tet[EN][8];

	Te[0].Color = Butcolor;
	Te[1].Color = Butcolor;
	Te[2].Color = Butcolor;


	Te[0].Textcolor = Textcol;
	Te[1].Textcolor = Textcol;
	Te[2].Textcolor = Textcol;



	for (int n = 0; n < 44; n++)
	{
		Col_but[n].W = Col_but[n].H = 36;
		Col_but[n].Color = (Colornum)n;
	}
	for (int i = 44; i < 48; i++)
	{
		Col_but[i].Textsize = Small;
		Col_but[i].butt = true;
		Col_but[i].Color = Yellow;
		Col_but[i].W = 99;
		Col_but[i].H = 36;
		Col_but[i].Textcolor = Textcol;

	}

	Col_but[44].Text = tet[EN][16];
	Col_but[45].Text = tet[EN][17];
	Col_but[46].Text = tet[EN][18];
	Col_but[47].Text = tet[EN][19];



}

void make(int ay, int ax)
{
	//*
	srand(time(NULL));
	int nx, ny;

	for (int i = 0; i < minecount; i++)
	{
		nx = rand() % mineW;
		ny = rand() % mineH;

		if ((ay + 1 >= ny && ay - 1 <= ny) && (ax + 1 >= nx && ax - 1 <= nx))
		{
			i--;
			continue;
		}


		if (P[ny][nx].Count < 9) {

			P[ny][nx] = 10;


			for (int k = ny - 1; k <= ny + 1; k++)
				for (int j = nx - 1; j <= nx + 1; j++)
				{
					if (k < 0 || j < 0 || k >= mineH || j >= mineW)
						continue;
					P[k][j] += 1;
				}

		}
		else i--;
	}
	//*/
	////////


	////////
	Gnew = 0;
}

void endofgame(int i)
{
	mous = 0;
	Gnew = 1;
	if (i - 100 >= mineH) {
		Gnew = 0;
		end = 1;
		mous = 1;
		return;
	}
	for (int j = 0; j < mineW; j++)
	{


		if (i - 100 < mineH - 1) {
			P[i - 100][j].Color = Green;
			P[i - 100][j].Coloropen = Green;

		}
		if (i - 100 > 0) {
			P[i - 101][j].Color = Butcolor;
			P[i - 101][j].Coloropen = Background;
		}
		if (P[i - 100][j].Count >= 10)
			P[i - 100][j].Bp = 1;

	}
	glutPostRedisplay();

	glutTimerFunc(75, endofgame, i + 1);

}

void bum(int ny, int nx)
{
	if (!win)

		for (int i = ny - 1; i <= ny + 1; i++)
			for (int j = nx - 1; j <= nx + 1; j++)
			{
				if (i < 0 || j < 0 || i >= mineH || j >= mineW)
					continue;
				P[i][j].Bp = 1;
			}

}

void Xach(int R)
{
	bac(0, 0, R);
}
void Bomb(int R) {
	anim(R);
}
void anim(int n, int Ny, int Nx, int Ny2, int Nx2, int Ay, int Ax, int Ay2, int Ax2)
{
	mous = 0;
	static int ny, nx, ny2, nx2, ay, ax, ay2, ax2;

	if (n == 2 || n == 7) {
		mous = 1;
		return;
	}

	if (Ny != -1)
	{
		ny = Ny;
		nx = Nx;
		ny2 = Ny2;
		nx2 = Nx2;
	}
	if (Ay != -1)
	{
		ay = Ay;
		ax = Ax;
		ay2 = Ay2;
		ax2 = Ax2;
	}


	if (n == 5 || n == 10) {
		P[ny][nx].Bum = 1;
		if (n >= 6)
			P[ay][ax].Bum = 1;
	}
	if (n == 4 || n == 9)
	{
		P[ny][nx].Bum = 0;
		P[ny2][nx2].Bum = 1;
		if (n >= 6) {
			P[ay][ax].Bum = 0;
			P[ay2][ax2].Bum = 1;
		}
	}
	if (n == 3 || n == 8) {
		P[ny2][nx2].Bum = 0;
		if (n >= 6)
			P[ay2][ax2].Bum = 0;
	}

	glutTimerFunc(400, Bomb, n - 1);

}
int hash(int ny, int nx) {

	int result(0), k(0);

	for (int i = ny - 1; i <= ny + 1; i++)
		for (int j = nx - 1; j <= nx + 1; j++)
		{
			k++;
			if (i < 0 || j < 0 || i >= mineH || j >= mineW)
			{
				result = result * 10 + k;
				continue;
			}
			if (P[i][j].Count >= 10)
			{
				result = result * 10 + k;
			}
		}
	return result;
}
int canak(int ny, int nx) {
	int qan(0);

	for (int i = ny - 1; i <= ny + 1; i++)
		for (int j = nx - 1; j <= nx + 1; j++)
		{
			if ((i < 0 || j < 0 || i >= mineH || j >= mineW) || (i == ny && j == nx))
				continue;
			if (P[i][j].Count >= 10)
				qan++;
		}
	return qan;
}
int pomosh1(int ny, int nx)
{
	int qan(0);
	bool das[26];

	for (int i = ny - 2; i <= ny + 2; i++)
		for (int j = nx - 2; j <= nx + 2; j++)
		{
			qan++;
			das[qan] = 0;
			if (i < 0 || j < 0 || i >= mineH || j >= mineW) {
				das[qan] = 1;
				continue;
			}

			if (P[i][j].Count >= 10)
			{
				das[qan] = 1;
			}
		}

	if (das[2] == 1 && das[5] == 1 && das[17] == 1 && das[20] == 1 && das[9] == 1 && das[13] == 1 && das[8] == 0 && das[14] == 0)
	{
		P[ny][nx + 1] = 11;
		P[ny - 1][nx] = 11;
		P[ny][nx] = 0;
		P[ny - 1][nx + 1] = canak(ny - 1, nx + 1);
		P[ny][nx] = canak(ny, nx);
		anim(10, ny, nx, ny, nx + 1, ny - 1, nx + 1, ny - 1, nx);

		return 1;
	}
	if (das[6] == 1 && das[9] == 1 && das[21] == 1 && das[24] == 1 && das[17] == 1 && das[13] == 1 && das[12] == 0 && das[18] == 0)
	{
		P[ny][nx - 1] = 11;
		P[ny + 1][nx] = 11;
		P[ny][nx] = 0;
		P[ny + 1][nx - 1] = canak(ny + 1, nx - 1);
		P[ny][nx] = canak(ny, nx);
		anim(10, ny, nx, ny, nx - 1, ny + 1, nx - 1, ny + 1, nx);
		return 1;
	}
	if (das[7] == 1 && das[10] == 1 && das[22] == 1 && das[25] == 1 && das[19] == 1 && das[13] == 1 && das[14] == 0 && das[18] == 0)
	{
		P[ny][nx + 1] = 11;
		P[ny + 1][nx] = 11;
		P[ny][nx] = 0;
		P[ny + 1][nx + 1] = canak(ny + 1, nx + 1);
		P[ny][nx] = canak(ny, nx);
		anim(10, ny, nx, ny, nx + 1, ny + 1, nx + 1, ny + 1, nx);
		return 1;
	}
	if (das[1] == 1 && das[4] == 1 && das[16] == 1 && das[19] == 1 && das[7] == 1 && das[13] == 1 && das[8] == 0 && das[12] == 0)
	{
		P[ny][nx - 1] = 11;
		P[ny - 1][nx] = 11;
		P[ny][nx] = 0;
		P[ny - 1][nx - 1] = canak(ny - 1, nx - 1);
		P[ny][nx] = canak(ny, nx);
		anim(10, ny, nx, ny, nx - 1, ny - 1, nx - 1, ny - 1, nx);
		return 1;
	}

	return 0;
}
void Pomosh(int ny, int nx)
{
	if (pomosh1(ny, nx))
		return;
	int has = hash(ny, nx);
	int p;

	if (has == 1235 || has / 100 == 123 || has / 1000 == 123) {
		p = hash(ny + 1, nx);
		if (p == 2789 || p % 1000 == 789)
		{
			if (P[ny + 1][nx].Count < 10) {
				P[ny + 1][nx] = 11;
				P[ny][nx] = canak(ny, nx);
				anim(5, ny, nx, ny + 1, nx);
			}
			return;
		}
	}

	if (has == 1457 || has == 12457 || has == 124578 || has == 124579 || has == 13457 || has == 134578 || has == 134579 ||
		has == 14578 || has == 14579 || has == 1234578 || has == 1234579 || has == 123457 || has == 145789 || has == 1245789 || has == 1345789) {
		p = hash(ny, nx + 1);
		if (p == 3469 || p == 13469 || p == 134679 || p == 134689 || p == 23469 || p == 234679 || p == 234689 || p == 34679 ||
			p == 34689 || p == 123469 || p == 1234679 || p == 1234689 || p == 346789 || p == 1346789 || p == 2346789)
		{
			if (P[ny][nx + 1].Count < 10) {
				P[ny][nx + 1] = 11;
				P[ny][nx] = canak(ny, nx);
				anim(5, ny, nx, ny, nx + 1);
			}
			return;
		}
	}

	if (has == 3569 || has == 13569 || has == 23569 || has == 35679 || has == 35689 || has == 135679 || has == 135689 || has == 235679 ||
		has == 235689 || has == 123569 || has == 1235679 || has == 1235689 || has == 356789 || has == 1356789 || has == 2356789) {
		p = hash(ny, nx - 1);
		if (p == 1467 || p == 12467 || p == 13467 || p == 14678 || p == 14679 || p == 124678 || p == 124679 || p == 134678 || p == 134679 ||
			p == 123467 || p == 1234678 || p == 1234679 || p == 146789 || p == 1246789 || p == 1346789)
		{
			if (P[ny][nx - 1].Count < 10) {
				P[ny][nx - 1] = 11;
				P[ny][nx] = canak(ny, nx);
				anim(5, ny, nx, ny, nx - 1);
			}
			return;
		}
	}

	if (has == 5789 || has % 1000 == 789) {
		p = hash(ny - 1, nx);
		if (p == 1238 || p / 100 == 123 || p / 1000 == 123)
		{
			if (P[ny - 1][nx].Count < 10) {
				P[ny - 1][nx] = 11;
				P[ny][nx] = canak(ny, nx);
				anim(5, ny, nx, ny - 1, nx);
			}
			return;
		}
	}



}
void bac(int ny, int nx, int R)
{

	static int Nx, Ny;

	if (R > 0 && R < 4) {
		if (P[Ny][Nx].Xach)
			P[Ny][Nx].Xach = 0;
		else
			P[Ny][Nx].Xach = 1;
		glutTimerFunc(100, Xach, R + 1);
		return;
	}
	if (R != 0)return;
	if (R == 0) {
		P[Ny][Nx].Xach = 0;
		Nx = nx;
		Ny = ny;
	}

	int qan(0);

	for (int i = ny - 1; i <= ny + 1; i++)
		for (int j = nx - 1; j <= nx + 1; j++)
		{
			if (i < 0 || j < 0 || i >= mineH || j >= mineW)
				continue;
			if (P[i][j].drosh)
				qan++;
		}

	if (qan == P[ny][nx].Count)
	{

		for (int i = ny - 1; i <= ny + 1; i++)
			for (int j = nx - 1; j <= nx + 1; j++)
			{
				if (i < 0 || j < 0 || i >= mineH || j >= mineW)
					continue;
				if (!P[i][j].drosh)
					P[i][j].Bp = 1;
			}

	}
	else {
		if (!P[ny][nx].Bp) {

			if (P[ny][nx].Count < 9) {
				P[ny][nx].Bp = 1;
			}
			else { Pomosh(ny, nx); P[ny][nx].Bp = 1; }
		}
		else {
			P[ny][nx].Xach = 1;
			glutTimerFunc(100, Xach, R + 1);
		}
	}
}

void restart()
{
	for (int i = 0; i < mineH; i++)
		for (int j = 0; j < mineW; j++)
		{
			P[i][j].Bp = 0;
			P[i][j].drosh = 0;
			P[i][j].Count = 0;
			P[i][j].G_end = false;
		}

	mes[4] = minecount;
	mes[5] = 0;
	end = 0;
	Gnew = 1;
	win = 0;


}

void Wingame(int i)
{
	mous = 0;
	if (i >= mineH) {
		win = 1;
		Gnew = 1;
		end = 1;
		mous = 1;
		return;
	}
	for (int j = 0; j < mineW; j++)
	{

		if (i < mineH - 1) {
			P[i][j].Color = Green;
			P[i][j].Bp = 0;
		}

		if (i > 0) {
			P[i - 1][j].Color = Butcolor;
			P[i - 1][j].Bp = true;
		}

		if (P[i][j].Count > 10)
			P[i][j].Bp = true;

	}
	glutPostRedisplay();

	glutTimerFunc(75, Wingame, i + 1);


}

void InitWnd()
{
	Win.X = Win.Y = -200.0f;
	Win.W = listW * 1.5f;
	Win.H = listH * 1.5f;
	Win.Color = Window;

	mes[11].Y = mes[0].Y + mes[0].H * 0.75f;
	mes[11].X = mes[0].X + mes[0].W * 0.45f;


	mes[1].Y = mes[0].Y + mes[0].H * 0.1f;
	mes[1].X = mes[0].X + mes[0].W * 0.052f;

	mes[2].Y = mes[0].Y + mes[0].H * 0.1f;
	mes[2].X = mes[0].X + mes[0].W * 0.38f;

	mes[3].Y = mes[0].Y + mes[0].H * 0.1f;
	mes[3].X = mes[0].X + mes[0].W * 0.7f;

	mes[6].Y = mes[0].Y + mes[0].H * 0.8f;
	mes[6].X = mes[0].X + mes[0].W * 0.65f;

	mes[7].Y = mes[0].Y + mes[0].H * 0.6f;
	mes[7].X = mes[0].X + mes[0].W * 0.65f;

	mes[8].Y = mes[0].Y + mes[0].H * 0.4f;
	mes[8].X = mes[0].X + mes[0].W * 0.65f;

	//mes[10].Y = mes[0].Y + mes[0].H*0.4f;
	//mes[10].X = mes[0].X + mes[0].W*0.65f;

	Te[0].X = mes[0].X + mes[0].W * 0.05f;
	Te[0].Y = mes[0].Y + mes[0].H * 0.75f;

	Te[1].X = mes[0].X + mes[0].W * 0.05f;
	Te[1].Y = mes[0].Y + mes[0].H * 0.59f;

	Te[2].X = mes[0].X + mes[0].W * 0.05f;
	Te[2].Y = mes[0].Y + mes[0].H * 0.43f;

	for (int n = 0; n < 44; n++)
	{
		Col_but[n].X = mes[0].X + (n % 11) * Col_but[0].W;
		Col_but[n].Y = mes[0].Y - (n / 11 + 2) * Col_but[0].W;
	}
	for (int i = 44; i < 48; i++)
	{
		Col_but[i].X = mes[0].X + (i % 11) * Col_but[i].W;
		Col_but[i].Y = mes[0].Y - Col_but[0].W;
	}


}

int save()
{
	using namespace std;

	ofstream fout;
	fout.open("Setting.txt");

	fout << mineH << " " << mineW << " " << minecount << " " << Butcolor << " " << Background << " " << Textcol << " " << listH << " " << listW << " " << Window << " " << EN;
	return 0;

}

int open()
{
	using namespace std;
	int B, B1, B2, B3;
	ifstream fin;
	fin.open("Setting.txt");
	if (fin.is_open()) {

		fin >> mineH >> mineW >> minecount >> B >> B1 >> B2 >> listH >> listW >> B3 >> EN;
		Butcolor = (Colornum)B;
		Background = (Colornum)B1;
		Textcol = (Colornum)B2;
		Window = (Colornum)B3;
	}
	return 0;

}

