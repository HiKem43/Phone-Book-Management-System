#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <vector>

// Cấu trúc dữ liệu Liên hệ
struct Contact {
    QString name;
    QString phone;
    QString email;
    QString address;
};

class PhoneBookWindow : public QMainWindow {
private:
    QTableWidget *tableWidget;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;
    QLineEdit *addressEdit;
    QLineEdit *searchEdit;

    std::vector<Contact> contacts;
    const QString fileName = "contacts.csv";

public:
    PhoneBookWindow() {
        setWindowTitle("Hệ Thống Quản Lý Danh Bạ - GUI");
        resize(900, 600);

        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

        // --- 1. Form nhập thông tin ---
        QFormLayout *formLayout = new QFormLayout();
        nameEdit = new QLineEdit();
        phoneEdit = new QLineEdit();
        emailEdit = new QLineEdit();
        addressEdit = new QLineEdit();

        formLayout->addRow("Họ và Tên (*):", nameEdit);
        formLayout->addRow("Số điện thoại (*):", phoneEdit);
        formLayout->addRow("Email:", emailEdit);
        formLayout->addRow("Địa chỉ:", addressEdit);

        // --- 2. Các nút chức năng ---
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        QPushButton *btnAdd = new QPushButton("Thêm mới");
        QPushButton *btnEdit = new QPushButton("Lưu chỉnh sửa");
        QPushButton *btnDelete = new QPushButton("Xóa liên hệ");
        QPushButton *btnClear = new QPushButton("Xóa trắng ô");

        buttonLayout->addWidget(btnAdd);
        buttonLayout->addWidget(btnEdit);
        buttonLayout->addWidget(btnDelete);
        buttonLayout->addWidget(btnClear);

        // --- 3. Thanh tìm kiếm ---
        QHBoxLayout *searchLayout = new QHBoxLayout();
        searchEdit = new QLineEdit();
        searchEdit->setPlaceholderText("Nhập từ khóa tìm kiếm (Tên, SĐT, Email, Address)...");
        searchLayout->addWidget(new QLabel("Tìm kiếm:"));
        searchLayout->addWidget(searchEdit);

        // --- 4. Bảng hiển thị (Table) ---
        tableWidget = new QTableWidget();
        tableWidget->setColumnCount(4);
        QStringList headers = {"Họ và Tên", "Số Điện Thoại", "Email", "Địa Chỉ"};
        tableWidget->setHorizontalHeaderLabels(headers);
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Đưa các thành phần vào Layout chính
        mainLayout->addLayout(formLayout);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addLayout(searchLayout);
        mainLayout->addWidget(tableWidget);

        setCentralWidget(centralWidget);

        // Tải dữ liệu ban đầu
        loadFromFile();
        refreshTable();

        // --- Sự kiện (Events / Signals & Slots) ---
        connect(btnAdd, &QPushButton::clicked, this, [this]() { addContact(); });
        connect(btnEdit, &QPushButton::clicked, this, [this]() { editContact(); });
        connect(btnDelete, &QPushButton::clicked, this, [this]() { deleteContact(); });
        connect(btnClear, &QPushButton::clicked, this, [this]() { clearFields(); });
        connect(searchEdit, &QLineEdit::textChanged, this, [this](const QString &text) { filterContacts(text); });
        connect(tableWidget, &QTableWidget::itemClicked, this, [this]() { populateFieldsFromTable(); });
    }

private:
    void addContact() {
        QString name = nameEdit->text().trimmed();
        QString phone = phoneEdit->text().trimmed();
        QString email = emailEdit->text().trimmed();
        QString address = addressEdit->text().trimmed();

        if (name.isEmpty() || phone.isEmpty()) {
            QMessageBox::warning(this, "Thông báo", "Vui lòng nhập đầy đủ Họ tên và Số điện thoại!");
            return;
        }

        contacts.push_back({name, phone, email, address});
        saveToFile();
        refreshTable();
        clearFields();
        QMessageBox::information(this, "Thành công", "Đã thêm liên hệ mới vào danh bạ!");
    }

    void editContact() {
        int row = tableWidget->currentRow();
        if (row < 0 || row >= static_cast<int>(contacts.size())) {
            QMessageBox::warning(this, "Thông báo", "Vui lòng chọn 1 dòng trong bảng để chỉnh sửa!");
            return;
        }

        contacts[row].name = nameEdit->text().trimmed();
        contacts[row].phone = phoneEdit->text().trimmed();
        contacts[row].email = emailEdit->text().trimmed();
        contacts[row].address = addressEdit->text().trimmed();

        saveToFile();
        refreshTable();
        clearFields();
        QMessageBox::information(this, "Thành công", "Đã cập nhật thông tin liên hệ!");
    }

    void deleteContact() {
        int row = tableWidget->currentRow();
        if (row < 0 || row >= static_cast<int>(contacts.size())) {
            QMessageBox::warning(this, "Thông báo", "Vui lòng chọn 1 dòng trong bảng để xóa!");
            return;
        }

        auto reply = QMessageBox::question(this, "Xác nhận xóa", "Bạn có chắc chắn muốn xóa liên hệ này?",
                                           QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            contacts.erase(contacts.begin() + row);
            saveToFile();
            refreshTable();
            clearFields();
        }
    }

    void populateFieldsFromTable() {
        int row = tableWidget->currentRow();
        if (row >= 0 && row < static_cast<int>(contacts.size())) {
            nameEdit->setText(contacts[row].name);
            phoneEdit->setText(contacts[row].phone);
            emailEdit->setText(contacts[row].email);
            addressEdit->setText(contacts[row].address);
        }
    }

    void clearFields() {
        nameEdit->clear();
        phoneEdit->clear();
        emailEdit->clear();
        addressEdit->clear();
        tableWidget->clearSelection();
    }

    void refreshTable() {
        tableWidget->setRowCount(0);
        for (size_t i = 0; i < contacts.size(); ++i) {
            tableWidget->insertRow(i);
            tableWidget->setItem(i, 0, new QTableWidgetItem(contacts[i].name));
            tableWidget->setItem(i, 1, new QTableWidgetItem(contacts[i].phone));
            tableWidget->setItem(i, 2, new QTableWidgetItem(contacts[i].email));
            tableWidget->setItem(i, 3, new QTableWidgetItem(contacts[i].address));
        }
    }

    void filterContacts(const QString &text) {
        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            bool match = false;
            for (int j = 0; j < tableWidget->columnCount(); ++j) {
                QTableWidgetItem *item = tableWidget->item(i, j);
                if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                    match = true;
                    break;
                }
            }
            tableWidget->setRowHidden(i, !match);
        }
    }

    void saveToFile() {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (const auto &c : contacts) {
                out << c.name << "," << c.phone << "," << c.email << "," << c.address << "\n";
            }
            file.close();
        }
    }

    void loadFromFile() {
        contacts.clear();
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(",");
                if (parts.size() >= 4) {
                    contacts.push_back({parts[0], parts[1], parts[2], parts[3]});
                }
            }
            file.close();
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PhoneBookWindow window;
    window.show();
    return app.exec();
}