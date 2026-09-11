#include "MenuUI.h"
#include "ContactService.h"
#include <string>

namespace
{
    enum
    {
        ID_LOGIN = 100,
        ID_REGISTER,
        ID_REGISTER_SUBMIT,
        ID_FORGOT,
        ID_CLOSE,
        ID_BACK,
        ID_LOGOUT,
        ID_CONTACTS,
        ID_GROUPS,
        ID_FAVORITES,
        ID_ACCOUNT,
        ID_ADD,
        ID_EDIT,
        ID_DELETE,
        ID_DETAIL,
        ID_SEARCH,
        ID_SAVE,
        ID_UPDATE,
        ID_CANCEL,
        ID_ASSIGN,
        ID_USER_MGMT,
        ID_REPORTS,
        ID_BACKUP,
        ID_RECOVERY,
        ID_CHANGE_PASSWORD,
        ID_ADMIN_MENU,
        ID_ADD_USER,
        ID_EDIT_USER,
        ID_DELETE_USER,
        ID_CREATE_BACKUP,
        ID_DOWNLOAD,
        ID_BROWSE,
        ID_RESTORE,
        ID_REFRESH,
        ID_FILTER,
        ID_SORT,
        ID_FAVORITE_TOGGLE,
        ID_ADD_GROUP,
        ID_EDIT_GROUP,
        ID_DELETE_GROUP,
        ID_VIEW_GROUP,
        ID_SEARCH_GROUP,
        ID_REGISTER_LOGIN,
        ID_ACCOUNT_UPDATE,
        ID_DEMO_USER,
        ID_DEMO_ADMIN,
        ID_GROUP_DETAIL,
        ID_CONFIRM_RESTORE
    };

    constexpr const char* kClassName = "PhoneBookManagementUI";

    std::string getEditText(HWND parent, int id)
    {
        char buffer[512] = {};
        GetDlgItemTextA(parent, id, buffer, sizeof(buffer));
        return std::string(buffer);
    }

    bool validPhoneValue(const std::string& phone)
    {
        if (phone.length() < 10 || phone.length() > 11)
            return false;

        for (char c : phone)
            if (!std::isdigit(static_cast<unsigned char>(c)))
                return false;

        return true;
    }

    void populateContactList(HWND list)
    {
        SendMessageA(list, LB_RESETCONTENT, 0, 0);

        const auto& contacts = ContactService::getContacts();
        if (contacts.empty())
        {
            SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"No contacts yet.");
            return;
        }

        for (const auto& contact : contacts)
        {
            std::string line = contact.name + " | " + contact.phone + " | " + contact.email;
            SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)line.c_str());
        }
    }
}

MenuUI::MenuUI()
    : hWnd(nullptr), hTitleFont(nullptr), hSubtitleFont(nullptr), hNormalFont(nullptr),
      hButtonFont(nullptr), hSmallFont(nullptr), hIconFont(nullptr),
      currentScreen("login"), previousScreen("login"), currentRole("")
{
}

MenuUI::~MenuUI()
{
    if (hTitleFont) DeleteObject(hTitleFont);
    if (hSubtitleFont) DeleteObject(hSubtitleFont);
    if (hNormalFont) DeleteObject(hNormalFont);
    if (hButtonFont) DeleteObject(hButtonFont);
    if (hSmallFont) DeleteObject(hSmallFont);
    if (hIconFont) DeleteObject(hIconFont);
}

void MenuUI::createFonts()
{
    hTitleFont = CreateFontA(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    hSubtitleFont = CreateFontA(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    hNormalFont = CreateFontA(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    hButtonFont = CreateFontA(14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    hSmallFont = CreateFontA(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                             DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                             CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    hIconFont = CreateFontA(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, "Segoe UI Symbol");
}

void MenuUI::clearScreen()
{
    for (HWND control : screenControls)
    {
        if (IsWindow(control)) DestroyWindow(control);
    }
    screenControls.clear();

    HWND child = GetWindow(hWnd, GW_CHILD);
    while (child)
    {
        HWND next = GetWindow(child, GW_HWNDNEXT);
        DestroyWindow(child);
        child = next;
    }

    RECT rc{};
    GetClientRect(hWnd, &rc);
    FillRect(GetDC(hWnd), &rc, (HBRUSH)(COLOR_WINDOW + 1));
    RedrawWindow(hWnd, nullptr, nullptr,
                 RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ALLCHILDREN);
}

void MenuUI::createLabel(const char* text, int x, int y, int w, int h, bool title)
{
    HWND label = CreateWindowA("STATIC", text, WS_CHILD | WS_VISIBLE,
                               x, y, w, h, hWnd, nullptr, GetModuleHandle(nullptr), nullptr);
    SendMessageA(label, WM_SETFONT, (WPARAM)(title ? hTitleFont : hNormalFont), TRUE);
    screenControls.push_back(label);
}

HWND MenuUI::createButton(const char* text, int x, int y, int w, int h, int id)
{
    HWND button = CreateWindowA("BUTTON", text,
                                WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                                x, y, w, h, hWnd, (HMENU)(INT_PTR)id,
                                GetModuleHandle(nullptr), nullptr);
    SendMessageA(button, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
    screenControls.push_back(button);
    return button;
}

HWND MenuUI::createIconButton(const wchar_t* text, int x, int y, int w, int h, int id)
{
    HWND button = CreateWindowW(L"BUTTON", text,
                                WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                                x, y, w, h, hWnd, (HMENU)(INT_PTR)id,
                                GetModuleHandleW(nullptr), nullptr);
    SendMessageW(button, WM_SETFONT, (WPARAM)hIconFont, TRUE);
    screenControls.push_back(button);
    return button;
}

HWND MenuUI::createEdit(const char* text, int x, int y, int w, int h, int id, bool password)
{
    DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL;
    if (password) style |= ES_PASSWORD;
    HWND edit = CreateWindowA("EDIT", text, style,
                              x, y, w, h, hWnd, (HMENU)(INT_PTR)id,
                              GetModuleHandle(nullptr), nullptr);
    SendMessageA(edit, WM_SETFONT, (WPARAM)hNormalFont, TRUE);
    screenControls.push_back(edit);
    return edit;
}

HWND MenuUI::createList(int x, int y, int w, int h, int id)
{
    HWND list = CreateWindowA("LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
                              x, y, w, h, hWnd, (HMENU)(INT_PTR)id,
                              GetModuleHandle(nullptr), nullptr);
    SendMessageA(list, WM_SETFONT, (WPARAM)hNormalFont, TRUE);
    screenControls.push_back(list);
    return list;
}

HWND MenuUI::createCombo(const char* text, int x, int y, int w, int h, int id)
{
    HWND combo = CreateWindowA("COMBOBOX", "", WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
                               x, y, w, h, hWnd, (HMENU)(INT_PTR)id,
                               GetModuleHandle(nullptr), nullptr);
    SendMessageA(combo, WM_SETFONT, (WPARAM)hNormalFont, TRUE);
    if (text)
    {
        SendMessageA(combo, CB_ADDSTRING, 0, (LPARAM)text);
        SendMessageA(combo, CB_SETCURSEL, 0, 0);
    }
    screenControls.push_back(combo);
    return combo;
}

void MenuUI::createBackButton(int id)
{
    createButton("< Back", 30, 535, 110, 40, id);
}

void MenuUI::createHeader(const char* title, const char* subtitle)
{
    createLabel(title, 30, 22, 680, 42, true);
    if (subtitle) createLabel(subtitle, 32, 67, 760, 32, false);
}

void MenuUI::createRoleBadge(const char* role)
{
    std::string text = "Current role: ";
    text += role;
    createLabel(text.c_str(), 650, 25, 160, 30, false);
}

void MenuUI::showScreen(const std::string& screen)
{
    previousScreen = currentScreen;
    currentScreen = screen;
    clearScreen();

    if (screen == "login") showLogin();
    else if (screen == "register") showRegister();
    else if (screen == "user") showUserMenu();
    else if (screen == "admin") showAdminMenu();
    else if (screen == "contacts") showContacts();
    else if (screen == "add_contact") showAddContact();
    else if (screen == "edit_contact") showEditContact();
    else if (screen == "delete_contact") showDeleteContact();
    else if (screen == "detail_contact") showContactDetail();
    else if (screen == "search") showSearchContacts();
    else if (screen == "groups") showGroups();
    else if (screen == "add_group") showAddGroup();
    else if (screen == "edit_group") showEditGroup();
    else if (screen == "delete_group") showDeleteGroup();
    else if (screen == "group_detail") showGroupDetail();
    else if (screen == "assign_contact") showAssignContact();
    else if (screen == "favorites") showFavorites();
    else if (screen == "account") showAccount();
    else if (screen == "change_password") showChangePassword();
    else if (screen == "users") showUserManagement();
    else if (screen == "add_user") showAddUser();
    else if (screen == "edit_user") showEditUser();
    else if (screen == "delete_user") showDeleteUser();
    else if (screen == "reports") showSystemReports();
    else if (screen == "backup") showBackup();
    else if (screen == "recovery") showRecovery();
    else if (screen == "forgot") showForgotPassword();

    InvalidateRect(hWnd, nullptr, TRUE);
    UpdateWindow(hWnd);
}

void MenuUI::showLogin()
{
    createLabel("PHONE BOOK MANAGEMENT SYSTEM", 115, 45, 620, 50, true);
    createLabel("Login", 380, 112, 120, 35, true);

    createLabel("Username", 205, 170, 120, 30);
    createEdit("", 335, 165, 305, 35, 1001);
    createLabel("Password", 205, 225, 120, 30);
    createEdit("", 335, 220, 305, 35, 1002, true);

    createIconButton(L"🔐  Login", 175, 285, 215, 48, ID_LOGIN);
    createIconButton(L"🔍  Forgot Password", 405, 285, 240, 48, ID_FORGOT);
    createIconButton(L"✚  Register", 175, 350, 215, 48, ID_REGISTER);
    createIconButton(L"✕  Close", 405, 350, 240, 48, ID_CLOSE);
}

void MenuUI::showRegister()
{
    createHeader("Register An Account", "Create a new account before using the system.");
    createLabel("Username", 160, 120, 120, 30); createEdit("", 300, 115, 380, 35, 1101);
    createLabel("Password", 160, 170, 120, 30); createEdit("", 300, 165, 380, 35, 1102, true);
    createLabel("Full Name", 160, 220, 120, 30); createEdit("", 300, 215, 380, 35, 1103);
    createLabel("Email", 160, 270, 120, 30); createEdit("", 300, 265, 380, 35, 1104);
    createLabel("Phone", 160, 320, 120, 30); createEdit("", 300, 315, 380, 35, 1105);
    createButton("Register", 300, 380, 180, 45, ID_REGISTER_SUBMIT);
    createButton("Login", 500, 380, 180, 45, ID_REGISTER_LOGIN);
    createBackButton();
}

void MenuUI::showUserMenu()
{
    createHeader("User Menu", "Manage your personal contacts, groups and account.");
    createRoleBadge("User");
    createIconButton(L"☎  Contacts Management", 115, 130, 290, 58, ID_CONTACTS);
    createIconButton(L"▦  Group Management", 445, 130, 290, 58, ID_GROUPS);
    createIconButton(L"♥  Favorite Management", 115, 215, 290, 58, ID_FAVORITES);
    createIconButton(L"⚙  Manage User Account", 445, 215, 290, 58, ID_ACCOUNT);
    createIconButton(L"⎋  Logout", 280, 330, 290, 58, ID_LOGOUT);
}

void MenuUI::showAdminMenu()
{
    createHeader("Admin Menu", "Administration functions are available only to Admin accounts.");
    createRoleBadge("Admin");
    createIconButton(L"♙  User Management", 105, 125, 300, 58, ID_USER_MGMT);
    createIconButton(L"▤  View System Reports", 445, 125, 300, 58, ID_REPORTS);
    createIconButton(L"▣  Backup Data", 105, 210, 300, 58, ID_BACKUP);
    createIconButton(L"↻  Data Recovery", 445, 210, 300, 58, ID_RECOVERY);
    createIconButton(L"⎋  Logout", 280, 330, 290, 58, ID_LOGOUT);
}

void MenuUI::showContacts()
{
    createHeader("Contacts Management", "View and manage contacts belonging to the current account.");
    createEdit("Search contacts...", 60, 105, 390, 38, 1201);
    createIconButton(L"🔍", 455, 105, 55, 38, ID_SEARCH);
    createButton("+ Add Contact", 525, 105, 145, 38, ID_ADD);
    createIconButton(L"♥", 685, 105, 50, 38, ID_FAVORITE_TOGGLE);
    createIconButton(L"↕", 745, 105, 50, 38, ID_SORT);

    createLabel("Name", 60, 165, 120, 28);
    createLabel("Phone", 180, 165, 120, 28);
    createLabel("Email", 300, 165, 180, 28);
    createLabel("Group", 480, 165, 120, 28);
    createLabel("Favorite", 600, 165, 100, 28);

    HWND list = createList(60, 195, 735, 265, 1202);
    populateContactList(list);

    createIconButton(L"👁  View", 130, 475, 115, 42, ID_DETAIL);
    createIconButton(L"✎  Edit", 260, 475, 115, 42, ID_EDIT);
    createIconButton(L"🗑  Delete", 390, 475, 125, 42, ID_DELETE);
    createIconButton(L"♥  Favorite", 530, 475, 135, 42, ID_FAVORITE_TOGGLE);
    createBackButton();
}

void MenuUI::showAddContact()
{
    createHeader("Add Contact", "Enter contact information and save it to the current account.");
    createLabel("Name", 150, 115, 120, 30); createEdit("", 290, 110, 400, 35, 1301);
    createLabel("Phone", 150, 165, 120, 30); createEdit("", 290, 160, 400, 35, 1302);
    createLabel("Email", 150, 215, 120, 30); createEdit("", 290, 210, 400, 35, 1303);
    createLabel("Address", 150, 265, 120, 30); createEdit("", 290, 260, 400, 35, 1304);
    createLabel("Group", 150, 315, 120, 30); createCombo("No Group", 290, 310, 400, 35, 1305);
    createLabel("Favorite", 150, 365, 120, 30); createIconButton(L"♥  Mark as Favorite", 290, 360, 190, 38, ID_FAVORITE_TOGGLE);
    createButton("Save", 300, 425, 170, 45, ID_SAVE);
    createButton("Cancel", 500, 425, 170, 45, ID_CANCEL);
}

void MenuUI::showEditContact()
{
    createHeader("Edit Contact", "Update the selected contact.");
    createLabel("Name", 150, 115, 120, 30); createEdit("Selected contact name", 290, 110, 400, 35, 1401);
    createLabel("Phone", 150, 165, 120, 30); createEdit("", 290, 160, 400, 35, 1402);
    createLabel("Email", 150, 215, 120, 30); createEdit("", 290, 210, 400, 35, 1403);
    createLabel("Address", 150, 265, 120, 30); createEdit("", 290, 260, 400, 35, 1404);
    createLabel("Group", 150, 315, 120, 30); createCombo("No Group", 290, 310, 400, 35, 1405);
    createLabel("Favorite", 150, 365, 120, 30); createIconButton(L"♥  Favorite", 290, 360, 160, 38, ID_FAVORITE_TOGGLE);
    createButton("Update", 300, 425, 170, 45, ID_UPDATE);
    createButton("Cancel", 500, 425, 170, 45, ID_CANCEL);
}

void MenuUI::showDeleteContact()
{
    createHeader("Delete Contact", "Confirmation is required before removing data.");
    createLabel("Selected Contact", 220, 145, 180, 30);
    createLabel("Contact name will appear here", 400, 145, 270, 30);
    createLabel("Are you sure you want to delete this contact?", 180, 220, 500, 40, true);
    createIconButton(L"🗑  Confirm Delete", 245, 300, 190, 48, ID_DELETE);
    createButton("Cancel", 455, 300, 180, 48, ID_CANCEL);
    createBackButton();
}

void MenuUI::showContactDetail()
{
    createHeader("Contact Details", "View information of the selected contact.");
    createLabel("Name:", 190, 130, 120, 30); createLabel("Selected contact", 330, 130, 350, 30);
    createLabel("Phone:", 190, 180, 120, 30); createLabel("-", 330, 180, 350, 30);
    createLabel("Email:", 190, 230, 120, 30); createLabel("-", 330, 230, 350, 30);
    createLabel("Address:", 190, 280, 120, 30); createLabel("-", 330, 280, 350, 30);
    createLabel("Group:", 190, 330, 120, 30); createLabel("-", 330, 330, 350, 30);
    createLabel("Favorite:", 190, 380, 120, 30); createLabel("-", 330, 380, 350, 30);
    createButton("Edit", 300, 445, 150, 45, ID_EDIT);
    createBackButton();
}

void MenuUI::showSearchContacts()
{
    createHeader("Search Contacts", "Search by name, phone or email.");
    createEdit("Enter keyword...", 65, 110, 400, 38, 1501);
    createIconButton(L"🔍", 470, 110, 55, 38, ID_SEARCH);
    createButton("Filter", 540, 110, 105, 38, ID_FILTER);
    createButton("Sort", 660, 110, 105, 38, ID_SORT);
    createLabel("Search Result", 65, 165, 200, 30, true);
    HWND list = createList(65, 200, 700, 280, 1502);
    SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"Search results will be displayed here.");
    createBackButton();
}

void MenuUI::showGroups()
{
    createHeader("Group Management", "Create, view, edit, delete, search and assign contacts to groups.");
    createButton("+ Add Group", 535, 105, 120, 40, ID_ADD_GROUP);
    createIconButton(L"🔍", 665, 105, 55, 40, ID_SEARCH_GROUP);
    createIconButton(L"🗑", 730, 105, 55, 40, ID_DELETE_GROUP);
    createLabel("Group Name", 70, 165, 180, 30);
    createLabel("Description", 250, 165, 300, 30);
    createLabel("Contacts", 550, 165, 150, 30);
    HWND list = createList(70, 195, 700, 255, 1601);
    SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"Groups will be loaded here.");
    createButton("View", 125, 475, 100, 42, ID_VIEW_GROUP);
    createButton("Edit", 245, 475, 100, 42, ID_EDIT_GROUP);
    createButton("Delete", 365, 475, 100, 42, ID_DELETE_GROUP);
    createButton("Assign Contact", 485, 475, 145, 42, ID_ASSIGN);
    createBackButton();
}

void MenuUI::showAddGroup()
{
    createHeader("Add Group", "Create a group for organizing contacts.");
    createLabel("Group Name", 160, 150, 130, 30); createEdit("", 310, 145, 380, 35, 1701);
    createLabel("Description", 160, 210, 130, 30); createEdit("", 310, 205, 380, 35, 1702);
    createButton("Save", 310, 285, 170, 45, ID_SAVE);
    createButton("Cancel", 510, 285, 170, 45, ID_CANCEL);
}

void MenuUI::showEditGroup()
{
    createHeader("Edit Group", "Update the selected group.");
    createLabel("Group Name", 160, 150, 130, 30); createEdit("Selected group", 310, 145, 380, 35, 1801);
    createLabel("Description", 160, 210, 130, 30); createEdit("", 310, 205, 380, 35, 1802);
    createButton("Update", 310, 285, 170, 45, ID_UPDATE);
    createButton("Cancel", 510, 285, 170, 45, ID_CANCEL);
}

void MenuUI::showDeleteGroup()
{
    createHeader("Delete Group", "Confirm before deleting a group.");
    createLabel("Are you sure you want to delete this group?", 190, 190, 500, 40, true);
    createIconButton(L"🗑  Confirm Delete", 250, 270, 180, 48, ID_DELETE_GROUP);
    createButton("Cancel", 450, 270, 180, 48, ID_CANCEL);
    createBackButton();
}

void MenuUI::showGroupDetail()
{
    createHeader("Group Details", "View the selected group and its contacts.");
    createLabel("Group Name:", 170, 130, 140, 30); createLabel("Selected group", 320, 130, 350, 30);
    createLabel("Description:", 170, 180, 140, 30); createLabel("-", 320, 180, 350, 30);
    createLabel("Contacts in Group", 170, 240, 250, 30, true);
    HWND list = createList(170, 280, 500, 170, 1950);
    SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"Contacts assigned to this group will appear here.");
    createBackButton();
}

void MenuUI::showAssignContact()
{
    createHeader("Assign Contact to Group", "Select a contact and a group.");
    createLabel("Contact", 160, 150, 120, 30); createCombo("Select Contact", 300, 145, 390, 35, 1901);
    createLabel("Group", 160, 210, 120, 30); createCombo("Select Group", 300, 205, 390, 35, 1902);
    createButton("Assign", 310, 285, 170, 45, ID_ASSIGN);
    createButton("Cancel", 510, 285, 170, 45, ID_CANCEL);
}

void MenuUI::showFavorites()
{
    createHeader("Favorite Management", "View contacts marked as favorite.");
    createIconButton(L"♥  Favorites", 650, 105, 140, 38, ID_FAVORITE_TOGGLE);
    createLabel("Name", 80, 160, 180, 30);
    createLabel("Phone", 260, 160, 180, 30);
    createLabel("Email", 440, 160, 200, 30);
    HWND list = createList(80, 190, 680, 260, 2001);
    SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"Favorite contacts will be displayed here.");
    createIconButton(L"♥  Remove Favorite", 300, 475, 180, 45, ID_FAVORITE_TOGGLE);
    createBackButton();
}

void MenuUI::showAccount()
{
    createHeader("Manage User Account", "View and update the current account.");
    createLabel("Username", 160, 120, 130, 30); createEdit("Current username", 310, 115, 390, 35, 2101);
    createLabel("Full Name", 160, 170, 130, 30); createEdit("Current full name", 310, 165, 390, 35, 2102);
    createLabel("Email", 160, 220, 130, 30); createEdit("Current email", 310, 215, 390, 35, 2103);
    createLabel("Phone", 160, 270, 130, 30); createEdit("Current phone", 310, 265, 390, 35, 2104);
    createButton("Update Profile", 300, 330, 180, 45, ID_ACCOUNT_UPDATE);
    createButton("Change Password", 500, 330, 180, 45, ID_CHANGE_PASSWORD);
    createBackButton();
}

void MenuUI::showChangePassword()
{
    createHeader("Change Password", "Change the password of the current account.");
    createLabel("Old Password", 160, 140, 130, 30); createEdit("", 310, 135, 390, 35, 2201, true);
    createLabel("New Password", 160, 195, 130, 30); createEdit("", 310, 190, 390, 35, 2202, true);
    createLabel("Confirm Password", 160, 250, 130, 30); createEdit("", 310, 245, 390, 35, 2203, true);
    createButton("Update", 310, 320, 170, 45, ID_UPDATE);
    createButton("Cancel", 510, 320, 170, 45, ID_CANCEL);
}

void MenuUI::showUserManagement()
{
    createHeader("User Management", "Admin-only management of User accounts.");
    createEdit("Search users...", 70, 105, 350, 38, 2301);
    createIconButton(L"🔍", 430, 105, 55, 38, ID_SEARCH);
    createButton("+ Add User", 500, 105, 120, 38, ID_ADD_USER);
    createIconButton(L"🗑", 635, 105, 55, 38, ID_DELETE_USER);
    createLabel("ID", 60, 165, 50, 30);
    createLabel("Username", 110, 165, 120, 30);
    createLabel("Full Name", 230, 165, 150, 30);
    createLabel("Email", 380, 165, 170, 30);
    createLabel("Phone", 550, 165, 110, 30);
    createLabel("Role", 660, 165, 100, 30);
    HWND list = createList(60, 195, 730, 255, 2302);
    SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"User accounts will be loaded here.");
    createButton("Edit", 250, 475, 110, 42, ID_EDIT_USER);
    createIconButton(L"🗑  Delete", 390, 475, 120, 42, ID_DELETE_USER);
    createBackButton(ID_ADMIN_MENU);
}

void MenuUI::showAddUser()
{
    createHeader("Add User", "Admin creates a new account.");
    createLabel("Username", 150, 105, 130, 30); createEdit("", 300, 100, 390, 35, 2401);
    createLabel("Password", 150, 155, 130, 30); createEdit("", 300, 150, 390, 35, 2402, true);
    createLabel("Full Name", 150, 205, 130, 30); createEdit("", 300, 200, 390, 35, 2403);
    createLabel("Email", 150, 255, 130, 30); createEdit("", 300, 250, 390, 35, 2404);
    createLabel("Phone", 150, 305, 130, 30); createEdit("", 300, 300, 390, 35, 2405);
    createLabel("Role", 150, 355, 130, 30); createCombo("User", 300, 350, 390, 35, 2406);
    createButton("Save", 300, 415, 170, 45, ID_SAVE);
    createButton("Cancel", 500, 415, 170, 45, ID_CANCEL);
}

void MenuUI::showEditUser()
{
    createHeader("Edit User", "Admin updates an existing account.");
    createLabel("Username", 150, 125, 130, 30); createEdit("Selected username", 300, 120, 390, 35, 2501);
    createLabel("Full Name", 150, 175, 130, 30); createEdit("", 300, 170, 390, 35, 2502);
    createLabel("Email", 150, 225, 130, 30); createEdit("", 300, 220, 390, 35, 2503);
    createLabel("Phone", 150, 275, 130, 30); createEdit("", 300, 270, 390, 35, 2504);
    createLabel("Role", 150, 325, 130, 30); createCombo("User", 300, 320, 390, 35, 2505);
    createButton("Update", 300, 390, 170, 45, ID_UPDATE);
    createButton("Cancel", 500, 390, 170, 45, ID_CANCEL);
}

void MenuUI::showDeleteUser()
{
    createHeader("Delete User", "Admin confirmation is required before deletion.");
    createLabel("Are you sure you want to delete this User account?", 170, 195, 540, 40, true);
    createIconButton(L"🗑  Confirm Delete", 245, 275, 180, 48, ID_DELETE_USER);
    createButton("Cancel", 455, 275, 180, 48, ID_CANCEL);
    createBackButton();
}

void MenuUI::showSystemReports()
{
    createHeader("View System Reports", "Summary information for Admin.");
    createLabel("Total Users", 100, 135, 180, 30, true);
    createLabel("--", 100, 170, 180, 45, true);
    createLabel("Total Contacts", 335, 135, 180, 30, true);
    createLabel("--", 335, 170, 180, 45, true);
    createLabel("Total Groups", 570, 135, 180, 30, true);
    createLabel("--", 570, 170, 180, 45, true);
    createLabel("Report table / statistics", 100, 250, 300, 30, true);
    HWND list = createList(100, 290, 650, 150, 2601);
    SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"Statistics will be loaded from the database.");
    createButton("Refresh", 330, 465, 170, 45, ID_REFRESH);
    createBackButton(ID_ADMIN_MENU);
}

void MenuUI::showBackup()
{
    createHeader("Backup Data", "Create and manage system backup files.");
    createIconButton(L"▣  Create Backup", 290, 105, 210, 48, ID_CREATE_BACKUP);
    createLabel("Backup History", 70, 180, 220, 30, true);
    createLabel("File name", 70, 215, 250, 30);
    createLabel("Created time", 320, 215, 180, 30);
    createLabel("Size", 500, 215, 100, 30);
    createLabel("Status", 600, 215, 120, 30);
    HWND list = createList(70, 245, 680, 200, 2701);
    SendMessageA(list, LB_ADDSTRING, 0, (LPARAM)"Backup history will be loaded here.");
    createButton("Download", 300, 465, 170, 45, ID_DOWNLOAD);
    createBackButton(ID_ADMIN_MENU);
}

void MenuUI::showRecovery()
{
    createHeader("Data Recovery", "Restore system data from a valid backup file.");
    createLabel("Backup File", 130, 145, 130, 30); createEdit("", 270, 140, 390, 35, 2801);
    createButton("Choose File", 675, 140, 120, 35, ID_BROWSE);
    createLabel("Selected file will be validated before Restore.", 130, 200, 620, 30);
    createIconButton(L"↻  Restore", 290, 270, 180, 48, ID_RESTORE);
    createButton("Cancel", 500, 270, 180, 48, ID_CANCEL);
    createBackButton(ID_ADMIN_MENU);
}

void MenuUI::showForgotPassword()
{
    createHeader("Forgot Password", "Password recovery interface.");
    createLabel("Username", 170, 140, 120, 30); createEdit("", 300, 135, 390, 35, 2901);
    createLabel("Email", 170, 195, 120, 30); createEdit("", 300, 190, 390, 35, 2902);
    createButton("Reset Password", 300, 265, 190, 45, ID_UPDATE);
    createButton("Cancel", 510, 265, 180, 45, ID_CANCEL);
    createBackButton();
}

void MenuUI::handleLogin()
{
    std::string username = getEditText(hWnd, 1001);
    std::string password = getEditText(hWnd, 1002);

    if (username.empty() || password.empty())
    {
        MessageBoxA(hWnd, "Bạn chưa nhập tài khoản hoặc mật khẩu.", "Login", MB_OK | MB_ICONWARNING);
        return;
    }

    if (username == "demo" && password == "demo")
    {
        currentRole = "User";
        showScreen("user");
        return;
    }

    MessageBoxA(hWnd,
                "Tài khoản chưa được đăng ký trong hệ thống.\n\nVui lòng nhấn Register để tạo tài khoản trước khi đăng nhập.",
                "Login", MB_OK | MB_ICONERROR);
}

void MenuUI::handleLogout()
{
    currentRole.clear();
    showScreen("login");
}

void MenuUI::handleClose()
{
    if (MessageBoxA(hWnd, "Are you sure you want to close the application?", "Close", MB_YESNO | MB_ICONQUESTION) == IDYES)
        DestroyWindow(hWnd);
}

void MenuUI::handleCommand(int id)
{
    switch (id)
    {
    case ID_LOGIN: handleLogin(); break;
    case ID_DEMO_USER:
        MessageBoxA(hWnd,
                    "Demo User đã bị vô hiệu hóa.\nBạn cần tạo tài khoản thật trước khi đăng nhập.",
                    "Login", MB_OK | MB_ICONWARNING);
        break;
    case ID_DEMO_ADMIN:
        MessageBoxA(hWnd,
                    "Demo Admin đã bị vô hiệu hóa.\nBạn cần tạo tài khoản thật trước khi đăng nhập.",
                    "Login", MB_OK | MB_ICONWARNING);
        break;
    case ID_REGISTER: showScreen("register"); break;
    case ID_REGISTER_SUBMIT:
        MessageBoxA(hWnd, "Register UI is ready. Account creation will be connected later.", "Register", MB_OK);
        break;
    case ID_REGISTER_LOGIN: showScreen("login"); break;
    case ID_FORGOT: showScreen("forgot"); break;
    case ID_CLOSE: handleClose(); break;
    case ID_LOGOUT: handleLogout(); break;

    case ID_CONTACTS: showScreen("contacts"); break;
    case ID_GROUPS: showScreen("groups"); break;
    case ID_FAVORITES:
        if (currentScreen == "contacts")
            MessageBoxA(hWnd, "Favorite toggle UI is ready. Favorite logic will be connected later.", "Favorite", MB_OK);
        else
            showScreen("favorites");
        break;
    case ID_ACCOUNT: showScreen("account"); break;

    case ID_ADD: showScreen("add_contact"); break;
    case ID_EDIT:
        if (currentScreen == "detail_contact") showScreen("edit_contact");
        else if (currentScreen == "contacts") showScreen("edit_contact");
        else showScreen("contacts");
        break;
    case ID_DELETE:
        if (currentScreen == "delete_contact")
        {
            MessageBoxA(hWnd, "Contact deletion UI is ready. Delete logic will be connected later.", "Delete Contact", MB_OK);
            showScreen("contacts");
        }
        else showScreen("delete_contact");
        break;
    case ID_DETAIL: showScreen("detail_contact"); break;
    case ID_SEARCH:
        if (currentScreen == "contacts") showScreen("search");
        else MessageBoxA(hWnd, "Search UI is ready. Search logic will be connected later.", "Search", MB_OK);
        break;
    case ID_FILTER: MessageBoxA(hWnd, "Filter UI is ready. Filter logic will be connected later.", "Filter", MB_OK); break;
    case ID_SORT: MessageBoxA(hWnd, "Sort UI is ready. Sort logic will be connected later.", "Sort", MB_OK); break;
    case ID_FAVORITE_TOGGLE:
        MessageBoxA(hWnd, "Favorite UI is ready. Favorite logic will be connected later.", "Favorite", MB_OK);
        break;

    case ID_SAVE:
        if (currentScreen == "add_contact")
        {
            std::string name = getEditText(hWnd, 1301);
            std::string phone = getEditText(hWnd, 1302);
            std::string email = getEditText(hWnd, 1303);
            std::string address = getEditText(hWnd, 1304);

            if (name.empty() || phone.empty())
            {
                MessageBoxA(hWnd, "Name and phone cannot be empty.", "Add Contact", MB_OK | MB_ICONWARNING);
                break;
            }

            if (!validPhoneValue(phone))
            {
                MessageBoxA(hWnd, "Phone must contain 10-11 digits.", "Add Contact", MB_OK | MB_ICONWARNING);
                break;
            }

            Contact contact;
            contact.account_id = 0;
            contact.group_id = 0;
            contact.name = name;
            contact.phone = phone;
            contact.email = email;
            contact.address = address;
            contact.isFavorite = false;

            ContactService::addContact(contact);
            showScreen("contacts");
        }
        else if (currentScreen == "add_group") showScreen("groups");
        else if (currentScreen == "add_user") showScreen("users");
        break;
    case ID_UPDATE:
        if (currentScreen == "edit_contact") showScreen("contacts");
        else if (currentScreen == "edit_group") showScreen("groups");
        else if (currentScreen == "edit_user") showScreen("users");
        else if (currentScreen == "change_password") showScreen("account");
        else if (currentScreen == "forgot")
        {
            MessageBoxA(hWnd, "Password recovery UI is ready. Recovery logic will be connected later.", "Forgot Password", MB_OK);
            showScreen("login");
        }
        else if (currentScreen == "account")
            MessageBoxA(hWnd, "Profile update UI is ready. Update logic will be connected later.", "Account", MB_OK);
        break;
    case ID_CANCEL:
        if (currentScreen == "add_contact" || currentScreen == "edit_contact" || currentScreen == "delete_contact" || currentScreen == "detail_contact" || currentScreen == "search") showScreen("contacts");
        else if (currentScreen == "add_group" || currentScreen == "edit_group" || currentScreen == "delete_group" || currentScreen == "group_detail" || currentScreen == "assign_contact") showScreen("groups");
        else if (currentScreen == "add_user" || currentScreen == "edit_user" || currentScreen == "delete_user") showScreen("users");
        else if (currentScreen == "change_password") showScreen("account");
        else if (currentScreen == "recovery") showScreen("admin");
        else if (currentScreen == "forgot") showScreen("login");
        else showScreen("login");
        break;

    case ID_ADD_GROUP: showScreen("add_group"); break;
    case ID_EDIT_GROUP: showScreen("edit_group"); break;
    case ID_DELETE_GROUP:
        if (currentScreen == "delete_group")
        {
            MessageBoxA(hWnd, "Group deletion UI is ready. Delete logic will be connected later.", "Delete Group", MB_OK);
            showScreen("groups");
        }
        else showScreen("delete_group");
        break;
    case ID_VIEW_GROUP: showScreen("group_detail"); break;
    case ID_GROUP_DETAIL: showScreen("group_detail"); break;
    case ID_SEARCH_GROUP: MessageBoxA(hWnd, "Search Group UI is ready. Search logic will be connected later.", "Search Group", MB_OK); break;
    case ID_ASSIGN:
        if (currentScreen == "groups") showScreen("assign_contact");
        else if (currentScreen == "assign_contact")
        {
            MessageBoxA(hWnd, "Assign Contact UI is ready. Assignment logic will be connected later.", "Assign Contact", MB_OK);
            showScreen("groups");
        }
        break;

    case ID_CHANGE_PASSWORD: showScreen("change_password"); break;
    case ID_ACCOUNT_UPDATE: MessageBoxA(hWnd, "Profile update UI is ready. Update logic will be connected later.", "Account", MB_OK); break;

    case ID_USER_MGMT: showScreen("users"); break;
    case ID_REPORTS: showScreen("reports"); break;
    case ID_BACKUP: showScreen("backup"); break;
    case ID_RECOVERY: showScreen("recovery"); break;
    case ID_ADMIN_MENU: showScreen("admin"); break;
    case ID_ADD_USER: showScreen("add_user"); break;
    case ID_EDIT_USER: showScreen("edit_user"); break;
    case ID_DELETE_USER:
        if (currentScreen == "delete_user")
        {
            MessageBoxA(hWnd, "User deletion UI is ready. Delete logic will be connected later.", "Delete User", MB_OK);
            showScreen("users");
        }
        else showScreen("delete_user");
        break;
    case ID_CREATE_BACKUP: MessageBoxA(hWnd, "Backup UI is ready. Backup logic will be connected later.", "Backup", MB_OK); break;
    case ID_DOWNLOAD: MessageBoxA(hWnd, "Download UI is ready. File handling will be connected later.", "Backup", MB_OK); break;
    case ID_BROWSE: MessageBoxA(hWnd, "File selection UI is ready. File validation will be connected later.", "Recovery", MB_OK); break;
    case ID_RESTORE:
        if (MessageBoxA(hWnd, "Are you sure you want to restore the data?", "Confirm Recovery", MB_YESNO | MB_ICONWARNING) == IDYES)
            MessageBoxA(hWnd, "Restore UI is ready. Recovery logic will be connected later.", "Recovery", MB_OK);
        break;
    case ID_REFRESH: MessageBoxA(hWnd, "Report refresh UI is ready. Data query will be connected later.", "Reports", MB_OK); break;

    case ID_BACK:
    case 900:
        if (currentScreen == "register" || currentScreen == "forgot") showScreen("login");
        else if (currentScreen == "contacts" || currentScreen == "groups" || currentScreen == "favorites" || currentScreen == "account") showScreen(currentRole == "Admin" ? "admin" : "user");
        else if (currentScreen == "add_contact" || currentScreen == "edit_contact" || currentScreen == "delete_contact" || currentScreen == "detail_contact" || currentScreen == "search") showScreen("contacts");
        else if (currentScreen == "add_group" || currentScreen == "edit_group" || currentScreen == "delete_group" || currentScreen == "group_detail" || currentScreen == "assign_contact") showScreen("groups");
        else if (currentScreen == "add_user" || currentScreen == "edit_user" || currentScreen == "delete_user" || currentScreen == "reports" || currentScreen == "backup" || currentScreen == "recovery") showScreen("admin");
        else if (currentScreen == "change_password") showScreen("account");
        else showScreen("login");
        break;
    }
}

LRESULT CALLBACK MenuUI::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MenuUI* ui = reinterpret_cast<MenuUI*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA));
    if (uMsg == WM_NCCREATE)
    {
        auto* cs = reinterpret_cast<CREATESTRUCTA*>(lParam);
        ui = reinterpret_cast<MenuUI*>(cs->lpCreateParams);
        SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ui));
        ui->hWnd = hwnd;
    }

    if (ui && uMsg == WM_COMMAND && HIWORD(wParam) == BN_CLICKED)
    {
        ui->handleCommand(LOWORD(wParam));
        return 0;
    }

    if (uMsg == WM_ERASEBKGND)
    {
        RECT rc{};
        GetClientRect(hwnd, &rc);
        FillRect((HDC)wParam, &rc, (HBRUSH)(COLOR_WINDOW + 1));
        return 1;
    }

    if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int MenuUI::run()
{
    HINSTANCE instance = GetModuleHandleA(nullptr);
    createFonts();

    WNDCLASSA wc{};
    wc.lpfnWndProc = MenuUI::WindowProc;
    wc.hInstance = instance;
    wc.lpszClassName = kClassName;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassA(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return 1;

    hWnd = CreateWindowA(
        kClassName,
        "Phone Book Management System",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        850, 620,
        nullptr, nullptr, instance, this);

    if (!hWnd) return 1;

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    showScreen("login");

    MSG msg{};
    while (GetMessageA(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return (int)msg.wParam;
}
