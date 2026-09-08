CREATE DATABASE IF NOT EXISTS phonebook_db CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE phonebook_db;

-- 1. Bảng Accounts
CREATE TABLE IF NOT EXISTS Accounts (
    account_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    fullname VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE,
    phone VARCHAR(15) NULL,
    role VARCHAR(20) NOT NULL DEFAULT 'user'
);

-- 2. Bảng Contacts
CREATE TABLE IF NOT EXISTS Contacts (
    contact_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    phone VARCHAR(15) NOT NULL,
    email VARCHAR(100) NULL,
    address VARCHAR(255) NULL,
    is_favorite BOOLEAN NOT NULL DEFAULT FALSE,
    account_id INT NOT NULL,
    FOREIGN KEY (account_id) REFERENCES Accounts(account_id) ON DELETE CASCADE
);

-- 3. Bảng Groups
CREATE TABLE IF NOT EXISTS Groups (
    group_id INT AUTO_INCREMENT PRIMARY KEY,
    group_name VARCHAR(100) NOT NULL,
    description VARCHAR(255) NULL,
    account_id INT NOT NULL,
    FOREIGN KEY (account_id) REFERENCES Accounts(account_id) ON DELETE CASCADE
);

-- 4. Bảng trung gian Contact_Group (N-N)
CREATE TABLE IF NOT EXISTS Contact_Group (
    contact_id INT NOT NULL,
    group_id INT NOT NULL,
    PRIMARY KEY (contact_id, group_id),
    FOREIGN KEY (contact_id) REFERENCES Contacts(contact_id) ON DELETE CASCADE,
    FOREIGN KEY (group_id) REFERENCES Groups(group_id) ON DELETE CASCADE
);