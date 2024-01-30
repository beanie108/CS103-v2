#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <map>
#include <string>
#include <vector>
#include "User.h"
#include "LunchOrder.h"
#include "Administrator.h"
#include "MenuItem.h"

class Administrator {
private:
    std::map<std::string, User> users;
    const std::string adminUsername = "admin";
    const std::string adminPassword = "admin789";
    std::vector<LunchOrder> lunchOrders;
    std::map<std::string, MenuItem> lunchMenu;
   
public:
    Administrator();
    bool login(const std::string& username, const std::string& password); 
    void addUser(const std::string& username, const std::string& password, UserType userType, bool showSuccessMessage = true); 
    bool isUserValid(const std::string& username, const std::string& password); 
    void editUserPassword(const std::string& username, const std::string& newPassword); 
    void deleteUser(const std::string& username); 
    void showAllUsers(); 
    void addLunchOrder(const std::string& username, const std::string& meal, float price); 
    void addOrUpdateMenuItem(const std::string& key, const std::string& name, float price); 
    void showLunchMenu();
    void generateLunchReport();
    float getDiscountPercentage(UserType userType);
    void purchaseMeal(const std::string& username, float mealPrice); 

};

#endif // ADMINISTRATOR_H
