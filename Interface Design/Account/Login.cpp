<<<<<<< HEAD
#include "Login.h"

#include <windows.h>
#include <commctrl.h>
#include <string>

#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_USERNAME        1001
#define ID_PASSWORD        1002

#define ID_LOGIN           1003
#define ID_CLEAR           1004
#define ID_REGISTER        1005
#define ID_CANCEL          1006

#define ID_TREE            1007

// =====================================================
// CONSTRUCTOR
// =====================================================

Login::Login()
{
    hWnd = NULL;

    hTree = NULL;

    hUsername = NULL;
    hPassword = NULL;

    hLoginButton = NULL;
    hClearButton = NULL;
    hRegisterButton = NULL;
    hCancelButton = NULL;

    hFont = NULL;
    hTitleFont = NULL;
    hButtonFont = NULL;
}

// =====================================================
// MESSAGE BOX
// =====================================================

void Login::showMessage(
    const wchar_t* message,
    const wchar_t* title,
    UINT type
)
{
    MessageBoxW(
        hWnd,
        message,
        title,
        type
    );
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void Login::createControls(HWND hwnd)
{

    hFont = CreateFontW(
        16,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"MS Sans Serif"
    );

    hTitleFont = CreateFontW(
        22,
        0,
        0,
        0,
        FW_BOLD,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"MS Sans Serif"
    );

    hButtonFont = CreateFontW(
        16,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"MS Sans Serif"
    );

    // =================================================
    // CATEGORY
    // =================================================

    HWND hCategory = CreateWindowW(
        L"STATIC",
        L"Category",
        WS_CHILD | WS_VISIBLE,
        18,
        18,
        220,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hCategory,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // TREE VIEW
    // =================================================

    hTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_TREEVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        TVS_HASLINES |
        TVS_LINESATROOT |
        TVS_HASBUTTONS |
        TVS_SHOWSELALWAYS,
        18,
        45,
        240,
        570,
        hwnd,
        (HMENU)ID_TREE,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // TREE ITEMS
    // =================================================

    TVINSERTSTRUCTW item = {};

    item.hInsertAfter = TVI_LAST;
    item.item.mask = TVIF_TEXT;

    // -------------------------
    // Account
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText = const_cast<LPWSTR>(L"Account");

    HTREEITEM accountNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Login");

    TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Register");

    TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Update Account");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Contacts
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Contacts");

    HTREEITEM contactsNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Contact List");

    TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Add Contact");

    TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Edit Contact");

    TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Delete Contact");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Search
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Search");

    HTREEITEM searchNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = searchNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Search Contact");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Groups
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Groups");

    HTREEITEM groupNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Add Group");

    TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"View Group");

    TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Edit Group");

    TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Delete Group");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Favorites
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Favorites");

    HTREEITEM favoriteNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = favoriteNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"View Favorites");

    TreeView_InsertItem(hTree, &item);

    item.hParent = favoriteNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Add Favorite");

    TreeView_InsertItem(hTree, &item);

    item.hParent = favoriteNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Remove Favorite");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // System
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"System");

    HTREEITEM systemNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = systemNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Backup Data");

    TreeView_InsertItem(hTree, &item);

    item.hParent = systemNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Data Recovery");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // About
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"About");

    HTREEITEM aboutNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = aboutNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Help");

    TreeView_InsertItem(hTree, &item);

    item.hParent = aboutNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"About System");

    TreeView_InsertItem(hTree, &item);

    // Mở Account để người dùng thấy Login/Register
    TreeView_Expand(
        hTree,
        accountNode,
        TVE_EXPAND
    );

    // =================================================
    // MAIN TITLE
    // =================================================

    HWND hTitle = CreateWindowW(
        L"STATIC",
        L"Login to your account",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        285,
        25,
        700,
        45,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hTitle,
        WM_SETFONT,
        (WPARAM)hTitleFont,
        TRUE
    );

    // =================================================
    // USERNAME LABEL
    // =================================================

    HWND hUsernameLabel = CreateWindowW(
        L"STATIC",
        L"Username:",
        WS_CHILD | WS_VISIBLE,
        350,
        130,
        110,
        30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hUsernameLabel,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // USERNAME EDIT
    // =================================================

    hUsername = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        470,
        125,
        400,
        35,
        hwnd,
        (HMENU)ID_USERNAME,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hUsername,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // PASSWORD LABEL
    // =================================================

    HWND hPasswordLabel = CreateWindowW(
        L"STATIC",
        L"Password:",
        WS_CHILD | WS_VISIBLE,
        350,
        195,
        110,
        30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hPasswordLabel,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // PASSWORD EDIT
    // =================================================

    hPassword = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_PASSWORD |
        ES_AUTOHSCROLL,
        470,
        190,
        400,
        35,
        hwnd,
        (HMENU)ID_PASSWORD,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hPassword,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // LOGIN BUTTON
    // =================================================

    hLoginButton = CreateWindowW(
        L"BUTTON",
        L"Login",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        450,
        270,
        140,
        45,
        hwnd,
        (HMENU)ID_LOGIN,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hLoginButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
    );

    // =================================================
    // CLEAR BUTTON
    // =================================================

    hClearButton = CreateWindowW(
        L"BUTTON",
        L"Clear",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        610,
        270,
        140,
        45,
        hwnd,
        (HMENU)ID_CLEAR,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hClearButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
    );

    // =================================================
    // REGISTER AREA
    // =================================================

    HWND hRegisterBox = CreateWindowW(
        L"BUTTON",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        BS_GROUPBOX,
        285,
        350,
        700,
        140,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hRegisterBox,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    HWND hRegisterText1 = CreateWindowW(
        L"STATIC",
        L"Don't have an account?",
        WS_CHILD | WS_VISIBLE,
        315,
        385,
        300,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hRegisterText1,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    HWND hRegisterText2 = CreateWindowW(
        L"STATIC",
        L"Click Register to create a new account.",
        WS_CHILD | WS_VISIBLE,
        315,
        420,
        350,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hRegisterText2,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // REGISTER BUTTON
    // =================================================

    hRegisterButton = CreateWindowW(
        L"BUTTON",
        L"Register",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        790,
        395,
        150,
        45,
        hwnd,
        (HMENU)ID_REGISTER,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hRegisterButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
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
        820,
        560,
        130,
        45,
        hwnd,
        (HMENU)ID_CANCEL,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hCancelButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
    );

    // =================================================
    // FOCUS USERNAME
    // =================================================

    SetFocus(hUsername);
}

// =====================================================
// CLEAR FIELDS
// =====================================================

void Login::clearFields()
{
    SetWindowTextW(
        hUsername,
        L""
    );

    SetWindowTextW(
        hPassword,
        L""
    );

    SetFocus(hUsername);
}

// =====================================================
// LOGIN
// =====================================================

void Login::handleLogin()
{
    wchar_t username[100] = {};
    wchar_t password[100] = {};

    GetWindowTextW(
        hUsername,
        username,
        100
    );

    GetWindowTextW(
        hPassword,
        password,
        100
    );

    std::wstring user(username);
    std::wstring pass(password);

    // -----------------------------------------------
    // UI stage only
    // -----------------------------------------------

    if (user.empty())
    {
        showMessage(
            L"Please enter username.",
            L"Login",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hUsername);
        return;
    }

    if (pass.empty())
    {
        showMessage(
            L"Please enter password.",
            L"Login",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPassword);
        return;
    }

    /*
        DATABASE CHƯA ĐƯỢC KẾT NỐI.

        Sau này:
        
        username + password
                 |
                 v
             D1 Account
                 |
                 v
            Check Account
                 |
          +------+------+
          |             |
         User          Admin
          |             |
          v             v
       MainMenu      MainMenu
                       +
                     System
    */

    showMessage(
        L"Login information received.",
        L"Login",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK Login::WindowProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    Login* login =
        reinterpret_cast<Login*>(
            GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )
        );

    switch (message)
    {
    case WM_NCCREATE:
    {
        CREATESTRUCTW* createStruct =
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        login =
            reinterpret_cast<Login*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(login)
        );

        login->hWnd = hwnd;

        return TRUE;
    }

    case WM_CREATE:
    {
        if (login)
        {
            login->createControls(hwnd);
        }

        return 0;
    }

    case WM_COMMAND:
    {
        if (!login)
            break;

        switch (LOWORD(wParam))
        {
        case ID_LOGIN:

            login->handleLogin();

            break;

        case ID_CLEAR:

            login->clearFields();

            break;

        case ID_REGISTER:

            login->showMessage(
                L"Register interface will be opened here.",
                L"Register",
                MB_OK | MB_ICONINFORMATION
            );

            break;

        case ID_CANCEL:

            login->clearFields();

            break;
        }

        return 0;
    }

    case WM_NOTIFY:
    {
        if (!login)
            break;

        NMHDR* notification =
            reinterpret_cast<NMHDR*>(lParam);

        if (notification->idFrom == ID_TREE &&
            notification->code == TVN_SELCHANGEDW)
        {
            NMTREEVIEWW* tree =
                reinterpret_cast<NMTREEVIEWW*>(lParam);

            wchar_t text[100] = {};

            TVITEMW selectedItem = {};
            selectedItem.mask = TVIF_TEXT;
            selectedItem.hItem = tree->itemNew.hItem;
            selectedItem.pszText = text;
            selectedItem.cchTextMax = 100;

            TreeView_GetItem(
                login->hTree,
                &selectedItem
            );

            std::wstring selected(text);

            // -----------------------------------------
            // Before Login:
            // only Login / Register / About are usable.
            // -----------------------------------------

            if (selected == L"Login")
            {
                SetFocus(login->hUsername);
            }
            else if (selected == L"Register")
            {
                login->showMessage(
                    L"Register interface will be opened here.",
                    L"Register",
                    MB_OK | MB_ICONINFORMATION
                );
            }
            else if (
                selected == L"Contact List" ||
                selected == L"Add Contact" ||
                selected == L"Edit Contact" ||
                selected == L"Delete Contact" ||
                selected == L"Search Contact" ||
                selected == L"Add Group" ||
                selected == L"View Group" ||
                selected == L"Edit Group" ||
                selected == L"Delete Group" ||
                selected == L"View Favorites" ||
                selected == L"Add Favorite" ||
                selected == L"Remove Favorite"
            )
            {
                login->showMessage(
                    L"Please login first.",
                    L"Access denied",
                    MB_OK | MB_ICONWARNING
                );
            }
            else if (
                selected == L"Backup Data" ||
                selected == L"Data Recovery"
            )
            {
                login->showMessage(
                    L"Administrator access is required.",
                    L"Access denied",
                    MB_OK | MB_ICONWARNING
                );
            }
        }

        return 0;
    }

    case WM_CLOSE:

        DestroyWindow(hwnd);

        return 0;

    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;
    }

    return DefWindowProcW(
        hwnd,
        message,
        wParam,
        lParam
    );
}

// =====================================================
// SHOW
// =====================================================

bool Login::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    // -----------------------------------------------
    // Initialize TreeView
    // -----------------------------------------------

    INITCOMMONCONTROLSEX commonControls = {};

    commonControls.dwSize =
        sizeof(INITCOMMONCONTROLSEX);

    commonControls.dwICC =
        ICC_TREEVIEW_CLASSES;

    InitCommonControlsEx(
        &commonControls
    );

    // -----------------------------------------------
    // Window class
    // -----------------------------------------------

    const wchar_t CLASS_NAME[] =
        L"PhoneBookLoginWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        Login::WindowProc;

    wc.hInstance =
        hInstance;

    wc.lpszClassName =
        CLASS_NAME;

    wc.hCursor =
        LoadCursor(
            NULL,
            IDC_ARROW
        );

    wc.hbrBackground =
        reinterpret_cast<HBRUSH>(
            COLOR_BTNFACE + 1
        );

    wc.style =
        CS_HREDRAW |
        CS_VREDRAW;

    RegisterClassW(&wc);

    // -----------------------------------------------
    // Create window
    // -----------------------------------------------

    hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1040,
        670,
        NULL,
        NULL,
        hInstance,
        this
    );

    if (!hWnd)
        return false;

    ShowWindow(
        hWnd,
        SW_SHOW
    );

    UpdateWindow(
        hWnd
    );

    // -----------------------------------------------
    // Message loop
    // -----------------------------------------------

    MSG msg = {};

    while (
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

    return true;
=======
#include "Login.h"

#include <windows.h>
#include <commctrl.h>
#include <string>

#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_USERNAME        1001
#define ID_PASSWORD        1002

#define ID_LOGIN           1003
#define ID_CLEAR           1004
#define ID_REGISTER        1005
#define ID_CANCEL          1006

#define ID_TREE            1007

// =====================================================
// CONSTRUCTOR
// =====================================================

Login::Login()
{
    hWnd = NULL;

    hTree = NULL;

    hUsername = NULL;
    hPassword = NULL;

    hLoginButton = NULL;
    hClearButton = NULL;
    hRegisterButton = NULL;
    hCancelButton = NULL;

    hFont = NULL;
    hTitleFont = NULL;
    hButtonFont = NULL;
}

// =====================================================
// MESSAGE BOX
// =====================================================

void Login::showMessage(
    const wchar_t* message,
    const wchar_t* title,
    UINT type
)
{
    MessageBoxW(
        hWnd,
        message,
        title,
        type
    );
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void Login::createControls(HWND hwnd)
{

    hFont = CreateFontW(
        16,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"MS Sans Serif"
    );

    hTitleFont = CreateFontW(
        22,
        0,
        0,
        0,
        FW_BOLD,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"MS Sans Serif"
    );

    hButtonFont = CreateFontW(
        16,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"MS Sans Serif"
    );

    // =================================================
    // CATEGORY
    // =================================================

    HWND hCategory = CreateWindowW(
        L"STATIC",
        L"Category",
        WS_CHILD | WS_VISIBLE,
        18,
        18,
        220,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hCategory,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // TREE VIEW
    // =================================================

    hTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_TREEVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        TVS_HASLINES |
        TVS_LINESATROOT |
        TVS_HASBUTTONS |
        TVS_SHOWSELALWAYS,
        18,
        45,
        240,
        570,
        hwnd,
        (HMENU)ID_TREE,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // TREE ITEMS
    // =================================================

    TVINSERTSTRUCTW item = {};

    item.hInsertAfter = TVI_LAST;
    item.item.mask = TVIF_TEXT;

    // -------------------------
    // Account
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText = const_cast<LPWSTR>(L"Account");

    HTREEITEM accountNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Login");

    TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Register");

    TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Update Account");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Contacts
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Contacts");

    HTREEITEM contactsNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Contact List");

    TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Add Contact");

    TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Edit Contact");

    TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Delete Contact");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Search
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Search");

    HTREEITEM searchNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = searchNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Search Contact");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Groups
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Groups");

    HTREEITEM groupNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Add Group");

    TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"View Group");

    TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Edit Group");

    TreeView_InsertItem(hTree, &item);

    item.hParent = groupNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Delete Group");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // Favorites
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"Favorites");

    HTREEITEM favoriteNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = favoriteNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"View Favorites");

    TreeView_InsertItem(hTree, &item);

    item.hParent = favoriteNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Add Favorite");

    TreeView_InsertItem(hTree, &item);

    item.hParent = favoriteNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Remove Favorite");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // System
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"System");

    HTREEITEM systemNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = systemNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Backup Data");

    TreeView_InsertItem(hTree, &item);

    item.hParent = systemNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Data Recovery");

    TreeView_InsertItem(hTree, &item);

    // -------------------------
    // About
    // -------------------------

    item.hParent = TVI_ROOT;
    item.item.pszText =
        const_cast<LPWSTR>(L"About");

    HTREEITEM aboutNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = aboutNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"Help");

    TreeView_InsertItem(hTree, &item);

    item.hParent = aboutNode;
    item.item.pszText =
        const_cast<LPWSTR>(L"About System");

    TreeView_InsertItem(hTree, &item);

    // Mở Account để người dùng thấy Login/Register
    TreeView_Expand(
        hTree,
        accountNode,
        TVE_EXPAND
    );

    // =================================================
    // MAIN TITLE
    // =================================================

    HWND hTitle = CreateWindowW(
        L"STATIC",
        L"Login to your account",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        285,
        25,
        700,
        45,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hTitle,
        WM_SETFONT,
        (WPARAM)hTitleFont,
        TRUE
    );

    // =================================================
    // USERNAME LABEL
    // =================================================

    HWND hUsernameLabel = CreateWindowW(
        L"STATIC",
        L"Username:",
        WS_CHILD | WS_VISIBLE,
        350,
        130,
        110,
        30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hUsernameLabel,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // USERNAME EDIT
    // =================================================

    hUsername = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        470,
        125,
        400,
        35,
        hwnd,
        (HMENU)ID_USERNAME,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hUsername,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // PASSWORD LABEL
    // =================================================

    HWND hPasswordLabel = CreateWindowW(
        L"STATIC",
        L"Password:",
        WS_CHILD | WS_VISIBLE,
        350,
        195,
        110,
        30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hPasswordLabel,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // PASSWORD EDIT
    // =================================================

    hPassword = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_PASSWORD |
        ES_AUTOHSCROLL,
        470,
        190,
        400,
        35,
        hwnd,
        (HMENU)ID_PASSWORD,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hPassword,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // LOGIN BUTTON
    // =================================================

    hLoginButton = CreateWindowW(
        L"BUTTON",
        L"Login",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        450,
        270,
        140,
        45,
        hwnd,
        (HMENU)ID_LOGIN,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hLoginButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
    );

    // =================================================
    // CLEAR BUTTON
    // =================================================

    hClearButton = CreateWindowW(
        L"BUTTON",
        L"Clear",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        610,
        270,
        140,
        45,
        hwnd,
        (HMENU)ID_CLEAR,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hClearButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
    );

    // =================================================
    // REGISTER AREA
    // =================================================

    HWND hRegisterBox = CreateWindowW(
        L"BUTTON",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        BS_GROUPBOX,
        285,
        350,
        700,
        140,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hRegisterBox,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    HWND hRegisterText1 = CreateWindowW(
        L"STATIC",
        L"Don't have an account?",
        WS_CHILD | WS_VISIBLE,
        315,
        385,
        300,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hRegisterText1,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    HWND hRegisterText2 = CreateWindowW(
        L"STATIC",
        L"Click Register to create a new account.",
        WS_CHILD | WS_VISIBLE,
        315,
        420,
        350,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    SendMessageW(
        hRegisterText2,
        WM_SETFONT,
        (WPARAM)hFont,
        TRUE
    );

    // =================================================
    // REGISTER BUTTON
    // =================================================

    hRegisterButton = CreateWindowW(
        L"BUTTON",
        L"Register",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        790,
        395,
        150,
        45,
        hwnd,
        (HMENU)ID_REGISTER,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hRegisterButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
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
        820,
        560,
        130,
        45,
        hwnd,
        (HMENU)ID_CANCEL,
        GetModuleHandleW(NULL),
        NULL
    );

    SendMessageW(
        hCancelButton,
        WM_SETFONT,
        (WPARAM)hButtonFont,
        TRUE
    );

    // =================================================
    // FOCUS USERNAME
    // =================================================

    SetFocus(hUsername);
}

// =====================================================
// CLEAR FIELDS
// =====================================================

void Login::clearFields()
{
    SetWindowTextW(
        hUsername,
        L""
    );

    SetWindowTextW(
        hPassword,
        L""
    );

    SetFocus(hUsername);
}

// =====================================================
// LOGIN
// =====================================================

void Login::handleLogin()
{
    wchar_t username[100] = {};
    wchar_t password[100] = {};

    GetWindowTextW(
        hUsername,
        username,
        100
    );

    GetWindowTextW(
        hPassword,
        password,
        100
    );

    std::wstring user(username);
    std::wstring pass(password);

    // -----------------------------------------------
    // UI stage only
    // -----------------------------------------------

    if (user.empty())
    {
        showMessage(
            L"Please enter username.",
            L"Login",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hUsername);
        return;
    }

    if (pass.empty())
    {
        showMessage(
            L"Please enter password.",
            L"Login",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPassword);
        return;
    }

    /*
        DATABASE CHƯA ĐƯỢC KẾT NỐI.

        Sau này:
        
        username + password
                 |
                 v
             D1 Account
                 |
                 v
            Check Account
                 |
          +------+------+
          |             |
         User          Admin
          |             |
          v             v
       MainMenu      MainMenu
                       +
                     System
    */

    showMessage(
        L"Login information received.",
        L"Login",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK Login::WindowProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    Login* login =
        reinterpret_cast<Login*>(
            GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )
        );

    switch (message)
    {
    case WM_NCCREATE:
    {
        CREATESTRUCTW* createStruct =
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        login =
            reinterpret_cast<Login*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(login)
        );

        login->hWnd = hwnd;

        return TRUE;
    }

    case WM_CREATE:
    {
        if (login)
        {
            login->createControls(hwnd);
        }

        return 0;
    }

    case WM_COMMAND:
    {
        if (!login)
            break;

        switch (LOWORD(wParam))
        {
        case ID_LOGIN:

            login->handleLogin();

            break;

        case ID_CLEAR:

            login->clearFields();

            break;

        case ID_REGISTER:

            login->showMessage(
                L"Register interface will be opened here.",
                L"Register",
                MB_OK | MB_ICONINFORMATION
            );

            break;

        case ID_CANCEL:

            login->clearFields();

            break;
        }

        return 0;
    }

    case WM_NOTIFY:
    {
        if (!login)
            break;

        NMHDR* notification =
            reinterpret_cast<NMHDR*>(lParam);

        if (notification->idFrom == ID_TREE &&
            notification->code == TVN_SELCHANGEDW)
        {
            NMTREEVIEWW* tree =
                reinterpret_cast<NMTREEVIEWW*>(lParam);

            wchar_t text[100] = {};

            TVITEMW selectedItem = {};
            selectedItem.mask = TVIF_TEXT;
            selectedItem.hItem = tree->itemNew.hItem;
            selectedItem.pszText = text;
            selectedItem.cchTextMax = 100;

            TreeView_GetItem(
                login->hTree,
                &selectedItem
            );

            std::wstring selected(text);

            // -----------------------------------------
            // Before Login:
            // only Login / Register / About are usable.
            // -----------------------------------------

            if (selected == L"Login")
            {
                SetFocus(login->hUsername);
            }
            else if (selected == L"Register")
            {
                login->showMessage(
                    L"Register interface will be opened here.",
                    L"Register",
                    MB_OK | MB_ICONINFORMATION
                );
            }
            else if (
                selected == L"Contact List" ||
                selected == L"Add Contact" ||
                selected == L"Edit Contact" ||
                selected == L"Delete Contact" ||
                selected == L"Search Contact" ||
                selected == L"Add Group" ||
                selected == L"View Group" ||
                selected == L"Edit Group" ||
                selected == L"Delete Group" ||
                selected == L"View Favorites" ||
                selected == L"Add Favorite" ||
                selected == L"Remove Favorite"
            )
            {
                login->showMessage(
                    L"Please login first.",
                    L"Access denied",
                    MB_OK | MB_ICONWARNING
                );
            }
            else if (
                selected == L"Backup Data" ||
                selected == L"Data Recovery"
            )
            {
                login->showMessage(
                    L"Administrator access is required.",
                    L"Access denied",
                    MB_OK | MB_ICONWARNING
                );
            }
        }

        return 0;
    }

    case WM_CLOSE:

        DestroyWindow(hwnd);

        return 0;

    case WM_DESTROY:

        PostQuitMessage(0);

        return 0;
    }

    return DefWindowProcW(
        hwnd,
        message,
        wParam,
        lParam
    );
}

// =====================================================
// SHOW
// =====================================================

bool Login::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    // -----------------------------------------------
    // Initialize TreeView
    // -----------------------------------------------

    INITCOMMONCONTROLSEX commonControls = {};

    commonControls.dwSize =
        sizeof(INITCOMMONCONTROLSEX);

    commonControls.dwICC =
        ICC_TREEVIEW_CLASSES;

    InitCommonControlsEx(
        &commonControls
    );

    // -----------------------------------------------
    // Window class
    // -----------------------------------------------

    const wchar_t CLASS_NAME[] =
        L"PhoneBookLoginWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        Login::WindowProc;

    wc.hInstance =
        hInstance;

    wc.lpszClassName =
        CLASS_NAME;

    wc.hCursor =
        LoadCursor(
            NULL,
            IDC_ARROW
        );

    wc.hbrBackground =
        reinterpret_cast<HBRUSH>(
            COLOR_BTNFACE + 1
        );

    wc.style =
        CS_HREDRAW |
        CS_VREDRAW;

    RegisterClassW(&wc);

    // -----------------------------------------------
    // Create window
    // -----------------------------------------------

    hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1040,
        670,
        NULL,
        NULL,
        hInstance,
        this
    );

    if (!hWnd)
        return false;

    ShowWindow(
        hWnd,
        SW_SHOW
    );

    UpdateWindow(
        hWnd
    );

    // -----------------------------------------------
    // Message loop
    // -----------------------------------------------

    MSG msg = {};

    while (
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

    return true;
>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
}