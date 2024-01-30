#include "User.h"

User::User() : userType(UserType::STUDENT) {}

User::User(std::string uname, std::string pword, UserType type)
    : username(uname), password(pword), userType(type) {}
