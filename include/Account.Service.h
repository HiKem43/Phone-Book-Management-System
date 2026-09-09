#ifndef ACCOUNT_SERVICE_H
#define ACCOUNT_SERVICE_H

#include <string>
#include "DatabaseConnector.h"

using namespace std;

class AccountService {
private:
    DatabaseConnector& db;

    bool loggedIn;
    int currentUserId;

    bool validateUsername(const string& username);
    bool validateEmail(const string& email);
    bool validatePassword(const string& password);

public:
    AccountService(DatabaseConnector& database);

    // Đăng ký tài khoản
    bool registerAccount(
        const string& username,
        const string& email,
        const string& password
    );

    // Đăng nhập
    bool login(
        const string& username,
        const string& password
    );

    // Đổi mật khẩu
    bool changePassword(
        const string& oldPassword,
        const string& newPassword
    );

    // Đăng xuất
    void logout();

    // Kiểm tra trạng thái đăng nhập
    bool isLoggedIn() const;

    // Lấy ID tài khoản đang đăng nhập
    int getCurrentUserId() const;
};

#endif
