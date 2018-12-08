#pragma once
#include "Utils.h"

class Camera
{
public:
	Camera();
	void UpdateViewParameters();
	void OnMouseEvent(int button, int state, int x, int y);
	void KeyboardSpecial(int key, int x, int y);
	void OnWindowSizeChanged(GLsizei width, GLsizei height);
protected:
	Point3f pos;
	GLdouble fAspect;
};

typedef Camera Drone;
