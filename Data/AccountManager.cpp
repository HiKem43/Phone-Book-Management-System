#include "AccountManager.h"
#include <iostream>
#include <regex>
#include <cctype>

using namespace std;

AccountManager::AccountManager(DatabaseConnector& database)
    : db(database), loggedIn(false), currentUserId(0) {
}

bool AccountManager::validateUsername(const string& username) {
    if (username.length() < 3 || username.length() > 30) {
        return false;
    }

    for (char c : username) {
        if (!isalnum(static_cast<unsigned char>(c)) && c != '_') {
            return false;
        }
    }

    return true;
}

bool AccountManager::validateEmail(const string& email) {
    regex pattern(
        R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"
    );

    return regex_match(email, pattern);
}

bool AccountManager::validatePassword(const string& password) {
    return password.length() >= 6;
}

bool AccountManager::registerAccount(
    const string& username,
    const string& email,
    const string& password) {

    if (!validateUsername(username)) {
        cerr << "Username khong hop le!" << endl;
        return false;
    }

    if (!validateEmail(email)) {
        cerr << "Email khong hop le!" << endl;
        return false;
    }

    if (!validatePassword(password)) {
        cerr << "Password phai co it nhat 6 ky tu!" << endl;
        return false;
    }

    string checkUsername =
        "SELECT id FROM accounts WHERE username = '" +
        username + "'";

    MYSQL_RES* result = db.executeQuery(checkUsername);

    if (result != nullptr) {
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row != nullptr) {
            db.freeResult(result);
            cerr << "Username da ton tai!" << endl;
            return false;
        }

        db.freeResult(result);
    }

    string checkEmail =
        "SELECT id FROM accounts WHERE email = '" +
        email + "'";

    result = db.executeQuery(checkEmail);

    if (result != nullptr) {
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row != nullptr) {
            db.freeResult(result);
            cerr << "Email da duoc su dung!" << endl;
            return false;
        }

        db.freeResult(result);
    }

    string query =
        "INSERT INTO accounts (username, email, password) "
        "VALUES ('" + username + "', '" +
        email + "', '" + password + "')";

    if (!db.executeNonQuery(query)) {
        cerr << "Dang ky that bai!" << endl;
        return false;
    }

    cout << "Dang ky thanh cong!" << endl;
    return true;
}

bool AccountManager::login(
    const string& username,
    const string& password) {

    if (username.empty() || password.empty()) {
        cerr << "Username va password khong duoc de trong!" << endl;
        return false;
    }

    string query =
        "SELECT id FROM accounts "
        "WHERE username = '" + username +
        "' AND password = '" + password + "'";

    MYSQL_RES* result = db.executeQuery(query);

    if (result == nullptr) {
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row != nullptr) {
        currentUserId = stoi(row[0]);
        loggedIn = true;

        db.freeResult(result);

        cout << "Dang nhap thanh cong!" << endl;
        return true;
    }

    db.freeResult(result);

    cerr << "Username hoac password khong dung!" << endl;
    return false;
}

bool AccountManager::changePassword(
    const string& oldPassword,
    const string& newPassword) {

    if (!loggedIn) {
        cerr << "Ban chua dang nhap!" << endl;
        return false;
    }

    if (!validatePassword(newPassword)) {
        cerr << "Password moi phai co it nhat 6 ky tu!" << endl;
        return false;
    }

    string checkQuery =
        "SELECT id FROM accounts "
        "WHERE id = " + to_string(currentUserId) +
        " AND password = '" + oldPassword + "'";

    MYSQL_RES* result = db.executeQuery(checkQuery);

    if (result == nullptr) {
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == nullptr) {
        db.freeResult(result);
        cerr << "Password cu khong dung!" << endl;
        return false;
    }

    db.freeResult(result);

    string updateQuery =
        "UPDATE accounts SET password = '" +
        newPassword +
        "' WHERE id = " +
        to_string(currentUserId);

    if (!db.executeNonQuery(updateQuery)) {
        cerr << "Doi password that bai!" << endl;
        return false;
    }

    cout << "Doi password thanh cong!" << endl;
    return true;
}

void AccountManager::logout() {

    if (!loggedIn) {
        cout << "Hien tai chua dang nhap." << endl;
        return;
    }

    loggedIn = false;
    currentUserId = 0;

    cout << "Dang xuat thanh cong!" << endl;
}

bool AccountManager::isLoggedIn() const {
    return loggedIn;
}

int AccountManager::getCurrentUserId() const {
    return currentUserId;
}
