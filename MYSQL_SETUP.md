# MySQL setup - Phone Book Management System

## 1. Start MySQL Server

Make sure the local MySQL Server is running on port `3306`.

Default connection used by the project:

- Host: `127.0.0.1`
- Port: `3306`
- User: `root`
- Password: empty
- Database: `phonebook`

If your MySQL `root` account has a password, edit the connection values in:

`src/DBManager.cpp`

Look for:

```cpp
db.connect("127.0.0.1", "root", "", "phonebook", 3306)
```

For example:

```cpp
db.connect("127.0.0.1", "root", "YOUR_PASSWORD", "phonebook", 3306)
```

## 2. Create the database

The program automatically creates the `phonebook` database and the four required tables when it starts, provided the MySQL user has permission to create databases/tables.

You can also run `phonebook.sql` manually in MySQL Workbench/phpMyAdmin.

## 3. Register and Login

The new flow is:

`Register -> AccountService -> DBManager -> MySQL INSERT`

`Login -> AccountService -> DBManager -> MySQL SELECT`

Password is stored as a SHA-256 hash using MySQL `SHA2(..., 256)`, so the plaintext password is not stored in `Accounts`.

## 4. Verify the account

After registering an account, run:

```sql
USE phonebook;
SELECT account_id, username, fullname, email, phone, role FROM Accounts;
```

You should see the newly registered account.

## 5. MySQL C API required for C++ build

The project uses the MySQL C API (`mysql/mysql.h` and `libmysql`). The VS Code build task therefore needs the MySQL client include and library directories.

If `g++` cannot find `mysql/mysql.h`, install MySQL Server/Client development files and then update the paths in `.vscode/tasks.json` or use the provided `build_mysql.bat`.
