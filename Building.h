#pragma once
#include <GL/glut.h>

class Building
{
public:
	Building(GLint wall_texture, bool mirror, bool transparent);
	void Draw();
	GLdouble x, y, height, width;
	GLint wall_texture, ceiling_texture;
	bool mirror, transparent;
private:
	void DrawWall();
	void DrawCeiling();
};

