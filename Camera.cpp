#include "Camera.h"

void Camera::OnWindowSizeChanged(GLsizei width, GLsizei height)
{
	if (height == 0) return;

	glViewport(0, 0, width, height);
	fAspect = width / (float)height;
}

Camera::Camera()
{
	pos.x = 0;
	pos.y = 1;
	pos.z = 1;
}

void Camera::UpdateViewParameters()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, fAspect, 1, 1300);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, pos.z, 0, 0, 0, 0, 1, 0);
}

void Camera::OnMouseEvent(int button, int state, int x, int y)
{
}

void Camera::KeyboardSpecial(int key, int x, int y)
{
	float step = 1;
	switch (key)
	{
	case GLUT_KEY_UP: // Moves upwards from the ground
		STEP_UP(pos.z, step, 1000);
		break;
	case GLUT_KEY_DOWN: // Moves towards the ground
		STEP_DOWN(pos.z, step, 0);
		break;
	case GLUT_KEY_RIGHT: // Moves right
		STEP_UP(pos.x, step, 500);
		break;
	case GLUT_KEY_LEFT: // Moves left
		STEP_DOWN(pos.x, step, 0);
		break;
	default:
		break;
	}
}
