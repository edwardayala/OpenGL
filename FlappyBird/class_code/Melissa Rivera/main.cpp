//
//  main.cpp
//  flappy-bird
//
//  Created by Melissa  Rivera  on 2/5/20.
//  Copyright © 2020 Melissa  Rivera . All rights reserved.
//
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

//======================================================
// CONSTANTS
//======================================================
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
float bird_x=40;
float bird_y=40;; // position of bird
double bird_vx = 0;
double bird_vy = 0;


float building1_x =100;
float building2_x =100;
float building3_x =100;


//accelertation
double bird_ax = 0;
double bird_ay = 0;
int bird_dx = 5; // incremental change inbird_x
float dt = 0.15; //0.05;
double impulse = 0;


                    //for background

double bg_ax = 0;
double bg_ay = 0;
int bg_dx = 5; // incremental change background
float bgdt = 0.15; //0.05;
double bgimpulse = 0;


//if impulseMax is faster or higher in num you don't have to space bar press it as ofter
double impulseMax = 80;
double vyMax = 40;
double vxMax = 40;


//initial values for object
double obj_x = 1000;
double obj_y = 200;

bool hasStarted = false;
int numUpdates = 0;
int BGUpdates = 0;
//======================================================
// IDLE CALLBACK ROUTINE
//======================================================
void bounce() {//add impulse assuming + direction
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
//windows for buildings
//meant to be circular looking windows
void window(){
    
    for (double i =0; i <=360; i++){
        
    glBegin(GL_LINE_LOOP);
    
    glVertex3f(2.0 * cos(i),2* sin(i), 1.0);
        glVertex3f(2.0 * cos(i+1),2* sin(i+1), 2.0);
        glVertex3f(2.0 * cos(i),2* sin(i), 2.0);
        glVertex3f(2.0 *cos(i+1),2* sin(i+1), 1.0);
        
        
        
        glEnd();
    }
}
//Implemeted Coords for background scene
//Used Polygons to represnt each graphic
void background() {
       
   //Sky
    glBegin(GL_POLYGON);
          glColor3f(0.3, .9, 1);
          glVertex2f(0, 500);
          glVertex2f(0, 75);
          glVertex2f(500,75);
          glVertex2f(500, 500);
       glEnd();
   
    //sidewalk
       glBegin(GL_POLYGON);
          glColor3f(1, 1, 0.7);
          glVertex2f(0, 75);
          glVertex2f(500, 75);
          glVertex2f(500,0);
          glVertex2f(0, 0);
       glEnd();
      
    //grass
       glBegin(GL_POLYGON);
          glColor3f(0, 1, 0.2);
          glVertex2f(0, 50);
          glVertex2f(500, 50);
          glVertex2f(500,75);
          glVertex2f(0, 75);
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
    
    glPushMatrix();
   
    
    //yellowish
    glColor3f(0.8, 1, 0);
       glBegin(GL_POLYGON);
       glVertex2i(245, 75);
       glVertex2i(245, 170);
       glVertex2i(320, 170);
       glVertex2i(320, 75);
    
    
    glEnd();
    glPopMatrix();
    
    
     glPushMatrix();
    //black building
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



//acc * dt to increase velcity, which in turns affects the position
void update()
{
    
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
  }

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
    //case 'r':
    //  theta = theta + 10.0;
    //  break;
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

void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
  float theta = 2 * 3.1415926 / float(num_segments);
  float c = cos(theta);//precalculate the sine and cosine
  float s = sin(theta);
  float t;

  float x = 10;//we start at angle = 0
  float y = 0;

  glBegin(GL_LINE_LOOP);
  for(int ii = 0; ii < num_segments; ii++)
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

void DrawCircle(float r, int num_segments) 
{
  float theta = 2 * 3.1415926 / float(num_segments);
  glBegin(GL_POLYGON);
  for(int ii=0; ii<num_segments; ii++) {
    float xi = r * cos( (theta*ii) );
    float yi = r * sin( (theta*ii) );
    glVertex2f(xi,yi);
  }
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

  //draw bird
  glPushMatrix();
  glTranslatef(bird_x, bird_y, 0.0);
  glRotatef(theta, 0, 0, 1.0);

  /*glBegin(GL_POLYGON);
  glColor3ub(255, 255, 0);
  glVertex2f(size, size);
  glVertex2f(-size, size);
  glVertex2f(-size, -size);
  glVertex2f(+size, -size);
  glEnd();
  */
  glColor3ub(255, 255, 0);
  DrawEllipse(3, 2, 3, 2, 20);
 
    
  glPopMatrix();

  //draw obj
  glPushMatrix();//When you call glPushMatrix you are pushing a copy of the current matrix on top of the current matrix stack; if it succeeds* there will be identical matrices at the top and just below the top of the current stack.
  glTranslatef(bird_ax, 0.0, 0.0);
  glColor3f(0, 1, 0);
  glColor3ub(0, 0, 250); 
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
  glClearColor(0.0, 0.5, 1.0, 0.0);
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
 

