#include "AccountManager.h"
#include <iostream>
#include <regex>

// Constructor
AccountManager::AccountManager(DatabaseConnector& database)
    : db(database), loggedIn(false), currentUserId(0) {
}

// Kiểm tra username
bool AccountManager::validateUsername(const std::string& username) {
    // Username phải có từ 3 đến 30 ký tự
    if (username.length() < 3 || username.length() > 30) {
        return false;
    }

    // Chỉ cho phép chữ cái, số và dấu _
    for (char c : username) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') {
            return false;
        }
    }

    return true;
}

// Kiểm tra email
bool AccountManager::validateEmail(const std::string& email) {
    // Kiểm tra định dạng email cơ bản
    const std::regex pattern(
        R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"
    );

    return std::regex_match(email, pattern);
}

// Kiểm tra password
bool AccountManager::validatePassword(const std::string& password) {
    // Password phải có ít nhất 6 ký tự
    if (password.length() < 6) {
        return false;
    }

    return true;
}

// =====================================================
// ĐĂNG KÝ
// =====================================================
bool AccountManager::registerAccount(
    const std::string& username,
    const std::string& email,
    const std::string& password) {

    // Kiểm tra username
    if (!validateUsername(username)) {
        std::cerr << "[Account Error] Username không hợp lệ!"
                  << std::endl;
        return false;
    }

    // Kiểm tra email
    if (!validateEmail(email)) {
        std::cerr << "[Account Error] Email không hợp lệ!"
                  << std::endl;
        return false;
    }

    // Kiểm tra password
    if (!validatePassword(password)) {
        std::cerr << "[Account Error] Password phải có ít nhất 6 ký tự!"
                  << std::endl;
        return false;
    }

    // Kiểm tra username đã tồn tại chưa
    std::string checkUsername =
        "SELECT id FROM accounts WHERE username = '" +
        username + "'";

    MYSQL_RES* result = db.executeQuery(checkUsername);

    if (result != nullptr) {
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row != nullptr) {
            db.freeResult(result);

            std::cerr << "[Account Error] Username đã tồn tại!"
                      << std::endl;

            return false;
        }

        db.freeResult(result);
    }

    // Kiểm tra email đã tồn tại chưa
    std::string checkEmail =
        "SELECT id FROM accounts WHERE email = '" +
        email + "'";

    result = db.executeQuery(checkEmail);

    if (result != nullptr) {
        MYSQL_ROW row = mysql_fetch_row(result);

        if (row != nullptr) {
            db.freeResult(result);

            std::cerr << "[Account Error] Email đã được sử dụng!"
                      << std::endl;

            return false;
        }

        db.freeResult(result);
    }

    // Thêm tài khoản vào database
    std::string query =
        "INSERT INTO accounts (username, email, password) "
        "VALUES ('" + username + "', '" +
        email + "', '" + password + "')";

    if (!db.executeNonQuery(query)) {
        std::cerr << "[Account Error] Đăng ký thất bại!"
                  << std::endl;
        return false;
    }

    std::cout << "[Account] Đăng ký thành công!"
              << std::endl;

    return true;
}

// =====================================================
// ĐĂNG NHẬP
// =====================================================
bool AccountManager::login(
    const std::string& username,
    const std::string& password) {

    if (username.empty() || password.empty()) {
        std::cerr << "[Account Error] Username và password không được để trống!"
                  << std::endl;
        return false;
    }

    std::string query =
        "SELECT id FROM accounts "
        "WHERE username = '" + username +
        "' AND password = '" + password + "'";

    MYSQL_RES* result = db.executeQuery(query);

    if (result == nullptr) {
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row != nullptr) {
        currentUserId = std::stoi(row[0]);

        loggedIn = true;

        db.freeResult(result);

        std::cout << "[Account] Đăng nhập thành công!"
                  << std::endl;

        return true;
    }

    db.freeResult(result);

    std::cerr << "[Account Error] Username hoặc password không đúng!"
              << std::endl;

    return false;
}

// =====================================================
// ĐỔI MẬT KHẨU
// =====================================================
bool AccountManager::changePassword(
    const std::string& oldPassword,
    const std::string& newPassword) {

    if (!loggedIn) {
        std::cerr << "[Account Error] Bạn chưa đăng nhập!"
                  << std::endl;
        return false;
    }

    if (!validatePassword(newPassword)) {
        std::cerr << "[Account Error] Password mới phải có ít nhất 6 ký tự!"
                  << std::endl;
        return false;
    }

    // Kiểm tra password cũ
    std::string checkQuery =
        "SELECT id FROM accounts "
        "WHERE id = " + std::to_string(currentUserId) +
        " AND password = '" + oldPassword + "'";

    MYSQL_RES* result = db.executeQuery(checkQuery);

    if (result == nullptr) {
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (row == nullptr) {
        db.freeResult(result);

        std::cerr << "[Account Error] Password cũ không đúng!"
                  << std::endl;

        return false;
    }

    db.freeResult(result);

    // Cập nhật password mới
    std::string updateQuery =
        "UPDATE accounts SET password = '" +
        newPassword +
        "' WHERE id = " +
        std::to_string(currentUserId);

    if (!db.executeNonQuery(updateQuery)) {
        std::cerr << "[Account Error] Đổi password thất bại!"
                  << std::endl;
        return false;
    }

    std::cout << "[Account] Đổi password thành công!"
              << std::endl;

    return true;
}

// =====================================================
// ĐĂNG XUẤT
// =====================================================
void AccountManager::logout() {

    if (!loggedIn) {
        std::cout << "[Account] Hiện tại chưa đăng nhập."
                  << std::endl;
        return;
    }

    loggedIn = false;
    currentUserId = 0;

    std::cout << "[Account] Đăng xuất thành công!"
              << std::endl;
}

// =====================================================
// KIỂM TRA TRẠNG THÁI ĐĂNG NHẬP
// =====================================================
bool AccountManager::isLoggedIn() const {
    return loggedIn;
}

// =====================================================
// LẤY ID USER HIỆN TẠI
// =====================================================
int AccountManager::getCurrentUserId() const {
    return currentUserId;
}
