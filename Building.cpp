#include "Building.h"


Building::Building(GLint wall_texture, bool mirror, bool transparent) : wall_texture(wall_texture), mirror(mirror), transparent(transparent)
{
	x = y = height = width = 0;
}

void Building::Draw()
{
	glBindTexture(GL_TEXTURE_2D, wall_texture);

	if (mirror)
	{
		glDisable(GL_BLEND);
		glDisable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		GLfloat specular[] = { 1, 1, 1, 0 };
		GLfloat ambient[] = { 1, 1, 1, 0 };
		GLfloat diffuse[] = { 1, 1, 1, 0 };

		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
	}
	else
	{
		glEnable(GL_BLEND);
		glEnable(GL_COLOR_MATERIAL);
		glDisable(GL_LIGHTING);
		transparent ? glColor4d(1, 1, 1, 0.5) : glColor4d(1, 1, 1, 1);
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslated(x, y, 0);

	// Front
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(-width / 2, 0, width / 2);
	glNormal3f(0, -1, 0);
	DrawWall();
	glPopMatrix();

	// Back
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(-width / 2, 0, -width / 2);
	glNormal3f(0, 1, 0);
	DrawWall();
	glPopMatrix();

	// Left
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(-width / 2, 0, -width / 2);
	glNormal3f(-1, 0, 0);
	DrawWall();
	glPopMatrix();

	// Right
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(-width / 2, 0, width / 2);
	glNormal3f(1, 0, 0);
	DrawWall();
	glPopMatrix();

	// Ceiling
	glBindTexture(GL_TEXTURE_2D, ceiling_texture);
	glPushMatrix();
	glTranslated(-width / 2, -width / 2, height);
	glNormal3f(0, 0, 1);
	DrawCeiling();

	glPopMatrix();

	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
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

void Building::DrawCeiling()
{
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);

		glTexCoord2d(0, width);
		glVertex2d(0, width);

		glTexCoord2d(width, width);
		glVertex2d(width, width);

		glTexCoord2d(width, 0);
		glVertex2d(width, 0);
	}
	glEnd();
}
