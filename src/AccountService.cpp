#include "AccountService.h"
#include <iostream>
#include <regex>
#include <cctype>

using namespace std;

// =====================================================
// KHỞI TẠO (CONSTRUCTOR)
// =====================================================

// Khởi tạo AccountService liên kết với cơ sở dữ liệu
AccountService::AccountService(DatabaseConnector& database)
    : db(database), loggedIn(false), currentUserId(0) {
}

// =====================================================
// HÀM KIỂM TRA DỮ LIỆU (VALIDATION)
// =====================================================

// Kiểm tra định dạng username (từ 3-30 ký tự, chỉ gồm chữ cái, chữ số và dấu _)
bool AccountService::validateUsername(const string& username) {

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

// Kiểm tra định dạng email theo mẫu regex
bool AccountService::validateEmail(const string& email) {

    regex pattern(
        R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)"
    );

    return regex_match(email, pattern);
}

// Kiểm tra mật khẩu (độ dài tối thiểu 6 ký tự)
bool AccountService::validatePassword(const string& password) {

    if (password.length() < 6) {
        return false;
    }

    return true;
}

// =====================================================
// ĐĂNG KÝ TÀI KHOẢN
// =====================================================

// Xử lý đăng ký tài khoản mới vào hệ thống
bool AccountService::registerAccount(
    const string& username,
    const string& email,
    const string& password,
    const string& fullName,
    const string& phone,
    const string& role) {

    if (!db.isConnected()) {
        cerr << "Database is not connected!" << endl;
        return false;
    }

    // Kiểm tra tính hợp lệ của thông tin đầu vào
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

    if (role != "User" && role != "Admin") {
        cerr << "Role khong hop le!" << endl;
        return false;
    }

    // Mã hóa ký tự đặc biệt phòng chống SQL Injection
    const string escapedUsername = db.escapeString(username);
    const string escapedEmail = db.escapeString(email);
    const string escapedPassword = db.escapeString(password);
    const string escapedFullName = db.escapeString(fullName);
    const string escapedPhone = db.escapeString(phone);

    // Kiểm tra trùng lặp username
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

    // Kiểm tra trùng lặp email
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

    // Thêm bản ghi tài khoản mới vào CSDL (mật khẩu mã hóa SHA256)
    string query =
        "INSERT INTO Accounts (username, email, password, fullname, phone, role) "
        "VALUES ('" +
        escapedUsername + "', '" +
        escapedEmail + "', SHA2('" +
        escapedPassword + "', 256), '" +
        escapedFullName + "', '" +
        escapedPhone + "', '" +
        db.escapeString(role) + "')";

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

// Xác thực tài khoản và đăng nhập hệ thống
bool AccountService::login(
    const string& username,
    const string& password) {

    if (!db.isConnected()) {
        cerr << "Database is not connected!" << endl;
        return false;
    }

    if (username.empty() || password.empty()) {
        cerr << "Username va password khong duoc de trong!"
             << endl;
        return false;
    }

    // Tìm kiếm thông tin đăng nhập trong CSDL
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

// Thay đổi mật khẩu cho tài khoản hiện tại
bool AccountService::changePassword(
    const string& oldPassword,
    const string& newPassword) {

    // Kiểm tra trạng thái đăng nhập
    if (!loggedIn) {
        cerr << "Ban chua dang nhap!" << endl;
        return false;
    }

    // Kiểm tra định dạng mật khẩu mới
    if (!validatePassword(newPassword)) {
        cerr << "Password moi phai co it nhat 6 ky tu!"
             << endl;
        return false;
    }

    // Xác nhận mật khẩu cũ
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

    // Cập nhật mật khẩu mới đã mã hóa
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
// ĐĂNG XUẤT VÀ TRẠNG THÁI
// =====================================================

// Thực hiện đăng xuất tài khoản
void AccountService::logout() {

    if (!loggedIn) {
        cout << "Hien tai chua dang nhap." << endl;
        return;
    }

    loggedIn = false;
    currentUserId = 0;

    cout << "Dang xuat thanh cong!" << endl;
}

// Kiểm tra trạng thái đã đăng nhập hay chưa
bool AccountService::isLoggedIn() const {
    return loggedIn;
}

// Lấy ID tài khoản hiện đang đăng nhập
int AccountService::getCurrentUserId() const {
    return currentUserId;
}