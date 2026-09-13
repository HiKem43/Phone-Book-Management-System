#pragma once
#include <string>

/**
 * @class Account
 * @brief Lớp Mô hình (Model) đại diện cho thông tin tài khoản người dùng trong hệ thống.
 * Chứa các thông tin định danh, đăng nhập và phân quyền của người dùng.
 */
class Account
{
private:
    int account_id;        // ID định danh duy nhất của tài khoản (Primary Key trong CSDL)
    std::string username;  // Tên đăng nhập
    std::string password;  // Mật khẩu (thường được mã hóa)
    std::string fullName;  // Họ và tên đầy đủ của người dùng
    std::string email;     // Địa chỉ email liên hệ
    std::string phone;     // Số điện thoại đăng ký
    std::string role;      // Vai trò / Phân quyền trong hệ thống (vd: "Admin", "User")

public:
    // --- KHỞI TẠO (CONSTRUCTORS) ---
    Account();
    Account(int account_id, std::string username, std::string password,
        std::string fullName, std::string email, std::string phone, std::string role);

    // --- CÁC HÀM LẤY DỮ LIỆU (GETTERS - const để bảo vệ dữ liệu không bị thay đổi ngoài ý muốn) ---
    int getAccountId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getRole() const;

    // --- CÁC HÀM CẬP NHẬT DỮ LIỆU (SETTERS) ---
    void setAccountId(int account_id);
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setFullName(std::string fullName);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    void setRole(std::string role);
};