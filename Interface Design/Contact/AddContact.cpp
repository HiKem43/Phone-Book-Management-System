#include "AddContact.h"

#include <windows.h>
#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_NAME         6001
#define ID_PHONE        6002
#define ID_EMAIL        6003
#define ID_ADDRESS      6004
#define ID_GROUP        6005
#define ID_FAVORITE     6006

#define ID_SAVE         6007
#define ID_CANCEL       6008

// =====================================================
// CONSTRUCTOR
// =====================================================

AddContact::AddContact()
{
    hWnd = NULL;

    hName = NULL;
    hPhone = NULL;
    hEmail = NULL;
    hAddress = NULL;
    hGroup = NULL;
    hFavorite = NULL;

    hSaveButton = NULL;
    hCancelButton = NULL;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void AddContact::createControls(HWND hwnd)
{
    // =================================================
    // HEADER
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"ADD CONTACT",
        WS_CHILD | WS_VISIBLE,
        25,
        20,
        700,
        40,
        hwnd,
        NULL,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // NAME
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Name:",
        WS_CHILD | WS_VISIBLE,
        30,
        90,
        120,
        25,
        hwnd,
        NULL,
        GetModuleHandleW(NULL),
        NULL
    );

    hName = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        160,
        87,
        500,
        28,
        hwnd,
        (HMENU)ID_NAME,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // PHONE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Phone:",
        WS_CHILD | WS_VISIBLE,
        30,
        135,
        120,
        25,
        hwnd,
        NULL,
        GetModuleHandleW(NULL),
        NULL
    );

    hPhone = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        160,
        132,
        500,
        28,
        hwnd,
        (HMENU)ID_PHONE,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // EMAIL
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Email:",
        WS_CHILD | WS_VISIBLE,
        30,
        180,
        120,
        25,
        hwnd,
        NULL,
        GetModuleHandleW(NULL),
        NULL
    );

    hEmail = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        160,
        177,
        500,
        28,
        hwnd,
        (HMENU)ID_EMAIL,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // ADDRESS
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Address:",
        WS_CHILD | WS_VISIBLE,
        30,
        225,
        120,
        25,
        hwnd,
        NULL,
        GetModuleHandleW(NULL),
        NULL
    );

    hAddress = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_MULTILINE |
        ES_AUTOVSCROLL |
        WS_VSCROLL,
        160,
        222,
        500,
        70,
        hwnd,
        (HMENU)ID_ADDRESS,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // GROUP
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Group:",
        WS_CHILD | WS_VISIBLE,
        30,
        315,
        120,
        25,
        hwnd,
        NULL,
        GetModuleHandleW(NULL),
        NULL
    );

    hGroup = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        160,
        312,
        500,
        28,
        hwnd,
        (HMENU)ID_GROUP,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // FAVORITE
    // =================================================

    hFavorite = CreateWindowW(
        L"BUTTON",
        L"Favorite",
        WS_CHILD |
        WS_VISIBLE |
        BS_AUTOCHECKBOX,
        160,
        355,
        120,
        25,
        hwnd,
        (HMENU)ID_FAVORITE,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // SAVE BUTTON
    // =================================================

    hSaveButton = CreateWindowW(
        L"BUTTON",
        L"Save",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        430,
        410,
        100,
        35,
        hwnd,
        (HMENU)ID_SAVE,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // CANCEL BUTTON
    // =================================================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        550,
        410,
        100,
        35,
        hwnd,
        (HMENU)ID_CANCEL,
        GetModuleHandleW(NULL),
        NULL
    );
}

// =====================================================
// SAVE CONTACT
// =====================================================

void AddContact::saveContact()
{
    wchar_t name[101] = {};
    wchar_t phone[16] = {};

    GetWindowTextW(
        hName,
        name,
        101
    );

    GetWindowTextW(
        hPhone,
        phone,
        16
    );

    // -------------------------------------------------
    // Required fields
    // -------------------------------------------------

    if (wcslen(name) == 0)
    {
        MessageBoxW(
            hWnd,
            L"Please enter the contact name.",
            L"Invalid Data",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hName);
        return;
    }

    if (wcslen(phone) == 0)
    {
        MessageBoxW(
            hWnd,
            L"Please enter the contact phone number.",
            L"Invalid Data",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPhone);
        return;
    }

    // -------------------------------------------------
    // UI stage only
    // -------------------------------------------------

    MessageBoxW(
        hWnd,
        L"Contact information is valid.\n\n"
        L"Database saving will be connected here.",
        L"Add Contact",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// CANCEL
// =====================================================

void AddContact::cancel()
{
    DestroyWindow(hWnd);
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK AddContact::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    AddContact* addContact =
        reinterpret_cast<AddContact*>(
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

        addContact =
            reinterpret_cast<AddContact*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(addContact)
        );

        if (addContact != NULL)
        {
            addContact->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (addContact == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_SAVE:
            addContact->saveContact();
            return 0;

        case ID_CANCEL:
            addContact->cancel();
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:

        if (addContact != NULL)
        {
            addContact->hWnd = NULL;
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

void AddContact::show()
{
    INITCOMMONCONTROLSEX icex = {};

    icex.dwSize =
        sizeof(INITCOMMONCONTROLSEX);

    icex.dwICC =
        ICC_STANDARD_CLASSES;

    InitCommonControlsEx(&icex);

    // =================================================
    // WINDOW CLASS
    // =================================================

    const wchar_t CLASS_NAME[] =
        L"PhoneBook_AddContact_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        AddContact::WindowProc;

    wc.hInstance =
        GetModuleHandleW(NULL);

    wc.lpszClassName =
        CLASS_NAME;

    wc.hCursor =
        LoadCursorW(
            NULL,
            MAKEINTRESOURCEW(32512)
        );

    wc.hbrBackground =
        (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    // =================================================
    // CREATE WINDOW
    // =================================================

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Add Contact",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        740,
        510,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Add Contact window.",
            L"Error",
            MB_OK | MB_ICONERROR
        );

        return;
    }

    createControls(hwnd);

    ShowWindow(
        hwnd,
        SW_SHOW
    );

    UpdateWindow(hwnd);

    // =================================================
    // MESSAGE LOOP
    // =================================================

    MSG msg;

    while (
        IsWindow(hwnd) &&
        GetMessageW(
            &msg,
            NULL,
            0,
            0
        ) > 0
    )
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}