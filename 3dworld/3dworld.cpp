
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include "Polyhedron.h"

vector<Polyhedron> polys;

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f, z=5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 0.9};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if (h == 0)
    h = 1;
  float ratio =  w * 1.0 / h;

  // Use the Projection Matrix
  glMatrixMode(GL_PROJECTION);

  // Reset Matrix
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set the correct perspective.
  gluPerspective(45.0f, ratio, 0.1f, 10000.0f);

  // Get Back to the Modelview
  glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan() {

  //glColor3f(1.0f, 1.0f, 1.0f);
  glColor3f(1.0f, 0.0f, 0.0f);

  // Draw Body

  glTranslatef(0.0f ,0.75f, 0.0f);
  glutSolidSphere(0.75f,20,20);

  // Draw Head
  glTranslatef(0.0f, 1.0f, 0.0f);
  glutSolidSphere(0.25f,20,20);

  // Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.05f, 0.10f, 0.18f);
  glutSolidSphere(0.05f,10,10);
  glTranslatef(-0.1f, 0.0f, 0.0f);
  glutSolidSphere(0.05f,10,10);
  glPopMatrix();

  // Draw Nose
  glColor3f(1.0f, 0.5f , 0.5f);
  glRotatef(0.0f,1.0f, 0.0f, 0.0f);
  glutSolidCone(0.08f,0.5f,10,2);
}

void computePos(float deltaMove) {

  x += deltaMove * lx * 0.2f;
  z += deltaMove * lz * 0.2f;
}

void computeDir(float deltaAngle) {

  angle += deltaAngle;
  lx = sin(angle);
  lz = -cos(angle);
}

void init() {
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

// void initPolyhedron() {
//   //TODO
  
//   Polyhedron p1("models/cube.obj", Vector3d(-5,5,0), 50, Vector3d(.3,.5,.3));
//   p1.Load();
//   p1.Recenter();
//   // p1.Print();
//   polys.push_back(p1);
  
// }

Vector3d randomPos(){
  double randx = (1.0 * (rand() % 100)) - 50;
  double randy = (1.0 * (rand() % 100)) - 50;
  double randz = (1.0 * (rand() % 100)) - 50;
  Vector3d randomVals(randx,randy,randz);
  return randomVals;
}

double randomRot(){
  return rand() % 360;
}

Vector3d randomColor(){
  double colorx = (1.0 * rand() / RAND_MAX);
  double colory = (1.0 * rand() / RAND_MAX);
  double colorz = (1.0 * rand() / RAND_MAX);
  Vector3d randomVals(colorx,colory,colorz);
  return randomVals;
}

void initPolyhedron() {
  for (int i = 0; i < 50; i++){
    Polyhedron p1("models/stone1_M.obj", 
                  Vector3d(randomPos().GetX(),15,randomPos().GetZ()),
                  randomRot(),
                  Vector3d(randomColor().GetX(),randomColor().GetY(),randomColor().GetZ()));
    p1.Load();
    p1.Recenter();
    polys.push_back(p1);
    Polyhedron p2("models/stone2_L.obj", 
                  Vector3d(randomPos().GetX(),10,randomPos().GetZ()),
                  randomRot(),
                  Vector3d(randomColor().GetX(),randomColor().GetY(),randomColor().GetZ()));
    p2.Load();
    p2.Recenter();
    polys.push_back(p2);
  }
    
}

void loadFromFile(string filename) {
  //TODO
}

void renderScene(void) {

  if (deltaMove)
    computePos(deltaMove);
  if (deltaAngle)
    computeDir(deltaAngle);

  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();
  // Set the camera
  gluLookAt(	x, 1.0f, z,
      x+lx, 1.0f,  z+lz,
      0.0f, 1.0f,  0.0f);

  // Draw ground

  glColor3f(0.9f, 0.9f, 0.9f);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();

  // Draw 36 SnowMen

  // if(1)
  // for(int i = -3; i < 3; i++)
  //   for(int j=-3; j < 3; j++) {
  //     glPushMatrix();
  //     glTranslatef(i*10.0,0,j * 10.0);
  //     drawSnowMan();
  //     glPopMatrix();
  //   }

  for(int i=0; i<(int)polys.size(); i++) {
    polys[i].Draw();
  }

  glutSwapBuffers();
}


void pressKey(int key, int xx, int yy) {

  switch (key) {
    case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
    case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
    case GLUT_KEY_UP : deltaMove = 0.5f; break;
    case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
  }
}

void releaseKey(int key, int x, int y) {

  switch (key) {
    case GLUT_KEY_LEFT :
    case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
    case GLUT_KEY_UP :
    case GLUT_KEY_DOWN : deltaMove = 0;break;
  }
}


void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 'q':
    case 27:             // ESCAPE key
      exit (0);
      break;
  }
}

int main(int argc, char **argv) {

  // init GLUT and create window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(640,640);
  glutCreateWindow("3D World");

  // register callbacks
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(pressKey);

  // here are the new entries
  glutIgnoreKeyRepeat(1);
  glutSpecialUpFunc(releaseKey);

  // OpenGL init
  glEnable(GL_DEPTH_TEST);
  init();
  initPolyhedron();
  // enter GLUT event processing cycle
  glutMainLoop();

  return 1;
}
