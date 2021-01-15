#include "GL.h"


//*////////////////////////////////

extern HDC hDC;
extern GLuint  arialbig;
extern GLuint  arialsm;

//-- Парметры Материала Куба ------
float mat_dif[] = { 0.0f, 0.5f, 1.0f };
float mat_amb[] = { 0.2f, 0.2f, 0.2f };
float mat_spec[] = { 0.6f, 0.6f, 0.6f };
float mat_shininess = 0.5f * 128;

//*////////////////////Fun

GLuint BuildFont(int size, const char* fontname)
{
	HFONT   font;
	HFONT   oldfont;
	GLuint basefont;

	basefont = glGenLists(255);
	font = CreateFontA(-size, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
		RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, DEFAULT_QUALITY | DEFAULT_PITCH,
		fontname);

	oldfont = (HFONT)SelectObject(hDC, font);
	wglUseFontBitmaps(hDC, 32, 224, basefont);
	SelectObject(hDC, oldfont);
	DeleteObject(font);
	return basefont;
}

GLvoid KillFont(GLuint basefont)
{
	glDeleteLists(basefont, 255);
}

GLvoid glText(GLfloat x, GLfloat y, const char* txt, GLuint basefont)
{
	glRasterPos2d(x, y);
	glPushAttrib(GL_LIST_BIT);
	glListBase(basefont - 32);
	glCallLists((GLsizei)strlen(txt), GL_UNSIGNED_BYTE, txt);
	glPopAttrib();
}


GLvoid InitMat()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}


////////////////*///
void ColorInit(Colornum color, float tiv)
{
	switch (color)
	{
	case Red:				glColor3f(1.00f + tiv, 0.00f + tiv, 0.00f + tiv);	break;
	case Blue:				glColor3f(0.00f + tiv, 0.00f + tiv, 1.00f + tiv);	break;
	case Black:				glColor3f(0.00f + tiv, 0.00f + tiv, 0.00f + tiv);	break;
	case White:				glColor3f(1.00f + tiv, 1.00f + tiv, 1.00f + tiv);	break;
	case Yellow:			glColor3f(0.00f + tiv, 1.00f + tiv, 0.00f + tiv);	break;
	case Green:				glColor3f(0.40f + tiv, 0.80f + tiv, 0.00f + tiv);	break;
	case Water:				glColor3f(0.15f + tiv, 0.15f + tiv, 0.15f + tiv);	break;
	case Plastic:			glColor3f(0.21f + tiv, 0.21f + tiv, 0.21f + tiv);	break;
	case Glass:				glColor3f(0.31f + tiv, 0.31f + tiv, 0.31f + tiv);	break;
	case Diamond:			glColor3f(0.45f + tiv, 0.45f + tiv, 0.45f + tiv);	break;
	case Iron:				glColor3f(0.77f + tiv, 0.78f + tiv, 0.78f + tiv);	break;
	case Copper:			glColor3f(0.98f + tiv, 0.82f + tiv, 0.76f + tiv);	break;
	case Gold:				glColor3f(1.00f + tiv, 0.90f + tiv, 0.00f + tiv);	break;
	case Aluminum:			glColor3f(0.96f + tiv, 0.96f + tiv, 0.97f + tiv);	break;
	case Silver:			glColor3f(0.70f + tiv, 0.70f + tiv, 0.70f + tiv);	break;
	case DeepSkyBlue:		glColor3f(0.30f + tiv, 0.70f + tiv, 1.00f + tiv);	break;
	case Lightskyblue:		glColor3f(0.30f + tiv, 0.80f + tiv, 1.00f + tiv);	break;
	case Mistyrose:			glColor3f(0.40f + tiv, 1.00f + tiv, 0.80f + tiv);	break;
	case Burlywood:			glColor3f(0.90f + tiv, 0.70f + tiv, 0.50f + tiv);	break;
	case Violet:			glColor3f(1.00f + tiv, 0.50f + tiv, 1.00f + tiv);	break;
	case Whitesmoke:		glColor3f(0.90f + tiv, 0.90f + tiv, 0.90f + tiv);	break;
	case Cyan:				glColor3f(0.00f + tiv, 1.00f + tiv, 1.00f + tiv);	break;
	case Lime:				glColor3f(0.00f + tiv, 1.00f + tiv, 0.00f + tiv);	break;
	case Tan:				glColor3f(1.00f + tiv, 0.60f + tiv, 0.60f + tiv);	break;
	case Lightgray:			glColor3f(0.80f + tiv, 0.70f + tiv, 0.70f + tiv);	break;
	case Lightsteelblue:	glColor3f(0.00f + tiv, 0.90f + tiv, 0.80f + tiv);	break;
	case Yellowgreen:		glColor3f(0.40f + tiv, 0.90f + tiv, 0.10f + tiv);	break;
	case Orange:			glColor3f(0.90f + tiv, 0.70f + tiv, 0.10f + tiv);	break;
	case Coral:				glColor3f(1.00f + tiv, 0.30f + tiv, 0.30f + tiv);	break;
	case Fuchsia:			glColor3f(1.00f + tiv, 0.00f + tiv, 0.90f + tiv);	break;
	case Dodgerblue:		glColor3f(0.60f + tiv, 0.30f + tiv, 0.10f + tiv);	break;
	case Plum:				glColor3f(0.00f + tiv, 0.70f + tiv, 0.70f + tiv);	break;
	case Limegreen:			glColor3f(0.40f + tiv, 0.80f + tiv, 0.00f + tiv);	break;
	case Olive:				glColor3f(0.80f + tiv, 0.50f + tiv, 0.20f + tiv);	break;
	case Darkmagenta:		glColor3f(0.60f + tiv, 0.00f + tiv, 0.60f + tiv);	break;
	case Gray:				glColor3f(0.40f + tiv, 0.40f + tiv, 0.40f + tiv);	break;
	case Dimgray:			glColor3f(0.00f + tiv, 0.40f + tiv, 0.40f + tiv);	break;
	case Brown:				glColor3f(0.70f + tiv, 0.00f + tiv, 0.00f + tiv);	break;
	case Darkslategray:		glColor3f(0.00f + tiv, 0.30f + tiv, 0.30f + tiv);	break;
	case Firebrick:			glColor3f(0.20f + tiv, 0.30f + tiv, 0.00f + tiv);	break;
	case Sienna:			glColor3f(0.40f + tiv, 0.20f + tiv, 0.10f + tiv);	break;
	case Maroon:			glColor3f(0.50f + tiv, 0.00f + tiv, 0.00f + tiv);	break;
	case Darkblue:			glColor3f(0.20f + tiv, 0.00f + tiv, 0.40f + tiv);	break;
	case Navy:				glColor3f(0.10f + tiv, 0.10f + tiv, 0.30f + tiv);	break;

	default:
		break;
	}

}


int autosize(char* Text, Size Textsize)
{
	int text_size(0), Zaz(0), result(0);

	while (Text[text_size] != '\0')
	{
		if (Text[text_size] <= 89 && Text[text_size] >= 65)
			Zaz += 5;
		else Zaz += 1;
		text_size++;
	}

	if (Textsize == Big)
		result = Zaz + text_size * 12;
	if (Textsize == Small)
		result = text_size * 9 + 30;

	return  result;
}

void TextPrint(char* Text, float X, float Y, float W, float H, TopL Top, Size Textsize, Colornum Textcolor, int size_font, Position pos)
{

	int text_size(0), Zaz(0);

	while (Text[text_size] != '\0')
	{
		if (Text[text_size] <= 89 && Text[text_size] >= 65)
			Zaz++;
		text_size++;
	}
	float  zaz(0), zazh(0), zazw(1);

	if (Text) {
		int  i(0), Exit(0);

		switch (pos)
		{
		case Left: zazw = autosize(Text, Textsize);
			break;
		case Centery:
			break;
		case Right:
			break;
		default:
			break;
		}

		switch (Top)
		{
		case Center:	zazh = 0;
			break;
		case Up:		zazh = W * 0.2;
			break;
		case Down:		zazh = -W * 0.1;
			break;
		default:
			break;
		}

		ColorInit(Textcolor, 0);


		///	int Ats;
		//	Ats = autosize(Text, Textsize);
		//	if (W < Ats)
		//		Textposition = Left;

	}

	if (Textsize == Big)
		glText(X + W * 0.4 - text_size * size_font * 0.2 - zazw * 0.4, Y + H * 0.3 + zazh, Text, arialbig);
	else
		glText(X + W * 0.4 - text_size * size_font * 0.2 - zazw * 0.4, Y + H * 0.35 + zazh, Text, arialsm);
}


/////////////////////////////////////////////////////////////////////////nkarner
void Flagprint(int X, int Y, int H, int W)
{

	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.8f, 1.0f);



	glVertex2f(X + W * 0.1f, Y + H * 0.15f);
	glVertex2f(X + W * 0.9f, Y + H * 0.15f);

	glVertex2f(X + W * 0.9f, Y + H * 0.18f);
	glVertex2f(X + W * 0.8f, Y + H * 0.2f);
	glVertex2f(X + W * 0.2f, Y + H * 0.2f);
	glVertex2f(X + W * 0.1f, Y + H * 0.18f);

	glEnd();


	glBegin(GL_POLYGON);

	glColor3f(0.3f, 0.4f, 0.0f);



	glVertex2f(X + W * 0.47f, Y + H * 0.2f);
	glVertex2f(X + W * 0.52f, Y + H * 0.2f);

	glVertex2f(X + W * 0.52f, Y + H * 0.9f);
	glVertex2f(X + W * 0.47f, Y + H * 0.9f);

	glEnd();

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex2f(X + W * 0.1f, Y + H * 0.7f);

	glVertex2f(X + W * 0.50f, Y + H * 0.5f);
	glVertex2f(X + W * 0.50f, Y + H * 0.9f);

	glEnd();


}

void Mineprint(int X, int Y, int H, int W)
{

	glBegin(GL_POLYGON);

	glColor3f(0.2f, 0.2f, 0.2f);

	for (float i = 0; i < 6; i += 0.1)
	{
		glVertex2f(X + W / 2 + cos(i) * W * 0.2, Y + H / 2 + sin(i) * W * 0.2);
	}

	glEnd();


	glBegin(GL_POLYGON);

	glColor3f(0.2f, 0.2f, 0.2f);

	for (float i = 0; i < 6; i += 1)
	{
		glVertex2f(X + W / 2 + cos(i - 0.4) * W * 0.1, Y + H / 2 + sin(i - 0.4) * W * 0.1);
		glVertex2f(X + W / 2 + cos(i) * W * 0.4, Y + H / 2 + sin(i) * W * 0.4);
		glVertex2f(X + W / 2 + cos(i + 0.4) * W * 0.1, Y + H / 2 + sin(i + 0.4) * W * 0.1);
	}

	glEnd();



	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.7f, 0.7f);

	for (float i = 0; i < 6; i += 0.1)
	{
		glVertex2f(X + W * 0.4 + cos(i) * W * 0.04, Y + H * 0.5 + sin(i) * W * 0.04);
	}

	glEnd();
}

void Xprint(int X, int Y, int H, int W) {

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(X + W * 0.05f, Y + H * 0.1f);
	glVertex2f(X + W * 0.1f, Y + H * 0.05f);
	glVertex2f(X + W * 0.95f, Y + H * 0.9f);
	glVertex2f(X + W * 0.9f, Y + H * 0.95f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(X + W * 0.9f, Y + H * 0.05f);
	glVertex2f(X + W * 0.95f, Y + H * 0.1f);
	glVertex2f(X + W * 0.1f, Y + H * 0.95f);
	glVertex2f(X + W * 0.05f, Y + H * 0.9f);
	glEnd();

}
////////////////////////////////////////////////////////////////////////knopka

Label::Label()
{
	textposition = Centery;
	Count = 0;
	Size_font = 15;
	X = Y = 10;
	W = H = 100;
	Enabled = true;
	Transporent = true;
	Autosize = false;
	Bp = false;
	drosh = false;
	butt = false;
	G_end = false;
	Xach = false;
	Bum = false;
	Color = DeepSkyBlue;
	Coloropen = White;
	Textcolor = Black;
	Textsize = Big;
	Top = Center;
	Text = new char[25];
	Text[0] = '0';
	Text[1] = '\0';

}

Label::~Label()
{
	//	delete[] Text;
}

char* Label::operator=(char* text)
{
	int text_size(0), i(0);
	Count = 0;


	while (text[text_size] != '\0')
		text_size++;



	while (i <= text_size && i < 25)
	{
		Text[i] = text[i];
		if (text[i] == '\0')
			break;
		i++;
	}





	return Text;
}

char* Label::operator=(int count)
{
	int  i(0);
	Count = count;


	char text[15];
	sprintf_s(text, "%d", count);


	while (i <= 15)
	{
		Text[i] = text[i];
		if (text[i] == '\0')
			break;
		i++;
	}

	return Text;
}

int Label::operator+= (int count)
{
	Count += count;
	this->operator=(Count);
	return Count;
}

int Label::operator-= (int count)
{
	Count -= count;
	this->operator=(Count);
	return Count;
}

int Label::Init(int end)
{
	Colornum Col = Color;

	if (!Enabled)
		return 0;
	if (Autosize)
	{
		W = autosize(Text, Textsize) + 30;
	}

	if (Transporent) {

		glBegin(GL_POLYGON);

		if (!butt)
			if (!Bp)
				Col = Color;
			else
				Col = Coloropen;

		ColorInit(Col, 0);

		glVertex2f(X, Y + H * 0.1f);
		glVertex2f(X + W * 0.03f, Y + H * 0.03f);
		glVertex2f(X + W * 0.1f, Y);


		ColorInit(Col, -0.1);

		glVertex2f(X + W * 0.9f, Y);
		glVertex2f(X + W * 0.97f, Y + H * 0.03f);
		glVertex2f(X + W, Y + H * 0.1f);

		ColorInit(Col, 0.1);

		glVertex2f(X + W, Y + H * 0.9f);
		glVertex2f(X + W * 0.97f, Y + H * 0.97f);
		glVertex2f(X + W * 0.9f, Y + H);

		ColorInit(Col, 0.2);

		glVertex2f(X + W * 0.1f, Y + H);
		glVertex2f(X + W * 0.03f, Y + H * 0.97f);
		glVertex2f(X, Y + H * 0.9f);

		glEnd();


		glBegin(GL_LINES);

		glColor3f(0, 0, 0);

		glVertex2f(X, Y + H * 0.1f);
		glVertex2f(X + W * 0.03f, Y + H * 0.03f);

		glVertex2f(X + W * 0.03f, Y + H * 0.03f);
		glVertex2f(X + W * 0.1f, Y);

		glVertex2f(X + W * 0.1f, Y);
		glVertex2f(X + W * 0.9f, Y);

		glVertex2f(X + W * 0.9f, Y);
		glVertex2f(X + W * 0.97f, Y + H * 0.03f);

		glVertex2f(X + W * 0.97f, Y + H * 0.03f);
		glVertex2f(X + W, Y + H * 0.1f);

		glVertex2f(X + W, Y + H * 0.1f);
		glVertex2f(X + W, Y + H * 0.9f);

		glVertex2f(X + W, Y + H * 0.9f);
		glVertex2f(X + W * 0.97f, Y + H * 0.97f);

		glVertex2f(X + W * 0.97f, Y + H * 0.97f);
		glVertex2f(X + W * 0.9f, Y + H);

		glVertex2f(X + W * 0.9f, Y + H);
		glVertex2f(X + W * 0.1f, Y + H);

		glVertex2f(X + W * 0.1f, Y + H);
		glVertex2f(X + W * 0.03f, Y + H * 0.97f);

		glVertex2f(X + W * 0.03f, Y + H * 0.97f);
		glVertex2f(X, Y + H * 0.9f);

		glVertex2f(X, Y + H * 0.9f);
		glVertex2f(X, Y + H * 0.1f);

		glEnd();

	}

	if (Count == 0 && Bp && !butt)
		return 1;
	if (Bum)
	{
		Mineprint(X, Y, H, W);
		return 0;
	}

	if (Bp && Count < 10 || butt)
		if (Text)
		{
			TextPrint(Text, X, Y, W, H, Top, Textsize, Textcolor, Size_font, textposition);

			if (Xach)		Xprint(X, Y, H, W);
			return 3;
		}



	if (Bp)///mine
	{
		if (Count >= 10)
		{
			Mineprint(X, Y, H, W);
			if (G_end)
				Xprint(X, Y, H, W);
			if (drosh)
				Flagprint(X, Y, H, W);
			return 2;
		}
	}


	if (drosh) {
		Flagprint(X, Y, H, W);
		if (Count < 10 && end)
			Xprint(X, Y, H, W);
	}



	return 0;


}

int Label::Mouse(int button, int state, int ax, int ay)
{
	x1 = ax - X;
	y1 = ay - Y;
	if (button == 0)
		is_klick = true;
	else is_klick = false;

	if (ax >= X && ax <= X + W && ay >= Y && ay <= Y + H) {
		if (state)
			if (button == 0)
			{
				return 1;
			}
			else {
				if (button == 2)
					return 2;
			}

	}
	else	is_klick = false;

	return 0;

}

int Label::Mouse(int ax, int ay)
{
	if (is_klick) {
		if (ax > X && ax<X + W && ay>Y && ay < Y + H) {
			X = ax - x1;
			Y = ay - y1;
			return 1;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////


Textbox::Textbox()
{
	Count = 0;
	X = Y = 10;
	W = 70;
	H = 30;
	Enabled = true;
	Autosize = false;
	Color = White;
	Textcolor = Black;
	Textsize = Small;
	Top = Center;
	Text = new char[50];

	Text[0] = '\0';
	Read = false;
	Textboxcount = true;


}

Textbox::~Textbox()
{
	delete[] Text;
}

char* Textbox::operator=(char* text)
{
	int text_size(0), i(0);
	Count = 0;


	while (text[text_size] != '\0')
		text_size++;



	while (i <= text_size && i < 48)
	{
		Text[i] = text[i];
		Text[i + 1] = '\0';
		if (text[i] == '\0')
			break;
		i++;
	}





	return Text;
}

char* Textbox::operator=(int count)
{
	int  i(0);
	Count = count;


	char text[15];
	sprintf_s(text, "%d", count);


	while (i <= 14)
	{
		Text[i] = text[i];
		Text[i + 1] = '\0';
		if (text[i] == '\0')
			break;
		i++;
	}

	return Text;
}

int Textbox::operator+= (int count)
{
	Count += count;
	this->operator=(Count);
	return Count;
}

int Textbox::operator-= (int count)
{
	Count -= count;
	this->operator=(Count);
	return Count;
}

void Textbox::Init()
{

	if (!Enabled)
		return;

	if (Autosize)
		W = autosize(Text, Textsize) + 30;

	if (!Transparent) {

		glBegin(GL_POLYGON);

		ColorInit(Color, 0);
		glVertex2f(X, Y);

		ColorInit(Color, -0.1);
		glVertex2f(X, Y + H);

		ColorInit(Color, 0.1);
		glVertex2f(X + W, Y + H);

		ColorInit(Color, 0.2);
		glVertex2f(X + W, Y);


		glEnd();


		glBegin(GL_LINES);

		if (Read)
			glColor3f(1.0f, 0.6f, 0.6f);
		else
			glColor3f(0.0f, 0.6f, 0.6f);

		glVertex2f(X, Y);
		glVertex2f(X, Y + H);

		glVertex2f(X, Y + H);
		glVertex2f(X + W, Y + H);

		glVertex2f(X + W, Y + H);
		glVertex2f(X + W, Y);

		glVertex2f(X + W, Y);
		glVertex2f(X, Y);


		glVertex2f(X + W * 0.03f, Y + H * 0.05f);
		glVertex2f(X + W * 0.03f, Y + H * 0.95f);

		glVertex2f(X + W * 0.03f, Y + H * 0.95f);
		glVertex2f(X + W * 0.97f, Y + H * 0.95f);

		glVertex2f(X + W * 0.97f, Y + H * 0.95f);
		glVertex2f(X + W * 0.97f, Y + H * 0.05f);

		glVertex2f(X + W * 0.97f, Y + H * 0.05f);
		glVertex2f(X + W * 0.03f, Y + H * 0.05f);

		glEnd();

	}

	TextPrint(Text, X + W * 0.045, Y, W - W * 0.05, H, Top, Textsize, Textcolor, Size_font, Centery);

	TextPrint(Caption, X + W * 0.5, Y, 100, H, Top, Textsize, Textcolor, Size_font, Centery);


}
///////////
void Textbox::Mouse(int button, int state, int ax, int ay)
{
	if (state)
		if (ax >= X && ax <= X + W && ay >= Y && ay <= Y + H)
		{
			Read = true;
			this->operator=(0);
		}
		else	Read = false;
}

void Textbox::Keys(unsigned char key)
{
	if (Read)
	{
		int i(0);
		while (Text[i] != '\0')
		{
			i++;

		}
		if (key != 8)
		{
			if (i >= 49)
				return;
			if (key >= 32 && key <= 126) {

				if (Textboxcount)
					if (key >= 48 && key <= 57)
						if (Count < 150)
							this->operator=(Count * 10 + key - 48);

				if (!Textboxcount) {
					Text[i] = key;
					Text[i + 1] = '\0';
				}
			}
		}
		else {
			if (!Textboxcount) {
				if (i > 0)
					Text[i - 1] = '\0';
			}
			else
				this->operator=(Count / 10);

		}
	}


}
