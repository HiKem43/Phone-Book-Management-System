<<<<<<< HEAD
#ifndef UPDATEACCOUNT_H
#define UPDATEACCOUNT_H

#include <windows.h>

class UpdateAccount
{
private:
    HWND hWnd;

    HWND hUsername;
    HWND hPassword;
    HWND hFullName;
    HWND hEmail;
    HWND hPhone;

    HWND hUpdateButton;
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
    void updateAccount();

public:
    UpdateAccount();

    bool show();
};

=======
#ifndef UPDATEACCOUNT_H
#define UPDATEACCOUNT_H

#include <windows.h>

class UpdateAccount
{
private:
    HWND hWnd;

    HWND hUsername;
    HWND hPassword;
    HWND hFullName;
    HWND hEmail;
    HWND hPhone;

    HWND hUpdateButton;
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
    void updateAccount();

public:
    UpdateAccount();

    bool show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif