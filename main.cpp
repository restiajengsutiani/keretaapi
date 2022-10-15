#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define Vrt glVertex3s

int proj = 1, new_mouse = 0, mouse_rot = 1, mouse_trn = 0;

float turn = 50.0, tipp = 30.0, twst = 0.0, x_click = 0, y_click = 0, xtm = 0.0, ytm = 0.0,
      scl = 1.0, xcr = 0.0;

GLfloat lit1_spc[] = {0.20, 0.20,  0.15, 1.00},
        lit1_dfs[] = {0.70, 0.70,  0.65, 1.00},
		lit1_amb[] = {0.25, 0.25,  0.20, 1.00},
		lit1_pos[] = {0.20, 2.50,  5.20, 1.00};

GLfloat lit2_spc[] = { 0.00,  0.00,  0.00, 1.00},
        lit2_dfs[] = { 0.30,  0.30,  0.35, 1.00},
		lit2_amb[] = { 0.20,  0.20,  0.25, 1.00},
		lit2_pos[] = { 1.50, -2.00, -4.00, 0.01};

//-----------------------------------------   Keybord   --------------------------------------------

void Keybord (unsigned char ch, int x, int y)
{
    printf ("   Keyboard -> '%c' pressed.", ch);

    switch (ch)  {
       case 'p' :  proj      = !proj;        break;
       case 'r' :  mouse_trn = 0;
                   mouse_rot = 1;            break;
       case 't' :  mouse_trn = 1;
                   mouse_rot = 0;            break;
       case 'z' :  turn = 0.0; tipp = 0.0;
                   xtm  = 0.0; ytm  = 0.0;
                   scl  = 1.0;               break;
       case '-' :  scl *= 0.92;              break;
       case '+' :  scl *= 1.06;              break;
       case 'd' :  xcr += 2.00;              break;
       case 'D' :  xcr -= 2.00;              break;

       case  27 :  exit (0);                 break;
    }

    glutPostRedisplay();
}

//--+----4----+----3----+----2----+----1----+----|----+----1----+----2----+----3----+----4----+----5
//------------------------------------------   Mouse   ---------------------------------------------

void Mouse (int button, int state, int x, int y)
{
    x_click = x;
    y_click = y;

    new_mouse = 1;
}

//--+----4----+----3----+----2----+----1----+----|----+----1----+----2----+----3----+----4----+----5
//------------------------------------------   Motion   --------------------------------------------

void Motion (int x, int y)
{
    float turn_del, tipp_del, x_del, y_del;

    static int c = 0, x_sav, y_sav;
    static float turn_save = 0.0, tipp_save = 0.0;

    // printf ("   Motion:  %5d ->   x = %5d, y = %5d.

    if (new_mouse)  {
       new_mouse = 0;
       x_sav = x_click;
       y_sav = y_click;
    }

    if (mouse_rot)  {

       turn_del = x - x_sav;
       turn += turn_del;

       tipp_del = y - y_sav;
       tipp += tipp_del;

    }  else if (mouse_trn)  {

       x_del = float(x - x_sav) * 0.01;
       xtm  += x_del;

       y_del = float(y - y_sav) * 0.01;
       ytm  -= y_del;

    }

    x_sav = x;
    y_sav = y;

    glutPostRedisplay();
}

//---9----8----7----6----5----4----3----2----1---++---1----2----3----4----5----6----7----8----9---\\
//---------------------------------------   Init_Lights   ------------------------------------------

void Init_Lights (void)
{
    glLightfv (GL_LIGHT1, GL_SPECULAR, lit1_spc);
    glLightfv (GL_LIGHT1, GL_DIFFUSE , lit1_dfs);
    glLightfv (GL_LIGHT1, GL_AMBIENT , lit1_amb);
    glLightfv (GL_LIGHT1, GL_POSITION, lit1_pos);

    glLightfv (GL_LIGHT2, GL_SPECULAR, lit2_spc);
    glLightfv (GL_LIGHT2, GL_DIFFUSE , lit2_dfs);
    glLightfv (GL_LIGHT2, GL_AMBIENT , lit2_amb);
    glLightfv (GL_LIGHT2, GL_POSITION, lit2_pos);

    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHT2);

    glEnable (GL_AUTO_NORMAL);
    glEnable (GL_NORMALIZE  );
}

//----------------------------------------   Draw_Rail   -------------------------------------------

void Draw_Rail (void)
{
    glColor3f (0.40,0.55,0.60);
    glEnable (GL_LIGHTING);

    glPushMatrix();
       glTranslatef (15.0, -26.0, 0.0);
       glScalef     (10.0, 0.3,3.0);
       glutSolidCube (-20.0f);
    glPopMatrix();

    glColor3f (0.40,0.35,0.30);
    glPushMatrix();
       glTranslatef (15.0, -25.0, 17.0);
       glScalef     (9.5, 0.3,0.1);
       glutSolidCube (-20.0f);
    glPopMatrix();

    glPushMatrix();
       glTranslatef (15.0, -25.0, -17.0);
       glScalef     (9.5, 0.3,0.1);
       glutSolidCube (-20.0f);
    glPopMatrix();
}

//-------------------------penyambung roda----------------

void Draw_Wheel (void)
{
    glColor3f (0.2,0.2,0.25);
    glEnable (GL_LIGHTING);

    glPushMatrix();  //rantai kanan
       glTranslatef (-16, -13.0, 17.0);
       glScalef     (2.2, 0.1,0.1);
       glutSolidCube (-20.0f);
    glPopMatrix();

    glPushMatrix(); //rantai kiri
       glTranslatef (-16, -13.0, -17.0);
       glScalef     (2.2, 0.1,0.1);
       glutSolidCube (-20.0f);
    glPopMatrix();

    glPushMatrix(); //rantai kiri gerbong
       glTranslatef (50, -15.0, -17.0);
       glScalef     (1.6, 0.1,0.1);
       glutSolidCube (-20.0f);
    glPopMatrix();

    glPushMatrix(); //rantai kanan gerbong
       glTranslatef (50, -15.0, 17.0);
       glScalef     (1.6, 0.1,0.1);
       glutSolidCube (-20.0f);
    glPopMatrix();
}


//---------------------------------------   Render_Wheel   -----------------------------------------

void Render_Wheel (int xt, int yt, int zt)
{
    glPushMatrix();
       glTranslatef   (xt, yt, zt);
       glutSolidTorus (2,5,12,36);
    glPopMatrix();
}

void Render_WheelB (int xt, int yt, int zt)
{
    glPushMatrix();
       glTranslatef   (xt, yt, zt);
       glutSolidTorus (2,7,12,36);
    glPopMatrix();
}

//-----------------------------------------   Draw_Car   -------------------------------------------

void Draw_Car (void)
{
    glDisable (GL_LIGHTING);

    glBegin (GL_QUADS);
       glColor3f (0.3, 0.6, 0.6);
       Vrt(-45,  0, 15); Vrt( 10,  0, 15); Vrt( 10,-15, 15); Vrt(-50,-15, 15);  // left
       Vrt(-45,  0,-15); Vrt( 10,  0,-15); Vrt( 10,-15,-15); Vrt(-50,-15,-15);  // right
       glColor3f (0.4, 0.6, 0.6);
       Vrt( 10,  0,-15); Vrt( 10,  0, 15); Vrt( 10,-15, 15); Vrt( 10,-15,-15);  // back
       Vrt(-45,  0,-15); Vrt(-45,  0, 15); Vrt(-50,-15, 15); Vrt(-50,-15,-15);  // front
       glColor3f (0.4, 0.6, 0.8);
       Vrt(-20, 20, 15); Vrt(-20, 20,-15); Vrt( 10, 20,-15); Vrt( 10, 20, 15);  // roof
       glColor3f (0.7, 0.7, 0.5);
       Vrt(-20,  0, 15); Vrt(-20, 20, 15); Vrt( 10, 20, 15); Vrt( 10,  0, 15);  // window l
       Vrt(-20,  0,-15); Vrt(-20, 20,-15); Vrt( 10, 20,-15); Vrt( 10,  0,-15);  // window r
       glColor3f (0.7, 0.6, 0.5);
       Vrt(-20, 20, 15); Vrt(-20,  0, 15); Vrt(-20,  0,-15); Vrt(-20, 20,-15);  // kaca depan
       Vrt( 10, 20, 15); Vrt( 10, 20,-15); Vrt( 10,  0,-15); Vrt( 10,  0, 15);  // kaca belakang
       glColor3f (0.4, 0.5, 0.5);
       Vrt(-50,-15, 15); Vrt(-50,-15,-15); Vrt( 10,-15,-15); Vrt( 10,-15, 15);  // bottom
       Vrt(-45,0, 15); Vrt(-45,0,-15); Vrt( -20,0,-15); Vrt( -20,0, 15);  // bagasi
       glEnd ();

       //gerbong
       glBegin (GL_QUADS);
       glColor3f (0.7, 0.6, 0.5);
       Vrt( 25, 15, 15); Vrt( 25, 15,-15); Vrt( 25,  0,-15); Vrt( 25,  0, 15); //kaca depan
       Vrt( 75, 15, 15); Vrt( 75, 15,-15); Vrt( 75,  0,-15); Vrt( 75,  0, 15); //kaca belakang
       glColor3f (0.4, 0.6, 0.6);
       Vrt( 25,  0,-15); Vrt( 25,  0, 15); Vrt( 25,-15, 15); Vrt( 25,-15,-15); // depan
       Vrt( 75,  0,-15); Vrt( 75,  0, 15); Vrt( 75,-15, 15); Vrt( 75,-15,-15); // belakang
       glColor3f (0.3, 0.6, 0.6);
       Vrt(25,  0, 15); Vrt( 75,  0, 15); Vrt(75,-15, 15); Vrt(25,-15, 15);  // kiri
       Vrt(25,  0,-15); Vrt( 75,  0,-15); Vrt(75,-15,-15); Vrt(25,-15,-15);  // kanan
       glColor3f (0.7, 0.7, 0.5);
       Vrt(25,  0, 15); Vrt( 75,  0, 15); Vrt(75,15, 15); Vrt(25,15, 15);  // kaca kiri
       Vrt(25,  0,-15); Vrt( 75,  0,-15); Vrt(75,15,-15); Vrt(25,15,-15);  // kaca kanan
       glColor3f (0.4, 0.6, 0.8);
       Vrt(25, 15, 15); Vrt(25, 15,-15); Vrt( 75, 15,-15); Vrt( 75, 15, 15);  // roof
       glColor3f (0.4, 0.5, 0.5);
       Vrt(25, -15, 15); Vrt(25, -15,-15); Vrt( 75, -15,-15); Vrt( 75, -15, 15);  // bottom
    glEnd ();

//       // penyambung ada dua
       glBegin (GL_QUADS);
       glColor3f (0.30,0.25,0.30);
       Vrt(10,  -11, 10); Vrt( 25,  -11, 10); Vrt(25,-14, 10); Vrt(10,-14, 10);  // kiri A
       Vrt(10,  -11, 7); Vrt( 25,  -11, 7); Vrt(25,-14, 7); Vrt(10,-14, 7);  // kanan B
       Vrt(10,  -11, -7); Vrt( 25,  -11, -7); Vrt(25,-14, -7); Vrt(10,-14, -7);  // kiri A
       Vrt(10,  -11,-10); Vrt( 25,  -11,-10); Vrt(25,-14,-10); Vrt(10,-14,-10);  // kanan B

       Vrt(10, -11, 10); Vrt(10, -11, 7); Vrt( 25, -11, 7); Vrt( 25, -11, 10);  // roof A
       Vrt(10, -11, -7); Vrt(10, -11,-10); Vrt( 25, -11, -10); Vrt( 25, -11, -7);  // roof B

       Vrt(10, -14, 10); Vrt(10, -14, 7); Vrt( 25, -14, 7); Vrt( 25, -11, 7);  // bottom A
       Vrt(10, -14, -7); Vrt(10, -14,-10); Vrt( 25, -14,-10); Vrt( 25, -11, -7);  // bottom B
    glEnd ();

       // penyambung ada satu
//       glColor3f (0.30,0.25,0.30);
//       glEnable (GL_LIGHTING);
//       glBegin (GL_QUADS);
//
//       glColor3f (0.30,0.25,0.30);
//       Vrt(10,  -11, 1); Vrt( 25,  -11, 1); Vrt(25,-14, 1); Vrt(10,-14, 1);  // kiri A
//       Vrt(10,  -11, -1); Vrt( 25,  -11, -1); Vrt(25,-14, -1); Vrt(10,-14, -1);  // kiri A
//       Vrt(10, -11, 1); Vrt(10, -11, -1); Vrt( 25, -11, -1); Vrt( 25, -11, 1);  // roof A
//       Vrt(10, -14, 1); Vrt(10, -14, -1); Vrt( 25, -14, -1); Vrt( 25, -11, -1);  // bottom A
//    glEnd ();



    // Render wheels using torus's with lighting on.

     glEnable     (GL_LIGHTING);
     glColor3f    (0.3, 0.3, 0.3);
     Render_Wheel (-35,-15, 17);
     Render_Wheel (-35,-15,-17);
     Render_WheelB ( -2.5,-13, 17);
     Render_WheelB ( 2.5,-13,-17);

     //roda gerbong
     Render_Wheel (35,-15, 17);
     Render_Wheel (35,-15,-17);
     Render_Wheel (65,-15, 17);
     Render_Wheel (65,-15,-17);

}

//------------------------------------------   Poster's Display   ----------------------------------

void Display (void)
{
    static float x = 2.0;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode   (GL_PROJECTION);
    glLoadIdentity ();

    if (proj == 0)  glOrtho        (-x, x, -x, x, 0.0, 10.0);
    else            gluPerspective ( 60.0,  1.0,  1.0, 10.0);

    glMatrixMode   (GL_MODELVIEW);
    glLoadIdentity ();

    glTranslatef (xtm, ytm, -4.0);       // Place objects between near and far clipping planes.
    glRotatef    (tipp,  1, 0, 0);       // Rotate around screen horizontal axis.
    glRotatef    (turn,  0, 1, 0);       // Rotate around world    vertical axis.
    glLightfv (GL_LIGHT1, GL_POSITION, lit1_pos);
    glLightfv (GL_LIGHT2, GL_POSITION, lit2_pos);
    glScalef     (scl, scl, scl );       // Scale world relative to its origin.
    glScalef     (0.02, 0.02, 0.02);

    Draw_Rail ();
    glTranslatef (-xcr, 0.0, 0.0);
    Draw_Wheel ();
    Draw_Car  ();

    glutSwapBuffers();
}

//-----------------------------------------   Init_GL   --------------------------------------------

void Init_GL (void)
{
    Init_Lights ();

    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING  );
    glEnable (GL_COLOR_MATERIAL);

    glColorMaterial (GL_AMBIENT_AND_DIFFUSE, GL_FRONT);
    glColorMaterial (GL_SPECULAR           , GL_FRONT);

    glClearColor (0.2, 0.3, 0.3, 1.0);
}

//----------------------------------------   Init_Glut   -------------------------------------------

int Init_Glut (void)
{
    glutInitDisplayMode    (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize     (800, 800);
    glutCreateWindow       ("Kereta");

    glutKeyboardFunc (Keybord);
    glutDisplayFunc  (Display);
    glutMouseFunc    (Mouse  );
    glutMotionFunc   (Motion );
}

//------------------------------------------   main   ----------------------------------------------

int main (int argc, char **argv)
{
    glutInit (&argc, argv);

    Init_Glut ();
    Init_GL   ();

    glutMainLoop ();

    return (1);
}
