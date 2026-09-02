<<<<<<< HEAD
#include "GroupMenu.h"
#include "AddGroup.h"
#include "EditGroup.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_GROUP_LIST       3001
#define ID_ADD_GROUP        3002
#define ID_EDIT_GROUP       3003
#define ID_DELETE_GROUP     3004
#define ID_CLOSE_GROUP      3005

// =====================================================
// CONSTRUCTOR
// =====================================================

GroupMenu::GroupMenu()
{
    hWnd = NULL;
    hGroupList = NULL;

    hAddButton = NULL;
    hEditButton = NULL;
    hDeleteButton = NULL;
    hCloseButton = NULL;
}

// =====================================================
// GET SELECTED INDEX
// =====================================================

int GroupMenu::getSelectedIndex()
{
    if (hGroupList == NULL)
        return -1;

    return static_cast<int>(
        SendMessageW(
            hGroupList,
            LB_GETCURSEL,
            0,
            0
        )
    );
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void GroupMenu::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group Management",
        WS_CHILD | WS_VISIBLE,
        20,
        20,
        500,
        35,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // GROUP LIST LABEL
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group List",
        WS_CHILD | WS_VISIBLE,
        20,
        70,
        150,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // GROUP LIST
    // =================================================

    hGroupList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"LISTBOX",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        WS_VSCROLL |
        LBS_NOTIFY |
        LBS_NOINTEGRALHEIGHT,
        20,
        100,
        500,
        300,
        hwnd,
        (HMENU)ID_GROUP_LIST,
        NULL,
        NULL
    );

    // =================================================
    // NOTE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"No groups loaded.",
        WS_CHILD | WS_VISIBLE,
        20,
        410,
        300,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // ADD
    // =================================================

    hAddButton = CreateWindowW(
        L"BUTTON",
        L"Add",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_ADD_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // EDIT
    // =================================================

    hEditButton = CreateWindowW(
        L"BUTTON",
        L"Edit",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        135,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_EDIT_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // DELETE
    // =================================================

    hDeleteButton = CreateWindowW(
        L"BUTTON",
        L"Delete",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        250,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_DELETE_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // CLOSE
    // =================================================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        420,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_CLOSE_GROUP,
        NULL,
        NULL
    );
}

// =====================================================
// ADD GROUP
// =====================================================

void GroupMenu::addGroup()
{
    AddGroup addGroup;
    addGroup.show();
}

// =====================================================
// EDIT GROUP
// =====================================================

void GroupMenu::editGroup()
{
    int selectedIndex = getSelectedIndex();

    if (selectedIndex == LB_ERR || selectedIndex < 0)
    {
        MessageBoxW(
            hWnd,
            L"Please select a group first.",
            L"Edit Group",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    EditGroup editGroup;
    editGroup.show();
}

// =====================================================
// DELETE GROUP
// =====================================================

void GroupMenu::deleteGroup()
{
    int selectedIndex = getSelectedIndex();

    if (selectedIndex == LB_ERR || selectedIndex < 0)
    {
        MessageBoxW(
            hWnd,
            L"Please select a group first.",
            L"Delete Group",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    int result = MessageBoxW(
        hWnd,
        L"Are you sure you want to delete this group?",
        L"Confirm Delete",
        MB_YESNO | MB_ICONQUESTION
    );

    if (result == IDYES)
    {
        // ---------------------------------------------
        // UI ONLY
        // Database integration will be added later.
        // ---------------------------------------------

        MessageBoxW(
            hWnd,
            L"Delete request received.",
            L"Delete Group",
            MB_OK | MB_ICONINFORMATION
        );
    }
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK GroupMenu::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    GroupMenu* groupMenu =
        reinterpret_cast<GroupMenu*>(
            GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )
        );

    switch (uMsg)
    {
    case WM_NCCREATE:
    {
        CREATESTRUCTW* createStruct =
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        groupMenu =
            reinterpret_cast<GroupMenu*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(groupMenu)
        );

        if (groupMenu != NULL)
        {
            groupMenu->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (groupMenu == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_ADD_GROUP:
            groupMenu->addGroup();
            return 0;

        case ID_EDIT_GROUP:
            groupMenu->editGroup();
            return 0;

        case ID_DELETE_GROUP:
            groupMenu->deleteGroup();
            return 0;

        case ID_CLOSE_GROUP:
            DestroyWindow(hwnd);
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        if (groupMenu != NULL)
        {
            groupMenu->hWnd = NULL;
        }

        return 0;
    }

    return DefWindowProcW(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}

// =====================================================
// SHOW GROUP MENU
// =====================================================

void GroupMenu::show()
{
    const wchar_t CLASS_NAME[] =
        L"PhoneBook_GroupMenu_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = GroupMenu::WindowProc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management - Group Management",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        580,
        550,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Group Management window.",
            L"Error",
            MB_OK | MB_ICONERROR
        );

        return;
    }

    createControls(hwnd);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;

    while (IsWindow(hwnd) &&
           GetMessageW(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
=======
#include "GroupMenu.h"
#include "AddGroup.h"
#include "EditGroup.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_GROUP_LIST       3001
#define ID_ADD_GROUP        3002
#define ID_EDIT_GROUP       3003
#define ID_DELETE_GROUP     3004
#define ID_CLOSE_GROUP      3005

// =====================================================
// CONSTRUCTOR
// =====================================================

GroupMenu::GroupMenu()
{
    hWnd = NULL;
    hGroupList = NULL;

    hAddButton = NULL;
    hEditButton = NULL;
    hDeleteButton = NULL;
    hCloseButton = NULL;
}

// =====================================================
// GET SELECTED INDEX
// =====================================================

int GroupMenu::getSelectedIndex()
{
    if (hGroupList == NULL)
        return -1;

    return static_cast<int>(
        SendMessageW(
            hGroupList,
            LB_GETCURSEL,
            0,
            0
        )
    );
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void GroupMenu::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group Management",
        WS_CHILD | WS_VISIBLE,
        20,
        20,
        500,
        35,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // GROUP LIST LABEL
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group List",
        WS_CHILD | WS_VISIBLE,
        20,
        70,
        150,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // GROUP LIST
    // =================================================

    hGroupList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"LISTBOX",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        WS_VSCROLL |
        LBS_NOTIFY |
        LBS_NOINTEGRALHEIGHT,
        20,
        100,
        500,
        300,
        hwnd,
        (HMENU)ID_GROUP_LIST,
        NULL,
        NULL
    );

    // =================================================
    // NOTE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"No groups loaded.",
        WS_CHILD | WS_VISIBLE,
        20,
        410,
        300,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // ADD
    // =================================================

    hAddButton = CreateWindowW(
        L"BUTTON",
        L"Add",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_ADD_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // EDIT
    // =================================================

    hEditButton = CreateWindowW(
        L"BUTTON",
        L"Edit",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        135,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_EDIT_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // DELETE
    // =================================================

    hDeleteButton = CreateWindowW(
        L"BUTTON",
        L"Delete",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        250,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_DELETE_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // CLOSE
    // =================================================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        420,
        450,
        100,
        35,
        hwnd,
        (HMENU)ID_CLOSE_GROUP,
        NULL,
        NULL
    );
}

// =====================================================
// ADD GROUP
// =====================================================

void GroupMenu::addGroup()
{
    AddGroup addGroup;
    addGroup.show();
}

// =====================================================
// EDIT GROUP
// =====================================================

void GroupMenu::editGroup()
{
    int selectedIndex = getSelectedIndex();

    if (selectedIndex == LB_ERR || selectedIndex < 0)
    {
        MessageBoxW(
            hWnd,
            L"Please select a group first.",
            L"Edit Group",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    EditGroup editGroup;
    editGroup.show();
}

// =====================================================
// DELETE GROUP
// =====================================================

void GroupMenu::deleteGroup()
{
    int selectedIndex = getSelectedIndex();

    if (selectedIndex == LB_ERR || selectedIndex < 0)
    {
        MessageBoxW(
            hWnd,
            L"Please select a group first.",
            L"Delete Group",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    int result = MessageBoxW(
        hWnd,
        L"Are you sure you want to delete this group?",
        L"Confirm Delete",
        MB_YESNO | MB_ICONQUESTION
    );

    if (result == IDYES)
    {
        // ---------------------------------------------
        // UI ONLY
        // Database integration will be added later.
        // ---------------------------------------------

        MessageBoxW(
            hWnd,
            L"Delete request received.",
            L"Delete Group",
            MB_OK | MB_ICONINFORMATION
        );
    }
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK GroupMenu::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    GroupMenu* groupMenu =
        reinterpret_cast<GroupMenu*>(
            GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )
        );

    switch (uMsg)
    {
    case WM_NCCREATE:
    {
        CREATESTRUCTW* createStruct =
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        groupMenu =
            reinterpret_cast<GroupMenu*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(groupMenu)
        );

        if (groupMenu != NULL)
        {
            groupMenu->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (groupMenu == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_ADD_GROUP:
            groupMenu->addGroup();
            return 0;

        case ID_EDIT_GROUP:
            groupMenu->editGroup();
            return 0;

        case ID_DELETE_GROUP:
            groupMenu->deleteGroup();
            return 0;

        case ID_CLOSE_GROUP:
            DestroyWindow(hwnd);
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        if (groupMenu != NULL)
        {
            groupMenu->hWnd = NULL;
        }

        return 0;
    }

    return DefWindowProcW(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}

// =====================================================
// SHOW GROUP MENU
// =====================================================

void GroupMenu::show()
{
    const wchar_t CLASS_NAME[] =
        L"PhoneBook_GroupMenu_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = GroupMenu::WindowProc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management - Group Management",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        580,
        550,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Group Management window.",
            L"Error",
            MB_OK | MB_ICONERROR
        );

        return;
    }

    createControls(hwnd);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;

    while (IsWindow(hwnd) &&
           GetMessageW(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
}