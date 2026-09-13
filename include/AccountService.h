#pragma once
#include <string>
#include "Account.h"
#include "DBManager.h"

using namespace std;

/**
 * @class AccountService
 * @brief Lớp Quản lý Nghiệp vụ Tài khoản (Business Logic Layer).
 * Đảm nhận các chức năng đăng ký, đăng nhập, đổi mật khẩu và kiểm tra định dạng dữ liệu đầu vào.
 */
class AccountService {
private:
    DatabaseConnector& db;   // Tham chiếu đến lớp kết nối CSDL (Dependency Injection)

    bool loggedIn;           // Trạng thái đăng nhập của người dùng (true: đã đăng nhập, false: chưa)
    int currentUserId;       // ID tài khoản hiện đang sử dụng hệ thống

    // --- CÁC HÀM KIỂM TRA HỢP LỆ NỘI BỘ (VALIDATION) ---
    bool validateUsername(const string& username); // Kiểm tra tên đăng nhập có hợp lệ không
    bool validateEmail(const string& email);       // Kiểm tra cú pháp Email (vd: user@domain.com)
    bool validatePassword(const string& password); // Kiểm tra độ mạnh / độ dài mật khẩu

public:
    // Khởi tạo Service với đối tượng Kết nối CSDL được truyền vào
    AccountService(DatabaseConnector& database);

    /**
     * @brief Đăng ký tài khoản người dùng mới vào hệ thống.
     * @return true nếu đăng ký thành công, false nếu thất bại (trùng username/email hoặc dữ liệu lỗi)
     */
    bool registerAccount(
        const string& username,
        const string& email,
        const string& password,
        const string& fullName,
        const string& phone,
        const string& role = "User"
    );

    /**
     * @brief Thực hiện xác thực đăng nhập tài khoản.
     * @return true nếu thông tin đúng, false nếu sai tài khoản hoặc mật khẩu.
     */
    bool login(
        const string& username,
        const string& password
    );

    /**
     * @brief Đổi mật khẩu tài khoản đang đăng nhập.
     * @return true nếu đổi thành công, false nếu mật khẩu cũ không đúng.
     */
    bool changePassword(
        const string& oldPassword,
        const string& newPassword
    );

    // Đăng xuất khỏi hệ thống và reset trạng thái người dùng
    void logout();

    // Kiểm tra xem hiện tại có tài khoản nào đang đăng nhập không
    bool isLoggedIn() const;

    // Lấy ID của tài khoản đang đăng nhập hiện tại
    int getCurrentUserId() const;
};