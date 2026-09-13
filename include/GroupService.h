#pragma once
#include <string>
#include <vector>
#include "Contact.h"
#include "Group.h"

using namespace std;

/**
 * @class GroupService
 * @brief Lớp Quản lý Nghiệp vụ Nhóm Danh Bạ (Ph thêm nhóm, xóa nhóm, gán người vào nhóm).
 */
class GroupService
{
private:
    static vector<Group> groups;                // Danh sách các nhóm hiện tại trong RAM
    static vector<ContactGroup> contactGroups;  // Danh sách các liên kết (Contact - Group) trong RAM
    static int nextId;                          // ID tự tăng dùng tạo nhóm mới
    static int currentAccountId;                // ID tài khoản đang sử dụng

    static string inputRequired(string message);

public:
    static void run();                          // Điều hướng menu điều khiển trên Console

    // --- THAO TÁC QUẢN LÝ NHÓM ---
    static void addGroup();
    static void addGroup(const Group& group);
    static void viewGroups();
    static void searchGroup();
    static void editGroup();
    static void deleteGroup();

    // --- GÁN VÀ LỌC DANH BẠ THEO NHÓM ---
    static void assignContact();                                      // Gán người liên hệ vào nhóm (Console UI)
    static bool assignContact(int contactId, int groupId);            // Thêm liên kết Contact - Group
    static bool setContactGroup(int contactId, int groupId);          // Cập nhật/thay đổi nhóm của một Contact
    static std::vector<Contact> getContactsForGroup(int groupId);     // Lấy tất cả người liên hệ thuộc 1 nhóm cụ thể

    // --- BỘ TRUY XUẤT DỮ LIỆU ---
    static const vector<Group>& getGroups();                          // Lấy toàn bộ danh sách nhóm
    static void loadForAccount(int accountId);                        // Đọc danh sách nhóm theo tài khoản từ CSDL
    static void clear();                                              // Xóa dữ liệu tạm trong RAM
    static bool updateGroup(const Group& group);                      // Lưu chỉnh sửa nhóm vào CSDL
    static bool removeGroup(int groupId);                             // Xóa nhóm khỏi CSDL
};