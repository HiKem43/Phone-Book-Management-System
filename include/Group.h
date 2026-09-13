#pragma once
#include <string>
using namespace std;

/**
 * @struct Group
 * @brief Lớp Mô hình (Model) cho Nhóm liên hệ (vd: Gia đình, Đồng nghiệp, Bạn bè).
 */
struct Group
{
    int id;                 // ID duy nhất của Nhóm
    int account_id;         // ID tài khoản tạo nhóm này
    string name;            // Tên nhóm danh bạ
    string description;     // Mô tả ngắn về nhóm

    // Constructors
    Group();
    Group(int group_id, int account_id,
        string groupName, string description);

    // Getters & Setters
    int getGroupId() const;
    int getAccountId() const;
    string getGroupName() const;
    string getDescription() const;
    void setGroupId(int group_id);
    void setAccountId(int account_id);
    void setGroupName(string groupName);
    void setDescription(string description);
};

/**
 * @struct ContactGroup
 * @brief Cấu trúc biểu diễn mối quan hệ Nhiều - Nhiều (Many-to-Many) giữa Contact và Group.
 */
struct ContactGroup
{
    int contactId; // ID danh bạ
    int groupId;   // ID nhóm
};