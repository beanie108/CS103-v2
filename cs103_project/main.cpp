#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <vector>
#include "Administrator.h"
#include "User.h"
#include "MenuItem.h"
#include "UserType.h"
#include "LunchOrder.h"

void showMenu();
void showAdminMenu();
void showAdminUserMenu();
void showSchoolLunchesMenu();
void showLunchMenuOptions();
void showSchoolUserMenu(Administrator& admin);


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
