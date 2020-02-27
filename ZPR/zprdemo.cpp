/*
Edward Ayala | 1/28/2020 | CSC - 4351 Computer Graphics | Assignment 2

SHAPES:
0       pentagon color = violet - DONE
1       hexagon color = pink - DONE
2       cylinder color = lavender -DONE
3       rectangular prism color = gold - DONE
4       cube color = red - DONE

EXTRA CREDIT: 
0       scene movement
1       solid/wireframe - DONE
2       background color - KINDA DONE
*/


#include "zpr.h"
#include <stdio.h>
#include <math.h>
#define GL_SILENCE_DEPRECATION

/* Macro for checking OpenGL error state */

#define GLERROR                                                    \
    {                                                              \
        GLenum code = glGetError();                                \
        while (code!=GL_NO_ERROR)                                  \
        {                                                          \
            printf("%s\n",(char *) gluErrorString(code));          \
                code = glGetError();                               \
        }                                                          \
    }

/* From cube.c */

GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

int shape = 0;

void
drawBox(void)
{
    int i;
    glColor3f(1.0, 0.0, 0.0);
    for (i = 0; i < 6; i++) {
        if (shape == 0)
        {
            glBegin(GL_QUADS);
        }
        else
        {
            glBegin(GL_LINE_LOOP);
        }        
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void
init(void)
{
    /* Setup cube vertex data. */
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
}

/* end from cube.c */


/* Draw axes */

void drawAxes(void)
{
    /* Name-stack manipulation for the purpose of
       selection hit processing when mouse button
       is pressed.  Names are ignored in normal
       OpenGL rendering mode.                    */

    glPushMatrix();
    /* No name for grey sphere */

    glColor3f(0.3, 0.3, 0.3);
    glutSolidSphere(0.7, 20, 20);

    glPushMatrix();
    glPushName(1);            /* Red cone is 1 */
    glColor3f(1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(0.6, 4.0, 20, 20);
    glPopName();
    glPopMatrix();

    glPushMatrix();
    glPushName(2);            /* Green cone is 2 */
    glColor3f(0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.6, 4.0, 20, 20);
    glPopName();
    glPopMatrix();

    glColor3f(0, 0, 1);         /* Blue cone is 3 */
    glPushName(3);
    glutSolidCone(0.6, 4.0, 20, 20);
    glPopName();

    glPopMatrix();
}


/* Draw Pentagon */
void drawPentagon(void) {
    glColor3f(0.93, 0.51, 0.93); // Voilet
    glNormal3fv(&n[0][0]);
    if (shape == 0)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }    
    glVertex3f(3.0, 1.0, 0.0);
    glVertex3f(4.0, 0.2, 0.0);
    glVertex3f(3.6, -1.0, 0.0);
    glVertex3f(2.4, -1.0, 0.0);
    glVertex3f(2.0, 0.2, 0.0);
    glEnd();
}

/* Draw Hexagon */
void drawHexagon(void) {
    glColor3f(1.0, 0.75, 0.79); // Pink
    glNormal3fv(&n[0][0]);
    if (shape == 0)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    glVertex3f(-3.0, 1.0, 0.0);
    glVertex3f(-2.0, 0.5, 0.0);
    glVertex3f(-2.0, -0.5, 0.0);
    glVertex3f(-3.0, -1.0, 0.0);
    glVertex3f(-4.0, -0.5, 0.0);
    glVertex3f(-4.0, 0.5, 0.0);
    glEnd();
}

void drawRect3D(void) {
    // GL_QUADS go in Counter-Clock Wise direction
    // top left, bottom left, top right, bottom right
    
    // FRONT FACE - long
    glNormal3fv(&n[0][0]);
    glColor3f(1.0, 1.0, 0.3);
    if (shape == 0)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    glVertex3f(-2.0, 4.0, 1.0); // TOP LEFT
    glVertex3f(2.0, 4.0, 1.0);  // TOP RIGHT
    glVertex3f(2.0, 2.0, 1.0);  // BOTTOM RIGHT
    glVertex3f(-2.0, 2.0, 1.0); // BOTTOM LEFT
    glEnd();
    
    // BACK FACE - long
    glNormal3fv(&n[1][0]);
    if (shape == 0)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }    
    glVertex3f(-2.0, 4.0, -1.0); // TOP LEFT
    glVertex3f(2.0, 4.0, -1.0);  // TOP RIGHT
    glVertex3f(2.0, 2.0, -1.0);  // BOTTOM RIGHT
    glVertex3f(-2.0, 2.0, -1.0); // BOTTOM LEFT
    glEnd();

    // LEFT FACE - short
    glNormal3fv(&n[2][0]);
    if (shape == 0)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }    
    glVertex3f(-2.0, 4.0, 1.0); // TOP LEFT
    glVertex3f(-2.0, 2.0, 1.0);  // TOP RIGHT
    glVertex3f(-2.0, 2.0, -1.0);  // BOTTOM RIGHT
    glVertex3f(-2.0, 4.0, -1.0); // BOTTOM LEFT
    glEnd();

    // RIGHT FACE - short
    glNormal3fv(&n[3][0]);
    if (shape == 0)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }    
    glVertex3f(2.0, 4.0, 1.0); // TOP LEFT
    glVertex3f(2.0, 2.0, 1.0);  // TOP RIGHT
    glVertex3f(2.0, 2.0, -1.0);  // BOTTOM RIGHT
    glVertex3f(2.0, 4.0, -1.0); // BOTTOM LEFT
    glEnd();

    // BOTTOM FACE - long
    glNormal3fv(&n[4][0]);
    if (shape == 0)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }    
    glVertex3f(-2.0, 2.0, 1.0); // TOP LEFT
    glVertex3f(2.0, 2.0, 1.0);  // TOP RIGHT
    glVertex3f(2.0, 2.0, -1.0);  // BOTTOM RIGHT
    glVertex3f(-2.0, 2.0, -1.0); // BOTTOM LEFT
    glEnd();

    // TOP FACE - long
    glNormal3fv(&n[5][0]);
    if (shape == 0)
    {
        glBegin(GL_QUADS);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }    
    glVertex3f(-2.0, 4.0, 1.0); // TOP LEFT
    glVertex3f(2.0, 4.0, 1.0);  // TOP RIGHT
    glVertex3f(2.0, 4.0, -1.0);  // BOTTOM RIGHT
    glVertex3f(-2.0, 4.0, -1.0); // BOTTOM LEFT
    glEnd();
}

void drawCylinder(void) {
    float theta;
    float PI = 3.14;
    
    glColor3f(0.9, 0.7, 0.98);
    if (shape == 0)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    // FRONT FACE
    glNormal3f(0.0, 0.0, 1.0);
    for (int i = 0; i < 360; i++)
    {
        theta = i * PI / 180;
        glVertex3f(cos(theta), sin(theta) - 3, -2.0);
        //glVertex3f(cos(theta), sin(theta) - 3, 3.0);

    }
    glEnd();
    if (shape == 0)
    {
        glBegin(GL_POLYGON);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    // BACK FACE
    glNormal3f(0.0, 0.0, 1.0);
    for (int i = 0; i < 360; i++)
    {
        theta = i * PI / 180;
        //glVertex3f(cos(theta), sin(theta) - 3, -3.0);
        glVertex3f(cos(theta), sin(theta) - 3, 2.0);

    }
    glEnd();
    if (shape == 0)
    {
        glBegin(GL_QUAD_STRIP);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    // TUBE
    for (int i = 0; i < 360; i++)
    {
        theta = i * PI / 180;
        glNormal3f(cos(theta), sin(theta), 0.0);
        glVertex3f(cos(theta), sin(theta) - 3, -2.0);
        glVertex3f(cos(theta), sin(theta) - 3, 2.0);

    }
    glEnd();
    
}

void processNormalKeys(unsigned char key, int x, int y) {

    if (key == 'q') {
        exit(0);
    }
    else if (key == 'w') {
        shape = 1;
        glutPostRedisplay();
    }
    else if (key == 's') {
        shape = 0;
        glutPostRedisplay();
    }
}

double myRand() {
    return (double)rand() / RAND_MAX;
}

double r = 1, g = 1, b = 1;

/* Background */
void changeBackground(double & v) {
    double eps = v * (myRand() - 0.5);
    v += eps;
    if (v < 0)
        v = 0;
    if (v > 1)
        v = 1;
}

/* Callback function for drawing */
void display(void)
{
    GLERROR;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    changeBackground(r);
    changeBackground(g);
    changeBackground(b);
    glClearColor(r, g, b, 1);
    
//    drawAxes();   // cones
    drawBox();
    drawPentagon();
    drawHexagon();
    drawRect3D();
    drawCylinder();
    glutSwapBuffers();

    GLERROR;
}

/* Callback function for pick-event handling from ZPR */

void pick(GLint name)
{
    printf("Pick: %d\n", name);
    fflush(stdout);
}

static GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//static GLfloat light_diffuse[]  = { 1.0, 0.0, 0.0, 1.0 };
static GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

static GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
static GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
static GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat high_shininess[] = { 100.0 };

/* Entry point */

int main(int argc, char* argv[])
{
    /* Initialise GLUT and create a window */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("GLT Mouse Zoom-Pan-Rotate - Edward Ayala");

    /* Configure GLUT callback functions */

    glutKeyboardFunc(processNormalKeys); 
    glutDisplayFunc(display);
    glutIdleFunc(display);
    

    glScalef(0.25, 0.25, 0.25);

    /* Configure ZPR module */
    init();                         /* <- from cube.c               */
    zprInit();
    zprSelectionFunc(drawAxes);     /* Selection mode draw function */
    zprPickFunc(pick);              /* Pick event client callback   */

     /* Initialise OpenGL */

    GLERROR;

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    GLERROR;

    /* Enter GLUT event loop */

    glutMainLoop();

    return 0;
}