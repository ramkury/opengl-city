#pragma once
#include <GL/glut.h>

class Building
{
public:
	Building(GLint texture, bool mirror, bool transparent);
	void Draw();
	GLdouble x, y, height, width;
	GLint texture;
	bool mirror, transparent;
private:
	void DrawWall();
};

