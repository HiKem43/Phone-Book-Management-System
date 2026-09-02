<<<<<<< HEAD
#include "DeleteContact.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define ID_CONFIRM  6001
#define ID_CANCEL   6002
#define ID_CLOSE    6003

DeleteContact::DeleteContact()
{
    hWnd = NULL;

    hMessage = NULL;
    hConfirmButton = NULL;
    hCancelButton = NULL;
    hCloseButton = NULL;
}

void DeleteContact::createControls(HWND hwnd)
{
    // =========================
    // TITLE
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Delete Contact",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        40, 30, 620, 45,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =========================
    // CONFIRMATION MESSAGE
    // =========================

    hMessage = CreateWindowW(
        L"STATIC",
        L"Are you sure you want to delete this contact?",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER,
        70, 120, 560, 40,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =========================
    // INFORMATION
    // =========================

    CreateWindowW(
        L"STATIC",
        L"This action cannot be undone.",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER,
        70, 165, 560, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =========================
    // CONFIRM BUTTON
    // =========================

    hConfirmButton = CreateWindowW(
        L"BUTTON",
        L"Confirm",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        180, 230, 130, 45,
        hwnd,
        (HMENU)ID_CONFIRM,
        NULL,
        NULL
    );

    // =========================
    // CANCEL BUTTON
    // =========================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        330, 230, 130, 45,
        hwnd,
        (HMENU)ID_CANCEL,
        NULL,
        NULL
    );

    // =========================
    // CLOSE BUTTON
    // =========================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        510, 300, 100, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}

void DeleteContact::handleConfirm()
{
    /*
        UI stage only.

        Chưa kết nối database.
        Chưa thực hiện xóa Contact thật.

        Sau này:
            Confirm
            -> gửi yêu cầu Delete Contact
            -> kiểm tra Contact
            -> xóa dữ liệu
            -> trả về kết quả
    */

    MessageBoxW(
        hWnd,
        L"Delete request received.",
        L"Delete Contact",
        MB_OK | MB_ICONINFORMATION
    );
}

LRESULT CALLBACK DeleteContact::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    DeleteContact* deleteContact =
        reinterpret_cast<DeleteContact*>(
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

        deleteContact =
            reinterpret_cast<DeleteContact*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(deleteContact)
        );

        deleteContact->hWnd = hwnd;

        return TRUE;
    }

    case WM_CREATE:
    {
        deleteContact->createControls(hwnd);
        return 0;
    }

    case WM_COMMAND:
    {
        if (!deleteContact)
            break;

        switch (LOWORD(wParam))
        {
        case ID_CONFIRM:
            deleteContact->handleConfirm();
            break;

        case ID_CANCEL:
            DestroyWindow(hwnd);
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
        return 0;
    }

    return DefWindowProcW(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}

bool DeleteContact::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    const wchar_t CLASS_NAME[] =
        L"PhoneBookDeleteContactWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = DeleteContact::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(
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
        L"Delete Contact - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        720,
        400,
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

    return true;
=======
#include "DeleteContact.h"

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define ID_CONFIRM  6001
#define ID_CANCEL   6002
#define ID_CLOSE    6003

DeleteContact::DeleteContact()
{
    hWnd = NULL;

    hMessage = NULL;
    hConfirmButton = NULL;
    hCancelButton = NULL;
    hCloseButton = NULL;
}

void DeleteContact::createControls(HWND hwnd)
{
    // =========================
    // TITLE
    // =========================

    CreateWindowW(
        L"STATIC",
        L"Delete Contact",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER |
        WS_BORDER,
        40, 30, 620, 45,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =========================
    // CONFIRMATION MESSAGE
    // =========================

    hMessage = CreateWindowW(
        L"STATIC",
        L"Are you sure you want to delete this contact?",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER,
        70, 120, 560, 40,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =========================
    // INFORMATION
    // =========================

    CreateWindowW(
        L"STATIC",
        L"This action cannot be undone.",
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER,
        70, 165, 560, 30,
        hwnd,
        NULL,
        NULL,
        NULL
    );

    // =========================
    // CONFIRM BUTTON
    // =========================

    hConfirmButton = CreateWindowW(
        L"BUTTON",
        L"Confirm",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        180, 230, 130, 45,
        hwnd,
        (HMENU)ID_CONFIRM,
        NULL,
        NULL
    );

    // =========================
    // CANCEL BUTTON
    // =========================

    hCancelButton = CreateWindowW(
        L"BUTTON",
        L"Cancel",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        330, 230, 130, 45,
        hwnd,
        (HMENU)ID_CANCEL,
        NULL,
        NULL
    );

    // =========================
    // CLOSE BUTTON
    // =========================

    hCloseButton = CreateWindowW(
        L"BUTTON",
        L"Close",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        510, 300, 100, 40,
        hwnd,
        (HMENU)ID_CLOSE,
        NULL,
        NULL
    );
}

void DeleteContact::handleConfirm()
{
    /*
        UI stage only.

        Chưa kết nối database.
        Chưa thực hiện xóa Contact thật.

        Sau này:
            Confirm
            -> gửi yêu cầu Delete Contact
            -> kiểm tra Contact
            -> xóa dữ liệu
            -> trả về kết quả
    */

    MessageBoxW(
        hWnd,
        L"Delete request received.",
        L"Delete Contact",
        MB_OK | MB_ICONINFORMATION
    );
}

LRESULT CALLBACK DeleteContact::WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    DeleteContact* deleteContact =
        reinterpret_cast<DeleteContact*>(
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

        deleteContact =
            reinterpret_cast<DeleteContact*>(
                cs->lpCreateParams
            );

        SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(deleteContact)
        );

        deleteContact->hWnd = hwnd;

        return TRUE;
    }

    case WM_CREATE:
    {
        deleteContact->createControls(hwnd);
        return 0;
    }

    case WM_COMMAND:
    {
        if (!deleteContact)
            break;

        switch (LOWORD(wParam))
        {
        case ID_CONFIRM:
            deleteContact->handleConfirm();
            break;

        case ID_CANCEL:
            DestroyWindow(hwnd);
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
        return 0;
    }

    return DefWindowProcW(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}

bool DeleteContact::show()
{
    HINSTANCE hInstance =
        GetModuleHandleW(NULL);

    const wchar_t CLASS_NAME[] =
        L"PhoneBookDeleteContactWindow";

    WNDCLASSW wc = {};

    wc.lpfnWndProc = DeleteContact::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(
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
        L"Delete Contact - Phone Book Management System",
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        720,
        400,
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

    return true;
>>>>>>> ff3ea22c60233653ffdd4ef41a52ae67eba114ce
}