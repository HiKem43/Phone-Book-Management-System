#pragma once
#include <string>
using namespace std;

/**
 * @struct Contact
 * @brief Lớp Mô hình (Model) đại diện cho một danh bạ/người liên hệ trong ứng dụng.
 */
struct Contact
{
    int id;             // ID duy nhất của người liên hệ
    int account_id;     // ID tài khoản sở hữu danh bạ này (Khóa ngoại nối tới Account)
    int group_id;       // ID nhóm danh bạ mà người này thuộc về (Khóa ngoại nối tới Group)
    string name;        // Tên hiển thị người liên hệ
    string phone;       // Số điện thoại
    string email;       // Email
    string address;     // Địa chỉ nhà/cơ quan
    bool isFavorite;    // Đánh dấu người liên hệ yêu thích (true/false)

    // Constructors
    Contact();
    Contact(int contact_id, int account_id, int group_id,
        string name, string phone, string email,
        string address, bool isFavorite);

    // Getters & Setters
    int getContactId() const;
    int getAccountId() const;
    int getGroupId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;
    string getAddress() const;
    bool getIsFavorite() const;
    
    void setContactId(int contact_id);
    void setAccountId(int account_id);
    void setGroupId(int group_id);
    void setName(string name);
    void setPhone(string phone);
    void setEmail(string email);
    void setAddress(string address);
    void setIsFavorite(bool isFavorite);
};