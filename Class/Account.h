#pragma once
#include <string>
class Account
{
private:
    int accountId;
    std::string username;
    std::string password;
    std::string fullName;
    std::string email;
    std::string phone;
public:
    Account();

    Account(int accountId,
        const std::string& username,
        const std::string& password,
        const std::string& fullName,
        const std::string& email,
        const std::string& phone);

    int getAccountId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getEmail() const;
    std::string getPhone() const;

    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setFullName(const std::string& fullName);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);

    bool validate() const;
};
