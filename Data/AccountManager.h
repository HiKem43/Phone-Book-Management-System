#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <string>
#include "DatabaseConnector.h"

using namespace std;

class AccountManager {
private:
    DatabaseConnector& db;

    bool loggedIn;
    int currentUserId;

    bool validateUsername(const string& username);
    bool validateEmail(const string& email);
    bool validatePassword(const string& password);

public:
    AccountManager(DatabaseConnector& database);

    bool registerAccount(
        const string& username,
        const string& email,
        const string& password
    );

    bool login(
        const string& username,
        const string& password
    );

    bool changePassword(
        const string& oldPassword,
        const string& newPassword
    );

    void logout();

    bool isLoggedIn() const;

    int getCurrentUserId() const;
};

#endif
