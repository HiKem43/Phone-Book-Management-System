<<<<<<< HEAD
#ifndef REGISTER_H
#define REGISTER_H

#include <windows.h>

class Register
{
private:
    HWND hWnd;

    HWND hUsername;
    HWND hPassword;
    HWND hFullName;
    HWND hEmail;
    HWND hPhone;

    HWND hRegisterButton;
    HWND hClearButton;
    HWND hCancelButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void clearFields();
    void registerAccount();

public:
    Register();

    bool show();
};

=======
#ifndef REGISTER_H
#define REGISTER_H

#include <windows.h>

class Register
{
private:
    HWND hWnd;

    HWND hUsername;
    HWND hPassword;
    HWND hFullName;
    HWND hEmail;
    HWND hPhone;

    HWND hRegisterButton;
    HWND hClearButton;
    HWND hCancelButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void clearFields();
    void registerAccount();

public:
    Register();

    bool show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif