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

    public:
        Administrator() {
            // Add predefined user Bob
            addUser("Bob", "Bob2024", UserType::STUDENT);
        }

    bool login(std::string username, std::string password) {
        return username == adminUsername && password == adminPassword;
    }

    void addUser(std::string username, std::string password, UserType userType) {
        if (users.find(username) == users.end()) {
            users[username] = User(username, password, userType);
            std::cout << "User " << username << " added successfully.\n";
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
        lunchOrders.push_back(LunchOrder{ username, meal, price });
    }

    void generateLunchReport() {
        float total = 0.0;
        std::cout << "Lunch Orders Report:\n";
        for (const auto& order : lunchOrders) {
            std::cout << "User: " << order.username << ", Meal: " << order.meal << ", Price: $" << order.price << std::endl;
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
    std::cout << "B3 - Return to Main Menu\n";
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
                admin.addLunchOrder(username, meal, price);
                std::cout << "Order placed successfully.\n";
            }

            else if (choice == "S2") {
                break; // Returning to the main menu
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
                        // ... [User management logic]
                    }
                    else if (adminChoice == "B" || adminChoice == "b") {
                        std::string schoolLunchChoice;
                        while (true) {
                            showSchoolLunchesMenu();
                            std::getline(std::cin, schoolLunchChoice);

                            if (schoolLunchChoice == "B1" || schoolLunchChoice == "b1") {
                                char lunchMenuChoice;
                                while (true) {
                                    showLunchMenuOptions();
                                    std::cin >> lunchMenuChoice;  // Here we can keep using cin as we expect single characters

                                    switch (lunchMenuChoice) {
                                    case '1':
                                        std::cout << "Chicken Pasta selected.\n";
                                        break;
                                    case '2':
                                        std::cout << "Spaghetti Bolognaise selected.\n";
                                        break;
                                    case '3':
                                        std::cout << "Falafel Salad selected.\n";
                                        break;
                                    case '4':
                                        std::cout << "Returning to School Lunches Menu.\n";
                                        break; // Exiting the Lunch Menu Options
                                    default:
                                        std::cout << "Invalid choice. Please try again.\n";
                                    }

                                    if (lunchMenuChoice == '4') {
                                        break; // Exit the Lunch Menu Options
                                    }
                                }
                            }
                            else if (schoolLunchChoice == "B2" || schoolLunchChoice == "b2") {
                                // Logic for "B2 - Run Daily Report"
                            }
                            else if (schoolLunchChoice == "B3" || schoolLunchChoice == "b3") {
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
            return 0;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
