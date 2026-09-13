#pragma once
#include <string>
#include <vector>
#include "Contact.h"
#include "Group.h"

using namespace std;

class GroupService
{
private:
    static vector<Group> groups;
    static vector<ContactGroup> contactGroups;
    static int nextId;
    static int currentAccountId;

    static string inputRequired(string message);

public:
    static void run();

    static void addGroup();
    static void addGroup(const Group& group);
    static void viewGroups();
    static void searchGroup();
    static void editGroup();
    static void deleteGroup();
    static void assignContact();
    static bool assignContact(int contactId, int groupId);
    static bool setContactGroup(int contactId, int groupId);
    static std::vector<Contact> getContactsForGroup(int groupId);
    static const vector<Group>& getGroups();
    static void loadForAccount(int accountId);
    static void clear();
    static bool updateGroup(const Group& group);
    static bool removeGroup(int groupId);
};