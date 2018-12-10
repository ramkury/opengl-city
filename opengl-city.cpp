#include <GL/glut.h>
#include <soil.h>
#include <vector>
#include "Camera.h"
#include "Building.h"
#include "House.h"

using namespace std;

Drone drone;
GLint ground_texture = 0, building_texture = 0, brick_texture = 0, concrete_texture = 0,
	glass_texture = 0, rooftiles_texture = 0, mountain_texture = 0;

vector<Building> buildings;
vector<House> houses;

GLfloat sun_position[] = { 1, -20, 100 };
GLfloat sun_color[] = { 1, 0.65f, 0.46f, 1 };

void LoadTextures()
{
	ground_texture    = loadTexture("textures/roads.png");
	building_texture  = loadTexture("textures/building.png");
	concrete_texture  = loadTexture("textures/concrete.png");
	glass_texture     = loadTexture("textures/glass.png");
	brick_texture     = loadTexture("textures/brick.png");
	rooftiles_texture = loadTexture("textures/roof.png");
	mountain_texture  = loadTexture("textures/mountain2.png");
	glBindTexture(GL_TEXTURE_2D, mountain_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CreateBuildings()
{
	Building normal(building_texture, false, false);
	Building transp(building_texture, false, true);
	Building reflex(glass_texture, true, false);

	normal.ceiling_texture = concrete_texture;
	reflex.ceiling_texture = concrete_texture;
	transp.ceiling_texture = concrete_texture;

	normal.height = 5;
	normal.width = 1.3;
	buildings.push_back(normal);
	
	reflex.height = 2.5;
	reflex.width = 1.3;
	reflex.x = -2;
	buildings.push_back(reflex);

	transp.height = 3;
	transp.width = 1.3;
	transp.x = 2;
	buildings.push_back(transp);
}

void CreateHouses()
{
	houses.emplace_back(brick_texture, rooftiles_texture, 4, 0, 1.3);
}

void setup() // Will only run once, on program startup
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHT0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.4f, .7f, .9f, 1.0f);
	LoadTextures();
	CreateBuildings();
	CreateHouses();
}

void DrawGround()
{
	glColor3d(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, ground_texture);
	glBegin(GL_QUADS);

	glTexCoord2d(0, 10);
	glVertex2d(-10, 10);

	glTexCoord2d(0, 0);
	glVertex2d(-10, -10);

	glTexCoord2d(10, 0);
	glVertex2d(10, -10);

	glTexCoord2d(10, 10);
	glVertex2d(10, 10);

	glEnd();
}

void DrawBackground()
{
	glBindTexture(GL_TEXTURE_2D, mountain_texture);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0, 10, 0);
	glRotated(90, 1, 0, 0);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(-10, 0);
		
		glTexCoord2d(0, 1);
		glVertex2d(-10, 10);
		
		glTexCoord2d(1, 1);
		glVertex2d(10, 10);
		
		glTexCoord2d(1, 0);
		glVertex2d(10, 0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -10, 0);
	glRotated(90, 1, 0, 0);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(-10, 0);

		glTexCoord2d(0, 1);
		glVertex2d(-10, 10);

		glTexCoord2d(1, 1);
		glVertex2d(10, 10);

		glTexCoord2d(1, 0);
		glVertex2d(10, 0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10, 0, 0);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(-10, 0);

		glTexCoord2d(0, 1);
		glVertex2d(-10, 10);

		glTexCoord2d(1, 1);
		glVertex2d(10, 10);

		glTexCoord2d(1, 0);
		glVertex2d(10, 0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-10, 0, 0);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0);
		glVertex2d(-10, 0);

		glTexCoord2d(0, 1);
		glVertex2d(-10, 10);

		glTexCoord2d(1, 1);
		glVertex2d(10, 10);

		glTexCoord2d(1, 0);
		glVertex2d(10, 0);
	}
	glEnd();
	glPopMatrix();
}

void Lighting()
{
	glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_color);

	glLighti(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.3);
	glLighti(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.3);
	glLighti(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.3);
}

void draw() // Renders the scene
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drone.UpdateViewParameters();
	DrawBackground();
	DrawGround();

	for (auto& b : buildings)
	{
		b.Draw();
	}

	for (auto& h : houses)
	{
		h.Draw();
	}

	Lighting();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(900, 600);
	glutCreateWindow("OpenGL City");

	glutDisplayFunc(draw);

	glutReshapeFunc([](int w, int h) {
		drone.OnWindowSizeChanged(w, h);
	});

	glutMouseFunc([](int button, int state, int x, int y) {
		drone.OnMouseEvent(button, state, x, y);
	});

	glutSpecialFunc([](int key, int x, int y) {
		drone.KeyboardSpecial(key, x, y);
	});

	glutKeyboardFunc([](unsigned char key, int x, int y) {
		//TODO: if key == 's' start drone
	});

	glutIdleFunc([] {glutPostRedisplay(); });

	setup();
	glutMainLoop();

	return 0;
}