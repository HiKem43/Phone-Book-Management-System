#include "Group.h"
using namespace std;

Group::Group()
{
    id = 0;
    account_id = 0;
    name = "";
    description = "";
}

Group::Group(int group_id, int account_id,
    string groupName, string description)
{
    this->id = group_id;
    this->account_id = account_id;
    this->name = groupName;
    this->description = description;
}

int Group::getGroupId() const
{
    return id;
}
int Group::getAccountId() const
{
    return account_id;
}
string Group::getGroupName() const
{
    return name;
}
string Group::getDescription() const
{
    return description;
}
void Group::setGroupId(int group_id)
{
    this->id = group_id;
}
void Group::setAccountId(int account_id)
{
    this->account_id = account_id;
}
void Group::setGroupName(string groupName)
{
    this->name = groupName;
}
void Group::setDescription(string description)
{
    this->description = description;
}