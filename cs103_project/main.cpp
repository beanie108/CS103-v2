#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <vector>


enum class UserType { TEACHER, STUDENT };

struct LunchOrder {
    std::string username;
    std::string meal;
    float price;
    std::string paymentMethod;  
};

struct MenuItem {
    std::string name;
    float price;
};

class User {
public:
    std::string username;
    std::string password;
    UserType userType;

    User() : userType(UserType::STUDENT) {}

    User(std::string uname, std::string pword, UserType type)
        : username(uname), password(pword), userType(type) {}
};


class Administrator {
private:
    std::map<std::string, User> users;
    const std::string adminUsername = "admin";
    const std::string adminPassword = "admin789";
    std::vector<LunchOrder> lunchOrders;
    std::map<std::string, MenuItem> lunchMenu;

public:
    Administrator() {
        // Add predefined user Bob
        addUser("Bob", "Bob2024", UserType::STUDENT, false);
        // Initialize with default menu items
        lunchMenu["OP1"] = { "Chicken Pasta", 10.0 };
        lunchMenu["OP2"] = { "Spaghetti Bolognaise", 12.0 };
        lunchMenu["OP3"] = { "Falafel Salad", 8.0 };
    }


    bool login(std::string username, std::string password) {
        return username == adminUsername && password == adminPassword;
    }

    void addUser(std::string username, std::string password, UserType userType, bool showSuccessMessage = true) {
        if (users.find(username) == users.end()) {
            users[username] = User(username, password, userType);
            if (showSuccessMessage) {
                std::cout << "User " << username << " added successfully.\n";
            }
        }
        else {
            std::cout << "User already exists.\n";
        }
    }

    bool isUserValid(std::string username, std::string password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.password == password) {
            return true;
        }
        return false;
    }

    void editUserPassword(std::string username, std::string newPassword) {
        auto it = users.find(username);
        if (it != users.end()) {
            it->second.password = newPassword;
            std::cout << "Password for " << username << " updated successfully.\n";
        }
        else {
            std::cout << "User not found.\n";
        }
    }

    void deleteUser(std::string username) {
        if (users.erase(username) > 0) {
            std::cout << "User " << username << " deleted successfully.\n";
        }
        else {
            std::cout << "User not found.\n";
        }
    }

    void showAllUsers() {
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

    void addLunchOrder(const std::string& username, const std::string& meal, float price) {
        auto userIt = users.find(username);
        if (userIt != users.end()) {
            float discount = getDiscountPercentage(userIt->second.userType);
            float discountedPrice = price * (1 - discount);
            std::string paymentMethod = (paymentMethod == "1" ? "Cash" : "Eftpos");
            lunchOrders.push_back(LunchOrder{ username, meal, discountedPrice, paymentMethod });
        }
        else {
            std::cout << "User not found, order not added.\n";
        }
    }

    void addOrUpdateMenuItem(const std::string& key, const std::string& name, float price) {
        auto it = lunchMenu.find(key);
        if (it != lunchMenu.end()) {
            it->second = { name, price };
            std::cout << "Menu item '" << key << "' updated to " << name << " with price $" << price << std::endl;
        }
        else {
            std::cout << "Invalid menu item key. Please use OP1, OP2, or OP3.\n";
        }
    }

    void showLunchMenu() {
        for (const auto& item : lunchMenu) {
            std::cout << item.first << " - " << item.second.name << " ($" << item.second.price << ")\n";
        }
    }

    void generateLunchReport() {
        float total = 0.0;
        std::cout << "Lunch Orders Report:\n";
        for (const auto& order : lunchOrders) {
            std::cout << "User: " << order.username << ", Meal: " << order.meal
                << ", Price: $" << order.price << ", Payment Method: " << order.paymentMethod << std::endl;
            total += order.price;
        }
        std::cout << "Total Revenue: $" << total << std::endl;
    }

    float getDiscountPercentage(UserType userType) {
        switch (userType) {
        case UserType::TEACHER:
            return 0.25; // 25% discount for teachers
        case UserType::STUDENT:
            return 0.0; // 0% discount for students
        default:
            return 0.0;
        }
    }

    void purchaseMeal(std::string username, float mealPrice) {
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
};

void showMenu() {
    std::cout << "Select an option:" << std::endl;
    std::cout << "1 - Administrator Login" << std::endl;
    std::cout << "2 - School User Login" << std::endl;
    std::cout << "3 - Exit" << std::endl;
}

void showAdminMenu() {
    std::cout << "\nAdministrator Menu:\n";
    std::cout << "A - Add, Edit or Delete School User\n";
    std::cout << "B - School Lunches\n";
    std::cout << "C - Return to Previous Menu\n";
    std::cout << "Please enter your choice: ";
}

void showAdminUserMenu() {
    std::cout << "\nUser Management Menu:\n";
    std::cout << "A1 - Add a School User\n";
    std::cout << "A2 - Edit School User Password\n";
    std::cout << "A3 - Delete School User\n";
    std::cout << "A4 - Show List of All School Users\n";
    std::cout << "A5 - Return to Main Menu\n";
    std::cout << "Please enter your choice: ";
}

void showSchoolLunchesMenu() {
    std::cout << "\nSchool Lunches Menu:\n";
    std::cout << "B1 - Menu\n";
    std::cout << "B2 - Run Daily Report\n";
    std::cout << "B3 - Edit Lunch Menu\n"; 
    std::cout << "B4 - Return to Main Menu\n";
    std::cout << "Please enter your choice: ";
}

void showLunchMenuOptions() {
    std::cout << "\nLunch Menu Options:\n";
    std::cout << "OP1 - Chicken Pasta\n";
    std::cout << "OP2 - Spaghetti Bolognaise\n";
    std::cout << "OP3 - Falafel Salad\n";
    std::cout << "OP4 - Return to Main Menu\n";
    std::cout << "Please enter your choice: ";
}

void showSchoolUserMenu(Administrator& admin) {
    std::string username, password;
    std::cout << "Enter school user username: ";
    std::getline(std::cin, username);
    std::cout << "Enter school user password: ";
    std::getline(std::cin, password);

    if (admin.isUserValid(username, password)) {
        std::cout << "School user logged in successfully.\n";
        std::string choice;
        while (true) {
            std::cout << "\nSchool User Menu:\n";
            std::cout << "S1 - Place lunch order\n";
            std::cout << "S2 - Return to main menu\n";
            std::cout << "Please enter your choice: ";
            std::getline(std::cin, choice);

            if (choice == "S1") {
                std::cout << "Select your meal:\n";
                std::cout << "1 - Chicken Pasta ($10)\n";
                std::cout << "2 - Spaghetti Bolognaise ($12)\n";
                std::cout << "3 - Falafel Salad ($8)\n";
                std::string mealChoice;
                std::getline(std::cin, mealChoice);
                float price = 0.0;
                std::string meal;
                if (mealChoice == "1") {
                    meal = "Chicken Pasta";
                    price = 10.0;
                }
                else if (mealChoice == "2") {
                    meal = "Spaghetti Bolognaise";
                    price = 12.0;
                }
                else if (mealChoice == "3") {
                    meal = "Falafel Salad";
                    price = 8.0;
                }
                else {
                    std::cout << "Invalid choice.\n";
                    return;
                }
                std::cout << "Select payment method:\n";
                std::cout << "1 - Cash\n";
                std::cout << "2 - Eftpos\n";
                std::string paymentChoice;
                std::getline(std::cin, paymentChoice);

                if (paymentChoice == "1" || paymentChoice == "2") {
                    admin.addLunchOrder(username, meal, price);  // Add the order
                    std::cout << "Order placed successfully with " << (paymentChoice == "1" ? "Cash" : "Eftpos") << " payment.\n";
                }
                else {
                    std::cout << "Invalid payment method selected.\n";
                    return; // Or handle this scenario as you see fit
                }

            }

            else if (choice == "S2") {
                break; // Returning to the main  menu
            }
            else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    else {
        std::cout << "Invalid school user username or password.\n";
    }
}

int main() {
    Administrator admin;
    std::string choice;
    std::string username, password;

    while (true) {
        showMenu();
        std::getline(std::cin, choice);

        if (choice == "1") { // Administrator Login
            std::cout << "Enter admin username: ";
            std::getline(std::cin, username);
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);

            if (admin.login(username, password)) {
                std::cout << "Admin logged in successfully.\n";
                std::string adminChoice;
                while (true) {
                    showAdminMenu();
                    std::getline(std::cin, adminChoice);

                    if (adminChoice == "A" || adminChoice == "a") {
                        std::string userManagementChoice;
                        while (true) {
                            showAdminUserMenu();
                            std::getline(std::cin, userManagementChoice);

                            if (userManagementChoice == "A1") {
                                // Logic for adding a school user
                                std::string username, password;
                                UserType userType;
                                std::cout << "Enter username: ";
                                std::getline(std::cin, username);
                                std::cout << "Enter password: ";
                                std::getline(std::cin, password);
                                int userTypeInput;
                                std::cout << "Enter user type (0 for TEACHER, 1 for STUDENT): ";
                                std::cin >> userTypeInput;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // To clear the input buffer
                                userType = static_cast<UserType>(userTypeInput);

                                admin.addUser(username, password, userType);
                            }
                            else if (userManagementChoice == "A2") {
                                // Logic for editing school user password
                                std::string username, newPassword;
                                std::cout << "Enter username: ";
                                std::getline(std::cin, username);
                                std::cout << "Enter new password: ";
                                std::getline(std::cin, newPassword);

                                admin.editUserPassword(username, newPassword);
                            }
                            else if (userManagementChoice == "A3") {
                                // Logic for deleting a school user
                                std::string username;
                                std::cout << "Enter username to delete: ";
                                std::getline(std::cin, username);

                                admin.deleteUser(username);
                                }
                            else if (userManagementChoice == "A4") {
                                // Logic for displaying all student users
                                admin.showAllUsers();
                            }
                            else if (userManagementChoice == "A5") {
                                std::cout << "Returning to Administrator Menu.\n";
                                break; // Exiting the User Management Menu
                            }
                            else {
                                std::cout << "Invalid choice. Please try again.\n";
                            }
                        }
                    }
                    else if (adminChoice == "B" || adminChoice == "b") {
                        std::string schoolLunchChoice;
                        while (true) {
                            showSchoolLunchesMenu();
                            std::getline(std::cin, schoolLunchChoice);

                            if (schoolLunchChoice == "B1" || schoolLunchChoice == "b1") {
                                admin.showLunchMenu();
                            }
                            else if (schoolLunchChoice == "B2" || schoolLunchChoice == "b2") {
                                // Logic for "B2 - Run Daily Report"
                                admin.generateLunchReport();
                            }
                            else if (schoolLunchChoice == "B3" || schoolLunchChoice == "b3") {
                                // Logic for "B3 - Edit Lunch Menu"
                                std::string key, name;
                                float price;
                                std::cout << "Enter menu item key (OP1, OP2, OP3): ";
                                std::getline(std::cin, key);
                                std::cout << "Enter menu item name: ";
                                std::getline(std::cin, name);
                                std::cout << "Enter price: ";
                                std::cin >> price;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                admin.addOrUpdateMenuItem(key, name, price);
                            }
                            else if (schoolLunchChoice == "B4" || schoolLunchChoice == "b4") {
                                std::cout << "Returning to Administrator Menu.\n";
                                break; // Exiting the School Lunches Menu
                            }
                            else {
                                std::cout << "Invalid choice. Please try again.\n";
                            }
                        }
                    }
                    else if (adminChoice == "C" || adminChoice == "c") {
                        std::cout << "Returning to main menu.\n";
                        break; // Exiting admin menu
                    }
                    else {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
            }
            else {
                std::cout << "Admin login failed.\n";
            }
        }
        else if (choice == "2") { // School User Login
            showSchoolUserMenu(admin);
        }
        else if (choice == "3") { // Exit
            std::cout << "Exiting the system.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
