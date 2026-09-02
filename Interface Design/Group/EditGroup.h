<<<<<<< HEAD
#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <windows.h>

class EditGroup
{
private:
    HWND hWnd;

    HWND hGroupId;
    HWND hGroupName;
    HWND hDescription;

    HWND hUpdateButton;
    HWND hCancelButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void updateGroup();

public:
    EditGroup();

    void show();
};

=======
#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <windows.h>

class EditGroup
{
private:
    HWND hWnd;

    HWND hGroupId;
    HWND hGroupName;
    HWND hDescription;

    HWND hUpdateButton;
    HWND hCancelButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void updateGroup();

public:
    EditGroup();

    void show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif