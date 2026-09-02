<<<<<<< HEAD
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

=======
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

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif