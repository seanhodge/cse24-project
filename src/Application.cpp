#include "Application.h"
#include "Enums.h"
#include <bobcat_ui/bobcat_ui.h>

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        canvas->startScribble();
        canvas->updateScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->erase(mx, my);
        canvas->redraw();
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == CIRCLE) { 
        canvas->addCircle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == TRIANGLE) { 
        canvas->addTriangle(mx, my, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == MOUSE) {
        selectedShape = canvas->getSelectedShape(mx, my);
    }

}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my) {
    canvas->endScribble();
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    if (tool == PENCIL) {
        canvas->updateScribble(mx, my, color.getR(), color.getG(), color.getB(), 7);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->erase(mx, my);
        canvas->redraw();
    }
    else if (tool == MOUSE) {
        if (selectedShape) {
            selectedShape->setPosition(mx, my);
            canvas->redraw();       
        }
    }
}


void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();
    TOOL tool = toolbar->getTool();

    if (action == CLEAR) { 
        canvas->clear();
        canvas->redraw();
        selectedShape = nullptr; // deselect crash here
    }
    else if (action == UNDO) {
        canvas->undo();
        canvas->redraw();
        selectedShape = nullptr; // deselect crash here
    }
    else if (action == SEND_TO_BACK) { // if element highlighted
        if (selectedShape) {
            cout << "Send to back" << endl;
            canvas->sendToBack(selectedShape);
            canvas->redraw();
        }
    }
    else if (action == BRING_TO_FRONT) { // if element highlighted
        if (selectedShape) {
            cout << "Bring to front" << endl;
            canvas->bringToFront(selectedShape);
            canvas->redraw();
        }
    }

    if ((tool != MOUSE) && (action != SEND_TO_BACK) && (action != BRING_TO_FRONT)) { // not tools that select
        selectedShape = nullptr; 
    }
}

void Application::onColorSelectorChange(bobcat::Widget* sender) {
    Color color = colorSelector->getColor();

    if (selectedShape) {
        cout << "Update selected shape color" << endl;
        selectedShape->setColor(color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
}

Application::Application() {
    window = new Window(25, 75, 440, 440, "Paint and Suffering");

    selectedShape = nullptr;

    toolbar = new Toolbar(0, 0, 40, 450);
    canvas = new Canvas(40, 0, 420, 400);
    colorSelector = new ColorSelector(40, 400, 400, 50);
    colorSelector->box(FL_BORDER_BOX);

    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);

    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_CHANGE(colorSelector, Application::onColorSelectorChange);
    window->show();
}