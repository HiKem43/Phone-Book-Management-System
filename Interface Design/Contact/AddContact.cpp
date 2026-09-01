#include "AddContact.h"

#include <windows.h>
#include <string>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define ID_NAME       5001
#define ID_PHONE      5002
#define ID_EMAIL      5003
#define ID_ADDRESS    5004
#define ID_GROUP      5005
#define ID_FAVORITE   5006

#define ID_SAVE       5007
#define ID_CANCEL     5008
#define ID_CLOSE      5009


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
    hCloseButton = NULL;
}


void AddContact::createControls(HWND hwnd)
{
    // =========================
    // TITLE
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Add Contact",
        WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
        300, 25, 650, 40,
        hwnd,
        NULL,
        NULL,
        NULL
    );


    // =========================
    // NAME
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Name:",
        WS_CHILD | WS_VISIBLE,
        350, 100, 100, 25,
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
        470, 95, 400, 30,
        hwnd,
        (HMENU)ID_NAME,
        NULL,
        NULL
    );


    // =========================
    // PHONE
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Phone:",
        WS_CHILD | WS_VISIBLE,
        350, 150, 100, 25,
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
        470, 145, 400, 30,
        hwnd,
        (HMENU)ID_PHONE,
        NULL,
        NULL
    );


    // =========================
    // EMAIL
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Email:",
        WS_CHILD | WS_VISIBLE,
        350, 200, 100, 25,
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
        470, 195, 400, 30,
        hwnd,
        (HMENU)ID_EMAIL,
        NULL,
        NULL
    );


    // =========================
    // ADDRESS
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Address:",
        WS_CHILD | WS_VISIBLE,
        350, 250, 100, 25,
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
        470, 245, 400, 30,
        hwnd,
        (HMENU)ID_ADDRESS,
        NULL,
        NULL
    );


    // =========================
    // GROUP
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Group:",
        WS_CHILD | WS_VISIBLE,
        350, 300, 100, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hGroup = CreateWindowW(
        L"COMBOBOX",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        CBS_DROPDOWNLIST |
        WS_VSCROLL,
        470, 295, 400, 120,
        hwnd,
        (HMENU)ID_GROUP,
        NULL,
        NULL
    );

    // Các nhóm hiện tại chỉ là lựa chọn giao diện.
    // Sau này có thể lấy dữ liệu Group từ phần Group Management.

    SendMessageW(
        hGroup,
        CB_ADDSTRING,
        0,
        (LPARAM)L"None"
    );

    SendMessageW(
        hGroup,
        CB_ADDSTRING,
        0,
        (LPARAM)L"Family"
    );

    SendMessageW(
        hGroup,
        CB_ADDSTRING,
        0,
        (LPARAM)L"Friend"
    );

    SendMessageW(
        hGroup,
        CB_ADDSTRING,
        0,
        (LPARAM)L"Work"
    );

    SendMessageW(
        hGroup,
        CB_SETCURSEL,
        0,
        0
    );


    // =========================
    // FAVORITE
    // =========================

    hFavorite = CreateWindowW(
        L"BUTTON",
        L"Favorite",
        WS_CHILD |
        WS_VISIBLE |
        BS_AUTOCHECKBOX,
        470, 345, 150, 30,
        hwnd,
        (HMENU)ID_FAVORITE,
        NULL,
        NULL
    );

    // Mặc định không phải Favorite.
    SendMessageW(
        hFavorite,
        BM_SETCHECK,
        BST_UNCHECKED,
        0
    );


    // =========================
    // SAVE
    // =========================

    hSaveButton = CreateWindowW(
        L"BUTTON",
        L"Save",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        470, 420, 130, 40,
        hwnd,
        (HMENU)ID_SAVE,
        NULL,
        NULL
    );


    // =========================
    // CANCEL
    // =========================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        620, 420, 130, 40,
        hwnd,
        (HMENU)ID_CANCEL,
        NULL,
        NULL
    );


    // =========================
    // CLOSE
    // =========================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        770, 420, 130, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}


void AddContact::clearFields()
{
    SetWindowTextW(hName, L"");
    SetWindowTextW(hPhone, L"");
    SetWindowTextW(hEmail, L"");
    SetWindowTextW(hAddress, L"");

    SendMessageW(
        hGroup,
        CB_SETCURSEL,
        0,
        0
    );

    SendMessageW(
        hFavorite,
        BM_SETCHECK,
        BST_UNCHECKED,
        0
    );

    SetFocus(hName);
}


void AddContact::saveContact()
{
    wchar_t name[200];
    wchar_t phone[100];
    wchar_t email[200];
    wchar_t address[300];

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

    std::wstring contactName(name);
    std::wstring contactPhone(phone);
    std::wstring contactEmail(email);
    std::wstring contactAddress(address);


    // =========================
    // BASIC VALIDATION
    // =========================

    if (contactName.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter contact name.",
            L"Add Contact",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hName);
        return;
    }

    if (contactPhone.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter phone number.",
            L"Add Contact",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPhone);
        return;
    }


    // =========================
    // GET FAVORITE STATUS
    // =========================

    LRESULT favoriteState = SendMessageW(
        hFavorite,
        BM_GETCHECK,
        0,
        0
    );

    bool isFavorite =
        (favoriteState == BST_CHECKED);


    // =========================
    // UI STAGE ONLY
    // =========================

    // Chưa kết nối database.
    // Chưa tự tạo Contact object của thành viên khác.
    // Chỉ kiểm tra giao diện và dữ liệu nhập.

    std::wstring message =
        L"Contact information received.\n\n"
        L"Name: " + contactName +
        L"\nPhone: " + contactPhone +
        L"\nEmail: " + contactEmail +
        L"\nAddress: " + contactAddress +
        L"\nFavorite: " +
        std::wstring(
            isFavorite ? L"Yes" : L"No"
        );

    MessageBoxW(
        hWnd,
        message.c_str(),
        L"Add Contact",
        MB_OK | MB_ICONINFORMATION
    );
}


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
        CREATESTRUCTW* cs =
            reinterpret_cast<CREATESTRUCTW*>(lParam);

        addContact =
            reinterpret_cast<AddContact*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(addContact)
        );

        addContact->hWnd = hwnd;

        return TRUE;
    }


    case WM_CREATE:
    {
        addContact->createControls(hwnd);
        return 0;
    }


    case WM_COMMAND:
    {
        if (!addContact)
            break;

        switch (LOWORD(wParam))
        {
        case ID_SAVE:
            addContact->saveContact();
            break;

        case ID_CANCEL:
            addContact->clearFields();
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


bool AddContact::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    const wchar_t CLASS_NAME[] =
        L"PhoneBookAddContactWindow";


    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        AddContact::WindowProc;

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
        L"Add Contact - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1050,
        540,
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
}