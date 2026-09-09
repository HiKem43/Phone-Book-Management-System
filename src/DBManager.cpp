#include "DBManager.h"
#include <iostream>

DBManager db;

DBManager::DBManager() {
    conn = mysql_init(NULL);
}

DBManager::~DBManager() {
    if (conn) {
        mysql_close(conn);
    }
}

bool DBManager::connect(const std::string& host, const std::string& user, const std::string& password, const std::string& database, unsigned int port) {
    if (mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, NULL, 0)) {
        mysql_set_character_set(conn, "utf8mb4");
        return true;
    } else {
        std::cerr << "Connection Error: " << mysql_error(conn) << std::endl;
        return false;
    }
}

MYSQL* DBManager::getConn() { 
    return conn; 
}

bool DBManager::executeQuery(const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

MYSQL_RES* DBManager::fetchQuery(const std::string& query) {
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query Error: " << mysql_error(conn) << std::endl;
        return NULL;
    }
    return mysql_store_result(conn);
}

std::string DBManager::escapeString(const std::string& str) {
    char escaped[str.length() * 2 + 1];
    mysql_real_escape_string(conn, escaped, str.c_str(), str.length());
    return std::string(escaped);
}

int DBManager::getInsertId() {
    return (int)mysql_insert_id(conn);
}