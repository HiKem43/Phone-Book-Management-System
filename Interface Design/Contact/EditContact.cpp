<<<<<<< HEAD
#include "EditContact.h"

#include <windows.h>
#include <commctrl.h>
#include <string>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comctl32.lib")

#define ID_NAME       6001
#define ID_PHONE      6002
#define ID_EMAIL      6003
#define ID_ADDRESS    6004
#define ID_GROUP      6005
#define ID_FAVORITE   6006

#define ID_SAVE       6007
#define ID_CANCEL     6008
#define ID_CLOSE      6009

#define ID_TREE       6010


EditContact::EditContact()
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
    hCloseButton = NULL;

    hTree = NULL;
}


// ============================================================
// CREATE CONTROLS
// ============================================================

void EditContact::createControls(HWND hwnd)
{
    // --------------------------------------------------------
    // CATEGORY
    // --------------------------------------------------------

    CreateWindowW(
        L"STATIC",
        L"Category",
        WS_CHILD | WS_VISIBLE,
        20, 20, 120, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // --------------------------------------------------------
    // TREE VIEW
    // --------------------------------------------------------

    hTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_TREEVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        TVS_HASLINES |
        TVS_LINESATROOT |
        TVS_HASBUTTONS,
        20, 50, 250, 500,
        hwnd,
        (HMENU)ID_TREE,
        GetModuleHandleW(NULL),
        NULL
    );

    if (hTree != NULL)
    {
        TVINSERTSTRUCTW item = {};

        HTREEITEM accountNode;
        HTREEITEM contactsNode;
        HTREEITEM systemNode;
        HTREEITEM aboutNode;

        item.hParent = TVI_ROOT;
        item.hInsertAfter = TVI_LAST;
        item.item.mask = TVIF_TEXT;

        // Account
        item.item.pszText = const_cast<LPWSTR>(L"Account");
        accountNode = TreeView_InsertItem(hTree, &item);

        item.hParent = accountNode;
        item.item.pszText = const_cast<LPWSTR>(L"Login");
        TreeView_InsertItem(hTree, &item);

        item.hParent = accountNode;
        item.item.pszText = const_cast<LPWSTR>(L"Register");
        TreeView_InsertItem(hTree, &item);

        // Contacts
        item.hParent = TVI_ROOT;
        item.item.pszText = const_cast<LPWSTR>(L"Contacts");
        contactsNode = TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Contact List");
        TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Add Contact");
        TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Groups");
        TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Favorites");
        TreeView_InsertItem(hTree, &item);

        // System
        item.hParent = TVI_ROOT;
        item.item.pszText = const_cast<LPWSTR>(L"System");
        systemNode = TreeView_InsertItem(hTree, &item);

        item.hParent = systemNode;
        item.item.pszText = const_cast<LPWSTR>(L"Backup Data");
        TreeView_InsertItem(hTree, &item);

        item.hParent = systemNode;
        item.item.pszText = const_cast<LPWSTR>(L"Data Recovery");
        TreeView_InsertItem(hTree, &item);

        // About
        item.hParent = TVI_ROOT;
        item.item.pszText = const_cast<LPWSTR>(L"About");
        aboutNode = TreeView_InsertItem(hTree, &item);

        item.hParent = aboutNode;
        item.item.pszText = const_cast<LPWSTR>(L"Help");
        TreeView_InsertItem(hTree, &item);

        item.hParent = aboutNode;
        item.item.pszText = const_cast<LPWSTR>(L"About System");
        TreeView_InsertItem(hTree, &item);

        // Chỉ mở Contacts để người xem biết đang ở khu vực Contact
        TreeView_Expand(
            hTree,
            contactsNode,
            TVE_EXPAND
        );
    }


    // ========================================================
    // MAIN TITLE
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Edit Contact",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        300, 30, 700, 45,
        hwnd,
        NULL,
        NULL,
        NULL
    );


    // ========================================================
    // NAME
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Name:",
        WS_CHILD | WS_VISIBLE,
        350, 110, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hName = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 105, 400, 35,
        hwnd,
        (HMENU)ID_NAME,
        NULL,
        NULL
    );


    // ========================================================
    // PHONE
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Phone:",
        WS_CHILD | WS_VISIBLE,
        350, 165, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hPhone = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 160, 400, 35,
        hwnd,
        (HMENU)ID_PHONE,
        NULL,
        NULL
    );


    // ========================================================
    // EMAIL
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Email:",
        WS_CHILD | WS_VISIBLE,
        350, 220, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hEmail = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 215, 400, 35,
        hwnd,
        (HMENU)ID_EMAIL,
        NULL,
        NULL
    );


    // ========================================================
    // ADDRESS
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Address:",
        WS_CHILD | WS_VISIBLE,
        350, 275, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hAddress = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 270, 400, 35,
        hwnd,
        (HMENU)ID_ADDRESS,
        NULL,
        NULL
    );


    // ========================================================
    // GROUP
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Group:",
        WS_CHILD | WS_VISIBLE,
        350, 330, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hGroup = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 325, 400, 35,
        hwnd,
        (HMENU)ID_GROUP,
        NULL,
        NULL
    );


    // ========================================================
    // FAVORITE
    // ========================================================

    hFavorite = CreateWindowW(
        L"BUTTON",
        L"Favorite",
        WS_CHILD |
        WS_VISIBLE |
        BS_AUTOCHECKBOX,
        480, 380, 120, 30,
        hwnd,
        (HMENU)ID_FAVORITE,
        NULL,
        NULL
    );


    // ========================================================
    // SAVE
    // ========================================================

    hSaveButton = CreateWindowW(
        L"BUTTON",
        L"Save",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        450, 440, 140, 45,
        hwnd,
        (HMENU)ID_SAVE,
        NULL,
        NULL
    );


    // ========================================================
    // CANCEL
    // ========================================================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        620, 440, 140, 45,
        hwnd,
        (HMENU)ID_CANCEL,
        NULL,
        NULL
    );


    // ========================================================
    // BOTTOM CLOSE
    // ========================================================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        850, 560, 130, 45,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}


// ============================================================
// CLEAR FIELDS
// ============================================================

void EditContact::clearFields()
{
    SetWindowTextW(hName, L"");
    SetWindowTextW(hPhone, L"");
    SetWindowTextW(hEmail, L"");
    SetWindowTextW(hAddress, L"");
    SetWindowTextW(hGroup, L"");

    SendMessageW(
        hFavorite,
        BM_SETCHECK,
        BST_UNCHECKED,
        0
    );

    SetFocus(hName);
}


// ============================================================
// SAVE CONTACT
// ============================================================

void EditContact::saveContact()
{
    wchar_t name[200];
    wchar_t phone[100];
    wchar_t email[200];
    wchar_t address[300];
    wchar_t group[100];

    GetWindowTextW(
        hName,
        name,
        200
    );

    GetWindowTextW(
        hPhone,
        phone,
        100
    );

    GetWindowTextW(
        hEmail,
        email,
        200
    );

    GetWindowTextW(
        hAddress,
        address,
        300
    );

    GetWindowTextW(
        hGroup,
        group,
        100
    );

    std::wstring nameValue(name);
    std::wstring phoneValue(phone);
    std::wstring emailValue(email);
    std::wstring addressValue(address);
    std::wstring groupValue(group);

    // Kiểm tra dữ liệu bắt buộc
    if (nameValue.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter contact name.",
            L"Edit Contact",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hName);
        return;
    }

    if (phoneValue.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter phone number.",
            L"Edit Contact",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPhone);
        return;
    }

    /*
        Giai đoạn hiện tại chỉ làm Interface Design.

        Chưa kết nối database.

        Sau này phần backend/database của nhóm sẽ:
        - xác định Contact cần chỉnh sửa
        - cập nhật Name
        - cập nhật Phone
        - cập nhật Email
        - cập nhật Address
        - cập nhật Group
        - cập nhật isFavorite
    */

    MessageBoxW(
        hWnd,
        L"Contact information is valid.",
        L"Edit Contact",
        MB_OK | MB_ICONINFORMATION
    );
}


// ============================================================
// WINDOW PROCEDURE
// ============================================================

LRESULT CALLBACK EditContact::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    EditContact* editContact =
        reinterpret_cast<EditContact*>(
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
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        editContact =
            reinterpret_cast<EditContact*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(editContact)
        );

        editContact->hWnd = hwnd;

        return TRUE;
    }


    case WM_CREATE:
    {
        editContact->createControls(hwnd);
        return 0;
    }


    case WM_COMMAND:
    {
        if (editContact == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_SAVE:
            editContact->saveContact();
            break;

        case ID_CANCEL:
            editContact->clearFields();
            break;

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


// ============================================================
// SHOW WINDOW
// ============================================================

bool EditContact::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    // Khởi tạo Common Controls cho TreeView
    INITCOMMONCONTROLSEX icc = {};

    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_TREEVIEW_CLASSES;

    InitCommonControlsEx(&icc);


    const wchar_t CLASS_NAME[] =
        L"PhoneBookEditContactWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = EditContact::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground =
        reinterpret_cast<HBRUSH>(
            COLOR_BTNFACE + 1
        );

    RegisterClassW(&wc);


    CreateWindowExW(
        0,
        CLASS_NAME,
        L"Edit Contact - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1040,
        670,
        NULL,
        NULL,
        hInstance,
        this
    );


    if (hWnd == NULL)
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
#include "EditContact.h"

#include <windows.h>
#include <commctrl.h>
#include <string>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "comctl32.lib")

#define ID_NAME       6001
#define ID_PHONE      6002
#define ID_EMAIL      6003
#define ID_ADDRESS    6004
#define ID_GROUP      6005
#define ID_FAVORITE   6006

#define ID_SAVE       6007
#define ID_CANCEL     6008
#define ID_CLOSE      6009

#define ID_TREE       6010


EditContact::EditContact()
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
    hCloseButton = NULL;

    hTree = NULL;
}


// ============================================================
// CREATE CONTROLS
// ============================================================

void EditContact::createControls(HWND hwnd)
{
    // --------------------------------------------------------
    // CATEGORY
    // --------------------------------------------------------

    CreateWindowW(
        L"STATIC",
        L"Category",
        WS_CHILD | WS_VISIBLE,
        20, 20, 120, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // --------------------------------------------------------
    // TREE VIEW
    // --------------------------------------------------------

    hTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        WC_TREEVIEWW,
        L"",
        WS_CHILD |
        WS_VISIBLE |
        TVS_HASLINES |
        TVS_LINESATROOT |
        TVS_HASBUTTONS,
        20, 50, 250, 500,
        hwnd,
        (HMENU)ID_TREE,
        GetModuleHandleW(NULL),
        NULL
    );

    if (hTree != NULL)
    {
        TVINSERTSTRUCTW item = {};

        HTREEITEM accountNode;
        HTREEITEM contactsNode;
        HTREEITEM systemNode;
        HTREEITEM aboutNode;

        item.hParent = TVI_ROOT;
        item.hInsertAfter = TVI_LAST;
        item.item.mask = TVIF_TEXT;

        // Account
        item.item.pszText = const_cast<LPWSTR>(L"Account");
        accountNode = TreeView_InsertItem(hTree, &item);

        item.hParent = accountNode;
        item.item.pszText = const_cast<LPWSTR>(L"Login");
        TreeView_InsertItem(hTree, &item);

        item.hParent = accountNode;
        item.item.pszText = const_cast<LPWSTR>(L"Register");
        TreeView_InsertItem(hTree, &item);

        // Contacts
        item.hParent = TVI_ROOT;
        item.item.pszText = const_cast<LPWSTR>(L"Contacts");
        contactsNode = TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Contact List");
        TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Add Contact");
        TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Groups");
        TreeView_InsertItem(hTree, &item);

        item.hParent = contactsNode;
        item.item.pszText = const_cast<LPWSTR>(L"Favorites");
        TreeView_InsertItem(hTree, &item);

        // System
        item.hParent = TVI_ROOT;
        item.item.pszText = const_cast<LPWSTR>(L"System");
        systemNode = TreeView_InsertItem(hTree, &item);

        item.hParent = systemNode;
        item.item.pszText = const_cast<LPWSTR>(L"Backup Data");
        TreeView_InsertItem(hTree, &item);

        item.hParent = systemNode;
        item.item.pszText = const_cast<LPWSTR>(L"Data Recovery");
        TreeView_InsertItem(hTree, &item);

        // About
        item.hParent = TVI_ROOT;
        item.item.pszText = const_cast<LPWSTR>(L"About");
        aboutNode = TreeView_InsertItem(hTree, &item);

        item.hParent = aboutNode;
        item.item.pszText = const_cast<LPWSTR>(L"Help");
        TreeView_InsertItem(hTree, &item);

        item.hParent = aboutNode;
        item.item.pszText = const_cast<LPWSTR>(L"About System");
        TreeView_InsertItem(hTree, &item);

        // Chỉ mở Contacts để người xem biết đang ở khu vực Contact
        TreeView_Expand(
            hTree,
            contactsNode,
            TVE_EXPAND
        );
    }


    // ========================================================
    // MAIN TITLE
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Edit Contact",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        300, 30, 700, 45,
        hwnd,
        NULL,
        NULL,
        NULL
    );


    // ========================================================
    // NAME
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Name:",
        WS_CHILD | WS_VISIBLE,
        350, 110, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hName = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 105, 400, 35,
        hwnd,
        (HMENU)ID_NAME,
        NULL,
        NULL
    );


    // ========================================================
    // PHONE
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Phone:",
        WS_CHILD | WS_VISIBLE,
        350, 165, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hPhone = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 160, 400, 35,
        hwnd,
        (HMENU)ID_PHONE,
        NULL,
        NULL
    );


    // ========================================================
    // EMAIL
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Email:",
        WS_CHILD | WS_VISIBLE,
        350, 220, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hEmail = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 215, 400, 35,
        hwnd,
        (HMENU)ID_EMAIL,
        NULL,
        NULL
    );


    // ========================================================
    // ADDRESS
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Address:",
        WS_CHILD | WS_VISIBLE,
        350, 275, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hAddress = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 270, 400, 35,
        hwnd,
        (HMENU)ID_ADDRESS,
        NULL,
        NULL
    );


    // ========================================================
    // GROUP
    // ========================================================

    CreateWindowW(
        L"STATIC",
        L"Group:",
        WS_CHILD | WS_VISIBLE,
        350, 330, 100, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hGroup = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        480, 325, 400, 35,
        hwnd,
        (HMENU)ID_GROUP,
        NULL,
        NULL
    );


    // ========================================================
    // FAVORITE
    // ========================================================

    hFavorite = CreateWindowW(
        L"BUTTON",
        L"Favorite",
        WS_CHILD |
        WS_VISIBLE |
        BS_AUTOCHECKBOX,
        480, 380, 120, 30,
        hwnd,
        (HMENU)ID_FAVORITE,
        NULL,
        NULL
    );


    // ========================================================
    // SAVE
    // ========================================================

    hSaveButton = CreateWindowW(
        L"BUTTON",
        L"Save",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        450, 440, 140, 45,
        hwnd,
        (HMENU)ID_SAVE,
        NULL,
        NULL
    );


    // ========================================================
    // CANCEL
    // ========================================================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        620, 440, 140, 45,
        hwnd,
        (HMENU)ID_CANCEL,
        NULL,
        NULL
    );


    // ========================================================
    // BOTTOM CLOSE
    // ========================================================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        850, 560, 130, 45,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}


// ============================================================
// CLEAR FIELDS
// ============================================================

void EditContact::clearFields()
{
    SetWindowTextW(hName, L"");
    SetWindowTextW(hPhone, L"");
    SetWindowTextW(hEmail, L"");
    SetWindowTextW(hAddress, L"");
    SetWindowTextW(hGroup, L"");

    SendMessageW(
        hFavorite,
        BM_SETCHECK,
        BST_UNCHECKED,
        0
    );

    SetFocus(hName);
}


// ============================================================
// SAVE CONTACT
// ============================================================

void EditContact::saveContact()
{
    wchar_t name[200];
    wchar_t phone[100];
    wchar_t email[200];
    wchar_t address[300];
    wchar_t group[100];

    GetWindowTextW(
        hName,
        name,
        200
    );

    GetWindowTextW(
        hPhone,
        phone,
        100
    );

    GetWindowTextW(
        hEmail,
        email,
        200
    );

    GetWindowTextW(
        hAddress,
        address,
        300
    );

    GetWindowTextW(
        hGroup,
        group,
        100
    );

    std::wstring nameValue(name);
    std::wstring phoneValue(phone);
    std::wstring emailValue(email);
    std::wstring addressValue(address);
    std::wstring groupValue(group);

    // Kiểm tra dữ liệu bắt buộc
    if (nameValue.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter contact name.",
            L"Edit Contact",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hName);
        return;
    }

    if (phoneValue.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter phone number.",
            L"Edit Contact",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPhone);
        return;
    }

    /*
        Giai đoạn hiện tại chỉ làm Interface Design.

        Chưa kết nối database.

        Sau này phần backend/database của nhóm sẽ:
        - xác định Contact cần chỉnh sửa
        - cập nhật Name
        - cập nhật Phone
        - cập nhật Email
        - cập nhật Address
        - cập nhật Group
        - cập nhật isFavorite
    */

    MessageBoxW(
        hWnd,
        L"Contact information is valid.",
        L"Edit Contact",
        MB_OK | MB_ICONINFORMATION
    );
}


// ============================================================
// WINDOW PROCEDURE
// ============================================================

LRESULT CALLBACK EditContact::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    EditContact* editContact =
        reinterpret_cast<EditContact*>(
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
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        editContact =
            reinterpret_cast<EditContact*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(editContact)
        );

        editContact->hWnd = hwnd;

        return TRUE;
    }


    case WM_CREATE:
    {
        editContact->createControls(hwnd);
        return 0;
    }


    case WM_COMMAND:
    {
        if (editContact == NULL)
            break;

        switch (LOWORD(wParam))
        {
        case ID_SAVE:
            editContact->saveContact();
            break;

        case ID_CANCEL:
            editContact->clearFields();
            break;

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


// ============================================================
// SHOW WINDOW
// ============================================================

bool EditContact::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    // Khởi tạo Common Controls cho TreeView
    INITCOMMONCONTROLSEX icc = {};

    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_TREEVIEW_CLASSES;

    InitCommonControlsEx(&icc);


    const wchar_t CLASS_NAME[] =
        L"PhoneBookEditContactWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = EditContact::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground =
        reinterpret_cast<HBRUSH>(
            COLOR_BTNFACE + 1
        );

    RegisterClassW(&wc);


    CreateWindowExW(
        0,
        CLASS_NAME,
        L"Edit Contact - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1040,
        670,
        NULL,
        NULL,
        hInstance,
        this
    );


    if (hWnd == NULL)
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