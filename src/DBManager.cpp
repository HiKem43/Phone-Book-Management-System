#include "DBManager.h"
#include <iostream>

// Khai báo thực thể CSDL toàn cục duy nhất
DBManager db;

// Hàm khởi tạo: Chuẩn bị cấu trúc kết nối MySQL
DBManager::DBManager() {
    conn = mysql_init(NULL); // Khởi tạo con trỏ MYSQL nội bộ
    connected = false;
}

// Hàm hủy: Giải phóng tài nguyên kết nối
DBManager::~DBManager() {
    if (conn) {
        mysql_close(conn); // Đóng kết nối CSDL an toàn khi chương trình kết thúc
    }
}

// Mở kết nối đến máy chủ MySQL
bool DBManager::connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port) {
    if (connectToServer(host, user, password, database, port)) {
        return initializeSchema();
    }

    // The server may be running while the project database has not been created yet.
    if (!connectToServer(host, user, password, "", port)) {
        connected = false;
        return false;
    }

    const std::string createDatabase =
        "CREATE DATABASE IF NOT EXISTS `" + escapeString(database) +
        "` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci";
    if (!executeNonQuery(createDatabase)) {
        connected = false;
        return false;
    }

    if (!connectToServer(host, user, password, database, port)) {
        connected = false;
        return false;
    }

    return initializeSchema();
}

bool DBManager::connectToServer(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port) {
    if (conn) {
        mysql_close(conn);
    }
    conn = mysql_init(nullptr);
    if (!conn || !mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(),
                                     database.empty() ? nullptr : database.c_str(), port, nullptr, 0)) {
        if (conn) {
            std::cerr << "Connection Error: " << mysql_error(conn) << std::endl;
        }
        connected = false;
        return false;
    }

    mysql_set_character_set(conn, "utf8mb4");
    connected = true;
    return true;
}

bool DBManager::initializeSchema() {
    const char* accountsTable =
        "CREATE TABLE IF NOT EXISTS Accounts ("
        "account_id INT AUTO_INCREMENT PRIMARY KEY,"
        "username VARCHAR(50) NOT NULL UNIQUE,"
        "password VARCHAR(255) NOT NULL,"
        "fullname VARCHAR(100) NOT NULL,"
        "email VARCHAR(100) NULL UNIQUE,"
        "phone VARCHAR(15) NULL,"
        "role VARCHAR(20) NOT NULL DEFAULT 'User'"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4";

    if (!executeNonQuery(accountsTable)) {
        connected = false;
        return false;
    }

    return true;
}

// Trả về con trỏ kết nối
MYSQL* DBManager::getConn() { 
    return conn; 
}

MYSQL_RES* DBManager::executeQuery(const std::string& query) {
    if (!connected) {
        std::cerr << "Query Error: database is not connected." << std::endl;
        return nullptr;
    }

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return nullptr;
    }
    return mysql_store_result(conn);
}

bool DBManager::executeNonQuery(const std::string& query) {
    if (!connected) {
        std::cerr << "Query Error: database is not connected." << std::endl;
        return false;
    }

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

// Thực thi câu lệnh SQL truy xuất/lấy dữ liệu (SELECT)
MYSQL_RES* DBManager::fetchQuery(const std::string& query) {
    if (!connected) {
        std::cerr << "Query Error: database is not connected." << std::endl;
        return nullptr;
    }

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return nullptr;
    }
    // Tải và lưu trữ toàn bộ bộ kết quả trả về vào bộ nhớ RAM
    return mysql_store_result(conn);
}

void DBManager::freeResult(MYSQL_RES* result) {
    if (result) {
        mysql_free_result(result);
    }
}

// Chuẩn hóa chuỗi để chống SQL Injection
std::string DBManager::escapeString(const std::string& str) const {
    if (!connected || conn == nullptr) {
        return str;
    }

    std::string escaped(str.length() * 2 + 1, '\0');
    mysql_real_escape_string(conn, &escaped[0], str.c_str(), static_cast<unsigned long>(str.length()));
    std::size_t pos = escaped.find('\0');
    if (pos != std::string::npos) {
        escaped.erase(pos);
    }
    return escaped;
}

// Trả về khóa chính (ID) tự động sinh ra gần nhất
int DBManager::getInsertId() const {
    return static_cast<int>(mysql_insert_id(conn));
}

bool DBManager::isConnected() const {
    return connected;
}