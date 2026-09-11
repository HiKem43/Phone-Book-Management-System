#pragma once
#include <string>
using namespace std;

struct Group
{
    int id;
    int account_id;
    string name;
    string description;

    Group();
    Group(int group_id, int account_id,
        string groupName, string description);

    int getGroupId() const;
    int getAccountId() const;
    string getGroupName() const;
    string getDescription() const;
    void setGroupId(int group_id);
    void setAccountId(int account_id);
    void setGroupName(string groupName);
    void setDescription(string description);
};
