#pragma once
#include <string>

class Account
{
private:
    int account_id;
    std::string username;
    std::string password;
    std::string fullName;
    std::string email;
    std::string phone;
    std::string role;
public:
    Account();
    Account(int account_id, std::string username, std::string password,
        std::string fullName, std::string email, std::string phone, std::string role);
    int getAccountId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getRole() const;
    void setAccountId(int account_id);
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setFullName(std::string fullName);
    void setEmail(std::string email);
    void setPhone(std::string phone);
    void setRole(std::string role);
};
