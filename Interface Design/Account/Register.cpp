<<<<<<< HEAD
#include "Register.h"

#include <windows.h>
#include <string>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define ID_USERNAME        7001
#define ID_PASSWORD        7002
#define ID_FULLNAME        7003
#define ID_EMAIL           7004
#define ID_PHONE           7005

#define ID_REGISTER        7006
#define ID_CLEAR           7007
#define ID_CANCEL          7008
#define ID_CLOSE           7009


Register::Register()
{
    hWnd = NULL;

    hUsername = NULL;
    hPassword = NULL;
    hFullName = NULL;
    hEmail = NULL;
    hPhone = NULL;

    hRegisterButton = NULL;
    hClearButton = NULL;
    hCancelButton = NULL;
    hCloseButton = NULL;
}


// =====================================================
// CREATE CONTROLS
// =====================================================

void Register::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Register An Account",
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


    // =================================================
    // USERNAME
    // =================================================

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


    // =================================================
    // PASSWORD
    // =================================================

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


    // =================================================
    // FULL NAME
    // =================================================

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


    // =================================================
    // EMAIL
    // =================================================

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


    // =================================================
    // PHONE
    // =================================================

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


    // =================================================
    // REGISTER BUTTON
    // =================================================

    hRegisterButton = CreateWindowW(
        L"BUTTON",
        L"Register",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        430, 370,
        140, 40,
        hwnd,
        (HMENU)ID_REGISTER,
        NULL,
        NULL
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
        590, 370,
        140, 40,
        hwnd,
        (HMENU)ID_CLEAR,
        NULL,
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
        750, 370,
        140, 40,
        hwnd,
        (HMENU)ID_CANCEL,
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
        850, 470,
        130, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}


// =====================================================
// CLEAR FIELDS
// =====================================================

void Register::clearFields()
{
    SetWindowTextW(
        hUsername,
        L""
    );

    SetWindowTextW(
        hPassword,
        L""
    );

    SetWindowTextW(
        hFullName,
        L""
    );

    SetWindowTextW(
        hEmail,
        L""
    );

    SetWindowTextW(
        hPhone,
        L""
    );

    SetFocus(hUsername);
}


// =====================================================
// REGISTER ACCOUNT
// =====================================================

void Register::registerAccount()
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


    // =================================================
    // BASIC VALIDATION
    // =================================================

    if (user.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter username.",
            L"Register",
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
            L"Register",
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
            L"Register",
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
            L"Register",
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
            L"Register",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPhone);
        return;
    }


    // =================================================
    // UI STAGE ONLY
    // =================================================

    MessageBoxW(
        hWnd,
        L"Registration information received.",
        L"Register",
        MB_OK | MB_ICONINFORMATION
    );
}


// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK Register::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    Register* registerWindow =
        reinterpret_cast<Register*>(
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

        registerWindow =
            reinterpret_cast<Register*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(
                registerWindow
            )
        );

        registerWindow->hWnd = hwnd;

        return TRUE;
    }


    case WM_CREATE:
    {
        registerWindow->createControls(hwnd);

        return 0;
    }


    case WM_COMMAND:
    {
        if (!registerWindow)
            break;


        switch (LOWORD(wParam))
        {
        case ID_REGISTER:

            registerWindow->registerAccount();

            break;


        case ID_CLEAR:

            registerWindow->clearFields();

            break;


        case ID_CANCEL:

            registerWindow->clearFields();

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

bool Register::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);


    const wchar_t CLASS_NAME[] =
        L"PhoneBookRegisterWindow";


    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        Register::WindowProc;

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
        L"Register - Phone Book Management System",
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
=======
#include "Register.h"

#include <windows.h>
#include <string>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define ID_USERNAME        7001
#define ID_PASSWORD        7002
#define ID_FULLNAME        7003
#define ID_EMAIL           7004
#define ID_PHONE           7005

#define ID_REGISTER        7006
#define ID_CLEAR           7007
#define ID_CANCEL          7008
#define ID_CLOSE           7009


Register::Register()
{
    hWnd = NULL;

    hUsername = NULL;
    hPassword = NULL;
    hFullName = NULL;
    hEmail = NULL;
    hPhone = NULL;

    hRegisterButton = NULL;
    hClearButton = NULL;
    hCancelButton = NULL;
    hCloseButton = NULL;
}


// =====================================================
// CREATE CONTROLS
// =====================================================

void Register::createControls(HWND hwnd)
{
    // =================================================
    // TITLE
    // =================================================

    CreateWindowW(
        L"STATIC",
        L"Register An Account",
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


    // =================================================
    // USERNAME
    // =================================================

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


    // =================================================
    // PASSWORD
    // =================================================

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


    // =================================================
    // FULL NAME
    // =================================================

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


    // =================================================
    // EMAIL
    // =================================================

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


    // =================================================
    // PHONE
    // =================================================

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


    // =================================================
    // REGISTER BUTTON
    // =================================================

    hRegisterButton = CreateWindowW(
        L"BUTTON",
        L"Register",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        430, 370,
        140, 40,
        hwnd,
        (HMENU)ID_REGISTER,
        NULL,
        NULL
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
        590, 370,
        140, 40,
        hwnd,
        (HMENU)ID_CLEAR,
        NULL,
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
        750, 370,
        140, 40,
        hwnd,
        (HMENU)ID_CANCEL,
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
        850, 470,
        130, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}


// =====================================================
// CLEAR FIELDS
// =====================================================

void Register::clearFields()
{
    SetWindowTextW(
        hUsername,
        L""
    );

    SetWindowTextW(
        hPassword,
        L""
    );

    SetWindowTextW(
        hFullName,
        L""
    );

    SetWindowTextW(
        hEmail,
        L""
    );

    SetWindowTextW(
        hPhone,
        L""
    );

    SetFocus(hUsername);
}


// =====================================================
// REGISTER ACCOUNT
// =====================================================

void Register::registerAccount()
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


    // =================================================
    // BASIC VALIDATION
    // =================================================

    if (user.empty())
    {
        MessageBoxW(
            hWnd,
            L"Please enter username.",
            L"Register",
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
            L"Register",
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
            L"Register",
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
            L"Register",
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
            L"Register",
            MB_OK | MB_ICONWARNING
        );

        SetFocus(hPhone);
        return;
    }


    // =================================================
    // UI STAGE ONLY
    // =================================================

    MessageBoxW(
        hWnd,
        L"Registration information received.",
        L"Register",
        MB_OK | MB_ICONINFORMATION
    );
}


// =====================================================
// WINDOW PROCEDURE
// =====================================================

LRESULT CALLBACK Register::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    Register* registerWindow =
        reinterpret_cast<Register*>(
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

        registerWindow =
            reinterpret_cast<Register*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(
                registerWindow
            )
        );

        registerWindow->hWnd = hwnd;

        return TRUE;
    }


    case WM_CREATE:
    {
        registerWindow->createControls(hwnd);

        return 0;
    }


    case WM_COMMAND:
    {
        if (!registerWindow)
            break;


        switch (LOWORD(wParam))
        {
        case ID_REGISTER:

            registerWindow->registerAccount();

            break;


        case ID_CLEAR:

            registerWindow->clearFields();

            break;


        case ID_CANCEL:

            registerWindow->clearFields();

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

bool Register::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);


    const wchar_t CLASS_NAME[] =
        L"PhoneBookRegisterWindow";


    WNDCLASSW wc = {};

    wc.lpfnWndProc =
        Register::WindowProc;

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
        L"Register - Phone Book Management System",
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
>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
}