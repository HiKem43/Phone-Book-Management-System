#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include "AccountService.h"

// Lớp giao diện chính của hệ thống.
class MenuUI
{
private:
    // Các thành phần và trạng thái của giao diện.
    HWND hWnd;
    HFONT hTitleFont;
    HFONT hSubtitleFont;
    HFONT hNormalFont;
    HFONT hButtonFont;
    HFONT hSmallFont;
    HFONT hIconFont;

    std::string currentScreen;
    std::string previousScreen;
    std::string currentRole;
    std::vector<HWND> screenControls;
    AccountService accountService;

    // Xử lý sự kiện của cửa sổ.
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Các hàm khởi tạo và chuyển đổi giao diện.
    void createFonts();
    void clearScreen();
    void showScreen(const std::string& screen);

    // Các giao diện đăng nhập và tài khoản.
    void showLogin();
    void showRegister();
    void showForgotPassword();
    void showAccount();
    void showChangePassword();

    // Các giao diện dành cho User.
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

    // Các giao diện dành cho Admin.
    void showAdminMenu();
    void showUserManagement();
    void showAddUser();
    void showEditUser();
    void showDeleteUser();
    void showSystemReports();
    void showBackup();
    void showRecovery();

    // Các hàm tạo thành phần giao diện.
    void createLabel(const char* text, int x, int y, int w, int h, bool title = false);
    HWND createButton(const char* text, int x, int y, int w, int h, int id);
    HWND createIconButton(const wchar_t* text, int x, int y, int w, int h, int id);
    HWND createEdit(const char* text, int x, int y, int w, int h, int id, bool password = false);
    HWND createList(int x, int y, int w, int h, int id);
    HWND createCombo(const char* text, int x, int y, int w, int h, int id);

    // Các thành phần dùng chung giữa các màn hình.
    void createBackButton(int id = 900);
    void createHeader(const char* title, const char* subtitle = nullptr);
    void createRoleBadge(const char* role);

    // Xử lý các thao tác của người dùng.
    void handleCommand(int id);
    void handleLogin();
    void handleClose();
    void handleLogout();

public:
    // Khởi tạo và hủy giao diện.
    MenuUI();
    ~MenuUI();

    // Chạy chương trình.
    int run();
};
