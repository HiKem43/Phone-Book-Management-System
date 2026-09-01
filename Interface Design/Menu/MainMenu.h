#ifndef MAINMENU_H
#define MAINMENU_H

#include <windows.h>

class MainMenu
{
private:
    HWND hWnd;

    HWND hCategoryTree;
    HWND hContentTitle;
    HWND hContentText;

    HWND hContactsButton;
    HWND hGroupsButton;
    HWND hFavoritesButton;
    HWND hAccountButton;
    HWND hRegisterButton;
    HWND hAboutButton;
    HWND hLogoutButton;
    HWND hCloseButton;

    bool isLoggedIn;
    bool isAdmin;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void showWelcome();
    void showContacts();
    void showGroups();
    void showFavorites();
    void showAccount();
    void showRegister();
    void showAbout();
    void logout();

public:
    MainMenu();

    void setLoginStatus(bool loggedIn);
    void setAdmin(bool admin);

    void show();
};

#endif