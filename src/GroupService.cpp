#include "GroupService.h"
#include "ContactService.h"
#include <iostream>

using namespace std;

vector<Group> GroupService::groups;
vector<ContactGroup> GroupService::contactGroups;
int GroupService::nextId = 1;

string GroupService::inputRequired(string message)
{
    string value;

    do
    {
        cout << message;
        getline(cin, value);

        if (value.empty())
            cout << "Input cannot be empty!\n";

    } while (value.empty());

    return value;
}

void GroupService::run()
{
    int choice;

    do
    {
        cout << "\n===== GROUP MANAGEMENT =====\n";
        cout << "1. Add Group\n";
        cout << "2. View Groups\n";
        cout << "3. Search Group\n";
        cout << "4. Edit Group\n";
        cout << "5. Delete Group\n";
        cout << "6. Assign Contact to Group\n";
        cout << "0. Back\n";
        cout << "Choose: ";

        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            addGroup();
            break;

        case 2:
            viewGroups();
            break;

        case 3:
            searchGroup();
            break;

        case 4:
            editGroup();
            break;

        case 5:
            deleteGroup();
            break;

        case 6:
            assignContact();
            break;

        case 0:
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}

void GroupService::addGroup()
{
    Group group;

    group.name = inputRequired("Group name: ");

    for (const Group& g : groups)
    {
        if (g.name == group.name)
        {
            cout << "Error: Group name already exists!\n";
            return;
        }
    }

    cout << "Description: ";
    getline(cin, group.description);

    group.id = nextId++;

    groups.push_back(group);

    cout << "Group added successfully!\n";
}

void GroupService::viewGroups()
{
    if (groups.empty())
    {
        cout << "No groups yet.\n";
        return;
    }

    cout << "\n===== GROUP LIST =====\n";

    for (const Group& g : groups)
    {
        cout << "ID: " << g.id << "\n";
        cout << "Name: " << g.name << "\n";
        cout << "Description: " << g.description << "\n";

        cout << "Contacts: ";

        bool hasContact = false;

        for (const ContactGroup& cg : contactGroups)
        {
            if (cg.groupId == g.id)
            {
                cout << cg.contactId << " ";
                hasContact = true;
            }
        }

        if (!hasContact)
            cout << "None";

        cout << "\n----------------------\n";
    }
}

void GroupService::searchGroup()
{
    string keyword;

    cout << "Enter group name: ";
    getline(cin, keyword);

    bool found = false;

    for (const Group& g : groups)
    {
        if (g.name.find(keyword) != string::npos)
        {
            cout << "\nID: " << g.id << "\n";
            cout << "Name: " << g.name << "\n";
            cout << "Description: " << g.description << "\n";

            found = true;
        }
    }

    if (!found)
        cout << "No matching group found.\n";
}

void GroupService::editGroup()
{
    int id;

    cout << "Enter Group ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    for (Group& g : groups)
    {
        if (g.id == id)
        {
            string name = inputRequired("New group name: ");

            for (const Group& other : groups)
            {
                if (other.id != id && other.name == name)
                {
                    cout << "Error: Group name already exists!\n";
                    return;
                }
            }

            cout << "New description: ";
            string description;
            getline(cin, description);

            g.name = name;
            g.description = description;

            cout << "Group updated successfully!\n";
            return;
        }
    }

    cout << "Error: Group not found!\n";
}

void GroupService::deleteGroup()
{
    int id;

    cout << "Enter Group ID: ";
    cin >> id;
    cin.ignore(1000, '\n');

    for (auto it = groups.begin(); it != groups.end(); ++it)
    {
        if (it->id == id)
        {
            char confirm;

            cout << "Are you sure you want to delete? (Y/N): ";
            cin >> confirm;
            cin.ignore(1000, '\n');

            if (confirm == 'Y' || confirm == 'y')
            {
                groups.erase(it);

                for (auto cg = contactGroups.begin();
                    cg != contactGroups.end();)
                {
                    if (cg->groupId == id)
                        cg = contactGroups.erase(cg);
                    else
                        ++cg;
                }

                cout << "Group deleted successfully!\n";
            }
            else
            {
                cout << "Delete cancelled.\n";
            }

            return;
        }
    }

    cout << "Error: Group not found!\n";
}

void GroupService::assignContact()
{
    int contactId;
    int groupId;

    cout << "Enter Contact ID: ";
    cin >> contactId;

    cout << "Enter Group ID: ";
    cin >> groupId;

    cin.ignore(1000, '\n');

    if (!ContactService::exists(contactId))
    {
        cout << "Error: Contact not found!\n";
        return;
    }

    bool groupExists = false;

    for (const Group& g : groups)
    {
        if (g.id == groupId)
        {
            groupExists = true;
            break;
        }
    }

    if (!groupExists)
    {
        cout << "Error: Group not found!\n";
        return;
    }

    for (const ContactGroup& cg : contactGroups)
    {
        if (cg.contactId == contactId &&
            cg.groupId == groupId)
        {
            cout << "Error: Contact already belongs to this group!\n";
            return;
        }
    }

    ContactGroup cg;
    cg.contactId = contactId;
    cg.groupId = groupId;

    contactGroups.push_back(cg);

    cout << "Contact assigned to group successfully!\n";
}