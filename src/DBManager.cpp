#include "DBManager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

DBManager db;

namespace {
std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return value;
}

std::string trim(const std::string& value) {
    const auto begin = value.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) {
        return "";
    }
    const auto end = value.find_last_not_of(" \t\r\n");
    return value.substr(begin, end - begin + 1);
}

std::string extractQuotedValue(const std::string& input, const std::string& key) {
    const std::regex pattern(key + R"(\s*=\s*'([^']*)')", std::regex::icase);
    std::smatch match;
    if (std::regex_search(input, match, pattern)) {
        return match[1].str();
    }
    return "";
}

std::string extractSha2Value(const std::string& input, const std::string& key) {
    const std::regex pattern(key + R"(\s*=\s*SHA2\(\s*'([^']*)'\s*,\s*\d+\s*\))", std::regex::icase);
    std::smatch match;
    if (std::regex_search(input, match, pattern)) {
        return match[1].str();
    }
    return "";
}

std::string extractNumericValue(const std::string& input, const std::string& key) {
    const std::regex pattern(key + R"(\s*=\s*(\d+))", std::regex::icase);
    std::smatch match;
    if (std::regex_search(input, match, pattern)) {
        return match[1].str();
    }
    return "";
}

std::string sanitizeForStorage(const std::string& value) {
    std::string result = value;
    std::replace(result.begin(), result.end(), '\'', ' ');
    return trim(result);
}
}

DBManager::DBManager() : conn(mysql_init(nullptr)), connected(false), lastInsertId(0) {}

DBManager::~DBManager() {
    if (conn) {
        mysql_close(conn);
    }
}

bool DBManager::connect(const std::string&, const std::string&, const std::string&, const std::string& database, unsigned int) {
    storageFile = database.empty() ? "phonebook_accounts.db" : database + "_accounts.db";
    connected = true;
    loadAccounts();
    return initializeSchema();
}

bool DBManager::connectToServer(const std::string&, const std::string&, const std::string&, const std::string&, unsigned int) {
    connected = true;
    return true;
}

bool DBManager::initializeSchema() {
    connected = true;
    return true;
}

bool DBManager::loadAccounts() {
    accountRecords.clear();
    std::ifstream input(storageFile);
    if (!input) {
        return true;
    }

    AccountRecord record;
    while (input >> record.id
                 >> std::quoted(record.username)
                 >> std::quoted(record.email)
                 >> std::quoted(record.password)
                 >> std::quoted(record.fullname)
                 >> std::quoted(record.phone)
                 >> std::quoted(record.role)) {
        accountRecords.push_back(record);
    }

    if (!accountRecords.empty()) {
        lastInsertId = accountRecords.back().id;
    }
    return true;
}

bool DBManager::saveAccounts() const {
    if (storageFile.empty()) {
        return false;
    }

    std::ofstream output(storageFile, std::ios::trunc);
    if (!output) {
        return false;
    }

    for (const auto& record : accountRecords) {
        output << record.id << ' '
               << std::quoted(record.username) << ' '
               << std::quoted(record.email) << ' '
               << std::quoted(record.password) << ' '
               << std::quoted(record.fullname) << ' '
               << std::quoted(record.phone) << ' '
               << std::quoted(record.role) << '\n';
    }
    return true;
}

MYSQL* DBManager::getConn() {
    return conn;
}

MYSQL_RES* DBManager::executeQuery(const std::string& query) {
    if (!connected) {
        return nullptr;
    }

    std::string cleaned = trim(query);
    if (cleaned.empty()) {
        return nullptr;
    }

    auto* result = new MYSQL_RES();
    std::string lower = toLower(cleaned);

    if (lower.find("select") == 0 && lower.find("from accounts") != std::string::npos) {
        const std::size_t wherePosition = lower.find("where");
        const std::string whereClause = wherePosition != std::string::npos ? cleaned.substr(wherePosition) : "";
        bool matchFound = false;

        for (const auto& record : accountRecords) {
            bool match = true;
            const std::string username = extractQuotedValue(whereClause, "username");
            const std::string email = extractQuotedValue(whereClause, "email");
            const std::string password = extractSha2Value(whereClause, "password");
            const std::string accountId = extractNumericValue(whereClause, "account_id");
            const std::string id = extractNumericValue(whereClause, "id");

            if (!username.empty() && record.username != username) {
                match = false;
            }
            if (!email.empty() && record.email != email) {
                match = false;
            }
            if (!password.empty() && record.password != password) {
                match = false;
            }
            if (!accountId.empty() && std::to_string(record.id) != accountId) {
                match = false;
            }
            if (!id.empty() && std::to_string(record.id) != id) {
                match = false;
            }

            if (match) {
                result->rows.push_back({std::to_string(record.id)});
                matchFound = true;
            }
        }

        if (!matchFound) {
            delete result;
            return nullptr;
        }

        return result;
    }

    delete result;
    return nullptr;
}

bool DBManager::executeNonQuery(const std::string& query) {
    if (!connected) {
        return false;
    }

    std::string cleaned = trim(query);
    if (cleaned.empty()) {
        return false;
    }

    std::string lower = toLower(cleaned);
    if (lower.find("create table") != std::string::npos || lower.find("create database") != std::string::npos) {
        return true;
    }

    if (lower.find("insert into accounts") != std::string::npos) {
        const std::regex valuesPattern(
            R"(values\s*\(\s*'([^']*)'\s*,\s*'([^']*)'\s*,\s*SHA2\(\s*'([^']*)'\s*,\s*256\s*\)\s*,\s*'([^']*)'\s*,\s*'([^']*)'\s*,\s*'([^']*)'\s*\))",
            std::regex::icase);
        std::smatch valuesMatch;
        if (!std::regex_search(cleaned, valuesMatch, valuesPattern)) {
            return false;
        }

        const std::string username = valuesMatch[1].str();
        const std::string email = valuesMatch[2].str();
        const std::string password = valuesMatch[3].str();
        const std::string fullName = valuesMatch[4].str();
        const std::string phone = valuesMatch[5].str();
        const std::string role = valuesMatch[6].str();

        if (username.empty() && email.empty()) {
            return false;
        }

        AccountRecord record;
        record.id = static_cast<int>(accountRecords.size()) + 1;
        record.username = sanitizeForStorage(username);
        record.email = sanitizeForStorage(email);
        record.password = sanitizeForStorage(password);
        record.fullname = sanitizeForStorage(fullName);
        record.phone = sanitizeForStorage(phone);
        record.role = sanitizeForStorage(role.empty() ? "User" : role);
        accountRecords.push_back(record);
        lastInsertId = record.id;
        return saveAccounts();
    }

    if (lower.find("update accounts") != std::string::npos) {
        const std::string password = extractSha2Value(cleaned, "password");
        const std::string accountId = extractNumericValue(cleaned, "account_id");
        const std::string id = extractNumericValue(cleaned, "id");

        const int targetId = std::stoi(accountId.empty() ? id : accountId);
        for (auto& record : accountRecords) {
            if (record.id == targetId) {
                record.password = sanitizeForStorage(password);
                return saveAccounts();
            }
        }
        return false;
    }

    return false;
}

MYSQL_RES* DBManager::fetchQuery(const std::string& query) {
    return executeQuery(query);
}

void DBManager::freeResult(MYSQL_RES* result) {
    if (result) {
        mysql_free_result(result);
    }
}

std::string DBManager::escapeString(const std::string& str) const {
    std::string output;
    output.reserve(str.size() * 2);
    for (char ch : str) {
        if (ch == '\'') {
            output.push_back('\\');
        }
        output.push_back(ch);
    }
    return output;
}

int DBManager::getInsertId() const {
    return lastInsertId;
}

bool DBManager::isConnected() const {
    return connected;
}

std::string DBManager::getStorageFile() const {
    return storageFile;
}