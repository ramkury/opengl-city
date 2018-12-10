#include "Camera.h"
#include <cstdio>

void Camera::OnWindowSizeChanged(GLsizei width, GLsizei height)
{
	if (height == 0) return;

	glViewport(0, 0, width, height);
	fAspect = width / (float)height;
}

Camera::Camera()
{
	pos.x = 0;
	pos.y = -10;
	pos.z = 3;
}

void Camera::UpdateViewParameters()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, fAspect, 0.01, 1300);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, pos.z, pos.x / 2, 0, pos.z / 2, 0, 0, 1);
}

void Camera::OnMouseEvent(int button, int state, int x, int y)
{
}

void Camera::KeyboardSpecial(int key, int x, int y)
{
	float step = 0.2;
	switch (key)
	{
	case GLUT_KEY_UP: // Moves upwards from the ground
		STEP_UP(pos.z, step, 10);
		break;
	case GLUT_KEY_DOWN: // Moves towards the ground
		STEP_DOWN(pos.z, step, 0.2);
		break;
	case GLUT_KEY_RIGHT: // Moves right
		STEP_UP(pos.x, step, 10);
		break;
	case GLUT_KEY_LEFT: // Moves left
		STEP_DOWN(pos.x, step, -10);
		break;
	default:
		break;
	}

	printf("X: %f, Y: %f, Z: %f\n", pos.x, pos.y, pos.z);
}
