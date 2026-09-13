#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include "AccountService.h"

/**
 * @class MenuUI
 * @brief Lớp Điều khiển Giao diện Người dùng trên Windows (Win32 API GUI).
 * Quản lý vẽ các cửa sổ, các ô nhập liệu, nút bấm, chuyển đổi màn hình và bắt sự kiện từ người dùng.
 */
class MenuUI
{
private:
    // --- QUẢN LÝ TÀI NGUYÊN GIAO DIỆN & PHÔNG CHỮ ---
    HWND hWnd;                 // Handle cửa sổ chính
    HFONT hTitleFont;          // Font tiêu đề lớn
    HFONT hSubtitleFont;       // Font tiêu đề phụ
    HFONT hNormalFont;         // Font chữ mặc định
    HFONT hButtonFont;         // Font nút bấm
    HFONT hSmallFont;          // Font chữ nhỏ (chú thích)
    HFONT hIconFont;           // Font hiển thị Biểu tượng (Icons)

    // --- TRẠNG THÁI HIỆN TẠI CỦA ỨNG DỤNG ---
    std::string currentScreen;     // Màn hình đang mở (vd: "LOGIN", "CONTACTS", "ADMIN")
    std::string previousScreen;    // Màn hình trước đó (dùng cho nút Back)
    std::string currentRole;       // Vai trò người dùng hiện tại ("Admin" / "User")
    int selectedContactId;         // ID danh bạ đang được chọn trên GUI
    int selectedGroupId;           // ID nhóm đang được chọn trên GUI
    int selectedAccountId;         // ID tài khoản đang được chọn (Admin View)
    
    std::vector<HWND> screenControls; // Danh sách quản lý các Nút, Textbox... của màn hình hiện tại (dùng để xóa khi đổi màn hình)
    AccountService accountService;   // Dịch vụ xác thực tài khoản kết nối trực tiếp vào UI

    /**
     * @brief Hàm lắng nghe & xử lý thông điệp hệ thống của Windows (Window Procedure).
     */
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // --- CÁC THAO TÁC CƠ BẢN QUẢN LÝ MÀN HÌNH ---
    void createFonts();                                 // Khởi tạo các phông chữ GUI
    void clearScreen();                                 // Xóa sạch các Widget/Control cũ trên cửa sổ
    void showScreen(const std::string& screen);         // Điều hướng vẽ màn hình theo tên

    // --- MÀN HÌNH ĐĂNG NHẬP / XÁC THỰC ---
    void showLogin();
    void showRegister();
    void showForgotPassword();
    void showAccount();
    void showChangePassword();

    // --- MÀN HÌNH CHỨC NĂNG DÀNH CHO USER ---
    void showUserMenu();
    void showContacts();
    void showAddContact();
    void showEditContact();
    void showDeleteContact();
    void showContactDetail();
    void showSearchContacts();
    void showGroups();
    void showAddGroup();
    void showEditGroup();
    void showDeleteGroup();
    void showGroupDetail();
    void showAssignContact();
    void showFavorites();

    // --- MÀN HÌNH CHỨC NĂNG DÀNH CHO ADMIN ---
    void showAdminMenu();
    void showUserManagement();
    void showAddUser();
    void showEditUser();
    void showDeleteUser();
    void showSystemReports();
    void showBackup();
    void showRecovery();

    // --- HÀM HỖ TRỢ VẼ CÁC WIDGET / COMPONENT ---
    void createLabel(const char* text, int x, int y, int w, int h, bool title = false);
    HWND createButton(const char* text, int x, int y, int w, int h, int id);
    HWND createIconButton(const wchar_t* text, int x, int y, int w, int h, int id);
    HWND createEdit(const char* text, int x, int y, int w, int h, int id, bool password = false);
    HWND createList(int x, int y, int w, int h, int id);
    HWND createCombo(const char* text, int x, int y, int w, int h, int id);

    // --- THÀNH PHẦN BỐ TRÍ DÙNG CHUNG (LAYOUT HELPER) ---
    void createBackButton(int id = 900);
    void createHeader(const char* title, const char* subtitle = nullptr);
    void createRoleBadge(const char* role);

    // --- HÀM XỬ LÝ SỰ KIỆN NÚT BẤM (EVENT HANDLERS) ---
    void handleCommand(int id);                         // Xử lý khi bấm nút bất kỳ
    void handleLogin();                                 // Xử lý sự kiện bấm nút Đăng nhập
    void handleClose();                                 // Xử lý đóng ứng dụng
    void handleLogout();                                // Xử lý sự kiện Đăng xuất

public:
    MenuUI();
    ~MenuUI();

    /**
     * @brief Vòng lặp chính khởi chạy ứng dụng GUI.
     */
    int run();
};