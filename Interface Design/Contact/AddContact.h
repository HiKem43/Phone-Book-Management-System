<<<<<<< HEAD
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
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void clearFields();
    void saveContact();

public:
    AddContact();

    bool show();
};

=======
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

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif