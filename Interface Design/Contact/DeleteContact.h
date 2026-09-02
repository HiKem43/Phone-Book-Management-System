<<<<<<< HEAD
#ifndef DELETECONTACT_H
#define DELETECONTACT_H

#include <windows.h>

class DeleteContact
{
private:
    HWND hWnd;

    HWND hMessage;
    HWND hConfirmButton;
    HWND hCancelButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void handleConfirm();

public:
    DeleteContact();

    bool show();
};

=======
#ifndef DELETECONTACT_H
#define DELETECONTACT_H

#include <windows.h>

class DeleteContact
{
private:
    HWND hWnd;

    HWND hMessage;
    HWND hConfirmButton;
    HWND hCancelButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void handleConfirm();

public:
    DeleteContact();

    bool show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif