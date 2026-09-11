#include "Contact.h"
using namespace std;

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

int Contact::getContactId() const
{
    return id;
}
int Contact::getAccountId() const
{
    return account_id;
}
int Contact::getGroupId() const
{
    return group_id;
}
string Contact::getName() const
{
    return name;
}
string Contact::getPhone() const
{
    return phone;
}
string Contact::getEmail() const
{
    return email;
}
string Contact::getAddress() const
{
    return address;
}
bool Contact::getIsFavorite() const
{
    return isFavorite;
}
void Contact::setContactId(int contact_id)
{
    this->id = contact_id;
}
void Contact::setAccountId(int account_id)
{
    this->account_id = account_id;
}
void Contact::setGroupId(int group_id)
{
    this->group_id = group_id;
}
void Contact::setName(string name)
{
    this->name = name;
}
void Contact::setPhone(string phone)
{
    this->phone = phone;
}
void Contact::setEmail(string email)
{
    this->email = email;
}
void Contact::setAddress(string address)
{
    this->address = address;
}
void Contact::setIsFavorite(bool isFavorite)
{
    this->isFavorite = isFavorite;
}