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
    //
}

void Scribble::minusSize() {
   //
}

bool Scribble::contains(float mx, float my) {
    for (int i = 0; i < points.size(); i++) {
        if (abs(points[i]->getX() - mx) < 0.05 && abs(points[i]->getY() - my) < 0.05) {
            return true;
        }
    }
    return false;
}

void Scribble::setColor(float r, float g, float b) {
    for (int i = 0; i < points.size(); i++) {
        points[i]->setColor(r, g, b);
    }
}

void Scribble::setPosition(float x, float y) {
    points[0]->setPosition(x, y);

    originX = points[0]->getX();
    originY = points[0]->getY();

    for (int i = 1; i < points.size(); i++) {
        
    }
}
