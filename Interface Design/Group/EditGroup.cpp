<<<<<<< HEAD
#include "EditGroup.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_EDIT_GROUP_ID        3201
#define ID_EDIT_GROUP_NAME      3202
#define ID_EDIT_DESCRIPTION     3203
#define ID_UPDATE_GROUP         3204
#define ID_CANCEL_EDIT_GROUP    3205

// =====================================================
// CONSTRUCTOR
// =====================================================

EditGroup::EditGroup()
{
    hWnd = NULL;

    hGroupId = NULL;
    hGroupName = NULL;
    hDescription = NULL;

    hUpdateButton = NULL;
    hCancelButton = NULL;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void EditGroup::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Edit Group",
        WS_CHILD | WS_VISIBLE,
        20,
        20,
        400,
        30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // GROUP ID
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group ID:",
        WS_CHILD | WS_VISIBLE,
        20,
        70,
        120,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hGroupId = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL |
        ES_READONLY,
        150,
        67,
        300,
        28,
        hwnd,
        (HMENU)ID_EDIT_GROUP_ID,
        NULL,
        NULL
    );

    // =================================================
    // GROUP NAME
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group Name:",
        WS_CHILD | WS_VISIBLE,
        20,
        115,
        120,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hGroupName = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        150,
        112,
        300,
        28,
        hwnd,
        (HMENU)ID_EDIT_GROUP_NAME,
        NULL,
        NULL
    );

    // =================================================
    // DESCRIPTION
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Description:",
        WS_CHILD | WS_VISIBLE,
        20,
        160,
        120,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hDescription = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_MULTILINE |
        ES_AUTOVSCROLL |
        WS_VSCROLL,
        150,
        157,
        300,
        100,
        hwnd,
        (HMENU)ID_EDIT_DESCRIPTION,
        NULL,
        NULL
    );

    // =================================================
    // UPDATE
    // =================================================

    hUpdateButton = CreateWindowW(
        L"BUTTON",
        L"Update",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        150,
        285,
        100,
        35,
        hwnd,
        (HMENU)ID_UPDATE_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // CANCEL
    // =================================================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        270,
        285,
        100,
        35,
        hwnd,
        (HMENU)ID_CANCEL_EDIT_GROUP,
        NULL,
        NULL
    );
}

// =====================================================
// UPDATE GROUP
// =====================================================

void EditGroup::updateGroup()
{
    wchar_t groupName[101] = {};
    wchar_t description[256] = {};

    GetWindowTextW(
        hGroupName,
        groupName,
        101
    );

    GetWindowTextW(
        hDescription,
        description,
        256
    );

    // =================================================
    // VALIDATION
    // =================================================

    if (wcslen(groupName) == 0)
    {
        MessageBoxW(
            hWnd,
            L"Group Name is required.",
            L"Invalid Data",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hGroupName);

        return;
    }

    // =================================================
    // UI ONLY
    // =================================================

    MessageBoxW(
        hWnd,
        L"Group information is valid.",
        L"Edit Group",
        MB_OK | MB_ICONINFORMATION
    );

    // Database update will be integrated later.
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK EditGroup::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    EditGroup* editGroup =
        reinterpret_cast<EditGroup*>(
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

        editGroup =
            reinterpret_cast<EditGroup*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(editGroup)
        );

        if (editGroup != NULL)
        {
            editGroup->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (editGroup == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_UPDATE_GROUP:
            editGroup->updateGroup();
            return 0;

        case ID_CANCEL_EDIT_GROUP:
            DestroyWindow(hwnd);
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        if (editGroup != NULL)
        {
            editGroup->hWnd = NULL;
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
// SHOW
// =====================================================

void EditGroup::show()
{
    const wchar_t CLASS_NAME[] =
        L"PhoneBook_EditGroup_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = EditGroup::WindowProc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management - Edit Group",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        420,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Edit Group window.",
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
#include "EditGroup.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_EDIT_GROUP_ID        3201
#define ID_EDIT_GROUP_NAME      3202
#define ID_EDIT_DESCRIPTION     3203
#define ID_UPDATE_GROUP         3204
#define ID_CANCEL_EDIT_GROUP    3205

// =====================================================
// CONSTRUCTOR
// =====================================================

EditGroup::EditGroup()
{
    hWnd = NULL;

    hGroupId = NULL;
    hGroupName = NULL;
    hDescription = NULL;

    hUpdateButton = NULL;
    hCancelButton = NULL;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void EditGroup::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Edit Group",
        WS_CHILD | WS_VISIBLE,
        20,
        20,
        400,
        30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // GROUP ID
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group ID:",
        WS_CHILD | WS_VISIBLE,
        20,
        70,
        120,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hGroupId = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL |
        ES_READONLY,
        150,
        67,
        300,
        28,
        hwnd,
        (HMENU)ID_EDIT_GROUP_ID,
        NULL,
        NULL
    );

    // =================================================
    // GROUP NAME
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group Name:",
        WS_CHILD | WS_VISIBLE,
        20,
        115,
        120,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hGroupName = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        150,
        112,
        300,
        28,
        hwnd,
        (HMENU)ID_EDIT_GROUP_NAME,
        NULL,
        NULL
    );

    // =================================================
    // DESCRIPTION
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Description:",
        WS_CHILD | WS_VISIBLE,
        20,
        160,
        120,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hDescription = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_MULTILINE |
        ES_AUTOVSCROLL |
        WS_VSCROLL,
        150,
        157,
        300,
        100,
        hwnd,
        (HMENU)ID_EDIT_DESCRIPTION,
        NULL,
        NULL
    );

    // =================================================
    // UPDATE
    // =================================================

    hUpdateButton = CreateWindowW(
        L"BUTTON",
        L"Update",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        150,
        285,
        100,
        35,
        hwnd,
        (HMENU)ID_UPDATE_GROUP,
        NULL,
        NULL
    );

    // =================================================
    // CANCEL
    // =================================================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        270,
        285,
        100,
        35,
        hwnd,
        (HMENU)ID_CANCEL_EDIT_GROUP,
        NULL,
        NULL
    );
}

// =====================================================
// UPDATE GROUP
// =====================================================

void EditGroup::updateGroup()
{
    wchar_t groupName[101] = {};
    wchar_t description[256] = {};

    GetWindowTextW(
        hGroupName,
        groupName,
        101
    );

    GetWindowTextW(
        hDescription,
        description,
        256
    );

    // =================================================
    // VALIDATION
    // =================================================

    if (wcslen(groupName) == 0)
    {
        MessageBoxW(
            hWnd,
            L"Group Name is required.",
            L"Invalid Data",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hGroupName);

        return;
    }

    // =================================================
    // UI ONLY
    // =================================================

    MessageBoxW(
        hWnd,
        L"Group information is valid.",
        L"Edit Group",
        MB_OK | MB_ICONINFORMATION
    );

    // Database update will be integrated later.
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK EditGroup::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    EditGroup* editGroup =
        reinterpret_cast<EditGroup*>(
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

        editGroup =
            reinterpret_cast<EditGroup*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(editGroup)
        );

        if (editGroup != NULL)
        {
            editGroup->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (editGroup == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_UPDATE_GROUP:
            editGroup->updateGroup();
            return 0;

        case ID_CANCEL_EDIT_GROUP:
            DestroyWindow(hwnd);
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        if (editGroup != NULL)
        {
            editGroup->hWnd = NULL;
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
// SHOW
// =====================================================

void EditGroup::show()
{
    const wchar_t CLASS_NAME[] =
        L"PhoneBook_EditGroup_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = EditGroup::WindowProc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management - Edit Group",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        420,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Edit Group window.",
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