#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Shape.h"
#include "Point.h"
#include <vector>

class Scribble: public Shape {
    std::vector<Point*> points;

    float x;
    float y;

    float originX;
    float originY;

    float offsetX;
    float offsetY;

    bool dragging;

public:

    void addPoint(float x, float y, float r, float g, float b, int size);

    void draw();

    bool contains(float mx, float my);

    void setColor(float r, float g, float b);

    void setPosition(float x, float y);

    void plusSize();

    void minusSize();


    Scribble();

    ~Scribble();
};
#endif