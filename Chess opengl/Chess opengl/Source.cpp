#include <iostream>
#include <ctime>
#include <vector>
#include <glut.h>


using namespace std;
float _angle = 0;
vector<int>v1;


GLuint _displayListId_blackArea; //The OpenGL id of the display list
GLuint _displayListId_whiteArea; //The OpenGL id of the display list
class Vector
{
public:
	Vector(float X = 0.0, float Y = 0.0, float Z = 0.0)
		: x(X), y(Y), z(Z)
	{}

	static Vector Cross(const Vector& vec1, const Vector& vec2)
	{
		Vector vecCross;

		vecCross.x = vec1.y * vec2.z - vec1.z * vec2.y;
		vecCross.y = vec1.z * vec2.x - vec1.x * vec2.z;
		vecCross.z = vec1.x * vec2.y - vec1.y * vec2.x;

		vecCross.Normalize();
		return vecCross;
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float Len = Length();
		x /= Len;
		y /= Len;
		z /= Len;
	}

	float x, y, z;
};
Vector vecEye(0, 0, 0);
Vector vecViewDirection(0, 0, -1);
Vector vecUp(0, 1, 0);
int k = 0;
float width, height;

const float MOVEMENT_SPEED = 0.1;
float angleY = 0.0;
bool animation = false;
double zp1, zp2, zp3, zq1, zq2, zb, zpb, zq12;
int counter = 0;
bool bLighting = true;
bool turn = false;

void DrawAxes()
{
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // x-axis
	glVertex3f(0, 0, 0);
	glVertex3f(.15, 0, 0);

	glColor3f(0, 1, 0); // y-axis
	glVertex3f(0, 0, 0);
	glVertex3f(0, .15, 0);

	glColor3f(0, 0, 1);// z-axis
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, .15);
	glEnd();
	glLineWidth(1.0);
}
void renderBitmapString(float x, float y, float z, void* font, const char* string)
{
	const char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}


void pawn() {
	// left side
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();

	// front side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();

	// right side
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();

	// back side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();

	glEndList();
	// -------------- //

}

void Movingpawn1() {
	if (animation&&counter == 0) {
		if (zp1 > -4)
			zp1 -= 0.01;
		else if (counter < 1) counter++;
	}
	// left side
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();

	// front side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();

	// right side
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();

	// back side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();

	glEndList();
	// -------------- //

}
void Movingpawn2() {
	if (animation&&counter == 1) {
		if (zp2 < 4)
			zp2 += 0.01;
		else if (counter < 2) counter++;
	}
	// left side
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();

	// front side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();

	// right side
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();

	// back side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();

	glEndList();
	// -------------- //

}
void Movingpawn3() {
	if (animation&&counter == 5) {
		if (zp3 < 2)
			zp3 += 0.01;
		else if (counter < 6) {
			counter++;
			turn = true;
		}
	}
	// left side
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();

	// front side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();

	// right side
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();

	// back side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();

	glEndList();
	// -------------- //

}
void Movingqueen1() {
	if (animation&&counter == 2) {
		if (zq1 > -4)
			zq1 -= 0.01;

		else if (counter < 3) counter++;
	}
	if (animation&& counter == 6) {
		if (zq12 > -8)
			zq12 -= 0.01;
	}
	else if (counter < 7 && turn) counter++;

	static GLUquadric* queenSphere = gluNewQuadric();
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glEnd();

	// front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glEnd();

	// right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glEnd();

	// back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glEnd();

	// the head
	// lower left side
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glEnd();

	// top plate
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glEnd();

	// left triangles
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glVertex3f(-0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glVertex3f(-0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(-0.65f, 4.0f, -0.65f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(-0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glEnd();

	// front triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, 0.65f);
	glVertex3f(0.0f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, 0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, 0.65f);
	glVertex3f(-0.65f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, 0.65f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glEnd();

	// right triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);
	glVertex3f(0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(0.65f, 4.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);
	glVertex3f(0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(0.65f, 4.0f, -0.65f);
	glEnd();

	// back triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, -0.65f);
	glVertex3f(0.0f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, -0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, -0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, -0.65f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glEnd();

	// sphere
	glTranslatef(0.0f, 3.0f + (2.0f / 2.0f + 0.05f), 0.0f);
	glScalef(0.12f, 0.1f, 0.12f);
	gluSphere(queenSphere, 2.0f, 64, 64);

	glEndList();

	// -------------- //
}
void Movingqueen2() {
	if (animation&&counter == 3) {
		if (zq2 < 8)
			zq2 += 0.01;
		else if (counter < 4) counter++;
	}

	static GLUquadric* queenSphere = gluNewQuadric();
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glEnd();

	// front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glEnd();

	// right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glEnd();

	// back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glEnd();

	// the head
	// lower left side
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glEnd();

	// top plate
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glEnd();

	// left triangles
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glVertex3f(-0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glVertex3f(-0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(-0.65f, 4.0f, -0.65f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(-0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glEnd();

	// front triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, 0.65f);
	glVertex3f(0.0f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, 0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, 0.65f);
	glVertex3f(-0.65f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, 0.65f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glEnd();

	// right triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);
	glVertex3f(0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(0.65f, 4.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);
	glVertex3f(0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(0.65f, 4.0f, -0.65f);
	glEnd();

	// back triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, -0.65f);
	glVertex3f(0.0f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, -0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, -0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, -0.65f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glEnd();

	// sphere
	glTranslatef(0.0f, 3.0f + (2.0f / 2.0f + 0.05f), 0.0f);
	glScalef(0.12f, 0.1f, 0.12f);
	gluSphere(queenSphere, 2.0f, 64, 64);

	glEndList();

	// -------------- //
}
void Movingbishop() {
	if (animation&&counter == 4) {
		if (zb > -6)
			zb -= 0.01;
		else if (counter < 5) counter++;
	}
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glEnd();

	// front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glEnd();

	// right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glEnd();

	// back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glEnd();

	// the diamond head
	// lower left side
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	// upper left side
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// upper front side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// upper right side
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	// upper back side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	glEndList();

	// -------------- //


}
void MovingpawnR() {
	if (animation&&zq12 <= -8) {
		if (zpb < 10)
			zpb += 0.01;
		else if (counter < 8) counter++;
	}
	// left side
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glEnd();

	// front side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd();

	// right side
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();

	// back side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glEnd();

	glEndList();
	// -------------- //

}
void DrawGround()
{
	glColor3f(0.9f, 0.9f, 0.9f);
	glPushMatrix();
	glScalef(100, 0.01, 100);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(-0.5, 0, -0.5);
	glEnd();
	glPopMatrix();
}
void rook() {
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 1.3f, 0.5f);
	glVertex3f(-0.5f, 1.3f, -0.5f);
	glEnd();

	// upper left side
	glBegin(GL_QUADS);
	glNormal3f(-0.5, -1.0f, 0.0f);
	glVertex3f(-0.5f, 1.3f, -0.5f);
	glVertex3f(-0.5f, 1.3f, 0.5f);
	glVertex3f(-0.75f, 1.3f*2.0f, 0.75f);
	glVertex3f(-0.75f, 1.3f*2.0f, -0.75f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 1.3f, 0.5f);
	glVertex3f(-0.5f, 1.3f, 0.5f);
	glEnd();

	// upper front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.5f);
	glVertex3f(-0.5f, 1.3f, 0.5f);
	glVertex3f(0.5f, 1.3f, 0.5f);
	glVertex3f(0.75f, 1.3f*2.0f, 0.75f);
	glVertex3f(-0.75f, 1.3f*2.0f, 0.75f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, 1.3f, -0.5f);
	glVertex3f(0.5f, 1.3f, 0.5f);
	glEnd();

	// upper right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, -1.0f, 0.0f);
	glVertex3f(0.5f, 1.3f, 0.5f);
	glVertex3f(0.5f, 1.3f, -0.5f);
	glVertex3f(0.75f, 1.3f*2.0f, -0.75f);
	glVertex3f(0.75f, 1.3f*2.0f, 0.75f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, 1.3f, -0.5f);
	glVertex3f(0.5f, 1.3f, -0.5f);
	glEnd();

	// upper back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -0.5f);
	glVertex3f(0.5f, 1.3f, -0.5f);
	glVertex3f(-0.5f, 1.3f, -0.5f);
	glVertex3f(-0.75f, 1.3f*2.0f, -0.75f);
	glVertex3f(0.75f, 1.3f*2.0f, -0.75f);
	glEnd();

	// top plate
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.75f, 1.3f*2.0f, 0.75f);
	glVertex3f(0.75f, 1.3f*2.0f, 0.75f);
	glVertex3f(0.75f, 1.3f*2.0f, -0.75f);
	glVertex3f(-0.75f, 1.3f*2.0f, -0.75f);
	glEnd();

	glEndList();

	// -------------- //*/
}
void knight() {
	static GLUquadric* knightEye = gluNewQuadric();
	// lower left side
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 1.4f, 0.5f);
	glVertex3f(-0.5f, 1.4f, -0.5f);
	glEnd();

	// upper left side
	glBegin(GL_QUADS);
	glNormal3f(-0.5, -1.0f, 0.0f);
	glVertex3f(-0.5f, 1.4f, -0.5f);
	glVertex3f(-0.5f, 1.4f, 0.5f);
	glVertex3f(-0.4f, 1.4f*1.5f, 0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f, -0.4f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 1.4f, 0.5f);
	glVertex3f(-0.5f, 1.4f, 0.5f);
	glEnd();

	// upper front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.5f);
	glVertex3f(-0.5f, 1.4f, 0.5f);
	glVertex3f(0.5f, 1.4f, 0.5f);
	glVertex3f(0.4f, 1.4f*1.5f, 0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f, 0.4f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, 1.4f, -0.5f);
	glVertex3f(0.5f, 1.4f, 0.5f);
	glEnd();

	// upper right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, -1.0f, 0.0f);
	glVertex3f(0.5f, 1.4f, 0.5f);
	glVertex3f(0.5f, 1.4f, -0.5f);
	glVertex3f(0.4f, 1.4f*1.5f, -0.4f);
	glVertex3f(0.4f, 1.4f*1.5f, 0.4f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, 1.4f, -0.5f);
	glVertex3f(0.5f, 1.4f, -0.5f);
	glEnd();

	// upper back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -0.5f);
	glVertex3f(0.5f, 1.4f, -0.5f);
	glVertex3f(-0.5f, 1.4f, -0.5f);
	glVertex3f(-0.4f, 1.4f*1.5f, -0.4f);
	glVertex3f(0.4f, 1.4f*1.5f, -0.4f);
	glEnd();

	// head
	glBegin(GL_QUADS);
	// left plate
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.4f, 1.4f*1.5f, -0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f, 0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, -0.4f);

	// front plate
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.4f, 1.4f*1.5f, 0.4f);
	glVertex3f(0.4f, 1.4f*1.5f, 0.4f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);

	// right plate
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 1.4f*1.5f, 0.4f);
	glVertex3f(0.4f, 1.4f*1.5f, -0.4f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, -0.4f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);

	// top plate
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, -0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, -0.4f);
	glEnd();

	// snout
	glBegin(GL_QUADS);
	// left plate
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.4f, 1.4f*1.5f - 0.3f, -1.3f);
	glVertex3f(-0.4f, 1.4f*1.5f, -0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, -0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f, -1.3f);

	// bottom plate
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.4f, 1.4f*1.5f, -0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f - 0.3f, -1.3f);
	glVertex3f(0.4f, 1.4f*1.5f - 0.3f, -1.3f);
	glVertex3f(0.4f, 1.4f*1.5f, -0.4f);

	// right plate
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 1.4f*1.5f, -0.4f);
	glVertex3f(0.4f, 1.4f*1.5f - 0.3f, -1.3f);
	glVertex3f(0.4f, 1.4f*1.5f, -1.3f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, -0.4f);

	// top plate
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-0.4f, 1.4f*1.5f, -1.3f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, -0.4f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, -0.4f);
	glVertex3f(0.4f, 1.4f*1.5f, -1.3f);

	// snout plate
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.4f, 1.4f*1.5f - 0.3f, -1.3f);
	glVertex3f(-0.4f, 1.4f*1.5f - 0.3f, -1.3f);
	glVertex3f(-0.4f, 1.4f*1.5f, -1.3f);
	glVertex3f(0.4f, 1.4f*1.5f, -1.3f);
	glEnd();

	// ears
	glBegin(GL_TRIANGLES);
	// left plates
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f + 0.35f, (0.4f));
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, (0.4f / 2.0f));

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, (0.4f / 2.0f));
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f + 0.35f, (0.4f));
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);

	// right plates
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-(0.4f - 0.1f), 1.4f*1.5f + 0.5f, (0.4f / 2.0f));
	glVertex3f(-(0.4f - 0.1f), 1.4f*1.5f + 0.5f + 0.35f, 0.4f);
	glVertex3f(-(0.4f - 0.1f), 1.4f*1.5f + 0.5f, 0.4f + 0.3f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f((0.4f - 0.1f), 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f((0.4f - 0.1f), 1.4f*1.5f + 0.5f + 0.35f, 0.4f);
	glVertex3f((0.4f - 0.1f), 1.4f*1.5f + 0.5f, (0.4f / 2.0f));
	glEnd();

	// ear plates
	glBegin(GL_QUADS);
	// left back
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(-(0.4f - 0.1f), 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(-(0.4f - 0.1f), 1.4f*1.5f + 0.5f + 0.35f, 0.4f);
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f + 0.35f, 0.4f);

	// right back
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f((0.4f - 0.1f), 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, 0.4f + 0.3f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f + 0.35f, 0.4f);
	glVertex3f((0.4f - 0.1f), 1.4f*1.5f + 0.5f + 0.35f, 0.4f);

	// left front
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-(0.4f - 0.1f), 1.4f*1.5f + 0.5f, (0.4f / 2.0f));
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f, (0.4f / 2.0f));
	glVertex3f(-0.4f, 1.4f*1.5f + 0.5f + 0.35f, 0.4f);
	glVertex3f(-(0.4f - 0.1f), 1.4f*1.5f + 0.5f + 0.35f, 0.4f);

	// right front
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f, (0.4f / 2.0f));
	glVertex3f((0.4f - 0.1f), 1.4f*1.5f + 0.5f, (0.4f / 2.0f));
	glVertex3f((0.4f - 0.1f), 1.4f*1.5f + 0.5f + 0.35f, 0.4f);
	glVertex3f(0.4f, 1.4f*1.5f + 0.5f + 0.35f, 0.4f);
	glEnd();

	// eyes
	glPushMatrix();
	glTranslatef(-(0.4f), 1.4f*1.5f + 0.5f - 0.7f * 0.3f, -0.4f);
	glScalef(0.12f, 0.1f, 0.12f);
	gluSphere(knightEye, 0.7f, 64, 64);
	glPopMatrix();

	glTranslatef(0.4f, 1.4f*1.5f + 0.5f - 0.7f * 0.3f, -0.4f);
	glScalef(0.12f, 0.1f, 0.12f);
	gluSphere(knightEye, 0.7f, 64, 64);

	glEndList();

	// -------------- //
}
void bishop() {
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glEnd();

	// front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glEnd();

	// right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glEnd();

	// back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glEnd();

	// the diamond head
	// lower left side
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	// upper left side
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.25f, 2.2f, 0.25f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// upper front side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.25f, 2.2f, 0.25f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// upper right side
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), 0.5f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.25f, 2.2f, -0.25f);
	glVertex3f(-0.25f, 2.2f, -0.25f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	// upper back side
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(-0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glVertex3f(0.0f, 2.2f + 1.68f, 0.0f);
	glVertex3f(0.5f, 2.2f + (1.68f / 2.0f), -0.5f);
	glEnd();

	glEndList();

	// -------------- //


}
void queen() {
	static GLUquadric* queenSphere = gluNewQuadric();
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glEnd();

	// front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glEnd();

	// right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glEnd();

	// back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glEnd();

	// the head
	// lower left side
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.35f, 3.0f, 0.35f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.35f, 3.0f, 0.35f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.35f, 3.0f, -0.35f);
	glVertex3f(-0.35f, 3.0f, -0.35f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glEnd();

	// top plate
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glEnd();

	// left triangles
	glBegin(GL_TRIANGLES);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glVertex3f(-0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glVertex3f(-0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(-0.65f, 4.0f, -0.65f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(-0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(-0.65f, 4.0f, 0.0f);
	glEnd();

	// front triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, 0.65f);
	glVertex3f(0.0f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, 0.65f);
	glVertex3f(0.65f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, 0.65f);
	glVertex3f(-0.65f, 4.0f, 0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.65f, 4.0f, 0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, 0.65f);
	glVertex3f(0.0f, 4.0f, 0.65f);
	glEnd();

	// right triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);
	glVertex3f(0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);
	glVertex3f(0.65f, 4.5f, 0.65f / 2.0f);
	glVertex3f(0.65f, 4.0f, 0.65f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(0.65f, 4.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.65f, 4.0f, 0.0f);
	glVertex3f(0.65f, 4.5f, -(0.65f / 2.0f));
	glVertex3f(0.65f, 4.0f, -0.65f);
	glEnd();

	// back triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.65f, 4.0f, -0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, -0.65f);
	glVertex3f(0.0f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glVertex3f(-(0.65f / 2.0f), 4.5f, -0.65f);
	glVertex3f(-0.65f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, -0.65f);
	glVertex3f(0.65f, 4.0f, -0.65f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.65f, 4.0f, -0.65f);
	glVertex3f(0.65f / 2.0f, 4.5f, -0.65f);
	glVertex3f(0.0f, 4.0f, -0.65f);
	glEnd();

	// sphere
	glTranslatef(0.0f, 3.0f + (2.0f / 2.0f + 0.05f), 0.0f);
	glScalef(0.12f, 0.1f, 0.12f);
	gluSphere(queenSphere, 2.0f, 64, 64);

	glEndList();

	// -------------- //
}
void king() {
	glBegin(GL_QUADS);
	glNormal3f(-0.5f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-0.4f, 3.5f, 0.4f);
	glVertex3f(-0.4f, 3.5f, -0.4f);
	glEnd();

	// front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.5f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.4f, 3.5f, 0.4f);
	glVertex3f(-0.4f, 3.5f, 0.4f);
	glEnd();

	// right side
	glBegin(GL_QUADS);
	glNormal3f(0.5f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.4f, 3.5f, -0.4f);
	glVertex3f(0.4f, 3.5f, 0.4f);
	glEnd();

	// back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, -0.5f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-0.4f, 3.5f, -0.4f);
	glVertex3f(0.4f, 3.5f, -0.4f);
	glEnd();

	// the head
	// lower left side
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(-0.4f, 3.5f, -0.4f);
	glVertex3f(-0.4f, 3.5f, 0.4f);
	glVertex3f(-0.7f, 3.5f + (2.2f / 2.0f), 0.7f);
	glVertex3f(-0.7f, 3.5f + (2.2f / 2.0f), -0.7f);
	glEnd();

	// lower front side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(-0.4f, 3.5f, 0.4f);
	glVertex3f(0.4f, 3.5f, 0.4f);
	glVertex3f(0.7f, 3.5f + (2.2f / 2.0f), 0.7f);
	glVertex3f(-0.7f, 3.5f + (2.2f / 2.0f), 0.7f);
	glEnd();

	// lower right side
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(0.4f, 3.5f, 0.4f);
	glVertex3f(0.4f, 3.5f, -0.4f);
	glVertex3f(0.7f, 3.5f + (2.2f / 2.0f), -0.7f);
	glVertex3f(0.7f, 3.5f + (2.2f / 2.0f), 0.7f);
	glEnd();

	// lower back side
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, -1.0f);
	glVertex3f(0.4f, 3.5f, -0.4f);
	glVertex3f(-0.4f, 3.5f, -0.4f);
	glVertex3f(-0.7f, 3.5f + (2.2f / 2.0f), -0.7f);
	glVertex3f(0.7f, 3.5f + (2.2f / 2.0f), -0.7f);
	glEnd();

	// top plate
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.7f, 3.5f + (2.2f / 2.0f), 0.7f);
	glVertex3f(0.7f, 3.5f + (2.2f / 2.0f), 0.7f);
	glVertex3f(0.7f, 3.5f + (2.2f / 2.0f), -0.7f);
	glVertex3f(-0.7f, 3.5f + (2.2f / 2.0f), -0.7f);
	glEnd();

	// cross
	// horizontal beam
	glBegin(GL_QUADS);
	// left plate
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, (0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, -(0.7f / 2.0f / 2.0f));

	// right plate
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, -(0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, (0.7f / 2.0f / 2.0f));

	// front plate
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, (0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, (0.7f / 2.0f / 2.0f));

	// back plate
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, -(0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, -(0.7f / 2.0f / 2.0f));

	// bottom plate
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f / 2.0f), (0.7f / 2.0f / 2.0f));

	// top plate
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, -(0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, -(0.7f / 2.0f / 2.0f));
	glVertex3f(-0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, (0.7f / 2.0f / 2.0f));
	glVertex3f(0.7f / 2.0f, 3.5f + (2.2f / 2.0f) + 0.7f / 2.0f, (0.7f / 2.0f / 2.0f));
	glEnd();

	// vertical beam
	glBegin(GL_QUADS);
	// left plate
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), (0.7f / 2.0f / 2.0f));
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), -(0.7f / 2.0f / 2.0f));

	// right plate
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), -(0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), (0.7f / 2.0f / 2.0f));

	// front plate
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), (0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), (0.7f / 2.0f / 2.0f));
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), (0.7f / 2.0f / 2.0f));

	// back plate
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), -(0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), -(0.7f / 2.0f / 2.0f));

	// top plate
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), (0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), (0.7f / 2.0f / 2.0f));
	glVertex3f((0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), -(0.7f / 2.0f / 2.0f));
	glVertex3f(-(0.7f / 2.0f / 2.5f), 3.5f + (2.2f / 2.0f) + (0.7f / 2.0f * 1.5f), -(0.7f / 2.0f / 2.0f));
	glEnd();

	glEndList();
}
void DrawTree()
{
	glPushMatrix();
	glColor3f(102 / 255.0, 51 / 255.0, 0);
	GLUquadricObj *p = gluNewQuadric();
	glRotatef(270, 1, 0, 0);
	gluCylinder(p, 1, 1, 3, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0 / 255.0, 51 / 255.0, 0);
	glTranslatef(0, 3, 0);
	glScalef(4, 4, 4);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(1, 1, 20, 20);
	glPopMatrix();
}
void drawBoard() {
	int q = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (q % 2 == 0) {
				if (j % 2 == 0)
					glColor3f(1, 1, 1);
				else
					glColor3f(0.6, 0.6, 0.6);
			}
			else {
				if (j % 2 == 0)
					glColor3f(0.6, 0.6, 0.6);
				else
					glColor3f(1, 1, 1);
			}

			glPushMatrix();
			glTranslatef(j * 2 * -1, 0, i * 2 * -1);
			glScalef(1, 0.2, 1);

			glutSolidCube(2);
			glPopMatrix();

		}
		q++;
	}
}



void init()
{
	// set up the parameters for lighting 
	GLfloat light_ambient[] = { .2, .2, .2, 1 };
	GLfloat light_diffuse[] = { .8, .8, .8, 1 };
	GLfloat light_specular[] = { 1, 1, 1, 1 };
	GLfloat light_pos[] = { 1, 1, 5, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	//glClearColor (0.0, 0.0, 0.0, 0.0);	// set display-window color to white
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
}
void reshape(int width, int height)
{
	::width = width;
	::height = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);		// set projection parameters
	glLoadIdentity();
	gluPerspective(60, width / (1.0 * height), 0.1, 100);

	glMatrixMode(GL_MODELVIEW);		// set projection parameters
}

void display()
{
	glLoadIdentity();
	gluLookAt(vecEye.x, vecEye.y, vecEye.z, vecEye.x +
		vecViewDirection.x, vecEye.y + vecViewDirection.y, vecEye.z + vecViewDirection.z,
		vecUp.x, vecUp.y + 2, vecUp.z);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// clear display window


	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glTranslatef(0, -2, -20);

	glRotatef(angleY, 0, 1, 0);

	if (!animation)glRotatef(-_angle, 0.0f, 1.0f, 0.0f);
	glRotatef(90, 0, 1, 0);
	glTranslatef(6, -2, 4 * 2);


	drawBoard();
	glPushMatrix();
	rook();
	glTranslatef(-2, 0, 0);
	knight();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4, 0, 0);
	bishop();
	glTranslatef(-2, 0, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	if (!turn)
		glTranslatef(zq1, 0, zq1);
	else {
		glTranslatef(-4, 0, -4);
		glTranslatef(0, 0, zq12);
		//cout<<zq12<<endl;
		//glTranslatef(0,0,zq12);
	}

	// cout<<counter<<endl;
	 // glTranslatef(0,0,zq12);
	Movingqueen1();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8, 0, 0);
	king();
	glTranslatef(-2, 0, 0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 0, 0);
	glTranslatef(-zb, 0, zb);
	Movingbishop();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-12, 0, 0);
	knight();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-14, 0, 0);
	rook();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -2);
	for (int i = 0; i < 8; ++i) {
		if (i == 4) {
			glTranslatef(-2, 0, 0);
			continue;
		}
		pawn();
		glTranslatef(-2, 0, 0);
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8, 0, -2);
	glTranslatef(0, 0, zp1);
	Movingpawn1();
	glPopMatrix();
	glColor3f(0.4, 0.4, 0.4);
	glPushMatrix();
	glTranslatef(0, 0, -14);
	rook();
	glTranslatef(-2, 0, 0);
	glRotatef(180, 0, 1, 0);
	// glTranslatef(-2,0,0);

	knight();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-4, 0, -14);
	bishop();
	glTranslatef(-2, 0, 0);
	glTranslatef(-zq2, 0, zq2);
	Movingqueen2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8, 0, -14);
	king();
	glTranslatef(-2, 0, 0);
	bishop();
	glTranslatef(-2, 0, 0);
	glRotatef(180, 0, 1, 0);
	knight();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-14, 0, -14);
	rook();
	glTranslatef(0, 0, 2);
	for (int i = 0; i < 8; i++) {
		if (i == 3 || i == 6 || i == 2) {
			glTranslatef(2, 0, 0);
			continue;
		}
		pawn();
		glTranslatef(2, 0, 0);
	}

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, 0, -12);
	glTranslatef(0, 0, zp3);
	Movingpawn3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 0, -12);

	glTranslatef(0, zpb, 0);
	// cout<<counter<<"   " <<zpb<<endl;
	MovingpawnR();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-8, 0, -12);
	glTranslatef(0, 0, zp2);
	Movingpawn2();





	glPopMatrix();

	glColor4f(1, 0, 0, 1);
	if (!animation)
		renderBitmapString(0, 10, 0, GLUT_BITMAP_TIMES_ROMAN_24, "press n to play");
	if (zq12 <= -8)
		renderBitmapString(0, 10, 0, GLUT_BITMAP_TIMES_ROMAN_24, "CheckMate");



	glutSwapBuffers();
	glFlush();			// process all openGl routines as quickly as possible
}
void red(int value) {
	_angle += 1.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, red, 0);
}
void moveForward()
{
	vecEye.x += MOVEMENT_SPEED * vecViewDirection.x;
	vecEye.y += MOVEMENT_SPEED * vecViewDirection.y;
	vecEye.z += MOVEMENT_SPEED * vecViewDirection.z;
}

void moveBackward()
{
	vecEye.x += -MOVEMENT_SPEED * vecViewDirection.x;
	vecEye.y += -MOVEMENT_SPEED * vecViewDirection.y;
	vecEye.z += -MOVEMENT_SPEED * vecViewDirection.z;
}

void moveLeft()
{
	Vector vecCross = Vector::Cross(vecViewDirection, vecUp);
	vecEye.x += -MOVEMENT_SPEED * vecCross.x;
	vecEye.y += -MOVEMENT_SPEED * vecCross.y;
	vecEye.z += -MOVEMENT_SPEED * vecCross.z;
}

void moveRight()
{
	Vector vecCross = Vector::Cross(vecViewDirection, vecUp);
	vecEye.x += MOVEMENT_SPEED * vecCross.x;
	vecEye.y += MOVEMENT_SPEED * vecCross.y;
	vecEye.z += MOVEMENT_SPEED * vecCross.z;
}

void moveUp()
{
	vecEye.x += MOVEMENT_SPEED * vecUp.x;
	vecEye.y += MOVEMENT_SPEED * vecUp.y;
	vecEye.z += MOVEMENT_SPEED * vecUp.z;
}

void moveDown()
{
	vecEye.x += -MOVEMENT_SPEED * vecUp.x;
	vecEye.y += -MOVEMENT_SPEED * vecUp.y;
	vecEye.z += -MOVEMENT_SPEED * vecUp.z;
}

void processKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':case 'w':
		moveForward(); break;
	case 'S':case 's':
		moveBackward(); break;
	case 'A':case 'a':
		moveLeft(); break;
	case 'D':case 'd':
		moveRight(); break;
	case 'R':case 'r':
		moveUp(); break;
	case 'E':case 'e':
		moveDown(); break;
	case 'n':case 'N':
		animation = !animation; break;
	case 'q':
		angleY += 1; break;
	case 't':
		angleY -= 1; break;
	case 'L': case 'l':
		bLighting = !bLighting;
		if (bLighting)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
		break;
	}

}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);										// initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// set display mode
	//glutInitWindowPosition (20, 20);							// set top left display window position
	glutInitWindowSize(800, 800);								// set display window width and height
	glutCreateWindow("OpenGL - Homework 2 - Summer 2017-2018");					// create display window

	init();

	glutKeyboardFunc(processKeyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);									// send graphics to display window
	glutIdleFunc(display);
	glutTimerFunc(25, red, 0);
	glutMainLoop();											// dispaly everthing and wait
}