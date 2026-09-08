#include "DatabaseConnector.h"
#include <iostream>

int main() {
    DatabaseConnector db;

    if (db.connect()) {
        std::cout << "Kết nối CSDL thành công!" << std::endl;

        // 1. Thao tác INSERT (Dùng cho đăng ký tài khoản / thêm liên hệ)
        std::string insertQuery = "INSERT INTO Accounts (username, password, fullname, email, role) "
                                  "VALUES ('thuylinh', 'hash_pass_123', 'Nguyen Thi Thuy Linh', 'linh@gmail.com', 'admin');";
        if (db.executeNonQuery(insertQuery)) {
            std::cout << "Thêm tài khoản thành công! ID vừa tạo: " << db.getLastInsertId() << std::endl;
        }

        // 2. Thao tác SELECT (Dùng cho đăng nhập / xem danh sách liên hệ)
        std::string selectQuery = "SELECT account_id, username, fullname, email FROM Accounts;";
        MYSQL_RES* res = db.executeQuery(selectQuery);

        if (res) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                std::cout << "ID: " << row[0] 
                          << " | User: " << row[1] 
                          << " | Name: " << row[2] 
                          << " | Email: " << row[3] << std::endl;
            }
            db.freeResult(res); // Luôn giải phóng bộ nhớ sau khi dùng xong
        }

        db.disconnect();
    }

    return 0;
}