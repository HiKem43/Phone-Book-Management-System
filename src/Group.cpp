#include "Group.h"
using namespace std;
Group::Group()
{
    group_id = 0;
    account_id = 0;
    groupName = "";
    description = "";
}
Group::Group(int group_id, int account_id,
    string groupName, string description)
{
    this->group_id = group_id;
    this->account_id = account_id;
    this->groupName = groupName;
    this->description = description;
}
int Group::getGroupId() const
{
    return group_id;
}
int Group::getAccountId() const
{
    return account_id;
}
string Group::getGroupName() const
{
    return groupName;
}
string Group::getDescription() const
{
    return description;
}
void Group::setGroupId(int group_id)
{
    this->group_id = group_id;
}
void Group::setAccountId(int account_id)
{
    this->account_id = account_id;
}
void Group::setGroupName(string groupName)
{
    this->groupName = groupName;
}
void Group::setDescription(string description)
{
    this->description = description;
}