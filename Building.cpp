#include "Building.h"


Building::Building(GLint texture, bool mirror, bool transparent) : texture(texture), mirror(mirror), transparent(transparent)
{
	x = y = height = width = 0;
}

void Building::Draw()
{
	glColor4d(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslated(x, y, 0);

	// Front
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(-width / 2, 0, width / 2);
	DrawWall();
	glPopMatrix();

	// Back
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(-width / 2, 0, -width / 2);
	DrawWall();
	glPopMatrix();

	// Left
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(-width / 2, 0, -width / 2);
	DrawWall();
	glPopMatrix();

	// Right
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(-width / 2, 0, width / 2);
	DrawWall();
	glPopMatrix();

	glPopMatrix();
}

void Building::DrawWall()
{
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);

		glTexCoord2d(0, height);
		glVertex2d(0, height);

		glTexCoord2d(width, height);
		glVertex2d(width, height);

		glTexCoord2d(width, 0);
		glVertex2d(width, 0);
	}
	glEnd();
}
