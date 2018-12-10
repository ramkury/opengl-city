#pragma once
#include <GL/glut.h>

class House
{
public:
	House(GLint wall_texture, GLint ceiling_texture, GLint x, GLint y, GLdouble width);
	void Draw();
	GLdouble height_house, height_roof, x, y, width;
	GLint wall_texture, ceiling_texture;
private:
	GLdouble roof_angle;
};

