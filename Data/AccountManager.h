#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include "DatabaseConnector.h"
#include <string>

class AccountManager {
private:
    DatabaseConnector& db;
    bool loggedIn;
    int currentUserId;

    // Kiểm tra dữ liệu tài khoản
    bool validateUsername(const std::string& username);
    bool validateEmail(const std::string& email);
    bool validatePassword(const std::string& password);

public:
    // Constructor
    AccountManager(DatabaseConnector& database);

    // Đăng ký tài khoản
    bool registerAccount(
        const std::string& username,
        const std::string& email,
        const std::string& password
    );

    // Đăng nhập
    bool login(
        const std::string& username,
        const std::string& password
    );

    // Đổi mật khẩu
    bool changePassword(
        const std::string& oldPassword,
        const std::string& newPassword
    );

    // Đăng xuất
    void logout();

    // Kiểm tra trạng thái đăng nhập
    bool isLoggedIn() const;

    // Lấy ID tài khoản hiện tại
    int getCurrentUserId() const;
};

#endif // ACCOUNT_MANAGER_H
