#include "Contact.h"
using namespace std;

// =====================================================
// KHỞI TẠO (CONSTRUCTORS)
// =====================================================

// Constructor mặc định - Khởi tạo giá trị ban đầu cho liên hệ
Contact::Contact()
{
    id = 0;
    account_id = 0;
    group_id = 0;
    name = "";
    phone = "";
    email = "";
    address = "";
    isFavorite = false;
}

// Constructor đầy đủ tham số - Khởi tạo liên hệ với thông tin chi tiết
Contact::Contact(int contact_id, int account_id, int group_id,
    string name, string phone, string email,
    string address, bool isFavorite)
{
    this->id = contact_id;
    this->account_id = account_id;
    this->group_id = group_id;
    this->name = name;
    this->phone = phone;
    this->email = email;
    this->address = address;
    this->isFavorite = isFavorite;
}

// =====================================================
// CÁC HÀM LẤY THÔNG TIN (GETTERS)
// =====================================================

// Lấy ID liên hệ
int Contact::getContactId() const
{
    return id;
}

// Lấy ID tài khoản sở hữu liên hệ
int Contact::getAccountId() const
{
    return account_id;
}

// Lấy ID nhóm liên hệ
int Contact::getGroupId() const
{
    return group_id;
}

// Lấy tên liên hệ
string Contact::getName() const
{
    return name;
}

// Lấy số điện thoại
string Contact::getPhone() const
{
    return phone;
}

// Lấy email liên hệ
string Contact::getEmail() const
{
    return email;
}

// Lấy địa chỉ liên hệ
string Contact::getAddress() const
{
    return address;
}

// Kiểm tra liên hệ có thuộc danh sách yêu thích hay không
bool Contact::getIsFavorite() const
{
    return isFavorite;
}

// =====================================================
// CÁC HÀM CẬP NHẬT THÔNG TIN (SETTERS)
// =====================================================

// Cập nhật ID liên hệ
void Contact::setContactId(int contact_id)
{
    this->id = contact_id;
}

// Cập nhật ID tài khoản sở hữu
void Contact::setAccountId(int account_id)
{
    this->account_id = account_id;
}

// Cập nhật ID nhóm
void Contact::setGroupId(int group_id)
{
    this->group_id = group_id;
}

// Cập nhật tên liên hệ
void Contact::setName(string name)
{
    this->name = name;
}

// Cập nhật số điện thoại
void Contact::setPhone(string phone)
{
    this->phone = phone;
}

// Cập nhật email liên hệ
void Contact::setEmail(string email)
{
    this->email = email;
}

// Cập nhật địa chỉ liên hệ
void Contact::setAddress(string address)
{
    this->address = address;
}

// Cập nhật trạng thái yêu thích
void Contact::setIsFavorite(bool isFavorite)
{
    this->isFavorite = isFavorite;
}