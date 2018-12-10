#pragma once
#include <GL/glut.h>

class House
{
public:
	House();
	void Draw();
	GLdouble x, y;
	GLint wall_texture, ceiling_texture;
private:
	void DrawWall();
};

