#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include <windows.h>

class AddContact
{
private:
    HWND hWnd;

    HWND hName;
    HWND hPhone;
    HWND hEmail;
    HWND hAddress;
    HWND hGroup;
    HWND hFavorite;

    HWND hSaveButton;
    HWND hCancelButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);

    void saveContact();
    void cancel();

public:
    AddContact();

    void show();
};

#endif