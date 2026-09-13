#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include "Contact.h"
#include "Group.h"

// --- MÔ PHỎNG CÁC STRUCT CỦA THƯ VIỆN MYSQL C ADAPTER ---
struct MYSQL {
    int dummy = 0;
};

struct MYSQL_RES {
    std::vector<std::vector<std::string>> rows;
    std::vector<std::string> columns;
    std::size_t currentRow = 0;
    std::vector<std::vector<char*>> rowStorage;
};

using MYSQL_ROW = char**;

// Cấu trúc Dữ liệu Tài khoản đọc từ CSDL
struct AccountData {
    int id = 0;
    std::string username;
    std::string email;
    std::string password;
    std::string fullname;
    std::string phone;
    std::string role;
};

// --- CÁC HÀM GIẢ LẬP MYSQL C API (NẾU CHƯA CÀI ĐẶT THƯ VIỆN MYSQL THỰC TẾ) ---
inline MYSQL* mysql_init(MYSQL*) { return new MYSQL(); }
inline MYSQL* mysql_real_connect(MYSQL*, const char*, const char*, const char*, const char*, unsigned int, const char*, unsigned long) { return new MYSQL(); }
inline int mysql_set_character_set(MYSQL*, const char*) { return 0; }
inline void mysql_close(MYSQL* conn) { delete conn; }
inline int mysql_query(MYSQL*, const char*) { return 0; }
inline MYSQL_RES* mysql_store_result(MYSQL*) { return nullptr; }
inline MYSQL_ROW mysql_fetch_row(MYSQL_RES* result) {
    if (result == nullptr || result->currentRow >= result->rows.size()) {
        return nullptr;
    }

    const auto& row = result->rows[result->currentRow++];
    std::vector<char*> values(row.size(), nullptr);
    result->rowStorage.push_back(values);

    for (std::size_t i = 0; i < row.size(); ++i) {
        const auto& value = row[i];
        char* copy = new char[value.size() + 1];
        std::copy(value.begin(), value.end(), copy);
        copy[value.size()] = '\0';
        result->rowStorage.back()[i] = copy;
    }

    MYSQL_ROW out = new char*[row.size() + 1];
    for (std::size_t i = 0; i < row.size(); ++i) {
        out[i] = result->rowStorage.back()[i];
    }
    out[row.size()] = nullptr;
    return out;
}
inline void mysql_free_result(MYSQL_RES* result) {
    if (!result) {
        return;
    }

    for (auto& row : result->rowStorage) {
        for (char* value : row) {
            delete[] value;
        }
    }

    delete result;
}
inline char* mysql_error(MYSQL*) { return nullptr; }
inline unsigned long long mysql_insert_id(MYSQL*) { return 0; }
inline unsigned long mysql_real_escape_string(MYSQL*, char* to, const char* from, unsigned long length) {
    if (length == 0) {
        if (to) *to = '\0';
        return 0;
    }

    std::string escaped(from, length);
    std::string output;
    output.reserve(escaped.size() * 2);
    for (char ch : escaped) {
        if (ch == '\'') {
            output += '\\';
        }
        output += ch;
    }

    if (to) {
        std::copy(output.begin(), output.end(), to);
        to[output.size()] = '\0';
    }
    return static_cast<unsigned long>(output.size());
}

/**
 * @interface DatabaseConnector
 * @brief Interface trừu tượng (Abstract Interface) định nghĩa chuẩn thao tác với CSDL.
 * Giúp dễ dàng thay thế giữa MySQL, SQLite hay File giả lập mà không hỏng ứng dụng (Dependency Inversion Principle).
 */
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
    virtual bool isConnected() const = 0;
};

/**
 * @class DBManager
 * @brief Tầng Quản lý CSDL thực tế (Data Access Layer - DAL).
 * Chịu trách nhiệm tương tác trực tiếp với cơ sở dữ liệu MySQL cũng như lưu trữ file dự phòng.
 */
class DBManager : public DatabaseConnector {
private:
    MYSQL* conn;                        // Con trỏ đối tượng kết nối MySQL C-API
    bool connected;                     // Cờ báo hiệu trạng thái kết nối thành công/thất bại
    int lastInsertId;                   // Lưu lại ID của bản ghi vừa chèn thành công
    std::string storageFile;            // Đường dẫn file lưu trữ dữ liệu cục bộ dự phòng (Fallback)

    // Cấu trúc bản ghi lưu trữ thông tin tài khoản
    struct AccountRecord {
        int id = 0;
        std::string username;
        std::string email;
        std::string password;
        std::string fullname;
        std::string phone;
        std::string role;
    };

    std::vector<AccountRecord> accountRecords;

    bool loadAccounts();
    bool saveAccounts() const;
    std::string getRelatedStorageFile(const std::string& suffix) const;

public:

    DBManager();
    ~DBManager();

    /**
     * Mở kết nối đến máy chủ CSDL MySQL.
     */
    bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port = 3306);

private:
    bool connectToServer(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port);
    bool initializeSchema(); // Khởi tạo các bảng dữ liệu (Tables) nếu chưa có trong CSDL

public:
    MYSQL* getConn() override;

    // --- CÁC THAO TÁC TRUY VẤN SQL ---
    MYSQL_RES* executeQuery(const std::string& query) override;
    bool executeNonQuery(const std::string& query) override;  // Thực thi DML (INSERT, UPDATE, DELETE)
    MYSQL_RES* fetchQuery(const std::string& query) override;   // Thực thi DQL (SELECT)
    void freeResult(MYSQL_RES* result) override;               // Giải phóng bộ nhớ của kết quả truy vấn

    /**
     * @brief Lọc chống tấn công SQL Injection bằng cách chèn escape character.
     */
    std::string escapeString(const std::string& str) const override;

    int getInsertId() const override;
    bool isConnected() const override;
    std::string getStorageFile() const;

    // --- QUẢN LÝ BẢNG ACCOUNTS ---
    std::vector<AccountData> getAccounts() const;
    bool getAccount(int accountId, AccountData& account) const;
    bool updateAccount(const AccountData& account);
    bool deleteAccount(int accountId);

    // --- QUẢN LÝ BẢNG CONTACTS ---
    std::vector<Contact> loadContacts(int accountId) const;
    bool saveContact(const Contact& contact) const;
    bool updateContact(const Contact& contact) const;
    bool deleteContact(int accountId, int contactId) const;

    // --- QUẢN LÝ BẢNG GROUPS ---
    std::vector<Group> loadGroups(int accountId) const;
    bool saveGroup(const Group& group) const;
    bool updateGroup(const Group& group) const;
    bool deleteGroup(int accountId, int groupId) const;

    // --- QUẢN LÝ BẢNG LIÊN KẾT DANH BẠ VÀ NHÓM (CONTACT_GROUPS) ---
    std::vector<ContactGroup> loadContactGroups(int accountId) const;
    bool saveContactGroup(int accountId, const ContactGroup& relation) const;
    bool deleteContactGroups(int accountId, int groupId) const;
    bool deleteContactGroup(int accountId, int contactId) const;
};

// Đối tượng DBManager dùng chung toàn ứng dụng (Singleton pattern dạng Extern Variable)
extern DBManager db;