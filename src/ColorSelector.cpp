#include "ColorSelector.h"
#include "Enums.h"
#include <FL/Enumerations.H>
#include <bobcat_ui/bobcat_ui.h>
#include <cstddef>
#include "Toolbar.h"
#include "Canvas.h"
using namespace bobcat;

void ColorSelector::deselectAllColors() { // deselects before selecting another
    redButton->label("");
    orangeButton->label("");
    yellowButton->label("");
    greenButton->label("");
    blueButton->label("");
    violetButton->label("");
    blackButton->label("");
    whiteButton->label("");
}

void ColorSelector::visualizeSelectedColor() { // highlights
    if (color == RED) {
        redButton->label("@-5square");
        redInput->value(255);
        greenInput->value(0);
        blueInput->value(0);
    }
    else if (color == ORANGE) {
        orangeButton->label("@-5square");
        redInput->value(255);
        greenInput->value(127);
        blueInput->value(0);
    }
    else if (color == YELLOW) {
        yellowButton->label("@-5square");
        redInput->value(255);
        greenInput->value(255);
        blueInput->value(0);
    }
    else if (color == GREEN) {
        greenButton->label("@-5square");
        redInput->value(0);
        greenInput->value(255);
        blueInput->value(0);
    }
    else if (color == BLUE) {
        blueButton->label("@-5square");
        redInput->value(0);
        greenInput->value(0);
        blueInput->value(255);
    }
    else if (color == VIOLET) {
        violetButton->label("@-5square");
        redInput->value(148);
        greenInput->value(0);
        blueInput->value(211);
    }
    else if (color == BLACK) {
        blackButton->label("@-5square");
        redInput->value(0);
        greenInput->value(0);
        blueInput->value(0);
    }
    else if (color == WHITE) {
        whiteButton->label("@-5square");
        redInput->value(255);
        greenInput->value(255);
        blueInput->value(255);
    } else if (color == CUSTOM) {
        deselectAllColors();
    }

    previewBox->color(fl_rgb_color(redInput->value(), greenInput->value(), blueInput->value()));
}

void ColorSelector::onUpdate(bobcat::Widget* sender) {
    deselectAllColors();

    if (redInput->empty()) {
        redInput->value(0);
    }
    if (greenInput->empty()) {
        greenInput->value(0);
    }
    if (blueInput->empty()) {
        blueInput->value(0);
    }

    if (redInput->value() > 255) {
        redInput->value(255);
    }
    if (greenInput->value() > 255) {
        greenInput->value(255);
    }
    if (greenInput->value() > 255) {
        blueInput->value(255);
    }

    Fl::focus(sender);
    if (sender == redButton) {
        color = RED;
    }
    else if (sender == orangeButton) {
        color = ORANGE;
    }
    else if (sender == yellowButton) {
        color = YELLOW;
    }
    else if (sender == greenButton) {
        color = GREEN;
    }
    else if (sender == blueButton) {
        color = BLUE;
    }
    else if (sender == violetButton) {
        color = VIOLET;
    }
    else if (sender == whiteButton) {
        color = WHITE;
    }
    else if (sender == blackButton) {
        color = BLACK;
    } else if ((sender == redInput) || (sender == greenInput) || (sender == blueInput)) {
        color = CUSTOM;
    }

    if (onChangeCb) {
        onChangeCb(this);
    }

    visualizeSelectedColor();
    redraw();
}

Color ColorSelector::getColor() const {
    if (color == RED) {
        return Color(255/255.0, 0/255.0, 0/255.0);
    }
    else if (color == ORANGE) {
        return Color(255/255.0, 127/255.0, 0/255.0);
    }
    else if (color == YELLOW) {
        return Color(255/255.0, 255/255.0, 0/255.0);
    }
    else if (color == GREEN) {
        return Color(0/255.0, 255/255.0, 0/255.0);
    }
    else if (color == BLUE) {
        return Color(0/255.0, 0/255.0, 255/255.0);
    }
    else if (color == VIOLET) {
        return Color(148/255.0, 0/255.0, 211/255.0);
    }
    else if (color == WHITE) {
        return Color(255/255.0, 255/255.0, 255/255.0);
    }
    else if (color == BLACK) {
        return Color(0/255.0, 0/255.0, 0/255.0);
    }
    else if (color == CUSTOM) {
        return Color ((redInput->value() / 255.0), (greenInput->value() / 255.0), (blueInput->value() / 255.0));
    }
    else {
        return Color();
    }
}



ColorSelector::ColorSelector(int x, int y, int w, int h) : Group(x, y, w, h) {
    redButton = new Button(x, y, 20, 20, "");
    redButton->color(FL_RED);
    orangeButton = new Button(x, y + 20, 20, 20, "");
    orangeButton->color(fl_rgb_color(255, 127, 0));
    yellowButton = new Button(x + 20, y, 20, 20, "");
    yellowButton->color(FL_YELLOW);
    greenButton = new Button(x + 20, y + 20, 20, 20, "");
    greenButton->color(FL_GREEN);
    blueButton = new Button(x + 40, y, 20, 20, "");
    blueButton->color(FL_BLUE);
    violetButton = new Button(x + 40, y + 20, 20, 20, "");
    violetButton->color(fl_rgb_color(148, 0, 211));
    whiteButton = new Button(x + 60, y, 20, 20, "");
    whiteButton->color(FL_WHITE);
    blackButton = new Button(x + 60, y + 20, 20, 20, "");
    blackButton->color(FL_BLACK);

    redInput = new IntInput(x + 80, y, 40, 40);
    redInput->textsize(18);
    redInput->color(fl_rgb_color(232, 130, 130));
    greenInput = new IntInput(x + 120, y, 40, 40);
    greenInput->textsize(18);
    greenInput->color(fl_rgb_color(130, 232, 130));
    blueInput = new IntInput(x + 160, y, 40, 40);
    blueInput->textsize(18);
    blueInput->color(fl_rgb_color(130, 130, 232));

    previewBox = new Fl_Box(x + 200, y, 40, 40, "Color");
    previewBox->box(FL_BORDER_BOX);
    previewBox->labelsize(10);



    color = RED;

    visualizeSelectedColor();

    ON_CLICK(redButton, ColorSelector::onUpdate);
    ON_CLICK(orangeButton, ColorSelector::onUpdate);
    ON_CLICK(yellowButton, ColorSelector::onUpdate);
    ON_CLICK(greenButton, ColorSelector::onUpdate);
    ON_CLICK(blueButton, ColorSelector::onUpdate);
    ON_CLICK(violetButton, ColorSelector::onUpdate);
    ON_CLICK(blackButton, ColorSelector::onUpdate);
    ON_CLICK(whiteButton, ColorSelector::onUpdate);

    ON_CHANGE(redInput, ColorSelector::onUpdate);
    ON_CHANGE(greenInput, ColorSelector::onUpdate);
    ON_CHANGE(blueInput, ColorSelector::onUpdate);

}