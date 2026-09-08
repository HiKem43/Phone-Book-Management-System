#pragma once
class Contact_Group
{
private:
    int contactId;
    int groupId;
public:
    Contact_Group();
    Contact_Group(int contactId,
        int groupId);
    int getContactId() const;
    int getGroupId() const;
    void setContactId(int contactId);
    void setGroupId(int groupId);
    bool validate() const;
};
