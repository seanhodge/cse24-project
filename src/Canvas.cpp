#include "Canvas.h"
#include "Circle.h"
#include "Scribble.h"
#include "Shape.h"
#include "Triangle.h"
#include "Pentagon.h"
#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>
#include <iostream>

Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    curr = nullptr;
}

void Canvas::addPoint(float x, float y, float r, float g, float b, int size) {
    shapes.push_back(new Point(x, y, r, g, b, size));
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Rectangle(x, y, r, g, b));
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Circle(x, y, r, g, b));
}

void Canvas::addPentagon(float x, float y, float r, float g, float b) {
    shapes.push_back(new Pentagon(x, y, r, g, b));
}

void Canvas::addTriangle(float x, float y, float r, float g, float b) {
    shapes.push_back(new Triangle(x, y, r, g, b));
}

void Canvas::clear() {
    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        delete shapes[i];
    }
    shapes.clear();
}

void Canvas::undo(){
    if (shapes.size() > 0){
        delete shapes[shapes.size() - 1];
        shapes.pop_back();
    }
}

void Canvas::render() {
    for (unsigned int i = 0 ; i < shapes.size(); i++) {
        shapes[i]->draw();
    }

    if (curr){
        curr->draw();
    }
}

void Canvas::erase(float mx, float my) {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        // ask every shape if we clicked on it
        if (shapes[i]->contains(mx, my)) {
            std::cout << "Erasing  shape[" << i << "]" << std::endl;
            shapes.erase(shapes.begin() + i);
            break;
        }
    }
}

Shape* Canvas::getSelectedShape(float mx, float my) {
    Shape* selectedShape = nullptr;
    selectedPosition = 0;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        // ask every shape if we clicked on it
        if (shapes[i]->contains(mx, my)) {
            std::cout << "Clicked on shape[" << i << "]" << std::endl;
            selectedShape = shapes[i];
            selectedPosition = i;
            break;
        }
    }

    if (selectedShape == nullptr) {
        std::cout << "No selected shape" << std::endl;
    }

    return selectedShape;

}

void Canvas::sendToBack(Shape* givenShape) {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        if (givenShape == shapes[i]) {
            shapes.erase(shapes.begin() + i);
            shapes.insert(shapes.begin(), givenShape);
        }
    }
}

void Canvas::bringToFront(Shape* givenShape) {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        if (givenShape == shapes[i]) {
            shapes.erase(shapes.begin() + i);
            shapes.push_back(givenShape);
        }
    }
}

void Canvas::sizeUp(Shape* givenShape) {
    for (int i = 0; i < shapes.size(); i++) {
        if (givenShape == shapes[i]) {
            shapes[i]->plusSize();
        }
    }
}

void Canvas::sizeDown(Shape* givenShape) {
    for (unsigned int i = 0; i < shapes.size(); i++) {
        if (givenShape == shapes[i]) {
            shapes[i]->minusSize();
        }
    }
}

void Canvas::startScribble(){
    curr = new Scribble();
}

void Canvas::updateScribble(float x, float y, float r, float g, float b, int size){
    if (curr){
        curr->addPoint(x, y, r, g, b, size);
    }
}

void Canvas::endScribble(){
    if (curr){
        shapes.push_back(curr);
        curr = nullptr;
    }
}