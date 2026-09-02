<<<<<<< HEAD
#include "AddGroup.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_GROUP_NAME       3101
#define ID_DESCRIPTION      3102
#define ID_SAVE_GROUP       3103
#define ID_CANCEL_GROUP     3104

// =====================================================
// CONSTRUCTOR
// =====================================================

AddGroup::AddGroup()
{
    hWnd = NULL;

    hGroupName = NULL;
    hDescription = NULL;

    hSaveButton = NULL;
    hCancelButton = NULL;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void AddGroup::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Add Group",
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
    // GROUP NAME
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group Name:",
        WS_CHILD | WS_VISIBLE,
        20,
        75,
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
        72,
        300,
        28,
        hwnd,
        (HMENU)ID_GROUP_NAME,
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
        125,
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
        122,
        300,
        100,
        hwnd,
        (HMENU)ID_DESCRIPTION,
        NULL,
        NULL
    );

    // =================================================
    // SAVE
    // =================================================

    hSaveButton = CreateWindowW(
        L"BUTTON",
        L"Save",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        150,
        250,
        100,
        35,
        hwnd,
        (HMENU)ID_SAVE_GROUP,
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
        250,
        100,
        35,
        hwnd,
        (HMENU)ID_CANCEL_GROUP,
        NULL,
        NULL
    );
}

// =====================================================
// SAVE GROUP
// =====================================================

void AddGroup::saveGroup()
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
        L"Add Group",
        MB_OK | MB_ICONINFORMATION
    );

    // Database saving will be integrated later.
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK AddGroup::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    AddGroup* addGroup =
        reinterpret_cast<AddGroup*>(
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

        addGroup =
            reinterpret_cast<AddGroup*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(addGroup)
        );

        if (addGroup != NULL)
        {
            addGroup->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (addGroup == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_SAVE_GROUP:
            addGroup->saveGroup();
            return 0;

        case ID_CANCEL_GROUP:
            DestroyWindow(hwnd);
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        if (addGroup != NULL)
        {
            addGroup->hWnd = NULL;
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

void AddGroup::show()
{
    const wchar_t CLASS_NAME[] =
        L"PhoneBook_AddGroup_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = AddGroup::WindowProc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management - Add Group",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        360,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Add Group window.",
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
#include "AddGroup.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_GROUP_NAME       3101
#define ID_DESCRIPTION      3102
#define ID_SAVE_GROUP       3103
#define ID_CANCEL_GROUP     3104

// =====================================================
// CONSTRUCTOR
// =====================================================

AddGroup::AddGroup()
{
    hWnd = NULL;

    hGroupName = NULL;
    hDescription = NULL;

    hSaveButton = NULL;
    hCancelButton = NULL;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void AddGroup::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Add Group",
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
    // GROUP NAME
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group Name:",
        WS_CHILD | WS_VISIBLE,
        20,
        75,
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
        72,
        300,
        28,
        hwnd,
        (HMENU)ID_GROUP_NAME,
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
        125,
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
        122,
        300,
        100,
        hwnd,
        (HMENU)ID_DESCRIPTION,
        NULL,
        NULL
    );

    // =================================================
    // SAVE
    // =================================================

    hSaveButton = CreateWindowW(
        L"BUTTON",
        L"Save",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        150,
        250,
        100,
        35,
        hwnd,
        (HMENU)ID_SAVE_GROUP,
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
        250,
        100,
        35,
        hwnd,
        (HMENU)ID_CANCEL_GROUP,
        NULL,
        NULL
    );
}

// =====================================================
// SAVE GROUP
// =====================================================

void AddGroup::saveGroup()
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
        L"Add Group",
        MB_OK | MB_ICONINFORMATION
    );

    // Database saving will be integrated later.
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK AddGroup::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    AddGroup* addGroup =
        reinterpret_cast<AddGroup*>(
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

        addGroup =
            reinterpret_cast<AddGroup*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(addGroup)
        );

        if (addGroup != NULL)
        {
            addGroup->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (addGroup == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_SAVE_GROUP:
            addGroup->saveGroup();
            return 0;

        case ID_CANCEL_GROUP:
            DestroyWindow(hwnd);
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        if (addGroup != NULL)
        {
            addGroup->hWnd = NULL;
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

void AddGroup::show()
{
    const wchar_t CLASS_NAME[] =
        L"PhoneBook_AddGroup_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = AddGroup::WindowProc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management - Add Group",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        500,
        360,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Add Group window.",
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