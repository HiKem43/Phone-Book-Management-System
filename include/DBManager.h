#pragma once
#include <string>
#include <mysql/mysql.h>

class DBManager {
private:
    MYSQL* conn;

public:
    DBManager();
    ~DBManager();

    bool connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port = 3306);
    MYSQL* getConn();
    bool executeQuery(const std::string& query);
    MYSQL_RES* fetchQuery(const std::string& query);
    std::string escapeString(const std::string& str);
    int getInsertId();
};

extern DBManager db; // Global DB instance