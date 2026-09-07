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

#endif