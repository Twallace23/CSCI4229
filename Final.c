/*
 *  Final Project
 *
 * Final Project: Football Scene
 *
 *  Key bindings:
 *  z          toggle projection / orthogonal
 *  l          Toggle lighting on/off
 *  m          Toggles texture mode modulate/replace
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  e/E        decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
int vmode=0;      // View Mode
int mode=0;       //  Texture mode
int ntex=0;       //  Cube faces
int axes=1;       //  Display axes
int th=0;         //  Azimuth of view angle
int fov=65;       //  Field of view (for perspective)
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=10.0;   //  Size of world
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[15]; // Texture names


 /*  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph)+3 , Cos(th)*Cos(ph));
}
//ADD Light
void draw_back(float x, float y, float z, float dx, float dy, float dz, float th, float ph){
    glPushMatrix();
    
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,1,0,0);
    glRotated(ph,0,1,0);
    glScaled(dx,dy,dz);
    //Enable textures
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    //  Cube
    glBegin(GL_QUADS);
    //High Back Bench Piece
    glColor3f(0.69,0.3,0);
    glNormal3f(-1,0,0);
    glTexCoord2f(0,1); glVertex3f(-1,-1, -0.5);
    glTexCoord2f(1,0); glVertex3f(+1,-1, -0.5);
    glTexCoord2f(1,1); glVertex3f(+1,+1, -0.5);
    glTexCoord2f(0,1); glVertex3f(-1,+1, -0.5);
    
    glEnd();
    
    //  Undo transformations
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
//The chains have a circle on the top
//Connected Down by A Triangle
void draw_wallsLR(float x, float y, float z, float dx, float dy, float dz, float th, float ph){
    
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,1,0,0);
    glRotated(ph,0,1,0);
    glScaled(dx,dy,dz);
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[2]);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    //glColor3f(1,1,1);
    glNormal3f(-1,0,0);
    glTexCoord2f(1,1); glVertex3f(-1,-1, -0.5);
    glTexCoord2f(1,0); glVertex3f(+1,-1, -0.5);
    glTexCoord2f(0,0); glVertex3f(+1,+1, -0.5);
    glTexCoord2f(0,1); glVertex3f(-1,+1, -0.5);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    //  Undo transformations
    glPopMatrix();
}

//Enable textures

void draw_wallsFB(float x, float y, float z, float dx, float dy, float dz, float th){
    glPushMatrix();
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,1,0,0);
    glScaled(dx,dy,dz);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[2]);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    //glColor3f(1,1,1);
    glTexCoord2f(1,1); glVertex3f(-1,-1, -0.5);
    glTexCoord2f(1,0); glVertex3f(+1,-1, -0.5);
    glTexCoord2f(0,0); glVertex3f(+1,+1, -0.5);
    glTexCoord2f(0,1); glVertex3f(-1,+1, -0.5);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void draw_chains(float x, float y, float z, float r, float h, float th){
    glPushMatrix();
    glTranslated(x,y,z);
    //glScaled(r,r,r);
    
    glBegin(GL_TRIANGLE_FAN);
    //First Face of the marker
    glVertex3f(-0.5,-0.4,1);
    glVertex3f(0.5,-0.4,1);
    glVertex3f(0,-2,1);
    //Second Face of the marker
    glVertex3f(-0.5,-0.4,-1);
    glVertex3f(0.5,-0.4,-1);
    glVertex3f(0,-2,-1);
    
    
    
    glEnd();
    
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    glColor3f(1,0.65,0);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(x,y,h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(r, 0.0, h);
    
    glEnd();
    
    glPopMatrix();
}
//Need Head CHECK
//Need Arms CHECK- Need to align arms to body
//Need Torso
//Need Bottoms
//Need Hands

void draw_player_defense(float x, float y, float z, float r, float h, float dx, float dy, float dz, float th, float ph){
    //Head
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glRotatef(th,1,0,0);
    glRotatef(ph,0,1,0);
    glColor3f(1,1,0);
    
    //glEnable(GL_TEXTURE_2D);
    //glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    //glBindTexture(GL_TEXTURE_2D,texture[12]);
    
    //glutSolidSphere(1.0,3,3);
    //  South pole cap
    //How can I move my circle up the z axis?
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLE_FAN);
    //Vertex(0,-90);
    
    const int d=15;
    for (int th=0;th<=360;th+=d)
    {
        glTexCoord2f(th,d-90); Vertex(th,d-90);
    }
    glEnd();

    //  Latitude bands
    for (int ph=d-90;ph<=90-2*d;ph+=d)
    {
       glBegin(GL_QUAD_STRIP);
       for (int th=0;th<=360;th+=d)
       {
           glTexCoord2f(th,ph); Vertex(th,ph);
           glTexCoord2f(th,ph+d); Vertex(th,ph+d);
       }
       glEnd();
    }

    //  North pole cap
    glBegin(GL_TRIANGLE_FAN);
    Vertex(0,90);
    for (int th=0;th<=360;th+=d)
    {
        glTexCoord2f(th,90-d); Vertex(th,90-d);
    }
    glEnd();
    
    //glDisable(GL_TEXTURE_2D);
    //Torso
    //  Save transformation
    //  Cube
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[6]);


    glBegin(GL_QUADS);
    //  Front
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(0.25,-1,1);
    glTexCoord2f(1,0); glVertex3f(-0.25,-1,1);
    glTexCoord2f(1,1); glVertex3f(-0.25,-2,1);
    glTexCoord2f(0,1); glVertex3f(0.25,-2,1);
    //  Back
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(+0.25,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-0.25,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-0.25,-2,-1);
    glTexCoord2f(0,1); glVertex3f(0.25,-2,-1);
    //  Right
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(0.25,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+0.25,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+0.25,-2,-1);
    glTexCoord2f(0,1); glVertex3f(+0.25,-2,+1);
    //  Left
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.25,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-0.25,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-0.25,-2,+1);
    glTexCoord2f(0,1); glVertex3f(-0.25,-2,-1);
    //  Top
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.25,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+0.25,-1,+1);
    glTexCoord2f(1,1); glVertex3f(+0.25,-2,-1);
    glTexCoord2f(0,1); glVertex3f(-0.25,-2,-1);
    //  Bottom
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.25,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+0.25,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+0.25,-2,+1);
    glTexCoord2f(0,1); glVertex3f(-0.25,-2,+1);
    //  End
    glEnd();
    
    //glDisable(GL_TEX
    //Legs
    //  Save transformation
    glBegin(GL_QUADS);
    //  Front
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2, 1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2, 1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4, 1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4, 1);
    //  Back
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(+0.07,-2,-1);
    glTexCoord2f(1,0); glVertex3f(-0.07,-2,-1);
    glTexCoord2f(1,1); glVertex3f(-0.07,-4,-1);
    glTexCoord2f(0,1); glVertex3f(+0.07,-4,-1);
    //  Right
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(+0.07,-2,+1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2,-1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4,-1);
    glTexCoord2f(0,1); glVertex3f(+0.07,-4,+1);
    //  Left
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2,-1);
    glTexCoord2f(1,0); glVertex3f(-0.07,-2,+1);
    glTexCoord2f(1,1); glVertex3f(-0.07,-4,+1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4,-1);
    //  Top
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2,+1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2,+1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4,-1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4,-1);
    //  Bottom
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2,-1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2,-1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4,+1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4,+1);
    //  End
    glEnd();
    
    glDisable(GL_TEXTURE_2D);

    //  Undo transformations
    //Torso
    //  Save transformation
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[6]);

    glBegin(GL_QUADS);
    //  Front
    glColor3f(1,1,1);
    glTexCoord2f(0,0);glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0);glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1);glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    //  Back
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    //  Right
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    //  Left
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Top
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Bottom
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
    //  End
    glEnd();

    
    //ARMS
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[10]);
    
    
    //Draw the tube
    glColor3f(1,0,0);
    glNormal3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for (int th=0; th<=360; th+=1){
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x,y,h);
        
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x, y , 0.0);
    }
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, y);
    
    
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, 0.0);
    
    glEnd();
     
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    glColor3f(1,0,0);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(x,y,h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(r, 0.0, h);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //float white[] = {1,1,1,1};
    //float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[10]);

    
    //Draw the tube
    glColor3f(1,0,0);
    glNormal3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for (int th=0; th<=360; th+=1){
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(x,y,0.0);
        glTexCoord2f(-x,y); glVertex3f(-x,-y,-h);
        
        glNormal3f(x,y,0.0);
        glTexCoord2f(-x,y); glVertex3f(x, -y , 0.0);
    }
    glNormal3f(x,y,0.0);
    glTexCoord2f(-x,y); glVertex3f(-r, 0.0, -y);
    
    
    glNormal3f(x,y,0.0);
    glTexCoord2f(-x,y); glVertex3f(-r, 0.0, 0.0);
    
    glEnd();
     
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    glColor3f(1,0,0);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(-x,-y,-h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,-1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(-r, 0.0, -h);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
 
}

void draw_player_offense(float x, float y, float z, float r, float h, float dx, float dy, float dz, float th, float ph){
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    //Head
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glRotatef(th,1,0,0);
    glRotatef(ph,0,1,0);
    glColor3f(1,1,0);
    
    //glEnable(GL_TEXTURE_2D);
    //glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
   // glBindTexture(GL_TEXTURE_2D,texture[11]);
    
    //glutSolidSphere(1.0,3,3);
    //  South pole cap
    //How can I move my circle up the z axis?
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLE_FAN);
    //Vertex(0,-90);
    
    const int d=15;
    for (int th=0;th<=360;th+=d)
    {
        glTexCoord2d(th,d-90); Vertex(th,d-90);
    }
    glEnd();

    //  Latitude bands
    for (int ph=d-90;ph<=90-2*d;ph+=d)
    {
       glBegin(GL_QUAD_STRIP);
       for (int th=0;th<=360;th+=d)
       {
           glTexCoord2f(th,ph); Vertex(th,ph);
           glTexCoord2f(th,ph+d); Vertex(th,ph+d);
       }
       glEnd();
    }

    //  North pole cap
    glBegin(GL_TRIANGLE_FAN);
    Vertex(0,90);
    for (int th=0;th<=360;th+=d)
    {
        glTexCoord2f(th,ph+d); Vertex(th,90-d);
    }
    glEnd();
    //glDisable(GL_TEXTURE_2D);
    
    
    //Torso
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[8]);


    glBegin(GL_QUADS);
    //  Front
    glColor3f(0,0,1);
    glTexCoord2f(0,0); glVertex3f(0.25,-1,1);
    glTexCoord2f(1,0); glVertex3f(-0.25,-1,1);
    glTexCoord2f(1,1); glVertex3f(-0.25,-2,1);
    glTexCoord2f(0,1); glVertex3f(0.25,-2,1);
    //  Back
    glColor3f(0,0,1);
    glTexCoord2f(0,0); glVertex3f(+0.25,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-0.25,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-0.25,-2,-1);
    glTexCoord2f(0,1); glVertex3f(0.25,-2,-1);
    //  Right
    glColor3f(0,0,1);
    glTexCoord2f(0,0); glVertex3f(0.25,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+0.25,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+0.25,-2,-1);
    glTexCoord2f(0,1); glVertex3f(+0.25,-2,+1);
    //  Left
    glColor3f(0,0,1);
    glTexCoord2f(0,0); glVertex3f(-0.25,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-0.25,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-0.25,-2,+1);
    glTexCoord2f(0,1); glVertex3f(-0.25,-2,-1);
    //  Top
    glColor3f(0,0,1);
    glTexCoord2f(0,0); glVertex3f(-0.25,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+0.25,-1,+1);
    glTexCoord2f(1,1); glVertex3f(+0.25,-2,-1);
    glTexCoord2f(0,1); glVertex3f(-0.25,-2,-1);
    //  Bottom
    glColor3f(0,0,1);
    glTexCoord2f(0,0); glVertex3f(-0.25,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+0.25,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+0.25,-2,+1);
    glTexCoord2f(0,1); glVertex3f(-0.25,-2,+1);
    //  End
    glEnd();
    
    
    //glDisable(GL_TEX
    //Legs
    //  Save transformation
    glBegin(GL_QUADS);
    //  Front
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2, 1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2, 1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4, 1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4, 1);
    //  Back
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(+0.07,-2,-1);
    glTexCoord2f(1,0); glVertex3f(-0.07,-2,-1);
    glTexCoord2f(1,1); glVertex3f(-0.07,-4,-1);
    glTexCoord2f(0,1); glVertex3f(+0.07,-4,-1);
    //  Right
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(+0.07,-2,+1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2,-1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4,-1);
    glTexCoord2f(0,1); glVertex3f(+0.07,-4,+1);
    //  Left
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2,-1);
    glTexCoord2f(1,0); glVertex3f(-0.07,-2,+1);
    glTexCoord2f(1,1); glVertex3f(-0.07,-4,+1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4,-1);
    //  Top
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2,+1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2,+1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4,-1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4,-1);
    //  Bottom
    glColor3f(0,0,0);
    glTexCoord2f(0,0); glVertex3f(-0.07,-2,-1);
    glTexCoord2f(1,0); glVertex3f(+0.07,-2,-1);
    glTexCoord2f(1,1); glVertex3f(+0.07,-4,+1);
    glTexCoord2f(0,1); glVertex3f(-0.07,-4,+1);
    //  End
    glEnd();
    
    glDisable(GL_TEXTURE_2D);

    //  Undo transformations
    //Torso
    //  Save transformation
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[8]);

    glBegin(GL_QUADS);
    //  Front
    glColor3f(1,1,1);
    glTexCoord2f(0,0);glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0);glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1);glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    //  Back
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    //  Right
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    //  Left
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Top
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Bottom
    glColor3f(1,1,1);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
    //  End
    glEnd();
    
    //ARMS
    //  Set specular color to white
    //float white[] = {1,1,1,1};
    //float black[] = {0,0,0,1};
    //glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[10]);
    
    
    //Draw the tube
    glColor3f(1,0,0);
    glNormal3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for (int th=0; th<=360; th+=1){
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x,y,h);
        
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x, y , 0.0);
    }
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, y);
    
    
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, 0.0);
    
    glEnd();
     
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    glColor3f(1,0,0);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(x,y,h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(r, 0.0, h);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //float white[] = {1,1,1,1};
    //float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[10]);

    
    //Draw the tube
    glColor3f(1,0,0);
    glNormal3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for (int th=0; th<=360; th+=1){
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(x,y,0.0);
        glTexCoord2f(-x,y); glVertex3f(-x,-y,-h);
        
        glNormal3f(x,y,0.0);
        glTexCoord2f(-x,y); glVertex3f(x, -y , 0.0);
    }
    glNormal3f(x,y,0.0);
    glTexCoord2f(-x,y); glVertex3f(-r, 0.0, -y);
    
    
    glNormal3f(x,y,0.0);
    glTexCoord2f(-x,y); glVertex3f(-r, 0.0, 0.0);
    
    glEnd();
     
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    glColor3f(1,0,0);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(-x,-y,-h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,-1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(-r, 0.0, -h);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
     
    glPopMatrix();
 
}

void draw_connector(float x, float y, float z, float dx, float dy, float dz,float th){
    
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glRotatef(th,1,0,0);
    
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    /*
    glColor3f(1,1,0);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(x,y,h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(r, 0.0, h);
    
    glEnd();
     */
    
    //Cone
    glColor3f(1.0,1.0,0);
    glBegin(GL_TRIANGLES);
    for (th=0;th<=360;th+=30){
        glNormal3f(0,1,0);
        glTexCoord2f(1,1); glVertex3f(0,0,1);
        glTexCoord2f(0,1); glVertex3f(Cos(th),Sin(th),0);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(Cos(th+30),Sin(th+30),0);
        }
    glEnd();
    
    glPopMatrix();
}

void draw_blades(float x, float y, float z, float dx, float dy, float dz,float th,float ph){
    
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    //glRotatef(th,1,0,0);
    glRotatef(th,1,0,0);
    //glRotatef(ph,,0,0);
    
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glColor3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    //Second Square Face
    glEnd();
    
    glPopMatrix();
    
}

void draw_bladesLR(float x, float y, float z, float dx, float dy, float dz,float th){
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glRotated(th,1,0,0);
    //glRotated(ph,0,0,1);
    //glRotatef(ph,,0,0);
    
    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glColor3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    //Second Square Face
    glEnd();
    
    glPopMatrix();
    
}
 

//Draw bottom base block -----Finished
    //Two Squares
    //Four Rectangles
//Draw Connector from base to fan head
    //Box going up?
    //Created a Cone from the Long connector to the blade
//Draw Fan Head
//Draw Fan Blades
//How can I flatten a sphere and make a circle
void draw_fan(float x, float y, float z, float r, float h, float dx, float dy, float dz, float th, float ph){
    //  Set specular color to white
        float white[] = {1,1,1,1};
        float black[] = {0,0,0,1};
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
        glPushMatrix();
        glTranslated(x,y,z);
        glRotatef(th,0,1,0);
        glRotatef(ph,1,0,0);
        glScaled(dx,dy,dz);
        
        glBegin(GL_QUADS);
        //First Square Facee
        glColor3f(1,0,0);
        glNormal3f( 0,+1, 0);
        glVertex3f(-1,+0.5,+1);
        glVertex3f(+1,+0.5,+1);
        glVertex3f(+1,+0.5,-1);
        glVertex3f(-1,+0.5,-1);
        //Second Square Face
        glColor3f(1,0,0);
        glNormal3f( 0,-1, 0);
        glVertex3f(-1,-0,-1);
        glVertex3f(+1,-0,-1);
        glVertex3f(+1,-0,+1);
        glVertex3f(-1,-0,+1);
        //Draw Right Rectangle Edge
        glColor3f(1,0,0);
        glNormal3f(+1, 0, 0);
        glVertex3f(+1,-0.5,+1);
        glVertex3f(+1,-0.5,-1);
        glVertex3f(+1,+0.5,-1);
        glVertex3f(+1,+0.5,+1);
        //Draw Left Rectangle Edge
        glColor3f(1,0,0);
        glNormal3f(-1, 0, 0);
        glVertex3f(-1,-0.5,+1);
        glVertex3f(-1,-0.5,-1);
        glVertex3f(-1,+0.5,-1);
        glVertex3f(-1,+0.5,+1);
        //Draw Front Rectangle Edge
        glColor3f(1,0,0);
        glNormal3f( 0, 0, 1);
        glVertex3f(-1,-0.5,1);
        glVertex3f(+1,-0.5,1);
        glVertex3f(+1,+0.5,1);
        glVertex3f(-1,+0.5,1);
        //Draw Back Rectangle Edge
        glColor3f(1,0,0);
        glNormal3f( 0, 0,-1);
        glVertex3f(+1,-0.5,-1);
        glVertex3f(-1,-0.5,-1);
        glVertex3f(-1,+0.5,-1);
        glVertex3f(+1,+0.5,-1);
        
        glEnd();
        
        glPopMatrix();
}
void draw_fan_piece(float x, float y, float z, float dx, float dy, float dz, float th, float ph){
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    //glRotated(th,1,0,0);
    glScaled(dx,dy,dz);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glColor3f(1,1,1);
    glNormal3f( 0, 0, 1);
    glVertex3f(-0.2,-0.2, 1);
    glVertex3f(+0.2,-0.2, 1);
    glVertex3f(+0.2,+0.2, 1);
    glVertex3f(-0.2,+0.2, 1);
    //  Back
    glColor3f(1,1,1);
    glNormal3f( 0, 0,-1);
    glVertex3f(+0.2,-0.2,-1);
    glVertex3f(-0.2,-0.2,-1);
    glVertex3f(-0.2,+0.2,-1);
    glVertex3f(+0.2,+0.2,-1);
    //  Right
    glColor3f(1,1,1);
    glNormal3f(+1, 0, 0);
    glVertex3f(+0.2,-0.2,+1);
    glVertex3f(+0.2,-0.2,-1);
    glVertex3f(+0.2,+0.2,-1);
    glVertex3f(+0.2,+0.2,+1);
    //  Left
    glColor3f(1,1,1);
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.2,-0.2,-1);
    glVertex3f(-0.2,-0.2,+1);
    glVertex3f(-0.2,+0.2,+1);
    glVertex3f(-0.2,+0.2,-1);
    //  Top
    glColor3f(1,1,1);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.2,+0.2,+1);
    glVertex3f(+0.2,+0.2,+1);
    glVertex3f(+0.2,+0.2,-1);
    glVertex3f(-0.2,+0.2,-1);
    //  Bottom
    glColor3f(1,1,1);
    glNormal3f(0, -1, 0);
    glVertex3f(-0.2,-0.2,-1);
    glVertex3f(+0.2,-0.2,-1);
    glVertex3f(+0.2,-0.2,+1);
    glVertex3f(0.2,-0.2,+1);
    glEnd();
    
    glPopMatrix();
}



void draw_bleachers(float x, float y, float z, float dx, float dy, float dz, float th){
    
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    //glRotated(th,1,0,0);
    glScaled(dx,dy,dz);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[5]);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glColor3f(0.5,0.3,0);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    //  Back
    glColor3f(0.5,0.3,0);
    glNormal3f( 0, 0,-1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    //  Right
    glColor3f(0.5,0.3,0);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    //  Left
    glColor3f(0.5,0.3,0);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Top
    glColor3f(0.5,0.3,0);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Bottom
    glColor3f(0.5,0.3,0);
    glNormal3f( 0,-1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
    glEnd();
    
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}



void draw_jug(float x, float y, float z, float r, float h, float th)
    {
        //  Set specular color to white
        float white[] = {1,1,1,1};
        float black[] = {0,0,0,1};
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
        //  Save transformation
        glPushMatrix();
        //  Offset and scale
        glTranslated(x,y,z);
        glScaled(r,r,r);
        glRotatef(th,0,1,0);
        //glRotatef(-90,1,0,0);
        
        
        //Enable textures
        //glEnable(GL_TEXTURE_2D);
        //glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
        //glBindTexture(GL_TEXTURE_2D,texture[ntex]);
        //if(ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
        
        
        //Draw the tube
        glColor3f(1.0,0.65,0.0);
        glNormal3f(0,0,1);
        glBegin(GL_QUAD_STRIP);
        for (int th=0; th<=360; th+=1){
            x = r * cos(th);
            y = r * sin(th);
            glNormal3f(x,y,0.0);
            glVertex3f(x,y,h);
            
            glNormal3f(x,y,0.0);
            glVertex3f(x, y , 0.0);
        }
        glNormal3f(x,y,0.0);
        glVertex3f(r, 0.0, y);
        
        
        glNormal3f(x,y,0.0);
        glVertex3f(r, 0.0, 0.0);
        
        glEnd();
         
        // Draw the circle on top of cylinder
        //glNormal3f(0,0,1)
        glColor3f(1.0,1.0,1.0);
        glNormal3f(0,1,0);
        glBegin(GL_POLYGON);
        for (int th=0; th<=360; th+=30) {
            x = r * cos(th);
            y = r * sin(th);
            glNormal3f(0,1,0);
            glTexCoord2f(0,1); glVertex3f(x,y,h);
        }
        glNormal3f(0,1,0);
        glTexCoord2f(1,1); glVertex3f(0,0,1);
       
        
        glNormal3f(0,1,0);
        glTexCoord2f(1,1); glVertex3f(r, 0.0, h);
    
        glEnd();
        
        //Jug Handles
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_QUADS);
        //Need to Create Rectangle for jug handles
        //Front Face
        glVertex3f(-0.5,-0.5,0.8);
        glVertex3f(0.5,-0.5,0.8);
        glVertex3f(0.5,0.5,0.8);
        glVertex3f(-0.5,0.5,0.8);
        glEnd();
        //Jug Spout
        glColor3f(0,0,1);
        glBegin(GL_QUAD_STRIP);
        for (int th=0; th<=360; th+=30) {
            x = r * cos(th);
            y = r * sin(th);
            glNormal3f(0,1,0);
            glVertex3f(x,y,z);
        }
        glVertex3f(0,0,1);
        glVertex3f(r, 0.0, 0.0);
    
        glEnd();
        
        
        
        //  Undo transformations
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
void draw_tent(float x, float y, float z, float dx, float dy, float dz, double th){
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[7]);
    //  Cube
    glBegin(GL_QUADS);
    //  Front
    glColor3f(0,0,1);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    //  Back
    glColor3f(0,0,1);
    glNormal3f( 0, 0, -1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    //  Right
    glColor3f(0,0,1);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    //  Left
    glColor3f(0,0,1);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    //  Top
    glColor3f(0,0,1);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}




void draw_head(float x, float y, float z, float r){
    
    
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(r,r,r);
    glRotatef(th,0,1,0);
    //  South pole cap
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLE_FAN);
    //Vertex(0,-90);
    
    const int d=15;
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
void draw_torso(float x, float y, float z){
    glPushMatrix();
    
    glTranslated(x,y,z);
    glScaled(x,x,x);
    
    
    // Having issues finishing the face of the trapezoid how to account for weird shape on the edge
    // How to handle the top and bottom faces
    glBegin(GL_QUADS); //Begin Trapezoid coordinates
    glVertex3f(-0.7, 1.0, 0.0);
    glVertex3f(0.7, 1.0, 0.0);
    glVertex3f(0.4, -0.25, 0.0);
    glVertex3f(-0.4, -0.25, 0.0);
    
    glVertex3f(-0.7, 1.0, 0.5);
    glVertex3f(0.7, 1.0, 0.5);
    glVertex3f(0.4, -0.25, 0.5);
    glVertex3f(-0.4, -0.25, 0.5);
    
    
    glEnd(); // End Trapezoid coordinates
    
    glPopMatrix();
}
 */

void draw_cylinder(float x, float y, float z, float r, float h, float th)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(x,y,z);
    glScaled(r,r,r);
    glRotatef(th,0,1,0);
    //glRotatef(-90,1,0,0);
    
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    //glBindTexture(GL_TEXTURE_2D,texture[ntex]);
    //if(nte)
    glBindTexture(GL_TEXTURE_2D,texture[1]);
    
    
    //Draw the tube
    glColor3f(1,1,1);
    glNormal3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for (int th=0; th<=360; th+=1){
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x,y,h);
        
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x, y , 0.0);
    }
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, y);
    
    
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, 0.0);
    
    glEnd();
     
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    glColor3f(1,1,1);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(x,y,h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(r, 0.0, h);
    
    glEnd();
    
    //  Undo transformations
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void draw_table_leg(float x, float y, float z, float r, float h, float th)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(x,y,z);
    glScaled(r,r,r);
    glRotatef(th,0,1,0);
    //glRotatef(-90,1,0,0);
    
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[4]);
    
    
    //Draw the tube
    glColor3f(0.3,0.6,0);
    glNormal3f(0,0,1);
    glBegin(GL_QUAD_STRIP);
    for (int th=0; th<=360; th+=1){
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x,y,h);
        
        glNormal3f(x,y,0.0);
        glTexCoord2f(x,y); glVertex3f(x, y , 0.0);
    }
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, y);
    
    
    glNormal3f(x,y,0.0);
    glTexCoord2f(x,y); glVertex3f(r, 0.0, 0.0);
    
    glEnd();
     
    // Draw the circle on top of cylinder
    //glNormal3f(0,0,1)
    glColor3f(0.3,0.6,0);
    glNormal3f(0,1,0);
    glBegin(GL_POLYGON);
    for (int th=0; th<=360; th+=30) {
        x = r * cos(th);
        y = r * sin(th);
        glNormal3f(0,1,0);
        glTexCoord2f(0,1); glVertex3f(x,y,h);
    }
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(0,0,1);
   
    
    glNormal3f(0,1,0);
    glTexCoord2f(1,1); glVertex3f(r, 0.0, h);
    
    glEnd();
    
    //  Undo transformations
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void field(float w,float x, float y, float z, float s){
                    
                    
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
                    
    glPushMatrix();
    glTranslated(x,y,z);
    glRotatef(-90,1,0,0);
    glScaled(s,s,s);
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glColor3f(0.0,1.0,0.0);
    glTexCoord2f(1,1); glVertex3f(w/2,0, w/2);
    glTexCoord2f(1,0); glVertex3f(w/2,0, -(w/2));
    glTexCoord2f(0,0); glVertex3f(-(w/2),0, -(w/2));
    glTexCoord2f(0,1); glVertex3f(-(w/2),0, w/2);
    
    glEnd();
    //glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    
    //Out Of Bounds
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,1);
    glVertex3f(8,12,-1.8);
    glVertex3f(8,-12,-1.8);
    glEnd();
    
    //Endzone
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,1);
    glVertex3f(-8,8.0,-1.8);
    glVertex3f(8,8.0,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,6.5,-1.8);
    glVertex3f(8,6.5,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,5,-1.8);
    glVertex3f(8,5,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,3.5,-1.8);
    glVertex3f(8,3.5,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,2,-1.8);
    glVertex3f(8,2,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,0.5,-1.8);
    glVertex3f(8,0.5,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,-1,-1.8);
    glVertex3f(8,-1,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,-2.5,-1.8);
    glVertex3f(8,-2.5,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,-4,-1.8);
    glVertex3f(8,-4,-1.8);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1,1,1);
    glVertex3f(-8,-5.5,-1.8);
    glVertex3f(8,-5.5,-1.8);
    glEnd();
    
    //Other Endzone
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,1);
    glVertex3f(-8,-7,-1.8);
    glVertex3f(8,-7,-1.8);
    glEnd();
    
    //Other Endzone
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,1);
    glVertex3f(-8,-7,-1.8);
    glVertex3f(8,-7,-1.8);
    glEnd();

    //Out Of Bounds
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,1);
    glVertex3f(-8,12,-1.8);
    glVertex3f(-8,-12,-1.8);
    glEnd();

}

static void draw_football(float x, float y, float z,float dx,float dy,float dz,float radius,float th)
{
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    const int d=15;

    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glRotatef(th,1,0,0);
    //  Latitude bands
    for (int ph=-90;ph<90;ph+=d)
    {
        glColor3f(0.58,0.29,0);
       glBegin(GL_QUAD_STRIP);
       for (int th=0;th<=360;th+=d)
       {
          Vertex(th+10,ph);
          Vertex(th+10,ph+d);
       }
       glEnd();
    }
    
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex3f(0.5,0.5,1);
    glVertex3f(-0.5,0.5,1);
    
    glEnd();

    //  Undo transformations
    glPopMatrix();
}

static void draw_stands(float w,float x, float y, float z, float s)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    glPushMatrix();
    glTranslated(x,y,z);
    glRotatef(-90,1,0,0);
    glScaled(s,s,s);
    
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[3]);
    
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glColor3f(0.5,0.5,0.5);
    glTexCoord2f(1,1); glVertex3f(w/2,0, w/2);
    glTexCoord2f(1,0); glVertex3f(w/2,0, -(w/2));
    glTexCoord2f(0,0); glVertex3f(-(w/2),0, -(w/2));
    glTexCoord2f(0,1); glVertex3f(-(w/2),0, w/2);
    
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    //float position = [];
    
    /*
    for(int i=0; i<x; i++){
       draw_chair(x+3,y+3,z+3,dx,dy,dz,th);
    }
     */
    
}
void draw_massage_table(float x, float y, float z, float dx, float dy, float dz)
{
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex3f(-1,-1, 1);
    glVertex3f(+1,-1, 1);
    glVertex3f(+1,+1, 1);
    glVertex3f(-1,+1, 1);
    //  Back
    glColor3f(0,0,0);
    glVertex3f(+1,-1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,+1,-1);
    glVertex3f(+1,+1,-1);
    //  Right
    glColor3f(0,0,0);
    glVertex3f(+1,-1,+1);
    glVertex3f(+1,-1,-1);
    glVertex3f(+1,+1,-1);
    glVertex3f(+1,+1,+1);
    //  Left
    glColor3f(0,0,0);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,+1);
    glVertex3f(-1,+1,+1);
    glVertex3f(-1,+1,-1);
    //  Top
    glColor3f(0,0,0);
    glVertex3f(-1,+1,+1);
    glVertex3f(+1,+1,+1);
    glVertex3f(+1,+1,-1);
    glVertex3f(-1,+1,-1);
   //  End
    glEnd();
    
    glPopMatrix();
    
}
     
    
   // glPopMatrix();
void draw_chair(float x, float y, float z, float dx, float dy, float dz, float th,float ph)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[8]);
    
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(dx,dy,dz);
    glRotatef(th,1,0,0);
    glRotatef(ph,0,1,0);
    glBegin(GL_QUADS);
    //  Back
    glColor3f(0,0,1);
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(1,-1,-1);
    glTexCoord2f(0,0);glVertex3f(1,-1,+1);
    glTexCoord2f(0,0); glVertex3f(1,+1,1);
    glTexCoord2f(0,0); glVertex3f(1,+1,-1);
    //  Bottom
    glColor3f(0,0,1);
    glNormal3f( 0,-1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    
}
/*
void movement(float x, float y, float z, float th){
    int wasd = 0;
    float walking_direction(th);
    bool walking = false;
    
    switch (wasd){
        case 1:
        case 11:
            //forwards
            walking = true;
            break;
        case 3:
            //left-forwards
            walking = true;
            walk_direction += 45
            break;
        case 2:
        case 7:
            //left
            walking = true;
            walk_direction += 90;
            break;
        case 6:
            //backwards
            walking = true;
            walk_direction += 135;
            break;
            
        case 4:
        case 14:
            //backwards
            walking = true;
            walk_direction +=180
            break;
        case 12:
            //right-backwards
            walking = true;
            walk_direction += 225;
            break;
            
        case 8:
        case 13:
            //right
            walking = true;
            walk_direction += 270;
            break;
            
        case 9:
            //right-forwards
            walking = true;
            walk_direction += 315
        
    }
    //move
    if(walking){
        x += 0.1 * vec3
        cos(th)(walking_direction)
    }
}
 */
    

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
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
     
     double Ex = 0;
     double Ey = 0;
     double Ez = 0;
     
        //Set Perspective
        //if viewing mode
      if (vmode == 1){
          Ex = -2*dim*Sin(th)*Cos(ph);
          Ey = +2*dim        *Sin(ph);
          Ez = +2*dim*Cos(th)*Cos(ph);
          gluLookAt(Ex,Ez,Ey , 0,0,0 , 0,0,Cos(ph));
          
      }
        //Set Orthogonal
      else if (vmode == 0){
          glRotatef(ph,1,0,0);
          glRotatef(th,0,0,1);
    //First-Person
      }else if(vmode == 2){
          
          double Cx = Cos(th);
          double Cy = Sin(ph);
          double Cz = Sin(th);
          
          Ex = 0;
          Ey = 0.8;
          Ez = 0.15;
          
          Cx = Cx + Ex;
          Cy = Cy + Ey;
          Cz = Cz + Ez;
          
          gluLookAt(Ex,Ez,Ey , Cx,Cz,Cy , 0,0,Cos(ph));
      }
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {5*Cos(zh),ylight,5*Sin(zh),1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);
    draw_football(1.5,-8,3, 0.25,0.25,0.5, 0.5,180);
    //D-Line
    //White Pants
    draw_player_defense(-0.5,0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_defense(0,0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_defense(1.0,0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_defense(0.5,0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //Linebackers
    draw_player_defense(-0.5,-2,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_defense(0.5,-2,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_defense(1.5,-2,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //draw_player(-1.0,-2,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //Corners
    draw_player_defense(7.5,-2,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_defense(-7.5,-2,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //Safetys
    draw_player_defense(5.5,-5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_defense(-5.5,-5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    
    
    //O-Line
    draw_player_offense(-0.5,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(-1.0,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(0,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(0.5,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(1.0,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //QB
    draw_player_offense(0.0,1.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(0.0,2.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    
    //WR
    draw_player_offense(7.5,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(6.5,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(5.5,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    draw_player_offense(-7.5,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    
    
    
    
    draw_wallsFB(0,-11.8,-1, 12,1,0, 90);
    draw_wallsFB(0,11.8,-1, 12,1,0, 90);
    draw_wallsLR(11.8,0,-1, 12,1,0, 90,90);
    draw_wallsLR(-11.5,0,-1, 12,1,0, 90,90);
    
    //
    draw_massage_table(-10,-3.0,-1.4, 0.25,0.5,0);
    draw_table_leg(-10,-2.6,-1.9, 0.25,2.0, 0);
    draw_table_leg(-9.75,-2.6,-1.9, 0.25,2.0, 0);
    draw_table_leg(-10,-3.5,-1.9, 0.25,2.0, 0);
    draw_table_leg(-9.75,-3.5,-1.9, 0.25,2.0, 0);
    
    draw_massage_table(10,-3.0,-1.4, 0.25,0.5,0);
    draw_table_leg(9.8,-2.6,-1.9, 0.25,2.0, 0);
    draw_table_leg(10.25,-2.6,-1.9, 0.25,2.0, 0);
    draw_table_leg(9.8,-3.5,-1.9, 0.25,2.0, 0);
    draw_table_leg(10.25,-3.5,-1.9, 0.25,2.0, 0);

    //Fan1
    draw_blades(10,-5.0,1.75, 0.2,1.0,0.75, 90,0);
    draw_blades(10,-5.0,0,    0.2,1.0,0.75, 90,0);
    draw_bladesLR(9.0,-5.75,1.0, 0.5,0.3,0.25, 90);
    draw_bladesLR(11.0,-5.75,1.0, 0.5,0.3,0.25, 90);
    draw_fan(10,-6.5,-1.5, 0.4,0.4, 0.5,0.5,0.5, 0,90);
    draw_fan_piece(10,-6.5,-0.25, 1,1,1, 0,0);
    draw_connector(10,-6.25,0.8, 0.4,0.4,0.4, 270);
    
    //Fan2
    draw_blades(-10,-5.0,1.75, 0.2,1.0,0.75, 90,0);
    draw_blades(-10,-5.0,0,    0.2,1.0,0.75, 90,0);
    draw_bladesLR(-9.0,-5.75,1.0, 0.5,0.3,0.25, 90);
    draw_bladesLR(-11.0,-5.75,1.0, 0.5,0.3,0.25, 90);
    draw_fan(-10,-6.5,-1.5, 0.4,0.4, 0.5,0.5,0.5, 0,90);
    draw_fan_piece(-10,-6.5,-0.25, 1,1,1, 0,0);
    draw_connector(-10,-6.25,0.8, 0.4,0.4,0.4, 270);

    //Left Stand
    draw_stands(12,-24,0,0.5,2);
    draw_chair(15,0,3.0, 2,2,2, 90,0);
    draw_chair(15,4,3.0, 2,2,2, 90,0);
    draw_player_defense(16,-1,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,-0.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,1.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,1.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,0.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,2.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,2.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,3.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,3.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,4.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(16,4.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    //Right Stand
    draw_stands(12,24,0,0.5,2);
    draw_chair(-15,0,3.0, 2,2,2, 90,180);
    draw_chair(-15,4,3.0, 2,2,2, 90,180);
    draw_player_offense(-16,-1,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,-0.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,1.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,1.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,0.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,2.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,2.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,3.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,3.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,4.0,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-16,4.5,1, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    
    draw_wallsFB(0,-11.8,-1, 12,1,0, 90);
    draw_wallsFB(0,11.8,-1, 12,1,0, 90);
    draw_wallsLR(11.8,0,-1, 12,1,0, 90,90);
    draw_wallsLR(-11.5,0,-1, 12,1,0, 90,90);
    field(12,0.5,0,-2.0,2);
  
    //glColor3f(1,1,1);
    draw_cylinder(-0.25,11,0, 0.5,4.0, 0);
    draw_cylinder(1.75,11,0, 0.5,4.0, 0);
    draw_cylinder(0.5,11,0,  0.5,3.0, 90);
    draw_cylinder(-0.5,11,0, 0.5,3.0, 90);
    draw_cylinder(0.75,11,0, 0.5,4.0, 180);
    
    
    draw_cylinder(-0.25,-11,0, 0.5,4.0, 0);
    draw_cylinder(1.75,-11,0, 0.5,4.0, 0);
    draw_cylinder(0.5,-11,0,  0.5,3.0, 90);
    draw_cylinder(-0.5,-11,0, 0.5,3.0, 90);
    draw_cylinder(0.75,-11,0, 0.5,4.0, 180);
    

    //right side of field
    draw_back(10.8,1.0,-0.5, 1.2,0.6,0.6, 90,90);
    draw_bleachers(10.0,1.0,-1.5, 0.6,1.2,0.6, 0);
    draw_player_defense(9.5,0.5,-0.75, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(9.5,1.0,-0.75, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(9.5,1.5,-0.75, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    //left side of field
    draw_back(-10.3,1.0,-0.5, 1.2,0.6,0.6, 90,90);
    draw_bleachers(-10.0,1.0, -1.5, 0.6,1.2,0.6, 0);
    draw_player_offense(-9.5,0.5,-0.75, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.5,1.0,-0.75, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.5,1.5,-0.75, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    //draw_player_offense(-1.0,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //draw_player_offense(0,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //draw_player_offense(0.5,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    //draw_player_offense(1.0,0.5,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,90);
    
    
    draw_tent(-10.0,-3.0,-1.5, 0.6,1.2,0.6, 0);
    draw_tent(10.0,-3.0,-1.5, 0.6,1.2,0.6, 0);
    
    draw_jug(-10.0,-1.0,-1.2, 0.5,1.0,0);
    draw_player_offense(-9.5,-1.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    draw_player_offense(-9.0,-8.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.5,-9.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.0,-7.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.5,-6.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    draw_player_offense(-9.0,8.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.5,9.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.0,7.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_offense(-9.5,6.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    draw_jug(10.0,-1.0,-1.2, 0.5,1.0,0);
    draw_player_defense(9.5,-1.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(9.5,-1.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    draw_player_defense(9.0,-8.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(9.0,-9.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(10.0,-7.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(10.5,-10.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    
    draw_player_defense(9.0,8.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(9.0,9.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(10.0,7.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
    draw_player_defense(10.5,10.0,-1.5, 0.5,4.0, 0.1,0.1,0.1, 90,0);
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      const double len=2.0; //  Length of axes
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
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Dim=%.1f Light=%s Texture=%s",dim,light?"On":"Off",mode?"Replace":"Modulate");
   if (light)
   {
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
       //glWindowPos2i(5,50);
       //Print("Angle=%d,%d FOV=%d Projection=%s",th,ph,fov,vmode?"Perspective":"First-Person");
   }
    glWindowPos2i(5,50);
    Print("Angle=%d,%d FOV=%d Projection=%s",th,ph,fov,vmode?"Orthogonal":"First-Person");
     

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
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
    // Toggle viewing mode
   //  Reset view angle
    /*
    else if(ch == 'w' )
        //movement
    else if(ch == 'a')
        
    else if(ch == 's')
    
    else if(ch == 'd')
     */
    
   else if (ch == '0')
      th = ph = 0;
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;
    // Change View Mode
   //  Toggle texture mode
   else if (ch == 'z' || ch == 'Z')
      vmode = 1-vmode;
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle textures mode
   else if (ch == 't')
      ntex = 1-ntex;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Repitition
   //else if (ch=='+')
    //  rep++;
   //else if (ch=='-' && rep>1)
     // rep--;
    //  Change field of view angle
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
    //vmode %=3;
    Project(45,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(45,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Final Project Tayvian Wallace");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("blades.bmp");
   texture[1] = LoadTexBMP("steel.bmp");
   texture[2] = LoadTexBMP("Brick.bmp");
   texture[3] = LoadTexBMP("24.bmp");
   texture[4] = LoadTexBMP("wood.bmp");
   texture[5] = LoadTexBMP("Darkwood.bmp");
   texture[6] = LoadTexBMP("Jersey.bmp");
   texture[7] = LoadTexBMP("tent.bmp");
   texture[8] = LoadTexBMP("bj.bmp");
   texture[9] = LoadTexBMP("il.bmp");
   texture[10] = LoadTexBMP("lego.bmp");
   texture[11] = LoadTexBMP("face.bmp");
   texture[12] = LoadTexBMP("face2.bmp");
    /*
 
     */
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}

