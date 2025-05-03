#include "Pentagon.h"
#include <GL/freeglut.h>

Pentagon::Pentagon() {
    x = 0.0;
    y = 0.0;
    size = 0.4;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

Pentagon::Pentagon(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    size = 0.5;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Pentagon::plusSize() {
    size += 0.1;
}

void Pentagon::minusSize() {
    size -= 0.1;
    if (size <= 0.1) {
        size = 0.1;
    }
}

void Pentagon::draw() {
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
        glVertex2f(x, y + size/2);
        glVertex2f(x - size/2.5, y + size/4);
        glVertex2f(x - size/3.5, y - size/3.5);
        glVertex2f(x + size/3.5, y - size/3.5);
        glVertex2f(x + size/2.5, y + size/4);
    glEnd();
}

bool Pentagon::contains(float mx, float my) {
    if (mx >= x - size/2 && mx <= x + size/2 && my <= y + size/2 && my >= y - size/2) {
        return true;
    }
    return false;
}

void Pentagon::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Pentagon::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}