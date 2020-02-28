#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

//======================================================
// CONSTANTS
//======================================================
// Flappy
float bird_y0;
// PI
long double const PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899863;
// Square size
#define size 50.0

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY reshapeCallBack( )
//======================================================
// Window size
int w_height = 500;
int w_width = 500;

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY displayCallBack( )
//======================================================
int display_count = 0; //keeps count of invocations

//======================================================
// GLOBAL VARIABLES WRITTEN TO BY keyboardCallBack( )
//======================================================
float theta = 0.0; // Rotation angle of bird 
int timer_period_in_ms = 100; // time between timer callbacks in milliseconds

//====================================================================
// GLOBAL VARIABLES WRITTEN TO BY motionCallBack( )
//====================================================================
int bird_r=20;
int Eye_radius = 20; // For Flappy's eye 
float Eye_pupil = 10; // For Flappy's pupil
float bird_x=40; 
float bird_y=40;; // position of bird
double bird_vx = 0; 
double bird_vy = 0;
double bird_ax = 0; 
double bird_ay = 0;
int bird_dx = 1; // incremental change inbird_x
float dt = 0.15; //0.05;
double impulse = 0;
double impulseMax = 80;
double vyMax = 40;
double vxMax = 40;
double obj_x = 1000;
double obj_y = 200;
bool hasStarted = false;
int numUpdates = 0;
int character = 1;
int counts = 0;
//======================================================
// IDLE CALLBACK ROUTINE 
//======================================================
void DisplayScore(int posx, int posy, int posz, int space_char, int scorevar)
{
    int j = 0, p, k;
    GLvoid* font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

    p = scorevar;
    j = 0;
    k = 0;
    while (p > 9)
    {
        k = p % 10;
        glRasterPos3f((posx - (j * space_char)), posy, posz);
        glutBitmapCharacter(font_style1, 48 + k);
        j++;
        p /= 10;
    }
    glRasterPos3f((posx - (j * space_char)), posy, posz);
    glutBitmapCharacter(font_style1, 48 + p);

}

void bounce() {
  //bird_ax += 0;
  //bird_ay += 20;
  impulse += impulseMax;
  bird_ax += 2;
}

void boundVelocityAcceleration(double& vx, double& vy, double& ax, double& ay) {
  if( vx > vxMax ) vx = vxMax;
  if( vy > vyMax ) vy = vyMax;
  if( ax > 20 ) ax = 20;
  if( ay < -10 ) ay = -9;
}

void boundImpulse() {
  if(impulse > impulseMax) impulse = 33;
  if(impulse < 0.5) impulse = 0;
}

//Implemeted Coords for background scene
//Used Polygons to represnt each graphic
void background() {
  //Sky
  glBegin(GL_POLYGON);
  glColor3f(0.3, .9, 1);
  glVertex2f(w_width * -1, w_height);
  glVertex2f(w_width, w_height);
  glVertex2f(w_width,w_height * -1);
  glVertex2f(w_width * -1, w_height * -1);
  glEnd();
   
  //sidewalk
  glBegin(GL_POLYGON);
  glColor3f(1, 1, 0.7);
  glVertex2f(w_width * -1, 75);
  glVertex2f(w_width, 75);
  glVertex2f(w_width,0);
  glVertex2f(w_width * -1, 0);
  glEnd();
      
  //grass
  glBegin(GL_POLYGON);
  glColor3f(0, 1, 0.5);
  glVertex2f(w_width * -1, 75);
  glVertex2f(w_width, 75);
  glVertex2f(w_width,50);
  glVertex2f(w_width * -1, 50);
  glEnd();
  //clouds
  //1
  glBegin(GL_POLYGON);
  glColor3f(1, 1, 1);
  glVertex2f(0, 150);
  glVertex2f(50, 250);
  glVertex2f(75,200);
  glVertex2f(250, 200);
  glEnd();

  //2
  glBegin(GL_POLYGON);
  glColor3f(1, 1, 1);
  glVertex2f(0, 270);
  glVertex2f(250, 300);
  glVertex2f(275,270);
  glVertex2f(450, 300);
  glEnd();  
  glFlush();
}
    
//Tries to for circular shapes as windows for testing purposes.
void trees(){ 
  for (double i =0; i <=360; i++){
    glBegin(GL_POLYGON);
    glVertex3f(2.0 * cos(i),2* sin(i), 1.0);
    glVertex3f(2.0 * cos(i+1),2* sin(i+1), 2.0);
    glVertex3f(2.0 * cos(i),2* sin(i), 2.0);
    glVertex3f(2.0 *cos(i+1),2* sin(i+1), 1.0);
    glEnd();
  }
}
//Buildings() displays buildings in different colors widths and heights.
void Buildings(){       
  ///One -red tri shap
  glColor3f(1, 0, 0);
  glPushMatrix();  
  glBegin(GL_POLYGON);
  glVertex2i(200,75);
  glVertex2i(200, 200);
  glVertex2i(100, 75);
  glVertex2i(100, 200);
  glEnd();
  glPopMatrix();

  ///purplish
  glPushMatrix();
  glColor3f(0.9, 0, 0.7);
  glBegin(GL_POLYGON);
  glVertex2i(445, 75);
  glVertex2i(445, 200);
  glVertex2i(350, 200);
  glVertex2i(350, 75);
  glEnd();
  glPopMatrix();
  
  //yellowish
  glPushMatrix();
  glColor3f(0.8, 1, 0);
  glBegin(GL_POLYGON);
  glVertex2i(245, 75);
  glVertex2i(245, 170);
  glVertex2i(320, 170);
  glVertex2i(320, 75);
  glEnd();
  glPopMatrix();
  
  //black building
  glPushMatrix();
  glColor3f(0, 0.2, 0);
  glBegin(GL_POLYGON);
  glVertex2i(300, 75);
  glVertex2i(300, 300);
  glVertex2i(320, 300);
  glVertex2i(360, 250);
  glVertex2i(360, 75);  
  glEnd();
  glPopMatrix();
}
    
void DrawBackground(){
  background();
  Buildings();
}

void DrawCollision(){
  // glBegin(GL_QUADS);
  // glVertex2d(w_width / 2 - (w_width / 5), w_height - (w_height / 8));
  // glVertex2d(w_width / 2 - (w_width / 8), w_height - (w_height / 8));
  // glVertex2d(w_width / 2 + (w_width / 5), w_height - (w_height / 2 + w_height / 5));
  // glVertex2d(w_width / 2 + (w_width / 8), w_height - (w_height / 2 + w_height / 5));
  // glEnd();

  glBegin(GL_POLYGON);
  glVertex2d(w_width / 2, w_height / 2);
  glVertex2d((w_width / 2) + 10, w_height / 2);
  glVertex2d((w_width / 2) + 10, (w_height / 2) - 10);
  glVertex2d(w_width / 2, (w_height / 2) - 10);
  glEnd();
}

void update()
{
  bird_y0 = bird_y;
  numUpdates++;
  if(numUpdates%100==0) cout << "Num updates = " << numUpdates << "bird_x = " << bird_x << " bird_y = " << bird_y << " vx = " << bird_vx << " vy = " << bird_vy << " ax = " << bird_ax << " ay = " << bird_ay << endl;
  if(hasStarted) {
    //acceleration gets updated  
    bird_ay += (-9.8 + impulse ) * dt;
    //velocity gets updated
    bird_vx += bird_ax * dt;
    bird_vy += bird_ay * dt;
    //position gets updated
    bird_x += bird_vx * dt;
    bird_y += bird_vy * dt;
    boundVelocityAcceleration(bird_vx, bird_vy, bird_ax, bird_ay);
    impulse *= 0.3;
    boundImpulse();
  }
  /*
  bird_x += bird_dx; //Increment x-position of bird
  if (bird_x > w_width || bird_x == 0) bird_dx *= -1; //Reverse direction if at edges
    */
  if(bird_y-bird_r<0) { bird_y = bird_r;
    bird_vy = 0;
    bird_ay = 0;
  }

  if(obj_x < (bird_x-w_width/2.0)) {
    //random x
    obj_x = bird_x + w_width/2.0 + (100.0*rand())/RAND_MAX;
    //random y
    obj_y = (rand())%w_height;
    counts++;
  }

  // Collision Check - Bao Pham
  // float r = ((double)rand() / (RAND_MAX));
	// float g = ((double)rand() / (RAND_MAX));
	// float b = ((double)rand() / (RAND_MAX));
	
	// if ( ((bird_x >= obj_x - 60) && (bird_x < obj_x)) && (bird_y >= obj_y + 100))
	// {
	// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 	glClearColor(r, g, b, 1.0);
	// 	glutSwapBuffers();
	// 	glutMainLoop();
	// }

	// if (((bird_x >= obj_x - 60) && (bird_x < obj_x)) && (bird_y <= obj_y - 100))
	// {
		
	// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 	glClearColor(r, g, b, 1.0);
	// 	glutSwapBuffers();
	// 	glutMainLoop();
	// }

  glutPostRedisplay();
}

//======================================================
// RESHAPE CALLBACK ROUTINE
//======================================================
void reshapeCallback(int width, int height)
{
  //Update globals containing window size
  w_width = width;
  w_height = height;
}

//======================================================
// MOUSE MOTION CALLBACK ROUTINE 
//======================================================
void motionCallBack(int x, int y)
{
  printf("YYYMotion call back: %d, %d)\n", x, y);
  //Set bird's location to current mouse position
  bird_x = x;
  bird_y = w_height - y; //Invert mouse y (as its measured from top)

  glutPostRedisplay();
}

//======================================================
// MOUSE CALLBACK ROUTINE 
//======================================================
void mouseCallBack(int btn, int state, int x, int y)
{
  printf("Mouse call back: button=%d, state=%d, x=%d, y=%d\n", btn, state, x, y);
  if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)   exit(0);
}

//======================================================
// KEYBOARD CALLBACK ROUTINE 
//======================================================
bool isSimulating = false;
void keyboardCallBack(unsigned char key, int x, int y)
{
  printf("Keyboard call back: key=%c, x=%d, y=%d, theta=%f\n", key, x, y, theta);
  switch (key)
  {
    case 'i':
    case 'I':
      if( !isSimulating ) {
        isSimulating = !isSimulating;
        printf("Idle function ON\n");
        break;
      }
      else {
        isSimulating = !isSimulating;
        glutIdleFunc(NULL);
        printf("Idle function OFF\n");
        break;
      }
    case 'r':
    //  theta = theta + 10.0;
      break;
    case ' ':
      hasStarted = true;
      isSimulating = true;
      bounce();
      break;
    case 27:
    case 'q':
      cout << "Exiting" << endl;
      exit(-1);
    default:
      printf("Press i (Idle Off), I (Idle ON) or r (Rotate)");
  }

  glutPostRedisplay();
}

bool collision = false;

bool checkCollision()
{
    if (bird_x >= obj_x - 30 && bird_x <= obj_x + 50)       // If bird is between sides of pipes
    {
        if (bird_y <= obj_y - 115 || bird_y >= obj_y + 115) // Then check if bird is above or below the space between pipes 
            collision = true;                               // Then bird hit a pipe
    }
    else collision = false;                                 // Else, no hit
    return collision;
}

void DrawPipes()
{
  int left = obj_x - 40;
  int right = obj_x + 40;
  int top = obj_y + 125;
  int bottom = obj_y - 125;

  glBegin(GL_QUADS);
  glVertex2f(left, top);
  glVertex2f(left, top + w_height);
  glVertex2f(right, top + w_height);
  glVertex2f(right, top);
  glEnd();
  
  glBegin(GL_QUADS);
  glVertex2f(left, bottom);
  glVertex2f(left, bottom - w_height);
  glVertex2f(right, bottom - w_height);
  glVertex2f(right, bottom);
  glEnd();

  	//Tip
	glBegin(GL_QUADS);
  glVertex2f(left - 15, top + 25);
  glVertex2f(right + 15, top + 25);
  glVertex2f(right + 15, top);
  glVertex2f(left - 15, top);
	glEnd();
	glBegin(GL_QUADS);
  glVertex2f(left - 15, bottom + 25);
  glVertex2f(right + 15, bottom + 25);
  glVertex2f(right + 15, bottom);
  glVertex2f(left - 15, bottom);
	glEnd();
}


//======================================================
// SHAPES AND OBJECTS 
//======================================================
void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
  float theta = 2 * 3.1415926 / float(num_segments);
  float c = cos(theta);//precalculate the sine and cosine
  float s = sin(theta);
  float t;

  float x = 10;//we start at angle = 0 
  float y = 0;

  glBegin(GL_POLYGON);
  for (int ii = 0; ii < num_segments + 3; ii++)
  {
    if (ii == 12)
    {
      glEnd();

      glColor3ub(249, 194, 44);
      glBegin(GL_POLYGON);
      glVertex2f(x * rx + cx, y * ry + cy);
    }
    else if (ii == 11)
    {
      //apply radius and offset
      glVertex2f(x * rx + cx, y * ry + cy);//output vertex 
    }
    else
    {
      //apply radius and offset
      glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

      //apply the rotation matrix
      t = x;
      x = c * x - s * y;
      y = s * t + c * y;
    }
  }
  glEnd();
}

void DrawBorder(float cx, float cy, float rx, float ry, int num_segments)
{
  float theta = 2 * 3.1415926 / float(num_segments);
  float c = cos(theta);//precalculate the sine and cosine
  float s = sin(theta);
  float t;

  float x = 10;//we start at angle = 0 
  float y = 0;

  glBegin(GL_LINE_STRIP);
  for (int ii = 0; ii < num_segments; ii++)
  {
    //apply radius and offset
    glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

    //apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
}

void DrawEye(float r, int num_segments) {
  float theta = 2 * 3.1415926 / float(num_segments);
  glBegin(GL_POLYGON);
  for (int ii = 0; ii < num_segments; ii++) {
    float xi = r * cos((theta * ii)) + 15.0f;
    float yi = r * sin((theta * ii)) + 5.0f;
    glVertex2f(xi, yi);
  }
  glEnd();
}

void DrawPupil()
{
  glBegin(GL_QUADS);
  glVertex2f(22, 12);
  glVertex2f(22, 4);
  glVertex2f(18, 4);
  glVertex2f(18, 12);
  glEnd();
}

void DrawLips()
{
  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(9, -3);
  glVertex2f(9, 0);
  glVertex2f(33, 0);
  glVertex2f(33, -3);
  glEnd();

  glColor3ub(253, 104, 75);
  glBegin(GL_QUADS);
  glVertex2f(9, -3);
  glVertex2f(9, -6);
  glVertex2f(33, -6);
  glVertex2f(33, -3);
  glEnd();

  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(9, -6);
  glVertex2f(9, -9);
  glVertex2f(33, -9);
  glVertex2f(33, -6);
  glEnd();

  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(9, -3);
  glVertex2f(9, -12);
  glVertex2f(6, -12);
  glVertex2f(6, -3);
  glEnd();

  glColor3ub(253, 104, 75);
  glBegin(GL_QUADS);
  glVertex2f(9, -6);
  glVertex2f(9, -9);
  glVertex2f(6, -9);
  glVertex2f(6, -6);
  glEnd();

  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(3, -6);
  glVertex2f(3, -9);
  glVertex2f(6, -9);
  glVertex2f(6, -6);
  glEnd();

  glColor3ub(253, 104, 75);
  glBegin(GL_QUADS);
  glVertex2f(9, -12);
  glVertex2f(9, -9);
  glVertex2f(30, -9);
  glVertex2f(30, -12);
  glEnd();

  glColor3f(0, 0, 0);
  glBegin(GL_QUADS);
  glVertex2f(9, -12);
  glVertex2f(9, -15);
  glVertex2f(30, -15);
  glVertex2f(30, -12);
  glEnd();
}

void DrawWing(float cx, float cy, float rx, float ry, int num_segments)
{
  float theta = 2 * 3.1415926 / float(num_segments);
  float c = cos(theta);//precalculate the sine and cosine
  float s = sin(theta);
  float t;

  float x = 10;//we start at angle = 0 
  float y = 0;

  glBegin(GL_POLYGON);
  for (int ii = 0; ii < num_segments + 3; ii++)
  {
    //apply radius and offset
    glVertex2f(x * rx + cx, y * ry + cy);//output vertex 

    //apply the rotation matrix
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
  //glRotatef(-30, 0, 0, 1);
}

void DrawPipe(float r)
{
  	glColor3f(0, 1, 0);
	//Pipes
	glBegin(GL_QUADS);
		glVertex2f(r, r - 200);
		glVertex2f(r + 50, r - 200);
		glVertex2f(r + 50, r - 4200);
		glVertex2f(r, r - 4200);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(r, r + 200);
		glVertex2f(r + 50, r + 200);
		glVertex2f(r + 50, r + 4200);
		glVertex2f(r, r + 4200);
	glEnd();

	//Tip
	glBegin(GL_QUADS);
		glVertex2f(r - 10, r - 200);
		glVertex2f(r + 60, r - 200);
		glVertex2f(r + 60, r - 220);
		glVertex2f(r - 10, r - 220);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(r - 10, r + 200);
		glVertex2f(r + 60, r + 200);
		glVertex2f(r + 60, r + 220);
		glVertex2f(r - 10, r + 220);
	glEnd();

	//Black Outline
	glColor3f(0.01, 0.01, 0.01);
	glBegin(GL_QUADS);
		glVertex2f(r - 10, r - 220);
		glVertex2f(r + 60, r - 220);
		glVertex2f(r + 60, r - 225);
		glVertex2f(r - 10, r - 225);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(r - 10, r + 220);
		glVertex2f(r + 60, r + 220);
		glVertex2f(r + 60, r + 225);
		glVertex2f(r - 10, r + 225);
	glEnd();
}

void DrawCircle(float r, int num_segments) {
    float theta = 2 * 3.1415926 / float(num_segments);
    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++) {
        float xi = r * cos((theta * ii));
        float yi = r * sin((theta * ii));
        glVertex2f(xi, yi);
    }
    glEnd();
}

void Draw_Wings() {
    glBegin(GL_POLYGON);
    glVertex3f(-20.0, 15.0, 0.0);
    glVertex3f(20.0, 15.0, 0.0); 
    glVertex3f(33.0, -30.0, 0.0);
    glVertex3f(0.0, -35.0, 0.0);
    glVertex3f(-33.0, -30.0, 0.0);
    glEnd();
}

void Draw_Beak() {
    glBegin(GL_TRIANGLES);
    glVertex3f(10.0, -30.0, 0.0);
    glVertex3f(50.0, -30.0, 0.0);
    glVertex3f(10.0, -10.0, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(10.0, -28.0, 0.0);
    glVertex3f(40.0, -35.0, 0.0);
    glVertex3f(10.0, -40.0, 0.0);
    glEnd();
}

void Draw_Tail() {
    glBegin(GL_QUADS);
    glVertex3f(-40.0, -15.0, 0.0);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(-80.0, -25.0, 0.0);
    glVertex3f(-50.0, -35.0, 0.0);
    glEnd();
}

//======================================================
// DISPLAY CALL BACK ROUTINE 
//======================================================
void displayCallBack(void)
{
  printf("Display call back %d\n", display_count++);
  cout << "pos of bird [" << bird_x << "," << bird_y << "]"<< endl;

  if( bird_x > w_width/2 ) {
    // Set Projection Mode and Volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0.0, w_width, 0.0, w_height, -1.0, 1.0);
    glOrtho(bird_x-w_width/2, bird_x+w_width/2, 0.0, w_height, -1.0, 1.0);
  }

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //draw background, the background should be drawn before drawing bird
	glPushMatrix();
	glTranslatef(bird_x - 250, 0, 0.0); // make it move to the x position of the bird, y doesnt change
	glRotatef(theta, 0, 0, 1.0);  //the program always draw the bird at bird_x, because of line 256. So all you need to do is let the background drawn at bird_x too
	glColor3ub(255, 255, 0);
	DrawBackground(); //just a simple background
	glPopMatrix();
	//end of drawing background
  
  if (character == 1){  
    // Draw Flappy - Joshua Chi
    glPushMatrix();
    glTranslatef(bird_x, bird_y, 0.0);
    glRotatef(theta, 0, 0, 1.0);
    glColor3ub(249, 241, 36);
    DrawEllipse(3, 2, 2.5f, 2, 20);
    glColor3f(0, 0, 0);
    DrawBorder(3, 2, 2.5f, 2, 20);
    glColor3f(1, 1, 1);
    DrawEye(bird_r, 20);
    glColor3f(0, 0, 0);
    DrawPupil();
    DrawLips();
    if (bird_y - bird_y0 - 1 > 0.0f)
    {
      glRotatef(30, 0, 0, 1);
      glTranslatef(1, 9, 0);
      glColor3ub(250, 252, 233);
      DrawWing(-15, -3, 1.2f, 1.f, 20);
    }
    else
    {
      glRotatef(-30, 0, 0, 1);
      glColor3ub(250, 252, 233);
      DrawWing(-15, -3, 1.2f, 1.f, 20);
    }
    glPopMatrix();
  }
  else {
    // Draw Birdy - Jordan Naser (somewhat broken after implementation - but working on its own)
    glPushMatrix();
    glTranslatef(bird_x, bird_y, 0.0);
    glRotatef(theta, 0, 0, 1.0);
    glColor3ub(0, 200, 255); //Changed to light blue
    DrawEllipse(7, 4, 7, 4, 40);
    glTranslatef(30.0, 30.0, 0.0);
    DrawCircle(bird_r, 30); //Draw head
    glTranslatef(-30.0, -20.0, 0.0);
    glColor3ub(0, 175, 255);
    Draw_Wings(); //Draw Flappy's wings
    glTranslatef(40.0, 32.0, 0.0);
    glColor3ub(255, 255, 255); //White
    DrawCircle(Eye_radius, 20); 
    glTranslatef(0.0, 1.5, 0.0);
    glColor3ub(0, 0, 0); //Black
    DrawCircle(Eye_pupil, 20);
    glTranslatef(13.5, 18.0, 0.0);
    glColor3ub(255, 175, 0); //Orange
    Draw_Beak();
    glTranslatef(-65.0, -20.0, 0.0);
    glColor3ub(0, 175, 255);
    Draw_Tail();
    glPopMatrix();
  }

  // Draw pipes - Enkh Onon
  // glPushMatrix();
  // glTranslatef(obj_x, obj_y, 0.0);
  // glColor3f(0, 1, 0);
  // DrawPipe(bird_r);
  // glPopMatrix();

  // Draw pipes - Mix of Jacob Puente's & Enkh Onon's Code
  glPushMatrix();
  if (checkCollision()) glColor3d(1,0,0); 
  else glColor3f(0, 1, 0);                    // Else, keep them green
  if (obj_x < 20000.0) glColor3d(0,1,0);
  else glColor3d(1, 0.65, 0);
  DrawPipes();
  glPopMatrix();

  if (checkCollision()){
    // glPushMatrix();
    printf("COLLISION\n");
    DrawCollision();
    isSimulating = false;
    // glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(bird_x - 200, 0.0, 0.0);
  glColor3f(1, 1, 1);
  DisplayScore(250, 500, 0, 20, counts);
  glPopMatrix();

  //Swap double buffers 
  glutSwapBuffers();
}

//======================================================
// MAIN PROGRAM
//======================================================
int main(int argc, char** argv)
{
  // Allow cmd line arguments to be passed to the glut
  glutInit(&argc, argv);

  // Create and name window
  glutInitWindowPosition(10, 10);
  glutInitWindowSize(w_width, w_height);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("Flappy Bird");

  // Set Projection Mode and Volume
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, w_width, 0.0, w_height, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);

  // Set clear color to black and clear window 
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();

  // Set up callbacks
  //glutMouseFunc(mouseCallBack);
  glutKeyboardFunc(keyboardCallBack);
  //glutMotionFunc(motionCallBack);
  glutDisplayFunc(displayCallBack);
  glutReshapeFunc(reshapeCallback);
  glutIdleFunc(update);

  // Enter main event loop
  glutMainLoop();
}