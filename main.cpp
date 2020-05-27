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

void paint(RenderWindow &win, TM &tm, const sf::Font &font) {
    int width = win.getSize().x;
    int height = win.getSize().y;
    double block_size = (width * 3.0 / 4) / (int) tm.get().size();
    block_size = block_size > height / 3 ? height / 3 : block_size;
    for (int i = 0; i < tm.get().size(); ++i) {
        sf::RectangleShape rect(sf::Vector2f(block_size, block_size));
        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setString(tm.get()[i]);
        text.setCharacterSize(block_size);
        text.setPosition(i * block_size + 10, height / 4.1);
        rect.setPosition(i * block_size + 10, height / 4);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(5);
        win.draw(rect);
        win.draw(text);
    }
    sf::RectangleShape rect(sf::Vector2f(block_size, block_size));
    rect.setPosition(tm.loc() * block_size + 10, height / 4 + block_size + 20);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(5);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("q" + to_string(tm.sta()));
    text.setCharacterSize(block_size / 1.5);
    text.setPosition(tm.loc() * block_size + 10, height / 4.1 + block_size + 20);

    win.draw(rect);
    win.draw(text);
}

#ifndef __TEST__

int main() {

    TM tm;
    vector<string> address;
    string folder("./rules");
    read_directory(folder, address);

    sf::Font font;
    if (!font.loadFromFile("./ttf/Bebas-Regular.ttf")) {
        exit(-1);
    }


    VideoMode model = VideoMode::getDesktopMode();
    model.height /= 1.2;
    model.width /= 1.2;
    RenderWindow win(model, "Turing Machine");

    Gui gui(win);

    auto listBox1 = tgui::ListBox::create();
    listBox1->setSize(win.getSize().y / 4, win.getSize().y * 4 / 5);
    listBox1->setItemHeight(24);
    listBox1->setPosition(win.getSize().x * 3 / 4 + 30 + win.getSize().y / 10, 0);
    listBox1->setTextSize(27);

    gui.add(listBox1);

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
    listBox->setSelectedItemByIndex(0);
    gui.add(listBox);

    auto button = tgui::Button::create();
    button->setSize(win.getSize().y / 10, win.getSize().y / 5);
    button->setPosition(win.getSize().x * 3 / 4 + 20, 0);
    button->setText("OK");
    button->setTextSize(win.getSize().y / 12);
    button->connect("pressed", [&]() {
        string s(listBox->getSelectedItem().toAnsiString());
        tm.init(editBox->getText().toAnsiString(), 'B', folder + "/" + s);
        auto rules = tm.rules;
        listBox1->removeAllItems();
        for (auto &i:rules) {
            string str =
                    "(" + to_string(get<0>(i.first)) + "," + get<1>(i.first) + ")->(" + to_string(get<0>(i.second)) +
                    "," +
                    get<1>(i.second) + "," + to_string(get<2>(i.second)) + ")";
            listBox1->addItem(str);
        }
    });
    gui.add(button);

    auto button1 = tgui::Button::create();
    button1->setSize(win.getSize().y / 10, win.getSize().y / 2.5);
    button1->setPosition(win.getSize().x * 3 / 4 + 20, win.getSize().y / 5 + 20);
    button1->setText("Step");
    button1->setTextSize(win.getSize().y / 12);
    button1->connect("pressed", [&]() {
        int success = tm.read();
        if (success == 0) {
            auto child = tgui::ChildWindow::create();
            child->setSize(300, 120);
            child->setPosition(420, 80);
            child->setTitle("Sorry");
            auto label = tgui::Label::create();
            label->setText("Sorry,it's not allowed");
            label->setPosition(0, 0);
            label->setTextSize(24);
            child->add(label);
            gui.add(child);
        }
        if (success == 2) {
            auto child = tgui::ChildWindow::create();
            child->setSize(300, 120);
            child->setPosition(420, 80);
            child->setTitle("Success");
            auto label = tgui::Label::create();
            label->setText("Success");
            label->setPosition(0, 0);
            label->setTextSize(24);
            child->add(label);
            gui.add(child);
        }
    });
    gui.add(button1);

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
        paint(win, tm, font);
        gui.draw();
        win.display();

    }
}

#endif