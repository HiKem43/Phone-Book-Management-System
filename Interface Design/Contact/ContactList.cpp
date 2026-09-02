<<<<<<< HEAD
#include "ContactList.h"

#include <windows.h>
#include <commctrl.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comctl32.lib")

#define ID_CONTACT_LIST  6001
#define ID_VIEW          6002
#define ID_CLOSE         6003

ContactList::ContactList()
{
    hWnd = NULL;

    hTree = NULL;
    hList = NULL;

    hViewButton = NULL;
    hCloseButton = NULL;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void ContactList::createControls(HWND hwnd)
{
    // =================================================
    // LEFT CATEGORY
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Category",
        WS_CHILD | WS_VISIBLE,
        15, 15,
        110, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_TREEVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        TVS_HASLINES |
        TVS_LINESATROOT |
        TVS_HASBUTTONS,
        15, 45,
        230, 550,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // TREE CATEGORY
    // =================================================

    TVINSERTSTRUCTW item = {};

    HTREEITEM accountNode;
    HTREEITEM contactsNode;
    HTREEITEM aboutNode;

    item.hParent = TVI_ROOT;
    item.hInsertAfter = TVI_LAST;
    item.item.mask = TVIF_TEXT;

    // Account
    item.item.pszText =
        const_cast<LPWSTR>(L"Account");

    accountNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;

    item.item.pszText =
        const_cast<LPWSTR>(L"Update Account");

    TreeView_InsertItem(hTree, &item);

    // Contacts
    item.hParent = TVI_ROOT;

    item.item.pszText =
        const_cast<LPWSTR>(L"Contacts");

    contactsNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;

    item.item.pszText =
        const_cast<LPWSTR>(L"Contact List");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"Add Contact");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"Groups");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"Favorites");

    TreeView_InsertItem(hTree, &item);

    // About
    item.hParent = TVI_ROOT;

    item.item.pszText =
        const_cast<LPWSTR>(L"About");

    aboutNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = aboutNode;

    item.item.pszText =
        const_cast<LPWSTR>(L"Help");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"About System");

    TreeView_InsertItem(hTree, &item);

    // Expand Contacts
    TreeView_Expand(
        hTree,
        contactsNode,
        TVE_EXPAND
    );

    // =================================================
    // MAIN TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Contact List",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        280, 20,
        700, 45,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // DESCRIPTION
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"List of contacts in your phone book.",
        WS_CHILD | WS_VISIBLE,
        310, 85,
        500, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // CONTACT LIST
    // =================================================

    hList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_LISTVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        LVS_REPORT |
        LVS_SINGLESEL |
        LVS_SHOWSELALWAYS,
        300, 125,
        680, 350,
        hwnd,
        (HMENU)ID_CONTACT_LIST,
        NULL,
        NULL
    );

    // =================================================
    // LIST COLUMNS
    // =================================================

    LVCOLUMNW column = {};

    column.mask = LVCF_TEXT | LVCF_WIDTH;

    column.pszText =
        const_cast<LPWSTR>(L"ID");

    column.cx = 60;

    ListView_InsertColumn(
        hList,
        0,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Name");

    column.cx = 150;

    ListView_InsertColumn(
        hList,
        1,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Phone");

    column.cx = 130;

    ListView_InsertColumn(
        hList,
        2,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Email");

    column.cx = 170;

    ListView_InsertColumn(
        hList,
        3,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Favorite");

    column.cx = 100;

    ListView_InsertColumn(
        hList,
        4,
        &column
    );

    // =================================================
    // VIEW BUTTON
    // =================================================

    hViewButton = CreateWindowW(
        L"BUTTON",
        L"View Contact",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        450, 510,
        150, 40,
        hwnd,
        (HMENU)ID_VIEW,
        NULL,
        NULL
    );

    // =================================================
    // CLOSE BUTTON
    // =================================================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        830, 510,
        130, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );

    // =================================================
    // SAMPLE DATA
    // =================================================

    loadSampleContacts();
}

// =====================================================
// SAMPLE CONTACTS
// =====================================================

void ContactList::loadSampleContacts()
{
    if (!hList)
        return;

    // Contact 1
    LVITEMW item = {};

    item.mask = LVIF_TEXT;
    item.iItem = 0;

    item.pszText =
        const_cast<LPWSTR>(L"1");

    ListView_InsertItem(
        hList,
        &item
    );

    ListView_SetItemText(
        hList,
        0,
        1,
        const_cast<LPWSTR>(L"NYC")
    );

    ListView_SetItemText(
        hList,
        0,
        2,
        const_cast<LPWSTR>(L"0900000001")
    );

    ListView_SetItemText(
        hList,
        0,
        3,
        const_cast<LPWSTR>(L"nyc@example.com")
    );

    ListView_SetItemText(
        hList,
        0,
        4,
        const_cast<LPWSTR>(L"No")
    );

    // Contact 2
    item.iItem = 1;

    item.pszText =
        const_cast<LPWSTR>(L"2");

    ListView_InsertItem(
        hList,
        &item
    );

    ListView_SetItemText(
        hList,
        1,
        1,
        const_cast<LPWSTR>(L"daddy")
    );

    ListView_SetItemText(
        hList,
        1,
        2,
        const_cast<LPWSTR>(L"0900000002")
    );

    ListView_SetItemText(
        hList,
        1,
        3,
        const_cast<LPWSTR>(L"daddy@example.com")
    );

    ListView_SetItemText(
        hList,
        1,
        4,
        const_cast<LPWSTR>(L"Yes")
    );
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK ContactList::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    ContactList* contactList =
        reinterpret_cast<ContactList*>(
            GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )
        );

    switch (uMsg)
    {
    case WM_NCCREATE:
    {
        CREATESTRUCTW* cs =
            reinterpret_cast<CREATESTRUCTW*>(
                lParam
            );

        contactList =
            reinterpret_cast<ContactList*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(
                contactList
            )
        );

        contactList->hWnd = hwnd;

        return TRUE;
    }

    case WM_CREATE:
    {
        contactList->createControls(hwnd);

        return 0;
    }

    case WM_COMMAND:
    {
        if (!contactList)
            break;

        switch (LOWORD(wParam))
        {
        case ID_VIEW:
        {
            int selected =
                ListView_GetNextItem(
                    contactList->hList,
                    -1,
                    LVNI_SELECTED
                );

            if (selected == -1)
            {
                MessageBoxW(
                    hwnd,
                    L"Please select a contact.",
                    L"View Contact",
                    MB_OK | MB_ICONWARNING
                );

                break;
            }

            MessageBoxW(
                hwnd,
                L"Contact information selected.",
                L"View Contact",
                MB_OK | MB_ICONINFORMATION
            );

            break;
        }

        case ID_CLOSE:
            DestroyWindow(hwnd);
            break;
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
        uMsg,
        wParam,
        lParam
    );
}

// =====================================================
// SHOW WINDOW
// =====================================================

bool ContactList::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    INITCOMMONCONTROLSEX icc = {};

    icc.dwSize =
        sizeof(INITCOMMONCONTROLSEX);

    icc.dwICC =
        ICC_TREEVIEW_CLASSES |
        ICC_LISTVIEW_CLASSES;

    InitCommonControlsEx(&icc);

    const wchar_t CLASS_NAME[] =
        L"PhoneBookContactListWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        ContactList::WindowProc;

    wc.hInstance =
        hInstance;

    wc.lpszClassName =
        CLASS_NAME;

    wc.hCursor =
        LoadCursorW(
            NULL,
            IDC_ARROW
        );

    wc.hbrBackground =
        reinterpret_cast<HBRUSH>(
            COLOR_BTNFACE + 1
        );

    RegisterClassW(&wc);

    hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Contact List - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1040,
        620,
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

    UpdateWindow(hWnd);

    MSG msg = {};

    while (
        GetMessageW(
            &msg,
            NULL,
            0,
            0
        )
    )
    {
        TranslateMessage(&msg);

        DispatchMessageW(&msg);
    }

    return true;
=======
#include "ContactList.h"

#include <windows.h>
#include <commctrl.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comctl32.lib")

#define ID_CONTACT_LIST  6001
#define ID_VIEW          6002
#define ID_CLOSE         6003

ContactList::ContactList()
{
    hWnd = NULL;

    hTree = NULL;
    hList = NULL;

    hViewButton = NULL;
    hCloseButton = NULL;
}

// =====================================================
// CREATE CONTROLS
// =====================================================

void ContactList::createControls(HWND hwnd)
{
    // =================================================
    // LEFT CATEGORY
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Category",
        WS_CHILD | WS_VISIBLE,
        15, 15,
        110, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_TREEVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        TVS_HASLINES |
        TVS_LINESATROOT |
        TVS_HASBUTTONS,
        15, 45,
        230, 550,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // TREE CATEGORY
    // =================================================

    TVINSERTSTRUCTW item = {};

    HTREEITEM accountNode;
    HTREEITEM contactsNode;
    HTREEITEM aboutNode;

    item.hParent = TVI_ROOT;
    item.hInsertAfter = TVI_LAST;
    item.item.mask = TVIF_TEXT;

    // Account
    item.item.pszText =
        const_cast<LPWSTR>(L"Account");

    accountNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = accountNode;

    item.item.pszText =
        const_cast<LPWSTR>(L"Update Account");

    TreeView_InsertItem(hTree, &item);

    // Contacts
    item.hParent = TVI_ROOT;

    item.item.pszText =
        const_cast<LPWSTR>(L"Contacts");

    contactsNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = contactsNode;

    item.item.pszText =
        const_cast<LPWSTR>(L"Contact List");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"Add Contact");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"Groups");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"Favorites");

    TreeView_InsertItem(hTree, &item);

    // About
    item.hParent = TVI_ROOT;

    item.item.pszText =
        const_cast<LPWSTR>(L"About");

    aboutNode =
        TreeView_InsertItem(hTree, &item);

    item.hParent = aboutNode;

    item.item.pszText =
        const_cast<LPWSTR>(L"Help");

    TreeView_InsertItem(hTree, &item);

    item.item.pszText =
        const_cast<LPWSTR>(L"About System");

    TreeView_InsertItem(hTree, &item);

    // Expand Contacts
    TreeView_Expand(
        hTree,
        contactsNode,
        TVE_EXPAND
    );

    // =================================================
    // MAIN TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Contact List",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        280, 20,
        700, 45,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // DESCRIPTION
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"List of contacts in your phone book.",
        WS_CHILD | WS_VISIBLE,
        310, 85,
        500, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =================================================
    // CONTACT LIST
    // =================================================

    hList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_LISTVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        LVS_REPORT |
        LVS_SINGLESEL |
        LVS_SHOWSELALWAYS,
        300, 125,
        680, 350,
        hwnd,
        (HMENU)ID_CONTACT_LIST,
        NULL,
        NULL
    );

    // =================================================
    // LIST COLUMNS
    // =================================================

    LVCOLUMNW column = {};

    column.mask = LVCF_TEXT | LVCF_WIDTH;

    column.pszText =
        const_cast<LPWSTR>(L"ID");

    column.cx = 60;

    ListView_InsertColumn(
        hList,
        0,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Name");

    column.cx = 150;

    ListView_InsertColumn(
        hList,
        1,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Phone");

    column.cx = 130;

    ListView_InsertColumn(
        hList,
        2,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Email");

    column.cx = 170;

    ListView_InsertColumn(
        hList,
        3,
        &column
    );

    column.pszText =
        const_cast<LPWSTR>(L"Favorite");

    column.cx = 100;

    ListView_InsertColumn(
        hList,
        4,
        &column
    );

    // =================================================
    // VIEW BUTTON
    // =================================================

    hViewButton = CreateWindowW(
        L"BUTTON",
        L"View Contact",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        450, 510,
        150, 40,
        hwnd,
        (HMENU)ID_VIEW,
        NULL,
        NULL
    );

    // =================================================
    // CLOSE BUTTON
    // =================================================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        830, 510,
        130, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );

    // =================================================
    // SAMPLE DATA
    // =================================================

    loadSampleContacts();
}

// =====================================================
// SAMPLE CONTACTS
// =====================================================

void ContactList::loadSampleContacts()
{
    if (!hList)
        return;

    // Contact 1
    LVITEMW item = {};

    item.mask = LVIF_TEXT;
    item.iItem = 0;

    item.pszText =
        const_cast<LPWSTR>(L"1");

    ListView_InsertItem(
        hList,
        &item
    );

    ListView_SetItemText(
        hList,
        0,
        1,
        const_cast<LPWSTR>(L"NYC")
    );

    ListView_SetItemText(
        hList,
        0,
        2,
        const_cast<LPWSTR>(L"0900000001")
    );

    ListView_SetItemText(
        hList,
        0,
        3,
        const_cast<LPWSTR>(L"nyc@example.com")
    );

    ListView_SetItemText(
        hList,
        0,
        4,
        const_cast<LPWSTR>(L"No")
    );

    // Contact 2
    item.iItem = 1;

    item.pszText =
        const_cast<LPWSTR>(L"2");

    ListView_InsertItem(
        hList,
        &item
    );

    ListView_SetItemText(
        hList,
        1,
        1,
        const_cast<LPWSTR>(L"daddy")
    );

    ListView_SetItemText(
        hList,
        1,
        2,
        const_cast<LPWSTR>(L"0900000002")
    );

    ListView_SetItemText(
        hList,
        1,
        3,
        const_cast<LPWSTR>(L"daddy@example.com")
    );

    ListView_SetItemText(
        hList,
        1,
        4,
        const_cast<LPWSTR>(L"Yes")
    );
}

// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK ContactList::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    ContactList* contactList =
        reinterpret_cast<ContactList*>(
            GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )
        );

    switch (uMsg)
    {
    case WM_NCCREATE:
    {
        CREATESTRUCTW* cs =
            reinterpret_cast<CREATESTRUCTW*>(
                lParam
            );

        contactList =
            reinterpret_cast<ContactList*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(
                contactList
            )
        );

        contactList->hWnd = hwnd;

        return TRUE;
    }

    case WM_CREATE:
    {
        contactList->createControls(hwnd);

        return 0;
    }

    case WM_COMMAND:
    {
        if (!contactList)
            break;

        switch (LOWORD(wParam))
        {
        case ID_VIEW:
        {
            int selected =
                ListView_GetNextItem(
                    contactList->hList,
                    -1,
                    LVNI_SELECTED
                );

            if (selected == -1)
            {
                MessageBoxW(
                    hwnd,
                    L"Please select a contact.",
                    L"View Contact",
                    MB_OK | MB_ICONWARNING
                );

                break;
            }

            MessageBoxW(
                hwnd,
                L"Contact information selected.",
                L"View Contact",
                MB_OK | MB_ICONINFORMATION
            );

            break;
        }

        case ID_CLOSE:
            DestroyWindow(hwnd);
            break;
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
        uMsg,
        wParam,
        lParam
    );
}

// =====================================================
// SHOW WINDOW
// =====================================================

bool ContactList::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    INITCOMMONCONTROLSEX icc = {};

    icc.dwSize =
        sizeof(INITCOMMONCONTROLSEX);

    icc.dwICC =
        ICC_TREEVIEW_CLASSES |
        ICC_LISTVIEW_CLASSES;

    InitCommonControlsEx(&icc);

    const wchar_t CLASS_NAME[] =
        L"PhoneBookContactListWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        ContactList::WindowProc;

    wc.hInstance =
        hInstance;

    wc.lpszClassName =
        CLASS_NAME;

    wc.hCursor =
        LoadCursorW(
            NULL,
            IDC_ARROW
        );

    wc.hbrBackground =
        reinterpret_cast<HBRUSH>(
            COLOR_BTNFACE + 1
        );

    RegisterClassW(&wc);

    hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Contact List - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1040,
        620,
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

    UpdateWindow(hWnd);

    MSG msg = {};

    while (
        GetMessageW(
            &msg,
            NULL,
            0,
            0
        )
    )
    {
        TranslateMessage(&msg);

        DispatchMessageW(&msg);
    }

    return true;
>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
}