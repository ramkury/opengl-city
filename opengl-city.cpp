#include <GL/glut.h>
#include <soil.h>
#include <vector>
#include "Camera.h"
#include "Building.h"

using namespace std;

Drone drone;
GLint ground_texture = 0, building_texture = 0, house_texture = 0;

vector<Building> buildings;

void LoadTextures()
{
	ground_texture   = loadTexture("textures/roads.png");
	building_texture = loadTexture("textures/building.png");
	//house_texture    = loadTexture("textures/house.png");
}

void CreateBuildings()
{
	Building b(building_texture, false, false);

	b.height = 5;
	b.width = 1.3;
	buildings.push_back(b);
	
	b.height = 2.5;
	b.width = 1.3;
	b.x = -2;
	buildings.push_back(b);
}

void setup() // Will only run once, on program startup
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.4f, .7f, .9f, 1.0f);
	LoadTextures();
	CreateBuildings();
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

void draw() // Renders the scene
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drone.UpdateViewParameters();

	DrawGround();
	for (auto& b : buildings)
	{
		b.Draw();
	}

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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