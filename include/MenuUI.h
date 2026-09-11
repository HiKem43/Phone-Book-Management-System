#pragma once

#include <windows.h>
#include <string>
#include <vector>

class MenuUI
{
private:
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

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void createFonts();
    void clearScreen();
    void showScreen(const std::string& screen);

    void showLogin();
    void showRegister();
    void showUserMenu();
    void showAdminMenu();
    void showUsers();
    void showReports();
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
    void showAccount();
    void showChangePassword();
    void showUserManagement();
    void showAddUser();
    void showEditUser();
    void showDeleteUser();
    void showSystemReports();
    void showBackup();
    void showRecovery();
    void showForgotPassword();

    void createLabel(const char* text, int x, int y, int w, int h, bool title = false);
    HWND createButton(const char* text, int x, int y, int w, int h, int id);
    HWND createIconButton(const wchar_t* text, int x, int y, int w, int h, int id);
    HWND createEdit(const char* text, int x, int y, int w, int h, int id, bool password = false);
    HWND createList(int x, int y, int w, int h, int id);
    HWND createCombo(const char* text, int x, int y, int w, int h, int id);
    void createBackButton(int id = 900);
    void createHeader(const char* title, const char* subtitle = nullptr);
    void createRoleBadge(const char* role);

    void handleCommand(int id);
    void handleLogin();
    void handleClose();
    void handleLogout();

public:
    MenuUI();
    ~MenuUI();
    int run();
};
