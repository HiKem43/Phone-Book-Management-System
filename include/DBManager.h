#pragma once
#include <string>
#include <algorithm>

#if __has_include(<mysql/mysql.h>)
#include <mysql/mysql.h>
#else
struct MYSQL { int dummy; };
struct MYSQL_RES { int dummy; };
using MYSQL_ROW = char**;
inline MYSQL* mysql_init(MYSQL*) { return nullptr; }
inline MYSQL* mysql_real_connect(MYSQL*, const char*, const char*, const char*, const char*, unsigned int, const char*, unsigned long) { return nullptr; }
inline int mysql_set_character_set(MYSQL*, const char*) { return 0; }
inline void mysql_close(MYSQL*) {}
inline int mysql_query(MYSQL*, const char*) { return 0; }
inline MYSQL_RES* mysql_store_result(MYSQL*) { return nullptr; }
inline MYSQL_ROW mysql_fetch_row(MYSQL_RES*) { return nullptr; }
inline void mysql_free_result(MYSQL_RES*) {}
inline char* mysql_error(MYSQL*) { return nullptr; }
inline unsigned long long mysql_insert_id(MYSQL*) { return 0; }
inline unsigned long mysql_real_escape_string(MYSQL*, char* to, const char* from, unsigned long length) { if (length == 0) { if (to) *to = '\0'; return 0; } std::string s(from, length); std::copy(s.begin(), s.end(), to); to[s.size()] = '\0'; return static_cast<unsigned long>(s.size()); }
#endif

class DatabaseConnector {
public:
    virtual ~DatabaseConnector() = default;
    virtual MYSQL_RES* executeQuery(const std::string& query) = 0;
    virtual bool executeNonQuery(const std::string& query) = 0;
    virtual MYSQL_RES* fetchQuery(const std::string& query) = 0;
    virtual void freeResult(MYSQL_RES* result) = 0;
    virtual int getInsertId() const = 0;
    virtual std::string escapeString(const std::string& str) const = 0;
    virtual MYSQL* getConn() = 0;
};

/**
 * @class DBManager
 * @brief Lớp quản lý kết nối và tương tác trực tiếp với Cơ sở dữ liệu MySQL.
 * 
 * Lớp này thuộc tầng CSDL (Database Access Layer), tập trung tất cả các thao tác 
 * mở/đóng kết nối, thực thi truy vấn SQL, lưu trữ kết quả và bảo mật dữ liệu.
 */
class DBManager : public DatabaseConnector {
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
    MYSQL* getConn() override;

    /**
     * Thực thi các câu lệnh SQL làm thay đổi dữ liệu (INSERT, UPDATE, DELETE).
     * @param query Chuỗi câu lệnh SQL
     * @return true nếu thực thi thành công, false nếu có lỗi
     */
    MYSQL_RES* executeQuery(const std::string& query) override;
    bool executeNonQuery(const std::string& query) override;

    /**
     * Thực thi các câu lệnh SQL lấy dữ liệu (SELECT).
     * @param query Chuỗi câu lệnh SQL truy vấn
     * @return Con trỏ MYSQL_RES* chứa tập kết quả hoặc NULL nếu thất bại
     */
    MYSQL_RES* fetchQuery(const std::string& query) override;
    void freeResult(MYSQL_RES* result) override;

    /**
     * Chuẩn hóa chuỗi văn bản đầu vào để chống tấn công lỗ hổng SQL Injection.
     * @param str Chuỗi văn bản thô do người dùng nhập
     * @return Chuỗi đã được chèn các ký tự escape an toàn
     */
    std::string escapeString(const std::string& str) const override;

    // Lấy ID tự động tăng (AUTO_INCREMENT) vừa sinh ra từ câu lệnh INSERT gần nhất
    int getInsertId() const override;
};

// Khai báo đối tượng toàn cục để tái sử dụng 1 kết nối duy nhất trong toàn bộ ứng dụng
extern DBManager db;