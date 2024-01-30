#ifndef LUNCH_ORDER_H
#define LUNCH_ORDER_H

#include <string>

struct LunchOrder {
    std::string username;
    std::string meal;
    float price;
    std::string paymentMethod;
};

#endif // LUNCH_ORDER_H
