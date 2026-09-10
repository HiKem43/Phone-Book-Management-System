#include "DBManager.h"
#include <iostream>

// Khai báo thực thể CSDL toàn cục duy nhất
DBManager db;

// Hàm khởi tạo: Chuẩn bị cấu trúc kết nối MySQL
DBManager::DBManager() {
    conn = mysql_init(NULL); // Khởi tạo con trỏ MYSQL nội bộ
}

// Hàm hủy: Giải phóng tài nguyên kết nối
DBManager::~DBManager() {
    if (conn) {
        mysql_close(conn); // Đóng kết nối CSDL an toàn khi chương trình kết thúc
    }
}

// Mở kết nối đến máy chủ MySQL
bool DBManager::connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port) {
    // Gọi hàm kết nối của MySQL C API
    if (mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, NULL, 0)) {
        // Cấu hình bảng mã UTF-8 để hỗ trợ tiếng Việt hoàn chỉnh
        mysql_set_character_set(conn, "utf8mb4");
        return true;
    } else {
        // In thông báo lỗi ra luồng cerr nếu kết nối thất bại
        std::cerr << "Connection Error: " << mysql_error(conn) << std::endl;
        return false;
    }
}

// Trả về con trỏ kết nối
MYSQL* DBManager::getConn() { 
    return conn; 
}

// Thực thi câu lệnh SQL cập nhật/thay đổi dữ liệu (INSERT, UPDATE, DELETE)
bool DBManager::executeQuery(const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

// Thực thi câu lệnh SQL truy xuất/lấy dữ liệu (SELECT)
MYSQL_RES* DBManager::fetchQuery(const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return NULL;
    }
    // Tải và lưu trữ toàn bộ bộ kết quả trả về vào bộ nhớ RAM
    return mysql_store_result(conn);
}

// Chuẩn hóa chuỗi để chống SQL Injection
std::string DBManager::escapeString(const std::string& str) {
    // Cấp phát bộ nhớ đệm an toàn (tối đa gấp 2 lần độ dài chuỗi + 1 ký tự null)
    char escaped[str.length() * 2 + 1];
    mysql_real_escape_string(conn, escaped, str.c_str(), str.length());
    return std::string(escaped);
}

// Trả về khóa chính (ID) tự động sinh ra gần nhất
int DBManager::getInsertId() {
    return (int)mysql_insert_id(conn);
}