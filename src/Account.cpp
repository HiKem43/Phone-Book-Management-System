#include "Account.h"
using namespace std;
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
int Account::getAccountId() const
{
    return account_id;
}
string Account::getUsername() const
{
    return username;
}
string Account::getPassword() const
{
    return password;
}
string Account::getFullName() const
{
    return fullName;
}
string Account::getEmail() const
{
    return email;
}
string Account::getPhone() const
{
    return phone;
}
string Account::getRole() const
{
    return role;
}
void Account::setAccountId(int account_id)
{
    this->account_id = account_id;
}
void Account::setUsername(string username)
{
    this->username = username;
}
void Account::setPassword(string password)
{
    this->password = password;
}
void Account::setFullName(string fullName)
{
    this->fullName = fullName;
}
void Account::setEmail(string email)
{
    this->email = email;
}
void Account::setPhone(string phone)
{
    this->phone = phone;
}
void Account::setRole(string role)
{
    this->role = role;
}