#include "AccountService.h"
#include <iostream>
#include <regex>
#include <cctype>

using namespace std;


// Constructor
AccountService::AccountService(DatabaseConnector& database)
    : db(database), loggedIn(false), currentUserId(0) {
}


// Kiểm tra username
bool AccountService::validateUsername(const string& username) {

    // Username phải từ 3 đến 30 ký tự
    if (username.length() < 3 || username.length() > 30) {
        return false;
    }

    // Chỉ cho phép chữ cái, số và dấu _
    for (char c : username) {
        if (!isalnum(static_cast<unsigned char>(c)) && c != '_') {
            return false;
        }
    }

    return true;
}


// Kiểm tra email
bool AccountService::validateEmail(const string& email) {

    regex pattern(
        R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"
    );

    return regex_match(email, pattern);
}


// Kiểm tra password
bool AccountService::validatePassword(const string& password) {

    // Password phải có ít nhất 6 ký tự
    if (password.length() < 6) {
        return false;
    }

    return true;
}


// =====================================================
// ĐĂNG KÝ
// =====================================================

bool AccountService::registerAccount(
    const string& username,
    const string& email,
    const string& password,
    const string& fullName,
    const string& phone) {

    // Kiểm tra username
    if (!validateUsername(username)) {
        cerr << "Username khong hop le!" << endl;
        return false;
    }

    // Kiểm tra email
    if (!validateEmail(email)) {
        cerr << "Email khong hop le!" << endl;
        return false;
    }

    // Kiểm tra password
    if (!validatePassword(password)) {
        cerr << "Password phai co it nhat 6 ky tu!" << endl;
        return false;
    }


    // Kiểm tra username đã tồn tại
    const string escapedUsername = db.escapeString(username);
    const string escapedEmail = db.escapeString(email);
    const string escapedPassword = db.escapeString(password);
    const string escapedFullName = db.escapeString(fullName);
    const string escapedPhone = db.escapeString(phone);

    string checkUsername =
        "SELECT account_id FROM Accounts WHERE username = '" +
        escapedUsername + "'";

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


    // Kiểm tra email đã tồn tại
    string checkEmail =
        "SELECT account_id FROM Accounts WHERE email = '" +
        escapedEmail + "'";

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


    // Thêm tài khoản vào database
    string query =
        "INSERT INTO Accounts (username, email, password, fullname, phone, role) "
        "VALUES ('" +
        escapedUsername + "', '" +
        escapedEmail + "', SHA2('" +
        escapedPassword + "', 256), '" +
        escapedFullName + "', '" +
        escapedPhone + "', 'User')";

    if (!db.executeNonQuery(query)) {
        cerr << "Dang ky that bai!" << endl;
        return false;
    }

    cout << "Dang ky thanh cong!" << endl;

    return true;
}


// =====================================================
// ĐĂNG NHẬP
// =====================================================

bool AccountService::login(
    const string& username,
    const string& password) {

    if (username.empty() || password.empty()) {
        cerr << "Username va password khong duoc de trong!"
             << endl;
        return false;
    }


    // Tìm tài khoản
    string query =
        "SELECT account_id FROM Accounts "
        "WHERE username = '" +
        db.escapeString(username) +
        "' AND password = SHA2('" +
        db.escapeString(password) +
        "', 256)";

    MYSQL_RES* result = db.executeQuery(query);

    if (result == nullptr) {
        return false;
    }


    MYSQL_ROW row = mysql_fetch_row(result);


    // Đăng nhập thành công
    if (row != nullptr) {

        currentUserId = stoi(row[0]);
        loggedIn = true;

        db.freeResult(result);

        cout << "Dang nhap thanh cong!" << endl;

        return true;
    }


    // Đăng nhập thất bại
    db.freeResult(result);

    cerr << "Username hoac password khong dung!" << endl;

    return false;
}


// =====================================================
// ĐỔI MẬT KHẨU
// =====================================================

bool AccountService::changePassword(
    const string& oldPassword,
    const string& newPassword) {

    // Kiểm tra đã đăng nhập
    if (!loggedIn) {
        cerr << "Ban chua dang nhap!" << endl;
        return false;
    }


    // Kiểm tra password mới
    if (!validatePassword(newPassword)) {
        cerr << "Password moi phai co it nhat 6 ky tu!"
             << endl;
        return false;
    }


    // Kiểm tra password cũ
    string checkQuery =
        "SELECT account_id FROM Accounts "
        "WHERE id = " +
        to_string(currentUserId) +
        " AND password = SHA2('" +
        db.escapeString(oldPassword) +
        "', 256)";

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


    // Cập nhật password mới
    string updateQuery =
        "UPDATE Accounts SET password = SHA2('" +
        db.escapeString(newPassword) +
        "', 256) WHERE account_id = " +
        to_string(currentUserId);

    if (!db.executeNonQuery(updateQuery)) {
        cerr << "Doi password that bai!" << endl;
        return false;
    }

    cout << "Doi password thanh cong!" << endl;

    return true;
}


// =====================================================
// ĐĂNG XUẤT
// =====================================================

void AccountService::logout() {

    if (!loggedIn) {
        cout << "Hien tai chua dang nhap." << endl;
        return;
    }

    loggedIn = false;
    currentUserId = 0;

    cout << "Dang xuat thanh cong!" << endl;
}


// =====================================================
// KIỂM TRA ĐĂNG NHẬP
// =====================================================

bool AccountService::isLoggedIn() const {
    return loggedIn;
}


// =====================================================
// LẤY ID USER HIỆN TẠI
// =====================================================

int AccountService::getCurrentUserId() const {
    return currentUserId;
}
