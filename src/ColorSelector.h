#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <bobcat_ui/all.h>
#include "Color.h"
#include "Enums.h"
#include <FL/Fl_Hor_Slider.H>
#include <bobcat_ui/int_input.h>
#include "Toolbar.h"
#include "Canvas.h"

class ColorSelector : public bobcat::Group {
    bobcat::Button* redButton;
    bobcat::Button* orangeButton;
    bobcat::Button* yellowButton;
    bobcat::Button* greenButton;
    bobcat::Button* blueButton;
    bobcat::Button* violetButton;
    bobcat::Button* whiteButton;
    bobcat::Button* blackButton;
    

    bobcat::IntInput* redInput;
    bobcat::IntInput* blueInput;
    bobcat::IntInput* greenInput;

 

    Fl_Box* previewBox;

    COLOR color;
    ACTION action;
    Toolbar* toolbar;
    Canvas* canvas;
    void deselectAllColors();
    void visualizeSelectedColor();
    void onUpdate(bobcat::Widget* sender);
    void sizeChange(bobcat::Widget* sender);

public:
    ColorSelector(int x, int y, int w, int h);


    Color getColor() const;
};

#endif