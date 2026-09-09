#pragma once
#include <string>
#include <vector>

using namespace std;

struct Group
{
    int id;
    string name;
    string description;
};

struct ContactGroup
{
    int contactId;
    int groupId;
};

class GroupService
{
private:
    static vector<Group> groups;
    static vector<ContactGroup> contactGroups;
    static int nextId;

    static string inputRequired(string message);

public:
    static void run();

    static void addGroup();
    static void viewGroups();
    static void searchGroup();
    static void editGroup();
    static void deleteGroup();
    static void assignContact();
};