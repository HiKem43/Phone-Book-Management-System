#include "UpdateAccount.h"

#include <windows.h>
#include <string>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define ID_USERNAME     8001
#define ID_PASSWORD     8002
#define ID_FULLNAME     8003
#define ID_EMAIL        8004
#define ID_PHONE        8005

#define ID_UPDATE       8006
#define ID_CLEAR        8007
#define ID_CANCEL       8008
#define ID_CLOSE        8009


UpdateAccount::UpdateAccount()
{
    hWnd = NULL;

    hUsername = NULL;
    hPassword = NULL;
    hFullName = NULL;
    hEmail = NULL;
    hPhone = NULL;

    hUpdateButton = NULL;
    hClearButton = NULL;
    hCancelButton = NULL;
    hCloseButton = NULL;
}


// =====================================================
// CREATE CONTROLS
// =====================================================

void UpdateAccount::createControls(HWND hwnd)
{
    CreateWindowW(
        L"STATIC",
        L"Update Account",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        300, 25,
        650, 45,
        hwnd,
        NULL,
        NULL,
        NULL
    );


    // Username

    CreateWindowW(
        L"STATIC",
        L"Username:",
        WS_CHILD |
        WS_VISIBLE,
        340, 100,
        110, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hUsername = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        470, 95,
        400, 30,
        hwnd,
        (HMENU)ID_USERNAME,
        NULL,
        NULL
    );


    // Password

    CreateWindowW(
        L"STATIC",
        L"Password:",
        WS_CHILD |
        WS_VISIBLE,
        340, 150,
        110, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hPassword = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_PASSWORD |
        ES_AUTOHSCROLL,
        470, 145,
        400, 30,
        hwnd,
        (HMENU)ID_PASSWORD,
        NULL,
        NULL
    );


    // Full Name

    CreateWindowW(
        L"STATIC",
        L"Full Name:",
        WS_CHILD |
        WS_VISIBLE,
        340, 200,
        110, 25,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    hFullName = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD |
        WS_VISIBLE |
        ES_AUTOHSCROLL,
        470, 195,
        400, 30,
        hwnd,
        (HMENU)ID_FULLNAME,
        NULL,
        NULL
    );


    // Email

    CreateWindowW(
        L"STATIC",
        L"Email:",
        WS_CHILD |
        WS_VISIBLE,
        340, 250,
        110, 25,
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
        470, 245,
        400, 30,
        hwnd,
        (HMENU)ID_EMAIL,
        NULL,
        NULL
    );


    // Phone

    CreateWindowW(
        L"STATIC",
        L"Phone:",
        WS_CHILD |
        WS_VISIBLE,
        340, 300,
        110, 25,
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
        470, 295,
        400, 30,
        hwnd,
        (HMENU)ID_PHONE,
        NULL,
        NULL
    );


    // Update

    hUpdateButton = CreateWindowW(
        L"BUTTON",
        L"Update",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        400, 370,
        140, 40,
        hwnd,
        (HMENU)ID_UPDATE,
        NULL,
        NULL
    );


    // Clear

    hClearButton = CreateWindowW(
        L"BUTTON",
        L"Clear",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        560, 370,
        140, 40,
        hwnd,
        (HMENU)ID_CLEAR,
        NULL,
        NULL
    );


    // Cancel

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        720, 370,
        140, 40,
        hwnd,
        (HMENU)ID_CANCEL,
        NULL,
        NULL
    );


    // Close

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        850, 470,
        130, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}


// =====================================================
// CLEAR
// =====================================================

void UpdateAccount::clearFields()
{
    SetWindowTextW(hUsername, L"");
    SetWindowTextW(hPassword, L"");
    SetWindowTextW(hFullName, L"");
    SetWindowTextW(hEmail, L"");
    SetWindowTextW(hPhone, L"");

    SetFocus(hUsername);
}


// =====================================================
// UPDATE ACCOUNT
// =====================================================

void UpdateAccount::updateAccount()
{
    wchar_t username[100];
    wchar_t password[100];
    wchar_t fullName[200];
    wchar_t email[200];
    wchar_t phone[100];

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

    GetWindowTextW(
        hFullName,
        fullName,
        200
    );

    GetWindowTextW(
        hEmail,
        email,
        200
    );

    GetWindowTextW(
        hPhone,
        phone,
        100
    );


    std::wstring user(username);
    std::wstring pass(password);
    std::wstring name(fullName);
    std::wstring mail(email);
    std::wstring number(phone);


    if (user.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter username.",
            L"Update Account",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hUsername);
        return;
    }


    if (pass.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter password.",
            L"Update Account",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPassword);
        return;
    }


    if (name.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter full name.",
            L"Update Account",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hFullName);
        return;
    }


    if (mail.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter email.",
            L"Update Account",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hEmail);
        return;
    }


    if (number.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter phone number.",
            L"Update Account",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPhone);
        return;
    }


    // UI prototype only.
    // Database update will be connected later.

    MessageBoxW(
        hWnd,
        L"Account information updated.",
        L"Update Account",
        MB_OK | MB_ICONINFORMATION
    );
}


// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK UpdateAccount::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    UpdateAccount* updateAccount =
        reinterpret_cast<UpdateAccount*>(
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

        updateAccount =
            reinterpret_cast<UpdateAccount*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(
                updateAccount
            )
        );

        updateAccount->hWnd = hwnd;

        return TRUE;
    }


    case WM_CREATE:
    {
        updateAccount->createControls(hwnd);

        return 0;
    }


    case WM_COMMAND:
    {
        if (!updateAccount)
            break;


        switch (LOWORD(wParam))
        {
        case ID_UPDATE:

            updateAccount->updateAccount();

            break;


        case ID_CLEAR:

            updateAccount->clearFields();

            break;


        case ID_CANCEL:

            updateAccount->clearFields();

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


// =====================================================
// SHOW
// =====================================================

bool UpdateAccount::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);


    const wchar_t CLASS_NAME[] =
        L"PhoneBookUpdateAccountWindow";


    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        UpdateAccount::WindowProc;

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
        L"Update Account - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1050,
        570,
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