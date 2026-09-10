#include "Utils.h"
#include <iostream>
#include <regex>
#include <limits>

bool validateEmail(const std::string& email) {
    if (email.empty()) return true;
    const std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, pattern);
}

bool validatePhone(const std::string& phone) {
    if (phone.empty()) return false;
    const std::regex pattern("^[0-9]{9,15}$");
    return std::regex_match(phone, pattern);
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}