#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include "Contact.h"
#include "Group.h"

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

struct AccountData {
    int id = 0;
    std::string username;
    std::string email;
    std::string password;
    std::string fullname;
    std::string phone;
    std::string role;
};

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
 * @brief Lớp quản lý kết nối và tương tác trực tiếp với Cơ sở dữ liệu MySQL.
 * 
 * Lớp này thuộc tầng CSDL (Database Access Layer), tập trung tất cả các thao tác 
 * mở/đóng kết nối, thực thi truy vấn SQL, lưu trữ kết quả và bảo mật dữ liệu.
 */
class DBManager : public DatabaseConnector {
private:
    MYSQL* conn;
    bool connected;
    int lastInsertId;
    std::string storageFile;

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
     * @param host Địa chỉ máy chủ CSDL (ví dụ: "localhost", "127.0.0.1" hoặc "db")
     * @param user Tên tài khoản MySQL
     * @param password Mật khẩu tài khoản MySQL
     * @param database Tên CSDL cần thao tác
     * @param port Cổng kết nối CSDL (mặc định 3306)
     * @return true nếu kết nối thành công, false nếu gặp lỗi
     */
    bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port = 3306);

private:
    bool connectToServer(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port);
    bool initializeSchema();

public:

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
    bool isConnected() const override;
    std::string getStorageFile() const;
    std::vector<AccountData> getAccounts() const;
    bool getAccount(int accountId, AccountData& account) const;
    bool updateAccount(const AccountData& account);
    bool deleteAccount(int accountId);

    std::vector<Contact> loadContacts(int accountId) const;
    bool saveContact(const Contact& contact) const;
    bool updateContact(const Contact& contact) const;
    bool deleteContact(int accountId, int contactId) const;

    std::vector<Group> loadGroups(int accountId) const;
    bool saveGroup(const Group& group) const;
    bool updateGroup(const Group& group) const;
    bool deleteGroup(int accountId, int groupId) const;

    std::vector<ContactGroup> loadContactGroups(int accountId) const;
    bool saveContactGroup(int accountId, const ContactGroup& relation) const;
    bool deleteContactGroups(int accountId, int groupId) const;
};

// Khai báo đối tượng toàn cục để tái sử dụng 1 kết nối duy nhất trong toàn bộ ứng dụng
extern DBManager db;