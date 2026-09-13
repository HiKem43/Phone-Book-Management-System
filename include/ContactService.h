#pragma once
#include <string>
#include <vector>
#include "Contact.h"

using namespace std;

class ContactService
{
private:
    static vector<Contact> contacts;
    static int nextId;
    static int currentAccountId;

    static string inputRequired(string message);
    static bool validPhone(string phone);
    static bool validEmail(string email);

public:
    static void run();

    static void addContact();
    static bool addContact(const Contact& contact);
    static const vector<Contact>& getContacts();
    static void viewContacts();
    static void searchContact();
    static void editContact();
    static void deleteContact();

    static bool exists(int contactId);
    static void loadForAccount(int accountId);
    static void clear();
    static void toggleFavorite(int contactId);
    static bool updateContact(const Contact& contact);
    static bool removeContact(int contactId);
    static void sortByName();
};