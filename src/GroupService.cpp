#include "GroupService.h"
#include "ContactService.h"
#include "DBManager.h"
#include <iostream>

using namespace std;

// Khởi tạo các biến tĩnh của lớp GroupService
vector<Group> GroupService::groups;
vector<ContactGroup> GroupService::contactGroups;
int GroupService::nextId = 1;
int GroupService::currentAccountId = 0;

// =====================================================
// HÀM BỔ TRỢ & CONSOLE RUNNER
// =====================================================

// Hàm yêu cầu nhập chuỗi không được bỏ trống
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

// Điều hướng menu quản lý nhóm danh bạ trên nền Console
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

// =====================================================
// CHỨC NĂNG QUẢN LÝ NHÓM TRÊN CONSOLE
// =====================================================

// Thêm nhóm mới từ Console
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

// Thêm nhóm từ đối tượng Group
void GroupService::addGroup(const Group& source)
{
    Group group = source;
    group.account_id = currentAccountId;
    group.id = nextId++;
    groups.push_back(group);
    db.saveGroup(group);
}

// Hiển thị danh sách nhóm ra Console
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

// Tìm kiếm nhóm theo tên trên Console
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

// Sửa tên và mô tả nhóm trên Console
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

// Xóa nhóm trên Console
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

                for (const Contact& contact : ContactService::getContacts())
                {
                    if (contact.group_id == id)
                    {
                        Contact updated = contact;
                        updated.group_id = 0;
                        ContactService::updateContact(updated);
                    }
                }

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

// Gán liên hệ vào nhóm trên Console
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

// =====================================================
// NGHIỆP VỤ HỆ THỐNG QUẢN LÝ NHÓM
// =====================================================

// Phân gán liên hệ vào nhóm theo ID
bool GroupService::assignContact(int contactId, int groupId)
{
    if (!ContactService::exists(contactId))
    {
        cout << "Error: Contact not found!\n";
        return false;
    }

    bool groupExists = false;
    for (const Group& group : groups)
    {
        if (group.id == groupId)
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

    return setContactGroup(contactId, groupId);
}

// Cập nhật mối quan hệ nhóm - liên hệ trong RAM và CSDL
bool GroupService::setContactGroup(int contactId, int groupId)
{
    if (!ContactService::exists(contactId))
        return false;

    if (groupId != 0)
    {
        bool groupExists = false;
        for (const Group& group : groups)
        {
            if (group.id == groupId)
            {
                groupExists = true;
                break;
            }
        }
        if (!groupExists)
            return false;
    }

    if (!db.deleteContactGroup(currentAccountId, contactId))
        return false;

    for (auto it = contactGroups.begin(); it != contactGroups.end();)
    {
        if (it->contactId == contactId)
            it = contactGroups.erase(it);
        else
            ++it;
    }

    if (groupId != 0)
    {
        ContactGroup relation{contactId, groupId};
        if (!db.saveContactGroup(currentAccountId, relation))
            return false;
        contactGroups.push_back(relation);
    }

    for (const Contact& contact : ContactService::getContacts())
    {
        if (contact.id == contactId)
        {
            Contact updated = contact;
            updated.group_id = groupId;
            return ContactService::updateContact(updated);
        }
    }

    return false;
}

// Trả về danh sách các liên hệ thuộc về một nhóm nhất định
vector<Contact> GroupService::getContactsForGroup(int groupId)
{
    vector<Contact> result;
    const auto& contacts = ContactService::getContacts();

    for (const ContactGroup& relation : contactGroups)
    {
        if (relation.groupId != groupId)
            continue;

        for (const Contact& contact : contacts)
        {
            if (contact.id == relation.contactId)
            {
                result.push_back(contact);
                break;
            }
        }
    }

    return result;
}

// Lấy toàn bộ danh sách nhóm trong bộ nhớ
const vector<Group>& GroupService::getGroups()
{
    return groups;
}

// Tải danh sách nhóm và các phân nhóm của một tài khoản từ CSDL
void GroupService::loadForAccount(int accountId)
{
    currentAccountId = accountId;
    groups = db.loadGroups(accountId);
    contactGroups = db.loadContactGroups(accountId);

    vector<ContactGroup> normalizedRelations;
    for (const ContactGroup& relation : contactGroups)
    {
        bool validContact = ContactService::exists(relation.contactId);
        bool validGroup = false;
        for (const Group& group : groups)
        {
            if (group.id == relation.groupId)
            {
                validGroup = true;
                break;
            }
        }

        bool duplicate = false;
        for (const ContactGroup& existing : normalizedRelations)
        {
            if (existing.contactId == relation.contactId)
            {
                duplicate = true;
                break;
            }
        }

        if (validContact && validGroup && !duplicate)
            normalizedRelations.push_back(relation);
    }
    contactGroups = normalizedRelations;

    for (const Contact& contact : ContactService::getContacts())
    {
        int membershipGroupId = 0;
        for (const ContactGroup& relation : contactGroups)
        {
            if (relation.contactId == contact.id)
            {
                membershipGroupId = relation.groupId;
                break;
            }
        }

        if (membershipGroupId == 0 && contact.group_id != 0)
        {
            bool validGroup = false;
            for (const Group& group : groups)
            {
                if (group.id == contact.group_id)
                {
                    validGroup = true;
                    break;
                }
            }
            if (validGroup)
            {
                ContactGroup relation{contact.id, contact.group_id};
                if (db.saveContactGroup(currentAccountId, relation))
                    contactGroups.push_back(relation);
            }
        }
        else if (membershipGroupId != 0 && contact.group_id != membershipGroupId)
        {
            Contact updated = contact;
            updated.group_id = membershipGroupId;
            ContactService::updateContact(updated);
        }
    }

    nextId = 1;
    for (const Group& group : groups)
        if (group.id >= nextId) nextId = group.id + 1;
}

// Xóa sạch bộ nhớ tạm của danh sách nhóm
void GroupService::clear()
{
    groups.clear();
    contactGroups.clear();
    currentAccountId = 0;
    nextId = 1;
}

// Cập nhật thông tin nhóm và đồng bộ CSDL
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

// Xóa nhóm và các liên kết liên hệ của nhóm đó
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

    for (const Contact& contact : ContactService::getContacts())
    {
        if (contact.group_id == groupId)
        {
            Contact updated = contact;
            updated.group_id = 0;
            ContactService::updateContact(updated);
        }
    }

    return true;
}