//
// Created by cezvedici on 16.04.2017.
//

#ifndef OPENGL_PLANETS_H
#define OPENGL_PLANETS_H


class Planet {
private:
    float size = 0.75;
    float r = 1, g = 1, b = 1;
    float position [3] = {0, 0, 0};
    float timeToFinish = 0; // default is 0
    float distanceFromSun = 0;
public:
    void setSize(float);
    void setPosition (float, float, float);
    void setColor(float, float, float);
    void draw(float day);
    void setTimeToFinish(int);
    void setDistanceFromSun(float);
};


#endif //OPENGL_PLANETS_H
