#include "Group.h"
using namespace std;

// =====================================================
// KHỞI TẠO (CONSTRUCTORS)
// =====================================================

// Constructor mặc định - Khởi tạo giá trị ban đầu cho nhóm
Group::Group()
{
    id = 0;
    account_id = 0;
    name = "";
    description = "";
}

// Constructor đầy đủ tham số - Khởi tạo nhóm với thông tin chi tiết
Group::Group(int group_id, int account_id,
    string groupName, string description)
{
    this->id = group_id;
    this->account_id = account_id;
    this->name = groupName;
    this->description = description;
}

// =====================================================
// CÁC HÀM LẤY THÔNG TIN (GETTERS)
// =====================================================

// Lấy ID nhóm
int Group::getGroupId() const
{
    return id;
}

// Lấy ID tài khoản sở hữu nhóm
int Group::getAccountId() const
{
    return account_id;
}

// Lấy tên nhóm
string Group::getGroupName() const
{
    return name;
}

// Lấy mô tả nhóm
string Group::getDescription() const
{
    return description;
}

// =====================================================
// CÁC HÀM CẬP NHẬT THÔNG TIN (SETTERS)
// =====================================================

// Cập nhật ID nhóm
void Group::setGroupId(int group_id)
{
    this->id = group_id;
}

// Cập nhật ID tài khoản sở hữu
void Group::setAccountId(int account_id)
{
    this->account_id = account_id;
}

// Cập nhật tên nhóm
void Group::setGroupName(string groupName)
{
    this->name = groupName;
}

// Cập nhật mô tả nhóm
void Group::setDescription(string description)
{
    this->description = description;
}