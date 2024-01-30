#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

struct MenuItem {
    std::string name;
    float price;

    MenuItem() : price(0.0f) {}
    MenuItem(std::string n, float p) : name(n), price(p) {}
};

#endif // MENU_ITEM_H
#pragma once
