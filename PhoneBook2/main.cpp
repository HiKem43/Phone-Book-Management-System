#include <iostream>
#include <vector>
#include "Account.h"
#include "Contact.h"
#include "Group.h"
#include "Contact_Group.h"
using namespace std;
int main() {
    // 1. Tạo Account
    Account account(
        1,
        "name",
        "123456",
        "Name",
        "name@gmail.com",
        "0901234567"
    );
    cout << "===== ACCOUNT =====" << endl;
    cout << "ID: " << account.getId() << endl;
    cout << "Username: " << account.getUsername() << endl;
    cout << "Name: " << account.getName() << endl;
    cout << "Email: " << account.getEmail() << endl;
    cout << "Phone: " << account.getPhone() << endl;
    // Kiểm tra dữ liệu Account
    if (account.validate()) {
        cout << "Account hop le!" << endl;
    }
    else {
        cout << "Account khong hop le!" << endl;
    }
    // 2. Tạo Contact
    Contact contact1(
        1,
        1,
        "Nguyen Van A",
        "0912345678",
        "a@gmail.com",
        "TP. Ho Chi Minh",
        false
    );
    Contact contact2(
        2,
        1,
        "Tran Thi B",
        "0987654321",
        "b@gmail.com",
        "Dong Nai",
        true
    );

    cout << "\n===== CONTACT =====" << endl;

    cout << "Contact 1:" << endl;
    cout << "ID: " << contact1.getId() << endl;
    cout << "Name: " << contact1.getName() << endl;
    cout << "Phone: " << contact1.getPhone() << endl;
    cout << "Email: " << contact1.getEmail() << endl;
    cout << "Address: " << contact1.getAddress() << endl;
    cout << "Favorite: "
        << (contact1.getFavorite() ? "Yes" : "No") << endl;
    cout << "\nContact 2:" << endl;
    cout << "ID: " << contact2.getId() << endl;
    cout << "Name: " << contact2.getName() << endl;
    cout << "Phone: " << contact2.getPhone() << endl;
    cout << "Email: " << contact2.getEmail() << endl;
    cout << "Address: " << contact2.getAddress() << endl;
    cout << "Favorite: "
        << (contact2.getFavorite() ? "Yes" : "No") << endl;
    // 3. Tạo Group
    Group group1(
        1,
        1,
        "Ban be",
        "Danh ba ban be"
    );

    Group group2(
        2,
        1,
        "Gia dinh",
        "Danh ba gia dinh"
    );
    cout << "\n===== GROUP =====" << endl;
    cout << "Group 1:" << endl;
    cout << "ID: " << group1.getId() << endl;
    cout << "Name: " << group1.getName() << endl;
    cout << "Description: " << group1.getDescription() << endl;

    cout << "\nGroup 2:" << endl;
    cout << "ID: " << group2.getId() << endl;
    cout << "Name: " << group2.getName() << endl;
    cout << "Description: " << group2.getDescription() << endl;
    // 4. Tạo Contact_Group
    Contact_Group cg1(
        contact1.getId(),
        group1.getId()
    );
    Contact_Group cg2(
        contact2.getId(),
        group2.getId()
    );
    cout << "\n===== CONTACT_GROUP =====" << endl;
    cout << "Contact " << cg1.getContactId()
        << " thuoc Group " << cg1.getGroupId() << endl;
    cout << "Contact " << cg2.getContactId()
        << " thuoc Group " << cg2.getGroupId() << endl;
    return 0;
}