#pragma once
#include <GL/glut.h>

#define STEP_UP(value, increment, limit) (value) += (increment); if ((value) > (limit)) (value) = (limit);
#define STEP_DOWN(value, decrement, limit) (value) -= (decrement); if ((value) < (limit)) (value) = (limit);
#define DEG2RAD(deg) ((deg) * 0.01745)
#define RAD2DEG(rad) ((rad) * 57.2960);

struct Point3f
{
	GLfloat x, y, z;
	Point3f() = default;
	Point3f(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
};

struct RGBColor
{
	GLubyte r, g, b;
	RGBColor() = default;
	RGBColor(GLubyte r, GLubyte g, GLubyte b) : r(r), g(g), b(b) {}
	void set() const {
		glColor3ub(r, g, b);
	}
};

GLint loadTexture(const char* name);