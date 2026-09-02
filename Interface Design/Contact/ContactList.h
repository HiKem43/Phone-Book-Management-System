<<<<<<< HEAD
#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <windows.h>

class ContactList
{
private:
    HWND hWnd;

    HWND hTree;
    HWND hList;

    HWND hViewButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void loadSampleContacts();

public:
    ContactList();

    bool show();
};

=======
#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <windows.h>

class ContactList
{
private:
    HWND hWnd;

    HWND hTree;
    HWND hList;

    HWND hViewButton;
    HWND hCloseButton;

    static LRESULT CALLBACK WindowProc(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    );

    void createControls(HWND hwnd);
    void loadSampleContacts();

public:
    ContactList();

    bool show();
};

>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
#endif