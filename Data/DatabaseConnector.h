#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <C:\Program Files\MySQL\MySQL Server 8.4\include\mysql.h>
#include <string>
#include <vector>
#include <iostream>

class DatabaseConnector {
private:
    MYSQL* conn;
    std::string host;
    std::string user;
    std::string password;
    std::string database;
    unsigned int port;

public:
    DatabaseConnector(std::string host = "127.0.0.1", 
                      std::string user = "root", 
                      std::string password = "", 
                      std::string database = "phonebook_db", 
                      unsigned int port = 3306);
    ~DatabaseConnector();

    // Mở và đóng kết nối CSDL
    bool connect();
    void disconnect();

    // Thực thi các câu lệnh INSERT, UPDATE, DELETE
    bool executeNonQuery(const std::string& query);

    // Thực thi các câu lệnh SELECT và trả về con trỏ MYSQL_RES
    MYSQL_RES* executeQuery(const std::string& query);

    // Giải phóng bộ nhớ của kết quả SELECT
    void freeResult(MYSQL_RES* res);

    // Lấy ID vừa được chèn tự động (AUTO_INCREMENT)
    my_ulonglong getLastInsertId();

    // Lấy con trỏ kết nối trực tiếp khi cần thao tác nâng cao
    MYSQL* getConnection() const { return conn; }
};

#endif // DATABASE_CONNECTOR_H