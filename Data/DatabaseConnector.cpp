#include "DatabaseConnector.h"

DatabaseConnector::DatabaseConnector(std::string host, std::string user, std::string password, std::string database, unsigned int port)
    : host(host), user(user), password(password), database(database), port(port), conn(nullptr) {}

DatabaseConnector::~DatabaseConnector() {
    disconnect();
}

bool DatabaseConnector::connect() {
    conn = mysql_init(0);
    if (!conn) {
        std::cerr << "[DB Error] Khởi tạo MySQL thất bại!" << std::endl;
        return false;
    }

    conn = mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, NULL, 0);
    if (conn) {
        // Thiết lập bộ mã hóa utf8mb4 cho Tiếng Việt
        mysql_set_character_set(conn, "utf8mb4");
        return true;
    } else {
        std::cerr << "[DB Error] Lỗi kết nối CSDL: " << mysql_error(conn) << std::endl;
        return false;
    }
}

void DatabaseConnector::disconnect() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

bool DatabaseConnector::executeNonQuery(const std::string& query) {
    if (!conn && !connect()) return false;

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "[DB Error] Lỗi thực thi truy vấn: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

MYSQL_RES* DatabaseConnector::executeQuery(const std::string& query) {
    if (!conn && !connect()) return nullptr;

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "[DB Error] Lỗi truy vấn dữ liệu: " << mysql_error(conn) << std::endl;
        return nullptr;
    }

    return mysql_store_result(conn);
}

void DatabaseConnector::freeResult(MYSQL_RES* res) {
    if (res) {
        mysql_free_result(res);
    }
}

my_ulonglong DatabaseConnector::getLastInsertId() {
    if (conn) {
        return mysql_insert_id(conn);
    }
    return 0;
}