/*
 *  3D Objects
 *
 *  Demonstrates how to draw objects in 3D.
 *
 *  Key bindings:
 *  m/M        Cycle through different sets of objects
 *  a          Toggle axes
 *  arrows     Change view angle
 *  0          Reset view angle
 *  ESC        Exit
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

int th=0;          //  Azimuth of view angle
int ph=0;          //  Elevation of view angle
double zh=0;       //  Rotation of teapot
int axes=1;        //  Display axes
int mode=0;        //  What to display
const char* text[] = {"Cuboids","Spheres","Goal-Posts","Star","Scene"};

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.14159265/180))
#define Sin(x) (sin((x)*3.14159265/180))
#define PI 3.1415927

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Check for OpenGL errors
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glColor3f(1,0,0);
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back
   glColor3f(0,0,1);
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right
   glColor3f(1,1,0);
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left
   glColor3f(0,1,0);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top
   glColor3f(0,1,1);
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom
   glColor3f(1,0,1);
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/*
 *  Draw a sphere (version 1)
 *     at (x,y,z)
 *     radius (r)
 */
static void sphere1(double x,double y,double z,double r)
{
   const int d=15;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  South pole cap
   glBegin(GL_TRIANGLE_FAN);
   Vertex(0,-90);
   for (int th=0;th<=360;th+=d)
   {
      Vertex(th,d-90);
   }
   glEnd();

   //  Latitude bands
   for (int ph=d-90;ph<=90-2*d;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  North pole cap
   glBegin(GL_TRIANGLE_FAN);
   Vertex(0,90);
   for (int th=0;th<=360;th+=d)
   {
      Vertex(th,90-d);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
static void goalPost(double x, double y, double z)
{
    //Want goal posts to be yellow color
    glBegin(GL_LINES);
    glColor3f(1.0,1.0,0.0);
    
    
    //Need a Middle Connecting the Left and Right
    
    //Left upright
    glVertex3d(0,1,0);
    glVertex3d(1,1,0);
    
    //Right upright
    glVertex3d(0,0,0);
    glVertex3d(1,0,0);
    
    
    //Need a Middle Connecting the Left and Right
    glVertex3d(0,0.5,0);
    glVertex3d(-0.5,0.5,0);
    
    //glEnd();
    /*
    glBegin(GL_LINE_STRIP);
      glVertex3d(1, 1, 0.0);  // V0
      glVertex3d(1, 0, 0.0);  // V1
      glVertex3d(-0.5, 0.5, 0.0);  // V2
    glEnd();
     */
    
}

void draw_cylinder(double x, double y, double z, double r)
{
    double new_x = 0.0;
    double new_y = 0.0;
    double angle = 0.0;
    double angle_stepsize = 0.1;
    
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(x,y,z);
    glScaled(r,r,r);
    
    /** Draw the tube */
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI ) {
        new_x = r * cos(angle);
        new_y = r * sin(angle);
        glVertex3f(new_x,new_y , y);
        glVertex3f(new_x, new_y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(new_x, 0.0, z);
    glVertex3f(new_x, 0.0, 0.0);
    glEnd();
    
    /** Draw the circle on top of cylinder */
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = r * cos(angle);
        y = r * sin(angle);
        glVertex3f(x, y , z);
        angle = angle + angle_stepsize;
    }
    glVertex3f(x, 0.0, z);
    
    glEnd();
    

    //  Undo transformations
    glPopMatrix();
    
}


static void Star(double x, double y, double z){
    
    //Triangle1
    glBegin(GL_TRIANGLES);
    glVertex3d(1.2,1.0,0.0);
    glVertex3d(1.2,1.5,0.0);
    glVertex3d(0.0,1.5, 0.0);
    glEnd();
    
    
    //Triangle2
    glBegin(GL_TRIANGLES);
    glVertex3d(1.2,1.5,0.0);
    glVertex3d(1.6,2.5,0.0);
    glVertex3d(2.0,1.5, 0.0);
    glEnd();
    
    
    //Triangle3
    glBegin(GL_TRIANGLES);
    glVertex3d(2.0,1.0,0.0);
    glVertex3d(1.6,0.5,0.0);
    glVertex3d(2.2,0.0, 0.0);
    glEnd();
    
    //Triangle4
    glBegin(GL_TRIANGLES);
    glVertex3d(2.0,1.5,0.0);
    glVertex3d(2.0,1.0,0.0);
    glVertex3d(3.0,1.5, 0.0);
    glEnd();
    

    //Triangle5
    glBegin(GL_TRIANGLES);
    glVertex3d(1.2,1.5,0.0);
    glVertex3d(1.2,1.0,0.0);
    glVertex3d(2.2,0.0,0.0);
    glEnd();
    
    //Pentagon
    glBegin(GL_POLYGON);
    glVertex3d(1.2,1.5,0.0);
    glVertex3d(1.2,1.0,0.0);
    glVertex3d(1.6,0.5,0.0);
    glVertex3d(2.0,1.0,0.0);
    glVertex3d(2.0,1.5, 0.0);
    glEnd();
    
    glFlush();

}


static void sphere2(double x,double y,double z,double r)
{
   const int d=15;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  Latitude bands
   for (int ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Set view angle
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   //  Decide what to draw
   switch (mode)
   {
      //  Draw cubes
      case 0:
         cube(0,0,0 , 0.3,0.3,0.3 , 0);
         cube(1,0,0 , 0.2,0.2,0.2 , 45);
         cube(0,1,0 , 0.4,0.4,0.2 , 90);
         break;
      //  Draw spheres
      case 1:
         sphere1(0,0,0 , 0.4);
         sphere1(1,0,0 , 0.2);
         sphere2(0,1,0 , 0.2);
         break;
           
     // Create Our Goal Post
     case 2:
           
           draw_cylinder(1,1,1, 0.2);
           glTranslatef(2,2,2);
           //draw_cylinder(1,0,0, 0.4);
           //draw_cylinder(0,2,0, 0.4);
           break;
      // Create Our Star
       case 3:
           // Mix of object
      case 4:
         //  Cube
         cube(-1,0,0 , 0.3,0.3,0.3 , 3*zh);
         //  Ball
         sphere1(0,0,0 , 0.3);
        // Star
        Star(0,1,0);
         //  Utah Teapot
         glPushMatrix();
         glTranslatef(0,0,-1);
         glRotatef(zh,0,1,0);
         glColor3f(Cos(zh)*Cos(zh),0,Sin(zh)*Sin(zh));
         glutSolidTeapot(0.5);
         glPopMatrix();
         break;
   }
   //  White

   glColor3f(1,1,1);
   //  Draw axes
   if (axes)
   {
      const double len=1.5;  //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   Print("Angle=%d,%d    %s",th,ph,text[mode]);
   //  Render the scene
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'a' || ch == 'A')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm')
      mode = (mode+1)%9;
   else if (ch == 'M')
      mode = (mode+8)%9;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   const double dim=2.5;
   double asp = (height>0) ? (double)width/height : 1;
   glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Objects");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
