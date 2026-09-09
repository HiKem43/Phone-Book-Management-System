#include "ContactService.h"
#include <iostream>
#include <cctype>

using namespace std;

vector<Contact> ContactService::contacts;
int ContactService::nextId = 1;

string ContactService::inputRequired(string message)
{
    string value;

    do
    {
        cout << message;
        getline(cin, value);

        if (value.empty())
            cout << "Error: This field cannot be empty!\n";

    } while (value.empty());

    return value;
}

bool ContactService::validPhone(string phone)
{
    if (phone.length() < 10 || phone.length() > 11)
        return false;

    for (char c : phone)
    {
        if (!isdigit(static_cast<unsigned char>(c)))
            return false;
    }

    return true;
}

bool ContactService::validEmail(string email)
{
    if (email.empty())
        return true;

    size_t at = email.find('@');
    size_t dot = email.find('.', at);

    return at != string::npos &&
        dot != string::npos &&
        at > 0 &&
        dot > at + 1 &&
        dot < email.length() - 1;
}

void ContactService::run()
{
    int choice;

    do
    {
        cout << "\n===== CONTACT MANAGEMENT =====\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Edit Contact\n";
        cout << "5. Delete Contact\n";
        cout << "0. Back\n";
        cout << "Choose: ";

        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            addContact();
            break;

        case 2:
            viewContacts();
            break;

        case 3:
            searchContact();
            break;

        case 4:
            editContact();
            break;

        case 5:
            deleteContact();
            break;

        case 0:
            break;

        default:
            cout << "Error: Invalid choice!\n";
        }

    } while (choice != 0);
}

void ContactService::addContact()
{
    Contact contact;

    contact.name = inputRequired("Name: ");

    for (const Contact& c : contacts)
    {
        if (c.name == contact.name)
        {
            cout << "Error: Contact name already exists!\n";
            return;
        }
    }

    contact.phone = inputRequired("Phone: ");

    if (!validPhone(contact.phone))
    {
        cout << "Error: Phone number must contain 10-11 digits!\n";
        return;
    }

    for (const Contact& c : contacts)
    {
        if (c.phone == contact.phone)
        {
            cout << "Error: Phone number already exists!\n";
            return;
        }
    }

    cout << "Email: ";
    getline(cin, contact.email);

    if (!validEmail(contact.email))
    {
        cout << "Error: Invalid email!\n";
        return;
    }

    cout << "Address: ";
    getline(cin, contact.address);

    contact.id = nextId++;

    contacts.push_back(contact);

    cout << "Contact added successfully!\n";
}

void ContactService::viewContacts()
{
    if (contacts.empty())
    {
        cout << "No contacts yet.\n";
        return;
    }

    cout << "\n===== CONTACT LIST =====\n";

    for (const Contact& c : contacts)
    {
        cout << "ID: " << c.id << "\n";
        cout << "Name: " << c.name << "\n";
        cout << "Phone: " << c.phone << "\n";
        cout << "Email: " << c.email << "\n";
        cout << "Address: " << c.address << "\n";
        cout << "----------------------\n";
    }
}

void ContactService::searchContact()
{
    string keyword;

    cout << "Enter name, phone or email: ";
    getline(cin, keyword);

    if (keyword.empty())
    {
        cout << "Error: Search keyword cannot be empty!\n";
        return;
    }

    bool found = false;

    for (const Contact& c : contacts)
    {
        if (c.name.find(keyword) != string::npos ||
            c.phone.find(keyword) != string::npos ||
            c.email.find(keyword) != string::npos)
        {
            cout << "\nID: " << c.id << "\n";
            cout << "Name: " << c.name << "\n";
            cout << "Phone: " << c.phone << "\n";
            cout << "Email: " << c.email << "\n";
            cout << "Address: " << c.address << "\n";
            cout << "----------------------\n";

            found = true;
        }
    }

    if (!found)
        cout << "No matching contact found.\n";
}

void ContactService::editContact()
{
    int id;

    cout << "Enter Contact ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    for (Contact& c : contacts)
    {
        if (c.id == id)
        {
            string name = inputRequired("New name: ");

            for (const Contact& other : contacts)
            {
                if (other.id != id && other.name == name)
                {
                    cout << "Error: Contact name already exists!\n";
                    return;
                }
            }

            string phone = inputRequired("New phone: ");

            if (!validPhone(phone))
            {
                cout << "Error: Phone number must contain 10-11 digits!\n";
                return;
            }

            for (const Contact& other : contacts)
            {
                if (other.id != id && other.phone == phone)
                {
                    cout << "Error: Phone number already exists!\n";
                    return;
                }
            }

            string email;

            cout << "New email: ";
            getline(cin, email);

            if (!validEmail(email))
            {
                cout << "Error: Invalid email!\n";
                return;
            }

            string address;

            cout << "New address: ";
            getline(cin, address);

            c.name = name;
            c.phone = phone;
            c.email = email;
            c.address = address;

            cout << "Contact updated successfully!\n";
            return;
        }
    }

    cout << "Error: Contact not found!\n";
}

void ContactService::deleteContact()
{
    int id;

    cout << "Enter Contact ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    for (auto it = contacts.begin(); it != contacts.end(); ++it)
    {
        if (it->id == id)
        {
            char confirm;

            cout << "Are you sure you want to delete? (Y/N): ";
            cin >> confirm;
            cin.ignore(1000, '\n');

            if (confirm == 'Y' || confirm == 'y')
            {
                contacts.erase(it);
                cout << "Contact deleted successfully!\n";
            }
            else
            {
                cout << "Delete cancelled.\n";
            }

            return;
        }
    }

    cout << "Error: Contact not found!\n";
}

bool ContactService::exists(int contactId)
{
    for (const Contact& c : contacts)
    {
        if (c.id == contactId)
            return true;
    }

    return false;
}