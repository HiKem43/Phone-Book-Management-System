#pragma once
#include <string>
using namespace std;
class Contact
{
private:
    int contact_id;
    int account_id;
    int group_id;
    string name;
    string phone;
    string email;
    string address;
    bool isFavorite;
public:
    Contact();
    Contact(int contact_id, int account_id, int group_id,
        string name, string phone, string email,
        string address, bool isFavorite);
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
