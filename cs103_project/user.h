#ifndef USER_H
#define USER_H

#include <string>
#include "UserType.h"

class User {
public:
    std::string username;
    std::string password;
    UserType userType;

    User();
    User(std::string uname, std::string pword, UserType type);
};

#endif // USER_H
