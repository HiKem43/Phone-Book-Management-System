#pragma once
#include <string>
#include <vector>

using namespace std;

struct Contact
{
    int id;
    string name;
    string phone;
    string email;
    string address;
};

class ContactService
{
private:
    static vector<Contact> contacts;
    static int nextId;

    static string inputRequired(string message);
    static bool validPhone(string phone);
    static bool validEmail(string email);

public:
    static void run();

    static void addContact();
    static void viewContacts();
    static void searchContact();
    static void editContact();
    static void deleteContact();

    static bool exists(int contactId);
};