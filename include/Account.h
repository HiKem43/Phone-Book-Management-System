#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;
class Account
{
private:
    int account_id;
    string username;
    string password;
    string fullName;
    string email;
    string phone;
    string role;
public:
    Account();
    Account(int account_id, string username, string password,
        string fullName, string email, string phone, string role);
    int getAccountId() const;
    string getUsername() const;
    string getPassword() const;
    string getFullName() const;
    string getEmail() const;
    string getPhone() const;
    string getRole() const;
    void setAccountId(int account_id);
    void setUsername(string username);
    void setPassword(string password);
    void setFullName(string fullName);
    void setEmail(string email);
    void setPhone(string phone);
    void setRole(string role);
};
#endif