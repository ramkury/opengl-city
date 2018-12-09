#include "Building.h"


Building::Building(GLint texture, bool mirror, bool transparent) : texture(texture), mirror(mirror), transparent(transparent)
{
	x = y = height = width = 0;
}

void Building::Draw()
{
	glColor3d(1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);

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

}

void Building::DrawWall()
{
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 10);
		glVertex2d(0, 0);

		glTexCoord2d(0, 0);
		glVertex2d(0, height);

		glTexCoord2d(10, 0);
		glVertex2d(width, height);

		glTexCoord2d(10, 10);
		glVertex2d(width, 0);
	}
	glEnd();
}
