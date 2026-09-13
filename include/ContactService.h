#pragma once
#include <string>
#include <vector>
#include "Contact.h"

using namespace std;

/**
 * @class ContactService
 * @brief Lớp Quản lý Nghiệp vụ Danh bạ.
 * Thực hiện các chức năng CRUD (Thêm, Xem, Sửa, Xóa), tìm kiếm, sắp xếp và lọc danh bạ.
 * Tất cả các phương thức đều là static để dùng làm phiên xử lý duy nhất trong ứng dụng.
 */
class ContactService
{
private:
    static vector<Contact> contacts;     // Bộ nhớ đệm (Cache) lưu danh sách danh bạ của tài khoản hiện tại
    static int nextId;                   // ID tự tăng dùng khi tạo mới người liên hệ
    static int currentAccountId;         // ID tài khoản người dùng đang đăng nhập

    // Hàm hỗ trợ nhập dữ liệu và kiểm tra tính hợp lệ nội bộ
    static string inputRequired(string message);
    static bool validPhone(string phone);
    static bool validEmail(string email);

public:
    // Chạy menu điều hướng dịch vụ danh bạ (dành cho bản Console UI)
    static void run();

    // --- CÁC THAO TÁC CƠ BẢN (CRUD) ---
    static void addContact();                             // Hàm nhập liệu thêm từ màn hình console
    static bool addContact(const Contact& contact);       // Hàm thêm trực tiếp đối tượng Contact
    static const vector<Contact>& getContacts();          // Lấy toàn bộ danh sách liên hệ đang lưu trong bộ nhớ
    static void viewContacts();                           // Hiển thị danh sách ra màn hình
    static void searchContact();                          // Tìm kiếm người liên hệ theo tên/sĐT
    static void editContact();                            // Sửa thông tin qua Console UI
    static void deleteContact();                          // Xóa người liên hệ qua Console UI

    // --- CÁC HÀM BẬC CAO TRUY XUẤT NGHỆP VỤ ---
    static bool exists(int contactId);                     // Kiểm tra ID danh bạ có tồn tại không
    static void loadForAccount(int accountId);            // Tải toàn bộ danh bạ từ CSDL lên bộ nhớ cho tài khoản cụ thể
    static void clear();                                  // Xóa sạch bộ nhớ đệm danh bạ (dùng khi Đăng xuất)
    static void toggleFavorite(int contactId);             // Bật/Tắt trạng thái Yêu thích (Favorite)
    static bool updateContact(const Contact& contact);    // Cập nhật thông tin danh bạ xuống CSDL
    static bool removeContact(int contactId);             // Xóa danh bạ theo ID khỏi CSDL
    static void sortByName();                             // Sắp xếp danh sách danh bạ theo Tên (A-Z)
};