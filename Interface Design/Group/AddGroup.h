#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <windows.h>

class AddGroup
{
private:
    HWND hWnd;

    HWND hGroupName;
    HWND hDescription;

    HWND hSaveButton;
    HWND hCancelButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void saveGroup();

public:
    AddGroup();

    void show();
};

#endif