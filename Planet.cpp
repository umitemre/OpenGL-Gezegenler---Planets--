//
// Created by cezvedici on 16.04.2017
//

#include <GL/glut.h>
#include "Planet.h"
#include <iostream>;
#include <math.h>

using namespace std;

void Planet::setSize(float size) {
    this->size = size;
}

void Planet::draw(float day) {
    glPushMatrix();
    glColor3f(this->r, this->g, this->b);

    day = (float) (day * M_PI / 180);

    if (this->timeToFinish > 0) {
        this->position[0] = this->distanceFromSun + (float) cos(360 / timeToFinish * day);
        this->position[1] = (float) sin(360 / timeToFinish * day);
    }

    glTranslatef(this->position[0], this->position[1], this->position[2]);
    glutSolidSphere(this->size, 360, 360);
    // glutSolidTeapot(this->size);
    glPopMatrix();
}

void Planet::setColor(float r, float g, float b) {
    this->r = r / 255;
    this->g = g / 255;
    this->b = b / 255;
}

void Planet::setTimeToFinish(int time) {
    this->timeToFinish = time;
}

void Planet::setDistanceFromSun(float distance) {
    this->distanceFromSun = distance;
}
