#include "Administrator.h"
#include <iostream>

Administrator ::Administrator() {
    // Initialize with default menu items
    lunchMenu["OP1"] = MenuItem("Chicken Pasta", 10.0);
    lunchMenu["OP2"] = MenuItem("Spaghetti Bolognaise", 12.0);
    lunchMenu["OP3"] = MenuItem("Falafel Salad", 8.0);
}

bool Administrator::login(const std::string& username, const std::string& password) {
    return username == adminUsername && password == adminPassword;
}

void Administrator::addUser(const std::string& username, const std::string& password, UserType userType, bool showSuccessMessage) {
    if (users.find(username) == users.end()) {
        users[username] = User(username, password, userType);
        if (showSuccessMessage) {
            std::cout << "User" << username << "added successfully.\n";
        }
        else {
            std::cout << "User already exists.\n";
        }
    }
}
 

bool Administrator ::isUserValid(const std::string& username, const std::string& password){//; {
        auto it = users.find(username);
        if (it != users.end() && it->second.password == password) {
            return true;
        }
        return false;
    }

void Administrator ::editUserPassword(const std::string& username, const std::string& newPassword) {
        auto it = this->users.find(username);
        if (it != this->users.end()) {
            it->second.password = newPassword;
            std::cout << "Password for " << username << " updated successfully.\n";
        }
        else {
            std::cout << "User not found.\n";
        }
    }

void Administrator ::deleteUser(const std::string& username) {
        if (users.erase(username) > 0) {
            std::cout << "User " << username << " deleted successfully.\n";
        }
        else {
            std::cout << "User not found.\n";
        }
    }

void Administrator ::showAllUsers() {
        if (users.empty()) {
            std::cout << "No users are currently registered.\n";
        }
        else {
            std::cout << "List of all registered users:\n";
            for (const auto& userPair : users) {
                std::cout << userPair.first << " (Type: " << static_cast<int>(userPair.second.userType) << ")" << std::endl;
            }
        }
    }

void Administrator:: addLunchOrder(const std::string& username, const std::string& meal, float price) {
        auto userIt = this->users.find(username);
        if (userIt != this->users.end()) {
            float discount = getDiscountPercentage(userIt->second.userType);
            float discountedPrice = price * (1 - discount);
            std::string paymentMethod = (paymentMethod == "1" ? "Cash" : "Eftpos");
            lunchOrders.push_back(LunchOrder{ username, meal, discountedPrice, paymentMethod });
        }
        else {
            std::cout << "User not found, order not added.\n";
        }
    }

void Administrator:: addOrUpdateMenuItem(const std::string& key, const std::string& name, float price) {
        auto it = this->lunchMenu.find(key);
        if (it != this->lunchMenu.end()) {
            it->second = { name, price };
            std::cout << "Menu item '" << key << "' updated to " << name << " with price $" << price << std::endl;
        }
        else {
            std::cout << "Invalid menu item key. Please use OP1, OP2, or OP3.\n";
        }
    }

void Administrator:: showLunchMenu() {
        for (const auto& item : lunchMenu) {
            std::cout << item.first << " - " << item.second.name << " ($" << item.second.price << ")\n";
        }
    }

void Administrator:: generateLunchReport() {
        float total = 0.0;
        std::cout << "Lunch Orders Report:\n";
        for (const auto& order : lunchOrders) {
            std::cout << "User: " << order.username << ", Meal: " << order.meal
                << ", Price: $" << order.price << ", Payment Method: " << order.paymentMethod << std::endl;
            total += order.price;
        }
        std::cout << "Total Revenue: $" << total << std::endl;
    }

float Administrator:: getDiscountPercentage(UserType userType) {
        switch (userType) {
        case UserType::TEACHER:
            return 0.25; // 25% discount for teachers
        case UserType::STUDENT:
            return 0.0; // 0% discount for students
        default:
            return 0.0;
        }
    }

void Administrator:: purchaseMeal(const std::string& username, float mealPrice) {
    auto it = users.find(username);
        if (it != users.end()) {
            float discount = getDiscountPercentage(it->second.userType);
            float discountedPrice = mealPrice * (1 - discount);
            std::cout << "Original price: $" << mealPrice << ", Discounted price: $" << discountedPrice << std::endl;
        }
        else {
            std::cout << "User not found.\n";
        }
    }