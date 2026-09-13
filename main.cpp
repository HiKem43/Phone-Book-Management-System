#include "MenuUI.h"

// =====================================================
// HÀM KHỞI CHẠY ỨNG DỤNG (ENTRY POINT)
// =====================================================

// Điểm khởi chạy chính của ứng dụng Windows GUI (Win32 API)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int) {
    MenuUI app;
    return app.run();
}