#include "Account.h"
using namespace std;

// =====================================================
// KHỞI TẠO (CONSTRUCTORS)
// =====================================================

// Constructor mặc định - Khởi tạo giá trị ban đầu cho tài khoản
Account::Account()
{
    account_id = 0;
    username = "";
    password = "";
    fullName = "";
    email = "";
    phone = "";
    role = "User";
}

// Constructor đầy đủ tham số - Khởi tạo tài khoản với thông tin cụ thể
Account::Account(int account_id, string username, string password,
    string fullName, string email, string phone, string role)
{
    this->account_id = account_id;
    this->username = username;
    this->password = password;
    this->fullName = fullName;
    this->email = email;
    this->phone = phone;
    this->role = role;
}

// =====================================================
// CÁC HÀM LẤY THÔNG TIN (GETTERS)
// =====================================================

// Lấy ID tài khoản
int Account::getAccountId() const
{
    return account_id;
}

// Lấy tên đăng nhập
string Account::getUsername() const
{
    return username;
}

// Lấy mật khẩu
string Account::getPassword() const
{
    return password;
}

// Lấy họ và tên
string Account::getFullName() const
{
    return fullName;
}

// Lấy địa chỉ email
string Account::getEmail() const
{
    return email;
}

// Lấy số điện thoại
string Account::getPhone() const
{
    return phone;
}

// Lấy vai trò (User / Admin)
string Account::getRole() const
{
    return role;
}

// =====================================================
// CÁC HÀM CẬP NHẬT THÔNG TIN (SETTERS)
// =====================================================

// Cập nhật ID tài khoản
void Account::setAccountId(int account_id)
{
    this->account_id = account_id;
}

// Cập nhật tên đăng nhập
void Account::setUsername(string username)
{
    this->username = username;
}

// Cập nhật mật khẩu
void Account::setPassword(string password)
{
    this->password = password;
}

// Cập nhật họ và tên
void Account::setFullName(string fullName)
{
    this->fullName = fullName;
}

// Cập nhật email
void Account::setEmail(string email)
{
    this->email = email;
}

// Cập nhật số điện thoại
void Account::setPhone(string phone)
{
    this->phone = phone;
}

// Cập nhật vai trò tài khoản
void Account::setRole(string role)
{
    this->role = role;
}