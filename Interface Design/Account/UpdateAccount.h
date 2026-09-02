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

#endif