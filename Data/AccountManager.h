#pragma once

#include "DatabaseConnector.h"
#include <string>

class AccountManager {
private:
    DatabaseConnector& db;
    bool loggedIn;
    int currentUserId;

    bool validateUsername(const std::string& username);
    bool validateEmail(const std::string& email);
    bool validatePassword(const std::string& password);

public:
    AccountManager(DatabaseConnector& database);

    bool registerAccount(
        const std::string& username,
        const std::string& email,
        const std::string& password
    );

    bool login(
        const std::string& username,
        const std::string& password
    );

    bool changePassword(
        const std::string& oldPassword,
        const std::string& newPassword
    );

    void logout();

    bool isLoggedIn() const;

    int getCurrentUserId() const;
};
