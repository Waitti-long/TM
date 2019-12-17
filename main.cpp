#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include <iostream>
#include "gtest/gtest.h"
#include "src/TM.h"
#include "src/Tools.h"


//#define __TEST__

using namespace sf;
using namespace tgui;
using namespace std;

void paint(RenderWindow &win, TM &tm) {
    int width = win.getSize().x;
    int height = win.getSize().y;
    double block_size = (width * 3.0 / 4) / (int) tm.get().size();

}

#ifndef __TEST__

int main() {

    TM tm;
    vector<string> address;
    string folder("./rules");
    read_directory(folder, address);

    VideoMode model = VideoMode::getDesktopMode();
    model.height /= 1.2;
    model.width /= 1.2;
    RenderWindow win(model, "Test");

    Gui gui(win);
//    button->connect("pressed",[&](){ cout << "clicked!"; });

    auto editBox = tgui::EditBox::create();
    editBox->setSize(win.getSize().x / 2, win.getSize().y / 5);
    editBox->setTextSize(18);
    editBox->setPosition(win.getSize().x / 4 + 10, 0);
    editBox->setDefaultText("Input String...");
    editBox->setTextSize(win.getSize().y / 9);
    gui.add(editBox);

    auto listBox = tgui::ListBox::create();
    listBox->setSize(win.getSize().x / 4, win.getSize().y / 5);
    listBox->setItemHeight(24);
    listBox->setPosition(0, 0);
    for (auto &i : address) {
        listBox->addItem(i);
    }
    listBox->setTextSize(win.getSize().y / 30);
    listBox->connect("ItemSelected", [&]() {
        string s(listBox->getSelectedItem().toAnsiString());
        tm.init(editBox->getText().toAnsiString(), 'B', folder + "/" + s);
    });
    gui.add(listBox);

    auto button = tgui::Button::create();
    button->setSize(win.getSize().y / 10, win.getSize().y / 5);
    button->setPosition(win.getSize().x * 3 / 4 + 20, 0);
    button->setText("OK");
    button->setTextSize(win.getSize().y / 12);
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
        win.clear(sf::Color(255, 255, 255));
        paint(win, tm);
        gui.draw();
        win.display();

    }
}

#endif