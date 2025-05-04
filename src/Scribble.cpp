#include "Scribble.h"
#include <iostream>

Scribble::Scribble() {
    x = 0.0;
    y = 0.0;
}

void Scribble::addPoint(float x, float y, float r, float g, float b, int size){
    points.push_back(new Point(x, y, r, g, b, size));
}

void Scribble::draw(){
    for (unsigned int i = 0; i < points.size(); i++){
        points[i]->draw();
    }
}

Scribble::~Scribble(){
    for (unsigned int i = 0; i < points.size(); i++){
        delete points[i];
    }
    points.clear();
}

void Scribble::plusSize() {
    for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->plusSize();
    }
}

void Scribble::minusSize() {
   for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->minusSize();
    }
}

bool Scribble::contains(float mx, float my) {
    for (unsigned int i = 0; i < points.size(); i++) {
        if (abs(points[i]->getX() - mx) < 0.05 && abs(points[i]->getY() - my) < 0.05) {
            return true;
        }
    }
    return false;
}

void Scribble::setColor(float r, float g, float b) {
    for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->setColor(r, g, b);
    }
}

void Scribble::setPosition(float x, float y) {

    // how to position other points to origin point?
    // 
    // if point1 is (3,5) and point2 follows at (5,9)
    // then point1 moves to (5,7) newPos
    // 
    // the offset from point1's originalPos and newPos is:
    // newX - oldX, newY - oldY
    // giving the offset of
    // 2, 2
    // meaning point2 should be at 7, 11
    
    originX = points[0]->getX();
    originY = points[0]->getY();

    points[0]->setPosition(x, y);

    offsetX = points[0]->getX() - originX;
    offsetY = points[0]->getY() - originY;

    std::cout << offsetX << ", " << offsetY << std::endl;

    for (unsigned int i = 1; i < points.size(); i++) {
        points[i]->setPosition(points[i]->getX() + offsetX, points[i]->getY() + offsetY);
    }

}
