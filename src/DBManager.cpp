#include <windows.h>
#include "DBManager.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
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
    char executablePath[MAX_PATH] = {};
    GetModuleFileNameA(nullptr, executablePath, MAX_PATH);
    const std::filesystem::path executableDirectory =
        std::filesystem::path(executablePath).parent_path();
    const std::string fileName = database.empty() ?
        "phonebook_accounts.db" : database + "_accounts.db";
    storageFile = (executableDirectory / fileName).string();
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

    for (const auto& record : accountRecords)
        if (record.id > lastInsertId) lastInsertId = record.id;
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
        record.id = 1;
        for (const auto& existing : accountRecords)
            if (existing.id >= record.id) record.id = existing.id + 1;
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

std::vector<AccountData> DBManager::getAccounts() const {
    std::vector<AccountData> accounts;
    for (const auto& record : accountRecords) {
        accounts.push_back({record.id, record.username, record.email, record.password,
                            record.fullname, record.phone, record.role});
    }
    return accounts;
}

bool DBManager::getAccount(int accountId, AccountData& account) const {
    for (const auto& record : accountRecords) {
        if (record.id == accountId) {
            account = {record.id, record.username, record.email, record.password,
                       record.fullname, record.phone, record.role};
            return true;
        }
    }
    return false;
}

bool DBManager::updateAccount(const AccountData& account) {
    for (auto& record : accountRecords) {
        if (record.id == account.id) {
            record.username = account.username;
            record.email = account.email;
            record.fullname = account.fullname;
            record.phone = account.phone;
            record.role = account.role;
            if (!account.password.empty()) record.password = account.password;
            return saveAccounts();
        }
    }
    return false;
}

bool DBManager::deleteAccount(int accountId) {
    const auto oldSize = accountRecords.size();
    accountRecords.erase(std::remove_if(accountRecords.begin(), accountRecords.end(),
        [accountId](const AccountRecord& record) { return record.id == accountId; }),
        accountRecords.end());
    if (accountRecords.size() == oldSize) return false;
    if (!saveAccounts()) return false;

    const auto contacts = loadContacts(accountId);
    for (const auto& contact : contacts) {
        if (!deleteContact(accountId, contact.id) ||
            !deleteContactGroup(accountId, contact.id)) return false;
    }

    const auto groups = loadGroups(accountId);
    for (const auto& group : groups) {
        if (!deleteGroup(accountId, group.id) ||
            !deleteContactGroups(accountId, group.id)) return false;
    }

    return true;
}

std::string DBManager::getRelatedStorageFile(const std::string& suffix) const {
    return storageFile + suffix;
}

std::vector<Contact> DBManager::loadContacts(int accountId) const {
    std::vector<Contact> contacts;
    std::ifstream input(getRelatedStorageFile(".contacts"));
    Contact contact;
    while (input >> contact.id >> contact.account_id >> contact.group_id
                 >> std::quoted(contact.name) >> std::quoted(contact.phone)
                 >> std::quoted(contact.email) >> std::quoted(contact.address)
                 >> contact.isFavorite) {
        if (contact.account_id == accountId) contacts.push_back(contact);
    }
    return contacts;
}

bool DBManager::saveContact(const Contact& contact) const {
    std::ofstream output(getRelatedStorageFile(".contacts"), std::ios::app);
    if (!output) return false;
    output << contact.id << ' ' << contact.account_id << ' ' << contact.group_id << ' '
           << std::quoted(contact.name) << ' ' << std::quoted(contact.phone) << ' '
           << std::quoted(contact.email) << ' ' << std::quoted(contact.address) << ' '
           << contact.isFavorite << '\n';
    return true;
}

bool DBManager::updateContact(const Contact& contact) const {
    std::ifstream input(getRelatedStorageFile(".contacts"));
    std::vector<Contact> all;
    Contact current;
    while (input >> current.id >> current.account_id >> current.group_id
                 >> std::quoted(current.name) >> std::quoted(current.phone)
                 >> std::quoted(current.email) >> std::quoted(current.address)
                 >> current.isFavorite) all.push_back(current);
    bool found = false;
    for (auto& item : all) {
        if (item.id == contact.id && item.account_id == contact.account_id) {
            item = contact;
            found = true;
        }
    }
    if (!found) return false;
    std::ofstream output(getRelatedStorageFile(".contacts"), std::ios::trunc);
    if (!output) return false;
    for (const auto& item : all)
        output << item.id << ' ' << item.account_id << ' ' << item.group_id << ' '
               << std::quoted(item.name) << ' ' << std::quoted(item.phone) << ' '
               << std::quoted(item.email) << ' ' << std::quoted(item.address) << ' '
               << item.isFavorite << '\n';
    return true;
}

bool DBManager::deleteContact(int accountId, int contactId) const {
    std::ifstream input(getRelatedStorageFile(".contacts"));
    std::vector<Contact> all;
    Contact current;
    while (input >> current.id >> current.account_id >> current.group_id
                 >> std::quoted(current.name) >> std::quoted(current.phone)
                 >> std::quoted(current.email) >> std::quoted(current.address)
                 >> current.isFavorite) all.push_back(current);
    std::ofstream output(getRelatedStorageFile(".contacts"), std::ios::trunc);
    if (!output) return false;
    for (const auto& item : all) {
        if (item.id == contactId && item.account_id == accountId) continue;
        output << item.id << ' ' << item.account_id << ' ' << item.group_id << ' '
               << std::quoted(item.name) << ' ' << std::quoted(item.phone) << ' '
               << std::quoted(item.email) << ' ' << std::quoted(item.address) << ' '
               << item.isFavorite << '\n';
    }
    return true;
}

std::vector<Group> DBManager::loadGroups(int accountId) const {
    std::vector<Group> groups;
    std::ifstream input(getRelatedStorageFile(".groups"));
    Group group;
    while (input >> group.id >> group.account_id >> std::quoted(group.name)
                 >> std::quoted(group.description)) {
        if (group.account_id == accountId) groups.push_back(group);
    }
    return groups;
}

bool DBManager::saveGroup(const Group& group) const {
    std::ofstream output(getRelatedStorageFile(".groups"), std::ios::app);
    if (!output) return false;
    output << group.id << ' ' << group.account_id << ' ' << std::quoted(group.name)
           << ' ' << std::quoted(group.description) << '\n';
    return true;
}

bool DBManager::updateGroup(const Group& group) const {
    std::ifstream input(getRelatedStorageFile(".groups"));
    std::vector<Group> all;
    Group current;
    while (input >> current.id >> current.account_id >> std::quoted(current.name)
                 >> std::quoted(current.description)) all.push_back(current);
    bool found = false;
    for (auto& item : all) {
        if (item.id == group.id && item.account_id == group.account_id) {
            item = group;
            found = true;
        }
    }
    if (!found) return false;
    std::ofstream output(getRelatedStorageFile(".groups"), std::ios::trunc);
    if (!output) return false;
    for (const auto& item : all)
        output << item.id << ' ' << item.account_id << ' ' << std::quoted(item.name)
               << ' ' << std::quoted(item.description) << '\n';
    return true;
}

bool DBManager::deleteGroup(int accountId, int groupId) const {
    std::ifstream input(getRelatedStorageFile(".groups"));
    std::vector<Group> all;
    Group current;
    while (input >> current.id >> current.account_id >> std::quoted(current.name)
                 >> std::quoted(current.description)) all.push_back(current);
    std::ofstream output(getRelatedStorageFile(".groups"), std::ios::trunc);
    if (!output) return false;
    for (const auto& item : all) {
        if (item.id == groupId && item.account_id == accountId) continue;
        output << item.id << ' ' << item.account_id << ' ' << std::quoted(item.name)
               << ' ' << std::quoted(item.description) << '\n';
    }
    return true;
}

std::vector<ContactGroup> DBManager::loadContactGroups(int accountId) const {
    std::vector<ContactGroup> relations;
    std::ifstream input(getRelatedStorageFile(".memberships"));
    int storedAccountId;
    ContactGroup relation;
    while (input >> storedAccountId >> relation.contactId >> relation.groupId) {
        if (storedAccountId == accountId) relations.push_back(relation);
    }
    return relations;
}

bool DBManager::saveContactGroup(int accountId, const ContactGroup& relation) const {
    std::ofstream output(getRelatedStorageFile(".memberships"), std::ios::app);
    if (!output) return false;
    output << accountId << ' ' << relation.contactId << ' ' << relation.groupId << '\n';
    return true;
}

bool DBManager::deleteContactGroups(int accountId, int groupId) const {
    std::ifstream input(getRelatedStorageFile(".memberships"));
    std::vector<std::tuple<int, int, int>> all;
    int storedAccountId, contactId, storedGroupId;
    while (input >> storedAccountId >> contactId >> storedGroupId)
        all.emplace_back(storedAccountId, contactId, storedGroupId);
    std::ofstream output(getRelatedStorageFile(".memberships"), std::ios::trunc);
    if (!output) return false;
    for (const auto& item : all) {
        if (std::get<0>(item) == accountId && std::get<2>(item) == groupId) continue;
        output << std::get<0>(item) << ' ' << std::get<1>(item) << ' ' << std::get<2>(item) << '\n';
    }
    return true;
}

bool DBManager::deleteContactGroup(int accountId, int contactId) const {
    std::ifstream input(getRelatedStorageFile(".memberships"));
    std::vector<std::tuple<int, int, int>> all;
    int storedAccountId, storedContactId, groupId;
    while (input >> storedAccountId >> storedContactId >> groupId)
        all.emplace_back(storedAccountId, storedContactId, groupId);

    std::ofstream output(getRelatedStorageFile(".memberships"), std::ios::trunc);
    if (!output) return false;
    for (const auto& item : all) {
        if (std::get<0>(item) == accountId && std::get<1>(item) == contactId) continue;
        output << std::get<0>(item) << ' ' << std::get<1>(item) << ' '
               << std::get<2>(item) << '\n';
    }
    return true;
}