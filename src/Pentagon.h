#ifndef PENTAGON_H
#define PENTAGON_H

#include "Shape.h"

class Pentagon : public Shape {
    float x;
    float y;
    float size;
    float r;
    float g;
    float b;

public:
    Pentagon();
    Pentagon(float x, float y, float r, float g, float b);
    void draw();
    bool contains(float mx, float my);
    void setColor(float r, float g, float b);
    void setPosition(float x, float y);
    void plusSize();
    void minusSize();
};

#endif