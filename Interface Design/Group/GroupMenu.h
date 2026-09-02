<<<<<<< HEAD
#ifndef GROUPMENU_H
#define GROUPMENU_H

#include <windows.h>

class GroupMenu
{
private:
    HWND hWnd;
    HWND hGroupList;

    HWND hAddButton;
    HWND hEditButton;
    HWND hDeleteButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void addGroup();
    void editGroup();
    void deleteGroup();

    int getSelectedIndex();

public:
    GroupMenu();

    void show();
};

=======
#ifndef GROUPMENU_H
#define GROUPMENU_H

#include <windows.h>

class GroupMenu
{
private:
    HWND hWnd;
    HWND hGroupList;

    HWND hAddButton;
    HWND hEditButton;
    HWND hDeleteButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void addGroup();
    void editGroup();
    void deleteGroup();

    int getSelectedIndex();

public:
    GroupMenu();

    void show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif