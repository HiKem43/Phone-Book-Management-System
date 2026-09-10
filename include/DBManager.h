#pragma once
#include <string>
#include <mysql/mysql.h>

/**
 * @class DBManager
 * @brief Lớp quản lý kết nối và tương tác trực tiếp với Cơ sở dữ liệu MySQL.
 * 
 * Lớp này thuộc tầng CSDL (Database Access Layer), tập trung tất cả các thao tác 
 * mở/đóng kết nối, thực thi truy vấn SQL, lưu trữ kết quả và bảo mật dữ liệu.
 */
class DBManager {
private:
    MYSQL* conn; // Con trỏ quản lý đối tượng phiên kết nối MySQL C API

public:

    DBManager();
    ~DBManager();

    /**
     * Mở kết nối đến máy chủ CSDL MySQL.
     * @param host Địa chỉ máy chủ CSDL (ví dụ: "localhost", "127.0.0.1" hoặc "db")
     * @param user Tên tài khoản MySQL
     * @param password Mật khẩu tài khoản MySQL
     * @param database Tên CSDL cần thao tác
     * @param port Cổng kết nối CSDL (mặc định 3306)
     * @return true nếu kết nối thành công, false nếu gặp lỗi
     */
    bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port = 3306);

    // Truy xuất trực tiếp con trỏ kết nối MySQL
    MYSQL* getConn();

    /**
     * Thực thi các câu lệnh SQL làm thay đổi dữ liệu (INSERT, UPDATE, DELETE).
     * @param query Chuỗi câu lệnh SQL
     * @return true nếu thực thi thành công, false nếu có lỗi
     */
    bool executeQuery(const std::string& query);

    /**
     * Thực thi các câu lệnh SQL lấy dữ liệu (SELECT).
     * @param query Chuỗi câu lệnh SQL truy vấn
     * @return Con trỏ MYSQL_RES* chứa tập kết quả hoặc NULL nếu thất bại
     */
    MYSQL_RES* fetchQuery(const std::string& query);

    /**
     * Chuẩn hóa chuỗi văn bản đầu vào để chống tấn công lỗ hổng SQL Injection.
     * @param str Chuỗi văn bản thô do người dùng nhập
     * @return Chuỗi đã được chèn các ký tự escape an toàn
     */
    std::string escapeString(const std::string& str);

    // Lấy ID tự động tăng (AUTO_INCREMENT) vừa sinh ra từ câu lệnh INSERT gần nhất
    int getInsertId();
};

// Khai báo đối tượng toàn cục để tái sử dụng 1 kết nối duy nhất trong toàn bộ ứng dụng
extern DBManager db;