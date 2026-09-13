#pragma once
#include <string>

/**
 * @file Utils.h
 * @brief Chứa các hàm tiện ích hỗ trợ kiểm tra định dạng dữ liệu và xử lý luồng nhập.
 */

/**
 * @brief Kiểm tra tính hợp lệ của cú pháp Email.
 * @param email Chuỗi Email cần kiểm tra.
 * @return true nếu đúng định dạng (vd: abc@def.com), ngược lại false.
 */
bool validateEmail(const std::string& email);

/**
 * @brief Kiểm tra tính hợp lệ của Số điện thoại.
 * @param phone Chuỗi sĐT cần kiểm tra (ví dụ: chỉ chứa số, độ dài từ 9-11 ký tự).
 * @return true nếu đúng định dạng sĐT hợp lệ, ngược lại false.
 */
bool validatePhone(const std::string& phone);

/**
 * @brief Xóa bộ đệm đệm nhập liệu (std::cin buffer) tránh trôi lệnh trong Console UI.
 */
void clearInputBuffer();