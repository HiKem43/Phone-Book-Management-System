<<<<<<< HEAD
#ifndef LOGIN_H
#define LOGIN_H

#include <windows.h>
#include <commctrl.h>

class Login
{
private:
    HWND hWnd;

    // TreeView
    HWND hTree;

    // Login controls
    HWND hUsername;
    HWND hPassword;

    HWND hLoginButton;
    HWND hClearButton;
    HWND hRegisterButton;
    HWND hCancelButton;

    // Fonts
    HFONT hFont;
    HFONT hTitleFont;
    HFONT hButtonFont;

    void createControls(HWND hwnd);
    void clearFields();
    void handleLogin();

    void showMessage(const wchar_t* message,
                     const wchar_t* title,
                     UINT type = MB_OK);

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

public:
    Login();

    bool show();
};

=======
#ifndef LOGIN_H
#define LOGIN_H

#include <windows.h>
#include <commctrl.h>

class Login
{
private:
    HWND hWnd;

    // TreeView
    HWND hTree;

    // Login controls
    HWND hUsername;
    HWND hPassword;

    HWND hLoginButton;
    HWND hClearButton;
    HWND hRegisterButton;
    HWND hCancelButton;

    // Fonts
    HFONT hFont;
    HFONT hTitleFont;
    HFONT hButtonFont;

    void createControls(HWND hwnd);
    void clearFields();
    void handleLogin();

    void showMessage(const wchar_t* message,
                     const wchar_t* title,
                     UINT type = MB_OK);

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

public:
    Login();

    bool show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif