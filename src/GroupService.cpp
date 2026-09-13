#include "GroupService.h"
#include "ContactService.h"
#include "DBManager.h"
#include <iostream>

using namespace std;

vector<Group> GroupService::groups;
vector<ContactGroup> GroupService::contactGroups;
int GroupService::nextId = 1;
int GroupService::currentAccountId = 0;

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

    group.account_id = currentAccountId;
    group.id = nextId++;

    groups.push_back(group);
    db.saveGroup(group);

    cout << "Group added successfully!\n";
}

void GroupService::addGroup(const Group& source)
{
    Group group = source;
    group.account_id = currentAccountId;
    group.id = nextId++;
    groups.push_back(group);
    db.saveGroup(group);
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
            db.updateGroup(g);

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
                db.deleteGroup(currentAccountId, it->id);
                db.deleteContactGroups(currentAccountId, it->id);
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

    if (!assignContact(contactId, groupId))
        return;

    cout << "Contact assigned to group successfully!\n";
}

bool GroupService::assignContact(int contactId, int groupId)
{
    if (!ContactService::exists(contactId))
    {
        cout << "Error: Contact not found!\n";
        return false;
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
        return false;
    }

    for (const ContactGroup& cg : contactGroups)
    {
        if (cg.contactId == contactId &&
            cg.groupId == groupId)
        {
            cout << "Error: Contact already belongs to this group!\n";
            return false;
        }
    }

    ContactGroup cg;
    cg.contactId = contactId;
    cg.groupId = groupId;

    contactGroups.push_back(cg);
    db.saveContactGroup(currentAccountId, cg);
    return true;
}

const vector<Group>& GroupService::getGroups()
{
    return groups;
}

void GroupService::loadForAccount(int accountId)
{
    currentAccountId = accountId;
    groups = db.loadGroups(accountId);
    contactGroups = db.loadContactGroups(accountId);
    nextId = 1;
    for (const Group& group : groups)
        if (group.id >= nextId) nextId = group.id + 1;
}

void GroupService::clear()
{
    groups.clear();
    contactGroups.clear();
    currentAccountId = 0;
    nextId = 1;
}

bool GroupService::updateGroup(const Group& updated)
{
    for (Group& group : groups) {
        if (group.id == updated.id && group.account_id == currentAccountId) {
            group = updated;
            return db.updateGroup(group);
        }
    }
    return false;
}

bool GroupService::removeGroup(int groupId)
{
    if (!db.deleteGroup(currentAccountId, groupId) ||
        !db.deleteContactGroups(currentAccountId, groupId)) return false;
    for (auto it = groups.begin(); it != groups.end(); ++it) {
        if (it->id == groupId) {
            groups.erase(it);
            break;
        }
    }
    for (auto it = contactGroups.begin(); it != contactGroups.end();) {
        if (it->groupId == groupId) it = contactGroups.erase(it);
        else ++it;
    }
    return true;
}