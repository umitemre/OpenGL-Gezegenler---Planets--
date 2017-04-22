#include <GL/glut.h>
#include <cstdio>
#include <string>
#include "Planet.h"

using namespace std;

Planet planets[4];  // güneş merkür venüs dünya

int WindowWidth = 1200;
int WindowHeight = 600;

float dayOfTheYear = 0;

bool Started = false;

void initGL();
void display();

void printtext(int x, int y, string String)
{
    glColor3f(1, 1, 1);
    //(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WindowWidth, 0, WindowHeight, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);

    for (int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw every star on the surface.
    for(int i = 0; i < 4; i++) {
        planets[i].draw(dayOfTheYear);
    }

    printtext(30, 30, "Gunes, Merkur, Venus, Dunya yildizlarina yukaridan baktiginizi hayal edin..");

    char string[64];
    sprintf(string, "Gun: %03d / 360", (int) dayOfTheYear);
    printtext(30, 70, string);

    printtext(30, 50, "Baslatmak / Durdurmak icin SPACE tusuna basin.");

    glLoadIdentity(); // --> replace current matrix with identity matrix

    glFlush(); // --> force execution of GL commands in finite time
}

void initGL() {
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // -->
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // -->
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // -->

//  These are required for enabling lightning
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);  // --> to colorize materials.
    glClearColor(0, 0, 0, 0);
}

void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
                 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
                 1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void animate(int) {
    if (Started)
        dayOfTheYear += 0.1;

    if (dayOfTheYear > 360)
        dayOfTheYear = 0;

    glutPostRedisplay();
    glutTimerFunc(100, animate, 1);
}

void createPlanets() {
    Planet gunes = Planet();
    gunes.setColor(255, 127, 0);
    gunes.setSize(0.6);

    // 88 gün
    Planet merkur = Planet();
    merkur.setSize(0.1);
    merkur.setColor(165, 42, 42);
    merkur.setTimeToFinish(88);
    merkur.setDistanceFromSun(0.1);   // 1 y

    // 225 gün
    Planet venus = Planet();
    venus.setSize(0.2);
    venus.setColor(220, 20, 60);
    venus.setTimeToFinish(225);
    venus.setDistanceFromSun(0.5);

    // 365 gün
    Planet dunya = Planet();
    dunya.setSize(0.3);
    dunya.setColor(66, 98, 244);
    dunya.setTimeToFinish(360);
    dunya.setDistanceFromSun(1.2);

    planets[0] = gunes;
    planets[1] = merkur;
    planets[2] = venus;
    planets[3] = dunya;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 32:
            Started = !Started;
            break;
        default:
            break;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Gezegenler");
    initGL();

    createPlanets();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100, animate, 1);

    glutMainLoop();
    return 0;
}