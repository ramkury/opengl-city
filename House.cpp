#include <cmath>
#include "House.h"
#include "Utils.h"

House::House(GLint wall_texture, GLint ceiling_texture, GLint x, GLint y, GLdouble width) : 
	wall_texture(wall_texture),
	ceiling_texture(ceiling_texture),
	x(x),
	y(y),
	width(width)
{
	height_house = 0.5;
	height_roof = 0.2;
	roof_angle = RAD2DEG(atan(height_roof / width));
}

void House::Draw()
{
	glColor4d(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, wall_texture);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslated(x, y, 0);

	// Front
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(-width / 2, 0, width / 2);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);

		glTexCoord2d(0, height_house);
		glVertex2d(0, height_house);

		glTexCoord2d(width, height_house);
		glVertex2d(width, height_house);
		
		glTexCoord2d(width, 0);
		glVertex2d(width, 0);
	}
	glEnd();
	glPopMatrix();

	// Back
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(-width / 2, 0, -width / 2);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);

		glTexCoord2d(0, height_house + height_roof);
		glVertex2d(0, height_house + height_roof);

		glTexCoord2d(width, height_house + height_roof);
		glVertex2d(width, height_house + height_roof);

		glTexCoord2d(width, 0);
		glVertex2d(width, 0);
	}
	glEnd();
	glPopMatrix();

	// Left
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(-width / 2, 0, -width / 2);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);

		glTexCoord2d(0, height_house);
		glVertex2d(0, height_house);

		glTexCoord2d(width, height_house + height_roof);
		glVertex2d(width, height_house + height_roof);

		glTexCoord2d(width, 0);
		glVertex2d(width, 0);
	}
	glEnd();
	glPopMatrix();

	// Right
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glTranslated(-width / 2, 0, width / 2);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);

		glTexCoord2d(0, height_house);
		glVertex2d(0, height_house);

		glTexCoord2d(width, height_house + height_roof);
		glVertex2d(width, height_house + height_roof);

		glTexCoord2d(width, 0);
		glVertex2d(width, 0);
	}
	glEnd();
	glPopMatrix();

	// Ceiling
	glBindTexture(GL_TEXTURE_2D, ceiling_texture);
	glPushMatrix();
	glTranslated(-width / 2, -width / 2, height_house);
	glRotated(roof_angle, 1, 0, 0);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);

		glTexCoord2d(0, width * 1.2);
		glVertex2d(0, width * 1.2);

		glTexCoord2d(width, width * 1.2);
		glVertex2d(width, width * 1.2);
		
		glTexCoord2d(width, 0);
		glVertex2d(width, 0);
	}
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

