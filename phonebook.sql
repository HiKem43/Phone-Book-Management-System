-- ============================================================
-- Phone Book Management System
-- MySQL database schema
-- ============================================================

CREATE DATABASE IF NOT EXISTS phonebook
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE phonebook;

-- ------------------------------------------------------------
-- Accounts
-- Password is stored as SHA-256 hash by MySQL SHA2(..., 256).
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Accounts (
    account_id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    fullname VARCHAR(100) NOT NULL,
    email VARCHAR(100) NULL UNIQUE,
    phone VARCHAR(15) NULL,
    role VARCHAR(20) NOT NULL DEFAULT 'User'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ------------------------------------------------------------
-- Contacts
-- Every contact belongs to exactly one account.
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Contacts (
    contact_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    phone VARCHAR(15) NOT NULL,
    email VARCHAR(100) NULL,
    address VARCHAR(255) NULL,
    is_favorite BOOLEAN NOT NULL DEFAULT FALSE,
    account_id INT NOT NULL,
    CONSTRAINT fk_contacts_account
        FOREIGN KEY (account_id) REFERENCES Accounts(account_id)
        ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ------------------------------------------------------------
-- Groups
-- Every group belongs to exactly one account.
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Groups (
    group_id INT AUTO_INCREMENT PRIMARY KEY,
    group_name VARCHAR(100) NOT NULL,
    description VARCHAR(255) NULL,
    account_id INT NOT NULL,
    CONSTRAINT fk_groups_account
        FOREIGN KEY (account_id) REFERENCES Accounts(account_id)
        ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ------------------------------------------------------------
-- Contacts_Groups
-- N-N relationship between Contacts and Groups.
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS Contacts_Groups (
    contact_id INT NOT NULL,
    group_id INT NOT NULL,
    PRIMARY KEY (contact_id, group_id),
    CONSTRAINT fk_cg_contact
        FOREIGN KEY (contact_id) REFERENCES Contacts(contact_id)
        ON DELETE CASCADE,
    CONSTRAINT fk_cg_group
        FOREIGN KEY (group_id) REFERENCES Groups(group_id)
        ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- ============================================================
-- Optional test Admin account
-- Username: admin
-- Password: admin123
-- Uncomment these two lines if you want a ready-made Admin.
-- ============================================================
-- INSERT INTO Accounts (username, password, fullname, email, phone, role)
-- VALUES ('admin', SHA2('admin123', 256), 'System Administrator', 'admin@phonebook.local', NULL, 'Admin');

-- Check the created tables:
-- SHOW TABLES;
-- SELECT account_id, username, fullname, email, phone, role FROM Accounts;
