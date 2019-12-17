#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include <iostream>
#include "gtest/gtest.h"

//#define __TEST__

using namespace sf;
using namespace tgui;
using namespace std;

void paint() {

}

#ifndef __TEST__

int main() {
    VideoMode model = VideoMode::getDesktopMode();
    model.width /= 2;
    model.height /= 2;
    RenderWindow win(model, "Test");

    Gui gui(win);
    Button::Ptr button = Button::create();
    button->setText("Click me");
    button->setPosition(100,100);
    button->connect("pressed",[&](){ cout << "clicked!"; });
    gui.add(button);

    win.setFramerateLimit(60);
    while (win.isOpen()) {
        Event e{};
        while (win.pollEvent(e)) {
            gui.handleEvent(e);

            if (e.type == Event::Closed) {
                win.close();
            }
        }
        win.clear();
        paint();

        gui.draw();
        win.display();

    }
}

#endif