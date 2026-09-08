#pragma once
#include <iostream>
#include <string>
using namespace std;
class Group {
private:
    int groupId;
    int accountId;
    string groupName;
    string description;
public:
    Group(int groupId, int accountId,
        string groupName, string description) {
        this->groupId = groupId;
        this->accountId = accountId;
        this->groupName = groupName;
        this->description = description;
    }
    int getId() {
        return groupId;
    }
    int getAccountId() {
        return accountId;
    }
    string getName() {
        return groupName;
    }
    string getDescription() {
        return description;
    }
    void setName(string name) {
        groupName = name;
    }
    void setDescription(string description) {
        this->description = description;
    }
    bool validate() {
        return groupId > 0 &&
            accountId > 0 &&
            !groupName.empty();
    }
};