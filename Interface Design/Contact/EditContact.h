<<<<<<< HEAD
#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <windows.h>

class EditContact
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

    HWND hTree;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void saveContact();
    void clearFields();

public:
    EditContact();

    bool show();
};

=======
#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <windows.h>

class EditContact
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

    HWND hTree;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void saveContact();
    void clearFields();

public:
    EditContact();

    bool show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif