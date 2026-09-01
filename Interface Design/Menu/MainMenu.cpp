#include "MainMenu.h"

#include <windows.h>
#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

// =====================================================
// CONTROL IDs
// =====================================================

#define ID_CATEGORY_TREE       4001

#define ID_CONTACTS_BUTTON     4002
#define ID_GROUPS_BUTTON       4003
#define ID_FAVORITES_BUTTON    4004
#define ID_ACCOUNT_BUTTON      4005
#define ID_REGISTER_BUTTON     4006
#define ID_ABOUT_BUTTON        4007
#define ID_LOGOUT_BUTTON       4008
#define ID_CLOSE_BUTTON        4009

// =====================================================
// CONSTRUCTOR
// =====================================================

MainMenu::MainMenu()
{
    hWnd = NULL;

    hCategoryTree = NULL;
    hContentTitle = NULL;
    hContentText = NULL;

    hContactsButton = NULL;
    hGroupsButton = NULL;
    hFavoritesButton = NULL;
    hAccountButton = NULL;
    hRegisterButton = NULL;
    hAboutButton = NULL;
    hLogoutButton = NULL;
    hCloseButton = NULL;

    // MainMenu mặc định chưa đăng nhập.
    isLoggedIn = false;

    // Mặc định không phải Admin.
    isAdmin = false;
}

// =====================================================
// SET LOGIN STATUS
// =====================================================

void MainMenu::setLoginStatus(bool loggedIn)
{
    isLoggedIn = loggedIn;
}

// =====================================================
// SET ADMIN
// =====================================================

void MainMenu::setAdmin(bool admin)
{
    isAdmin = admin;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void MainMenu::createControls(HWND hwnd)
{
    // =================================================
    // HEADER
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"PHONE BOOK MANAGEMENT SYSTEM",
        WS_CHILD | WS_VISIBLE,
        20,
        15,
        600,
        35,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // CATEGORY LABEL
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Category",
        WS_CHILD | WS_VISIBLE,
        20,
        65,
        180,
        25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // CATEGORY TREE
    // =================================================

    hCategoryTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_TREEVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        TVS_HASLINES |
        TVS_LINESATROOT |
        TVS_HASBUTTONS,
        20,
        95,
        210,
        330,
        hwnd,
        (HMENU)ID_CATEGORY_TREE,
        GetModuleHandleW(NULL),
        NULL
    );

    // =================================================
    // TREE ITEMS
    // =================================================

    TVINSERTSTRUCTW rootItem = {};

    rootItem.hParent = TVI_ROOT;
    rootItem.hInsertAfter = TVI_LAST;
    rootItem.item.mask = TVIF_TEXT;
    rootItem.item.pszText =
        const_cast<LPWSTR>(L"Phone Book");

    HTREEITEM hRoot =
        TreeView_InsertItem(
            hCategoryTree,
            &rootItem
        );

    TVINSERTSTRUCTW childItem = {};

    childItem.hParent = hRoot;
    childItem.hInsertAfter = TVI_LAST;
    childItem.item.mask = TVIF_TEXT;

    childItem.item.pszText =
        const_cast<LPWSTR>(L"Contacts");

    TreeView_InsertItem(
        hCategoryTree,
        &childItem
    );

    childItem.item.pszText =
        const_cast<LPWSTR>(L"Groups");

    TreeView_InsertItem(
        hCategoryTree,
        &childItem
    );

    childItem.item.pszText =
        const_cast<LPWSTR>(L"Favorites");

    TreeView_InsertItem(
        hCategoryTree,
        &childItem
    );

    childItem.item.pszText =
        const_cast<LPWSTR>(L"Account");

    TreeView_InsertItem(
        hCategoryTree,
        &childItem
    );

    TreeView_Expand(
        hCategoryTree,
        hRoot,
        TVE_EXPAND
    );

    // =================================================
    // CONTENT AREA
    // =================================================

    hContentTitle = CreateWindowW(
        L"STATIC",
        L"Welcome",
        WS_CHILD | WS_VISIBLE,
        260,
        75,
        500,
        35,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hContentText = CreateWindowW(
        L"STATIC",
        L"",
        WS_CHILD | WS_VISIBLE,
        260,
        120,
        500,
        100,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // CONTACTS
    // =================================================

    hContactsButton = CreateWindowW(
        L"BUTTON",
        L"Contacts",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        260,
        250,
        120,
        35,
        hwnd,
        (HMENU)ID_CONTACTS_BUTTON,
        NULL,
        NULL
    );

    // =================================================
    // GROUPS
    // =================================================

    hGroupsButton = CreateWindowW(
        L"BUTTON",
        L"Groups",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        395,
        250,
        120,
        35,
        hwnd,
        (HMENU)ID_GROUPS_BUTTON,
        NULL,
        NULL
    );

    // =================================================
    // FAVORITES
    // =================================================

    hFavoritesButton = CreateWindowW(
        L"BUTTON",
        L"Favorites",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        530,
        250,
        120,
        35,
        hwnd,
        (HMENU)ID_FAVORITES_BUTTON,
        NULL,
        NULL
    );

    // =================================================
    // ACCOUNT
    // =================================================

    hAccountButton = CreateWindowW(
        L"BUTTON",
        L"Account",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        260,
        300,
        120,
        35,
        hwnd,
        (HMENU)ID_ACCOUNT_BUTTON,
        NULL,
        NULL
    );

    // =================================================
    // REGISTER
    // =================================================

    hRegisterButton = CreateWindowW(
        L"BUTTON",
        L"Register",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        395,
        300,
        120,
        35,
        hwnd,
        (HMENU)ID_REGISTER_BUTTON,
        NULL,
        NULL
    );

    // =================================================
    // ABOUT
    // =================================================

    hAboutButton = CreateWindowW(
        L"BUTTON",
        L"About",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        530,
        300,
        120,
        35,
        hwnd,
        (HMENU)ID_ABOUT_BUTTON,
        NULL,
        NULL
    );

    // =================================================
    // LOGOUT
    // =================================================

    hLogoutButton = CreateWindowW(
        L"BUTTON",
        L"Logout",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        260,
        370,
        120,
        35,
        hwnd,
        (HMENU)ID_LOGOUT_BUTTON,
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
        530,
        370,
        120,
        35,
        hwnd,
        (HMENU)ID_CLOSE_BUTTON,
        NULL,
        NULL
    );

    showWelcome();
}

// =====================================================
// WELCOME
// =====================================================

void MainMenu::showWelcome()
{
    SetWindowTextW(
        hContentTitle,
        L"Phone Book Management"
    );

    if (isLoggedIn)
    {
        SetWindowTextW(
            hContentText,
            L"Welcome to the system.\n"
            L"Please select a function from the menu."
        );
    }
    else
    {
        SetWindowTextW(
            hContentText,
            L"Please login to manage your contacts."
        );
    }
}

// =====================================================
// CONTACTS
// =====================================================

void MainMenu::showContacts()
{
    if (!isLoggedIn)
    {
        MessageBoxW(
            hWnd,
            L"Please login before using Contacts.",
            L"Access Denied",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    SetWindowTextW(
        hContentTitle,
        L"Contacts Management"
    );

    SetWindowTextW(
        hContentText,
        L"Manage your personal contacts."
    );

    MessageBoxW(
        hWnd,
        L"Contacts Management selected.",
        L"Contacts",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// GROUPS
// =====================================================

void MainMenu::showGroups()
{
    if (!isLoggedIn)
    {
        MessageBoxW(
            hWnd,
            L"Please login before using Groups.",
            L"Access Denied",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    SetWindowTextW(
        hContentTitle,
        L"Group Management"
    );

    SetWindowTextW(
        hContentText,
        L"Manage your contact groups."
    );

    MessageBoxW(
        hWnd,
        L"Group Management selected.",
        L"Groups",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// FAVORITES
// =====================================================

void MainMenu::showFavorites()
{
    if (!isLoggedIn)
    {
        MessageBoxW(
            hWnd,
            L"Please login before using Favorites.",
            L"Access Denied",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    SetWindowTextW(
        hContentTitle,
        L"Favorite Management"
    );

    SetWindowTextW(
        hContentText,
        L"Manage your favorite contacts."
    );

    MessageBoxW(
        hWnd,
        L"Favorite Management selected.",
        L"Favorites",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// ACCOUNT
// =====================================================

void MainMenu::showAccount()
{
    if (!isLoggedIn)
    {
        MessageBoxW(
            hWnd,
            L"Please login before managing your account.",
            L"Access Denied",
            MB_OK | MB_ICONWARNING
        );

        return;
    }

    SetWindowTextW(
        hContentTitle,
        L"Account Management"
    );

    SetWindowTextW(
        hContentText,
        L"Manage your account information and password."
    );

    MessageBoxW(
        hWnd,
        L"Account Management selected.",
        L"Account",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// REGISTER
// =====================================================

void MainMenu::showRegister()
{
    SetWindowTextW(
        hContentTitle,
        L"Register An Account"
    );

    SetWindowTextW(
        hContentText,
        L"Create a new account for the Phone Book system."
    );

    MessageBoxW(
        hWnd,
        L"Register An Account selected.",
        L"Register",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// ABOUT
// =====================================================

void MainMenu::showAbout()
{
    MessageBoxW(
        hWnd,
        L"Phone Book Management System\n\n"
        L"Contact management application.",
        L"About",
        MB_OK | MB_ICONINFORMATION
    );
}

// =====================================================
// LOGOUT
// =====================================================

void MainMenu::logout()
{
    if (!isLoggedIn)
    {
        MessageBoxW(
            hWnd,
            L"No account is currently logged in.",
            L"Logout",
            MB_OK | MB_ICONINFORMATION
        );

        return;
    }

    int result = MessageBoxW(
        hWnd,
        L"Are you sure you want to logout?",
        L"Logout",
        MB_YESNO | MB_ICONQUESTION
    );

    if (result == IDYES)
    {
        isLoggedIn = false;
        isAdmin = false;

        showWelcome();

        MessageBoxW(
            hWnd,
            L"You have been logged out.",
            L"Logout",
            MB_OK | MB_ICONINFORMATION
        );
    }
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK MainMenu::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    MainMenu* mainMenu =
        reinterpret_cast<MainMenu*>(
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

        mainMenu =
            reinterpret_cast<MainMenu*>(
                createStruct->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(mainMenu)
        );

        if (mainMenu != NULL)
        {
            mainMenu->hWnd = hwnd;
        }

        return TRUE;
    }

    case WM_COMMAND:
    {
        if (mainMenu == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_CONTACTS_BUTTON:
            mainMenu->showContacts();
            return 0;

        case ID_GROUPS_BUTTON:
            mainMenu->showGroups();
            return 0;

        case ID_FAVORITES_BUTTON:
            mainMenu->showFavorites();
            return 0;

        case ID_ACCOUNT_BUTTON:
            mainMenu->showAccount();
            return 0;

        case ID_REGISTER_BUTTON:
            mainMenu->showRegister();
            return 0;

        case ID_ABOUT_BUTTON:
            mainMenu->showAbout();
            return 0;

        case ID_LOGOUT_BUTTON:
            mainMenu->logout();
            return 0;

        case ID_CLOSE_BUTTON:
            DestroyWindow(hwnd);
            return 0;
        }

        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        if (mainMenu != NULL)
        {
            mainMenu->hWnd = NULL;
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

void MainMenu::show()
{
    // -------------------------------------------------
    // Initialize common controls for TreeView.
    // -------------------------------------------------

    INITCOMMONCONTROLSEX icex = {};

    icex.dwSize =
        sizeof(INITCOMMONCONTROLSEX);

    icex.dwICC =
        ICC_TREEVIEW_CLASSES;

    InitCommonControlsEx(&icex);

    // -------------------------------------------------
    // Window class
    // -------------------------------------------------

    const wchar_t CLASS_NAME[] =
        L"PhoneBook_MainMenu_Window";

    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        MainMenu::WindowProc;

    wc.hInstance =
        GetModuleHandleW(NULL);

    wc.lpszClassName =
        CLASS_NAME;

    wc.hCursor =
        LoadCursorW(
            NULL,
            IDC_ARROW
        );

    wc.hbrBackground =
        (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    // -------------------------------------------------
    // Create window
    // -------------------------------------------------

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        500,
        NULL,
        NULL,
        GetModuleHandleW(NULL),
        this
    );

    if (hwnd == NULL)
    {
        MessageBoxW(
            NULL,
            L"Cannot create Main Menu window.",
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

    // -------------------------------------------------
    // Message loop
    // -------------------------------------------------

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