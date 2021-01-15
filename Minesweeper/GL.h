#pragma once
#include <GL\freeglut.h>
#include <GL\glut.h>
#include <string>
#include <stdio.h>
#include <ctime>
#include <random>
#include <cmath>
#include <fstream>
#include <iostream>
#include <windows.h>     
#include <stdarg.h>




//*/////////////////////////////////////////////

GLvoid KillFont(GLuint basefont);
GLvoid InitMat();
GLvoid glText(GLfloat x, GLfloat y, const char* txt, GLuint basefont);
GLuint BuildFont(int size, const char* fontname);

//---------------------------


////////////////////////////////////////*///
enum Size { Big, Small };
enum TopL { Up, Down, Center };
enum Position { Left, Centery, Right };
enum Colornum {
	Red, Blue, Black, White, Yellow, Green, Water, Plastic, Glass,
	Diamond, Iron, Copper, Gold, Aluminum, Silver, DeepSkyBlue, Lightskyblue, Mistyrose,
	Burlywood, Violet, Whitesmoke, Cyan, Lime, Tan, Lightgray, Lightsteelblue,
	Yellowgreen, Orange, Coral, Fuchsia, Dodgerblue, Plum, Limegreen,
	Olive, Darkmagenta, Gray, Dimgray, Brown, Darkslategray, Firebrick,
	Sienna, Maroon, Darkblue, Navy
};
///////////////////////////////////////*///
class Label
{
public:
	Label();
	~Label();

	float X, Y, H, W;
	int Count, Size_font;
	bool Enabled, Autosize, Bp, drosh, butt, G_end, Xach, Bum, Transporent;
	char* Text;
	Position textposition;
	Colornum Color;
	Colornum Textcolor;
	Colornum Coloropen;
	Size  Textsize;
	TopL Top;

	char* operator=(char*);
	char* operator=(int);
	int Label::operator+= (int);
	int Label::operator-= (int);
	int Init(int = 0);

	bool is_klick;
	float x1, y1;
	int Mouse(int, int, int, int);
	int Mouse(int ax, int ay);
};
///////////////////////////////////////*///
class Textbox
{
public:
	Textbox();
	~Textbox();

	float X, Y, H, W;
	int Count, Size_font;
	bool Enabled, Autosize, Transparent, Textboxcount;
	char* Text;
	char* Caption;
	Colornum Color;
	Colornum Textcolor;
	Size  Textsize;
	TopL Top;
	//	Position Textposition;

	char* operator=(char*);
	char* operator=(int);
	int operator+= (int);
	int operator-= (int);
	void Init();

	void Mouse(int, int, int, int);
	void Keys(unsigned char key);

private:
	bool Read;
};

/*/////////////////////////////////////////

class cLight
{
private:
	GLfloat position[3];
	GLfloat ambient[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLenum cap;
public:
	cLight(GLfloat cx, GLfloat cy, GLfloat cz, unsigned char id)
	{
		position[0] = cx;
		position[1] = cy;
		position[2] = cz;
		position[3] = 0.0f;

		ambient[0] = 0.0f;
		ambient[1] = 0.0f;
		ambient[2] = 0.0f;
		ambient[3] = 1.0f;

		diffuse[0] = 1.0f;
		diffuse[1] = 1.0f;
		diffuse[2] = 1.0f;
		diffuse[3] = 1.0f;

		specular[0] = 1.0f;
		specular[1] = 1.0f;
		specular[2] = 1.0f;
		specular[3] = 1.0f;

		switch (id)
		{
		case 0: cap = 0x4000; break;
		case 1: cap = 0x4001; break;
		case 2: cap = 0x4002; break;
		case 3: cap = 0x4003; break;
		case 4: cap = 0x4004; break;
		case 5: cap = 0x4005; break;
		case 6: cap = 0x4006; break;
		case 7: cap = 0x4007; break;
		}
	}
	~cLight() {}

	void Position(GLfloat cx, GLfloat cy, GLfloat cz)
	{
		position[0] = cx;
		position[1] = cy;
		position[2] = cz;
		glLightfv(cap, GL_POSITION, position);
	}

	void Init()
	{
		glLightfv(cap, GL_AMBIENT, ambient);
		glLightfv(cap, GL_DIFFUSE, diffuse);
		glLightfv(cap, GL_SPECULAR, specular);
		glLightfv(cap, GL_POSITION, position);
		glEnable(cap);
	}
};
///////////////////////////////////////*///