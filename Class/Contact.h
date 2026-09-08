#pragma once
#include <string>
class Contact
{
private:
    int contactId;
    int accountId;
    std::string name;
    std::string phone;
    std::string email;
    std::string address;
    bool isFavorite;
public:
    Contact();
    Contact(int contactId,
        int accountId,
        const std::string& name,
        const std::string& phone,
        const std::string& email,
        const std::string& address,
        bool isFavorite = false);

    int getContactId() const;
    int getAccountId() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getAddress() const;
    bool getFavorite() const;

    void setName(const std::string& name);
    void setPhone(const std::string& phone);
    void setEmail(const std::string& email);
    void setAddress(const std::string& address);
    void setFavorite(bool favorite);
    bool validate() const;
};
