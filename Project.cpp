#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;
const string MEMBERS_FILE = "member.txt";
const string MEMBERS_ID_FILE = "member_id.txt";
const string ADMINS_FILE = "admin.txt";
const string ADMINS_ID_FILE = "admin_id.txt";
const string PRODUCT_FILE = "product.txt";
const string ORDER_ID_FILE = "order_id_counter.txt";
const string PURCHASE_HISTORY_FILE = "purchase_history.txt";
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& value) {
        data = value;
        next = nullptr;
    }
};
struct Member {
    string member_id;
    string full_name;
    string email;
    string password;
    string contact;
    string status;
    Member( string id="", string name="", string mail="", 
            string pass="", string cont="", string stat="Active"){
        member_id = id;
        full_name = name;
        email = mail;
        password = pass;
        contact = cont;
        status = stat;
    }
};
struct Admin {
    string admin_id;
    string full_name;
    string email;
    string password;
    string contact;
    string position;
    string status;
    Admin(  string id="", string name="", string mail="", string pass="", 
            string cont="", string pos="Admin", string stat="Active"){
        admin_id = id;
        full_name = name;
        email = mail;
        password = pass;
        contact = cont;
        position = pos;
        status = stat;
    }
};
struct Product {
    string product_id;
    string product_name;
    string category;
    double price;
    int stock;
    string description;
    string status;
    Product(string id = "", string name = "", string cat = "", double cost = 0.0,
            int quantity = 0, string desc = "", string stat = "") {
        product_id = id;
        product_name = name;
        category = cat;
        price = cost;
        stock = quantity;
        description = desc;
        status = stat;
    }
};
struct Attribute2{
    string attribute_name;
    double addUp;
    Attribute2(string name = "", double cost = 0.0) {
        attribute_name = name;
        addUp = cost;
    }
};
struct CartItem {
    Product product;
    string product_id;
    string product_name;
    double price;
    int quantity;
    string attribute1;
    string attribute2;
    double addUp;
    double total;
    string status;
    CartItem(Product p = Product(), string pid = "", string name = "", double pr = 0.0,
             int q = 0, string att1="", string att2="", double add = 0.00, double t = 0.0, string stat = "") {
        product = p;
        product_id = pid;
        product_name = name;
        price = pr;
        quantity = q;
        attribute1 = att1;
        attribute2 = att2;
        addUp = add;
        total = t;
        status = stat;
    }
};
template <typename T>
class LinkedList {
    protected:
        Node<T> *head, *temp;
    public:
        LinkedList() {head=nullptr;}
        bool isEmpty() const {
            if (head == nullptr)
                return true;
            else
                return false;
        }
        void append(const T& value) {
            Node<T>* newNode = new Node<T>(value);
            if (isEmpty()) {
                head = newNode;
            } 
            else {
                temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        Node<T>* getHead() const {
            return head;
        }
        void clear() {
            while (head != nullptr) {
                temp = head;
                head = head->next;
                delete temp;
            }
        }
        virtual ~LinkedList() {
            clear();
        }
};
class MemberLinkedList : public LinkedList<Member> {
public:
    void loadMembers() {
        ifstream file(MEMBERS_FILE);
        if (!file) {
            ofstream createFile(MEMBERS_FILE);
            createFile.close();
            return;
        }
        clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Member member;
            member.member_id = line;
            getline(file, member.full_name);
            getline(file, member.email);
            getline(file, member.password);
            getline(file, member.contact);
            getline(file, member.status);
            append(member);
        }
        file.close();
    }
    bool emailExists(const string& email) const {
        Node<Member>* current = head;
        while (current != nullptr) {
            if (current->data.email == email) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    Member* findMemberByEmail(const string& email) {
        Node<Member>* current = head;
        while (current != nullptr) {
            if (current->data.email == email) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
};
class AdminLinkedList : public LinkedList<Admin> {
public:
    void loadAdmins() {
        ifstream file(ADMINS_FILE);
        if (!file) {
            ofstream createFile(ADMINS_FILE);
            createFile.close();
            return;
        }
        clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Admin admin;
            admin.admin_id = line;
            getline(file, admin.full_name);
            getline(file, admin.email);
            getline(file, admin.password);
            getline(file, admin.contact);
            getline(file, admin.position);
            getline(file, admin.status);
            append(admin);
        }
        file.close();
    }
    bool emailExists(const string& email) const {
        Node<Admin>* current = head;
        while (current != nullptr) {
            if (current->data.email == email) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    Admin* findAdminByEmail(const string& email) {
        Node<Admin>* current = head;
        while (current != nullptr) {
            if (current->data.email == email) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
};
MemberLinkedList memberList;
AdminLinkedList adminList;
Member loggedInMember;
Admin loggedInAdmin;
Product* products = nullptr;
int productCount = 0;
void mainMenu();
void memberMenu(Member loggedInMember);
void adminMenu(Admin loggedInAdmin);
void filterProducts();
void printWrappedText(const string& text);
void displayProduct(const Product& product);
string getAttribute1(string category);
Attribute2 getAttribute2(string category);
void addToCart(const string& product_id, int quantity, string attribute1, Attribute2 obj);
void displayCart(Member loggedInMember);
void deleteCart(CartItem*& cart, int& cartSize);
void editCart(CartItem*& cart, int& cartSize);
void proceedToPayment(CartItem* cart, int cartSize);
void creditCardPayment(CartItem* cart, int cartSize, double totalPayment);
void cashPayment(CartItem* cart, int cartSize, double totalPayment);
bool isValidCardNumber(const string& cardNumber);
bool isValidExpiryDate(const string& expiryDate);
bool isValidCVV(const string& cvv);
void recordPurchaseHistory(CartItem* cart, int cartSize, double total);
string generateOrderId();
void clearCartFile(const string& member_id);
void clearScreen() {
    system("cls");
}
void printWrappedText(const string& text) {
 	int lineLength = 60;
    int count = 0;
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        count++;
        if (count >= lineLength && text[i] == ' ') {
            cout << '\n';
            count = 0;
        }
    }
    cout << endl;
}
int splitAttribute(const string& line, string* parts, int maxParts) {
    int count = 0;
    bool inQuotes = false;
    string current;
    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } 
        else if (c == ',' && !inQuotes) {
            if (count < maxParts) {
                parts[count++] = current;
                current.clear();
            }
            else {
                break;
            }
        } 
        else {
            current += c;
        }
    }
    if (count < maxParts) {
        parts[count++] = current;
    }
    return count;
}
string removeQuotes(const string& s) {
    string trimmed="";
    if (s.length() >= 2 && s[0] == '"' && s[s.length() - 1] == '"') {
        for(int i=1;i<s.length()-1;i++){
            trimmed+=s[i];
        }
        return trimmed;
    }
    else
        return s;
}
int partitionProduct(Product* arr, int low, int high, const string& key) {
    Product pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool condition = false;
        if (key == "product_id") {
            condition = arr[j].product_id < pivot.product_id;
        }
        if (condition) {
            i++;
            Product temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Product temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}
void quickSortProduct(Product* arr, int low, int high, const string& key) {
    if (low < high) {
        int pivot = partitionProduct(arr, low, high, key);
        quickSortProduct(arr, low, pivot - 1, key);
        quickSortProduct(arr, pivot + 1, high, key);
    }
}
int partitionCartItem(CartItem* arr, int low, int high, const string& key) {
    CartItem pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool condition = false;
        if (key == "product_id") {
            condition = arr[j].product_id < pivot.product_id;
        }
        if (condition) {
            i++;
            CartItem temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    CartItem temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}
void quickSortCartItem(CartItem* arr, int low, int high, const string& key) {
    if (low < high) {
        int pi = partitionCartItem(arr, low, high, key);
        quickSortCartItem(arr, low, pi - 1, key);
        quickSortCartItem(arr, pi + 1, high, key);
    }
}
Product* binarySearchProduct(Product* arr, int first, int last, const string& target, const string& key) {
    while (first <= last) {
        int mid = first + (last - first) / 2;
        string current;
        if (key == "product_id") {
            current = arr[mid].product_id;
        }
        if (current == target) return &arr[mid];
        else if (current < target) first = mid + 1;
        else last = mid - 1;
    }
    return nullptr;
}
CartItem* binarySearchCartItem(CartItem* arr, int low, int high, const string& target, const string& key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        string current;
        if (key == "product_id") {
            current = arr[mid].product_id;
        }
        if (current == target) return &arr[mid];
        else if (current < target) low = mid + 1;
        else high = mid - 1;
    }
    return nullptr;
}
string getNextMemberId() {
    ifstream file(MEMBERS_ID_FILE);
    string lastId;
    if (file) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) lastId = line;
        }
        file.close();
    } else {
        ofstream createFile(MEMBERS_ID_FILE);
        createFile << "U0001\n";
        createFile.close();
        return "U0001";
    }
    if (!lastId.empty()) {
        string numericPart = "";
        numericPart += lastId[1];
        numericPart += lastId[2];
        numericPart += lastId[3];
        numericPart += lastId[4];
        int num = stoi(numericPart);
        stringstream finalId;
        finalId << "U" << setw(4) << setfill('0') << (num + 1);
        return finalId.str();
    }
    return "U0001";
}
string getNextAdminId() {
    ifstream file(ADMINS_ID_FILE);
    string lastId;
    if (file) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) lastId = line;
        }
        file.close();
    } else {
        ofstream createFile(ADMINS_ID_FILE);
        createFile << "A0001\n";
        createFile.close();
        return "A0001";
    }
    if (!lastId.empty()) {
        string numericPart = "";
        numericPart += lastId[1];
        numericPart += lastId[2];
        numericPart += lastId[3];
        numericPart += lastId[4];
        int num = stoi(numericPart);
        stringstream finalId;
        finalId << "A" << setw(4) << setfill('0') << (num + 1);
        return finalId.str();
    }
    return "A0001";
}
void saveMember(const Member& member) {
    bool fileIsEmpty = true;
    {
        ifstream file(MEMBERS_FILE);
        if (file) {
            string line;
            if (getline(file, line)) {
                fileIsEmpty = false;
            }
        }
    }
    ofstream file(MEMBERS_FILE, ios::app);
    if (file) {
        if (!fileIsEmpty) {
            file << "\n";
        }
        file << member.member_id << "\n"
             << member.full_name << "\n"
             << member.email << "\n"
             << member.password << "\n"
             << member.contact << "\n"
             << member.status << "\n";
    }
}
void signup() {
    string member_id = getNextMemberId();
    string status = "Active";
    string full_name, email, password, confirm_password, contact;
    while (true) {
        cout << "_______________________________________________\n";
        cout << "| NAME REQUIREMENTS                           |\n";
        cout << "|_____________________________________________|\n";
        cout << "|1. Name must have at least 5 characters      |\n";
        cout << "|2. No special character(s) allowed           |\n";
        cout << "|3. No number(s) allowed                      |\n";
        cout << "|_____________________________________________|\n";
        cout << "\nEnter your full name, [R] to return to the main menu: ";
        getline(cin, full_name);
        if (full_name == "R" || full_name == "r") {
            clearScreen();
            mainMenu();
            return;
        }
        bool valid = true;
        int letterCount = 0;
        for (int i = 0; i < full_name.length(); ++i) {
            char c = full_name[i];
            if (!isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
            if (isalpha(c)) 
                letterCount++;
        }
        if (!valid || letterCount < 5) {
            cout << "_______________________________________________\n";
            cout << "| ERROR! INVALID NAME                         |\n";
            cout << "|_____________________________________________|\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "\nEnter your email (example: user@example.com): ";
        getline(cin, email);
        int atPosition = -1;
        int dotPosition = -1;
        int atCount = 0;
        for (int i = 0; i < email.length(); i++) {
            if (email[i] == '@') {
                atCount++;
                atPosition = i;
            } else if (email[i] == '.' && atPosition != -1 && i > atPosition) {
                dotPosition = i;
            }
        }
        bool valid = true;
        if (email.length() < 5) 
            valid = false; 
        else if (atCount != 1) 
            valid = false;  
        else if (atPosition <= 0 || atPosition >= email.length() - 1) 
            valid = false; 
        else if (dotPosition == -1 || dotPosition == atPosition + 1) 
            valid = false; 
        else if (dotPosition >= email.length() - 1) 
            valid = false; 
        else if (email[0] == '.' || email[email.length() - 1] == '.') 
            valid = false; 
        for (int i = 0; i < email.length() - 1; ++i) {
            if (email[i] == '.' && email[i + 1] == '.') {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "____________________________________________________\n";
            cout << "|Invalid email format! Please enter a valid email. |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        if (memberList.emailExists(email)) {
            cout << "____________________________________________________\n";
            cout << "|This email is already registered!                 |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "_______________________________________________\n";
        cout << "| PASSWORD REQUIREMENTS                       |\n";
        cout << "|_____________________________________________|\n";
        cout << "|1. Password must be at least 8 characters    |\n";
        cout << "|2. Password must have at least 1 uppercase   |\n";
        cout << "|3. Password must have at least 1 lowercase   |\n";
        cout << "|4. Password must have at least 1 number      |\n";
        cout << "|_____________________________________________|\n";
        cout << "\nEnter your new password (example: Xuanting123): ";
        getline(cin, password);
        if (password.length() < 8) {
            cout << "____________________________________________________\n";
            cout << "|Password must be at least 8 characters!           |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        bool hasUpper = false, hasLower = false, hasDigit = false;
        for (int i = 0; i < password.length(); ++i) {
            char c = password[i];
            if (isupper(c)) hasUpper = true;
            if (islower(c)) hasLower = true;
            if (isdigit(c)) hasDigit = true;
        }
        if (!hasUpper) {
            cout << "____________________________________________________\n";
            cout << "|Password must have at least 1 uppercase!          |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        if (!hasLower) {
            cout << "____________________________________________________\n";
            cout << "|Password must have at least 1 lowercase!          |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        if (!hasDigit) {
            cout << "____________________________________________________\n";
            cout << "|Password must have at least 1 number!             |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        cout << "\nConfirm your password: ";
        getline(cin, confirm_password);
        if (confirm_password != password) {
            cout << "____________________________________________________\n";
            cout << "|Passwords do not match!                           |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "\nEnter your contact number (example: 012-34567890): ";
        getline(cin, contact);
        if (contact.length() < 4 || contact[3] != '-') {
            cout << "____________________________________________________\n";
            cout << "|Invalid format! Example: 012-34567890             |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        string part1 = "";
        for(int i=0;i<3;i++){
            part1 += contact[i];
        }
        string part2 = "";
        for (int i = 4; i < contact.length(); ++i) {
            part2 += contact[i];
        }
        if (!(part1[0] == '0' && part1[1] == '1')) {
            cout << "____________________________________________________\n";
            cout << "|Phone number must start with '01'!                |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        string combined = part1 + part2;
        bool onlyDigits = true;
        for (int i = 0; i < combined.length(); ++i) {
            if (!isdigit(combined[i])) {
                onlyDigits = false;
                break;
            }
        }
        if (!onlyDigits) {
            cout << "____________________________________________________\n";
            cout << "|Phone number cannot contain symbols (except '-')  |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        if (combined.length() != 10 && combined.length() != 11) {
            cout << "________________________________________________________\n";
            cout << "|Phone number must be 10 or 11 digits (excluding '-')! |\n";
            cout << "|______________________________________________________|\n";
            continue;
        }
        break;
    }
    Member newMember(member_id, full_name, email, password, contact, status);
    memberList.append(newMember);
    saveMember(newMember);
    ofstream idFile(MEMBERS_ID_FILE, ios::app);
    if (idFile) {
        idFile << member_id << "\n";
        idFile.close();
    }
    cout << "________________________________________________________\n";
    cout << "|Registration successful! Your Member ID: " << member_id << "        |\n";
    cout << "|______________________________________________________|\n";
    cout << "\nPress [ENTER] to return to Main Menu.";
    cin.ignore();
    clearScreen();
}
void login() {
    string email, password;
    bool hasAt = false, hasDot = false;
    do {
        cout << "\nEnter your email, [R] to return to the main menu: ";
        getline(cin, email);
        if (email == "R" || email == "r") {
            clearScreen();
            mainMenu();
            return;
        }
        for (int i=0;i<email.length();i++) {
            char c = email[i];
            if (c == '@') hasAt = true;
            if (c == '.') hasDot = true;
        }
        if (!hasAt || !hasDot) {
            cout << "________________________________________________________\n";
            cout << "|Invalid email format! Must include @ and . symbol     |\n";
            cout << "|______________________________________________________|\n";
        }
    } while (!hasAt || !hasDot);
    Member* member = memberList.findMemberByEmail(email);
    if (member == nullptr) {
        cout << "________________________________________________________\n";
        cout << "|Email not found.                                      |\n";
        cout << "|______________________________________________________|\n";
        cout << "\nPress [ENTER] to return to Main Menu.";
        cin.ignore();
        clearScreen();
        return;
    }
    if (member->status != "Active") {
        cout << "________________________________________________________\n";
        cout << "|Your account is inactive. Please contact admin.       |\n";
        cout << "|______________________________________________________|\n";
        cout << "\nPress [ENTER] to return to Main Menu.";
        cin.ignore();
        clearScreen();
        return;
    }
    int attempts = 0;
    string currentPassword;
    cout << "\nEnter your password: ";
    getline(cin, currentPassword);
    while (attempts < 3) {
        if (currentPassword == member->password) {
            cout << "________________________________________________________\n";
            cout << "|Logged in Successfully!                               |\n";
            cout << "|______________________________________________________|\n";
            loggedInMember = *member;
            cout << "\nPress [ENTER] to continue.";
            cin.ignore();
            memberMenu(loggedInMember);
            return;
        } else {
            attempts++;
            cout << "________________________________________________________\n";
            cout << "|Incorrect password! Attempts left: " << 3 - attempts <<"                  |\n";
            cout << "|______________________________________________________|\n";
            if (attempts < 3) {
                cout << "\nPlease enter your password again: ";
                getline(cin, currentPassword);
            }
        }
    }
    cout << "\n________________________________________________________\n";
    cout << "|Too many failed attempts. Login terminated.           |\n";
    cout << "|______________________________________________________|\n";
    cout << "\nPress [ENTER] to return to Main Menu.";
    cin.ignore();
    clearScreen();
}
void adminLogin() {
    string email, password;
    bool hasAt = false, hasDot = false;
    do {
        cout << "\nEnter your email, [R] to return to the main menu: ";
        getline(cin, email);
        if (email == "R" || email == "r") {
            clearScreen();
            mainMenu();
            return;
        }
        for (int i=0;i<email.length();i++) {
            char c = email[i];
            if (c == '@') hasAt = true;
            if (c == '.') hasDot = true;
        }
        if (!hasAt || !hasDot) {
            cout << "________________________________________________________\n";
            cout << "|Invalid email format! Must include @ and . symbol     |\n";
            cout << "|______________________________________________________|\n";
        }
    } while (!hasAt || !hasDot);
    Admin* admin = adminList.findAdminByEmail(email);
    if (admin == nullptr) {
        cout << "________________________________________________________\n";
        cout << "|Email not found.                                      |\n";
        cout << "|______________________________________________________|\n";
        cout << "\nPress [ENTER] to continue.";
        cin.ignore();
        clearScreen();
        return;
    }
    if (admin->status != "Active") {
        cout << "________________________________________________________\n";
        cout << "|Your account is inactive. Please contact Superadmin.  |\n";
        cout << "|______________________________________________________|\n";
        cout << "\nPress [ENTER] to return to Main Menu.";
        cin.ignore();
        clearScreen();
        return;
    }
    int attempts = 0;
    string currentPassword;
    cout << "\nEnter your password: ";
    getline(cin, currentPassword);
    while (attempts < 3) {
        if (currentPassword == admin->password) {
            cout << "________________________________________________________\n";
            cout << "|Logged in Successfully!                               |\n";
            cout << "|______________________________________________________|\n";
            loggedInAdmin = *admin;
            cout << "\nPress [ENTER] to continue.";
            cin.ignore();
            adminMenu(loggedInAdmin);
            return;
        } else {
            attempts++;
            cout << "________________________________________________________\n";
            cout << "|Incorrect password! Attempts left: " << 3 - attempts <<"                  |\n";
            cout << "|______________________________________________________|\n";
            if (attempts < 3) {
                cout << "\nPlease enter your password again: ";
                getline(cin, currentPassword);
            }
        }
    }
    cout << "\n________________________________________________________\n";
    cout << "|Too many failed attempts. Login terminated.           |\n";
    cout << "|______________________________________________________|\n";
    cout << "\nPress [ENTER] to return to Main Menu.";
    cin.ignore();
    clearScreen();
}
void memberMenu(Member loggedInMember) {
    while (true) {
        clearScreen();
        cout << "\n===============================================================\n";
        cout << "                          WELCOME " << loggedInMember.full_name << endl;
        cout << "===============================================================\n";
        cout << "1. Browse Product\n";
        cout << "2. View My Cart\n";
        cout << "3. View Order History\n";
        cout << "4. View My Profile\n";
        cout << "5. Rate Our System\n";
        cout << "6. Log Out\n";
        cout << "===============================================================\n";
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
        if (choice == "1") {
            clearScreen();
            filterProducts();
            return;
        }
        else if (choice == "2") {
            clearScreen();
            displayCart(loggedInMember);
            return;
        }
        else if (choice == "6") {
            clearScreen();
            mainMenu();
            return;
        }
        else {
            cout << "Invalid choice! Press [ENTER] to retry.";
            cin.get();
        }
    }
}
bool loadProducts() {
    ifstream file(PRODUCT_FILE);
    if (!file) {
        cout << "Error: Product file not found!" << endl;
        return false;
    }
    productCount = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) productCount++;
    }
    file.close();
    if (products) delete[] products;
    products = new Product[productCount];
    ifstream openfile(PRODUCT_FILE);
    if (!openfile) {
        cout << "Error: Product file not found on second open!" << endl;
        return false;
    }
    int index = 0;
    while (getline(openfile, line) && index < productCount) {
        if (line.empty()) continue;
        string parts[7];
        int fieldsFound = splitAttribute(line, parts, 7);
        if (fieldsFound < 7) {
            cout << "Warning: Line skipped because extracted fiels max out" << endl;
            continue;
        }
        for (int i = 0; i < 7; i++) {
            parts[i] = removeQuotes(parts[i]);
        }
        products[index].product_id = parts[0];
        products[index].product_name = parts[1];
        products[index].category = parts[2];
        try {
            products[index].price = stod(parts[3]);
        } catch (const invalid_argument& e) {
            cout << "Warning: Invalid price format in line: " << line << endl;
            products[index].price = 0;
        }
        try {
            products[index].stock = stoi(parts[4]);
        } catch (const invalid_argument& e) {
            cout << "Warning: Invalid stock format in line: " << line << endl;
            products[index].stock = 0;
        }
        products[index].description = parts[5];
        products[index].status = parts[6];
        index++;
    }
    openfile.close();
    productCount = index;
    quickSortProduct(products, 0, productCount - 1, "product_id");
    return true;
}
void filterProducts() {
    if (!loadProducts()) {
        cout << "Failed to load products." << endl;
        cout << "Press [ENTER] to return to Main Menu.";
        cin.ignore();
        cin.get();
        clearScreen();
        mainMenu();
        return;
    }
    while (true) {
        clearScreen();
        cout << "===============================================================" << endl;
        cout << "|                  WELCOME TO OUR PIZZA STORE!                |" << endl;
        cout << "===============================================================" << endl;
        cout << "| Select a category:                                          |" << endl;
        cout << "| 1. Pizza                                                    |" << endl;
        cout << "| 2. Side                                                     |" << endl;
        cout << "| 3. Beverage                                                 |" << endl;
        cout << "| 4. Back to Main Menu                                        |" << endl;
        cout << "===============================================================" << endl;
        string choiceString;
        cout << "Enter your choice : ";
        getline(cin,choiceString);
        int choice = stoi(choiceString);
        string categories[] = {"Pizza", "Side", "Beverage"};
        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Press [ENTER] to retry.";
            cin.get();
            filterProducts();
        }
        else if (choice == 4) {
            clearScreen();
            memberMenu(loggedInMember);
            return;
        }
        string selectedCategory = categories[choice - 1];
        while (true) {
            clearScreen();
            cout << "Products in Category: " << selectedCategory << endl;
            loadProducts();
            bool found = false;
            for (int i = 0; i < productCount; i++) {
                if (products[i].category == selectedCategory && products[i].status == "Active") {
                    displayProduct(products[i]);
                    found = true;
                }
            }
            if (!found) {
                cout << "\nNo available products found in '" << selectedCategory << "' category." << endl;
            }
            cout << "\n-----------------------------------------------------------------" << endl;
            cout << " _________________________________" << endl;
            cout << "| Options:                        |" << endl;
            cout << "| Enter Product ID to add to cart |" << endl;
            cout << "| [C] View Cart                   |" << endl;
            cout << "| [B] Back to Category Selection  |" << endl;
            cout << "| [M] Back to Main Menu           |" << endl;
            cout << "|_________________________________|" << endl;
            string selection;
            cout << "\nEnter your choice: ";
            cin >> selection;
            if (selection == "C" || selection == "c") {
                cin.ignore();
                displayCart(loggedInMember);
                continue;  
            } else if (selection == "B" || selection == "b") {
                cin.ignore();
                break;
            } else if (selection == "M" || selection == "m") {
                clearScreen();
                cin.ignore();
                memberMenu(loggedInMember);
                return;
            }
            string product_id = selection;
            Product* product = binarySearchProduct(products, 0, productCount - 1, product_id, "product_id");
            if (!product) {
                cout << "Product with ID '" << product_id << "' not found." << endl;
                cout << "Press [ENTER] to continue.";
                cin.ignore();
                cin.get();
                continue;
            } else if (product->category != selectedCategory) {
                cout << "Product with ID '" << product_id << "' not found in '" 
                     << selectedCategory << "' category." << endl;
                cout << "Press [ENTER] to continue.";
                cin.ignore();
                cin.get();
                continue;
            }
            if (product->status == "Inactive") {
                cout << "\nThis product is currently unavailable." << endl;
                cout << "Press [ENTER] to continue.";
                cin.ignore();
                cin.get();
                continue;
            }
            if (product->stock <= 0) {
                cout << "\nSorry, this product is out of stock!" << endl;
                cout << "Press [ENTER] to continue.";
                cin.ignore();
                cin.get();
                continue;
            }
            cout << "Selecting product: " << product->product_name << endl;
            string attribute1 = getAttribute1(selectedCategory);
            Attribute2 obj = getAttribute2(selectedCategory);
            while (true) {
                cout << "\nEnter quantity (available: " << product->stock << "): ";
                string quantity;
                cin >> quantity;
                bool isNumber = true;
                for (int i=0;i<quantity.length();i++) {
                    char c = quantity[i];
                    if (!isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }
                if (!isNumber) {
                    cout << "Invalid input. Please enter a number." << endl;
                    continue;
                }
                int qty = stoi(quantity);
                if (qty <= 0) {
                    cout << "Quantity must be positive." << endl;
                } else if (qty > product->stock) {
                    cout << "Not enough stock available." << endl;
                } else {
                    addToCart(product_id, qty, attribute1, obj);
                    cout << "Press [ENTER] to continue.";
                    cin.ignore();
                    cin.get();
                    break;
                }
            }
        }
    }
}
string getAttribute1(string category){
    string attribute1;
    string choice;
    cin.ignore();
    if(category=="Pizza"){
        cout << "\n__________________________" << endl;
        cout << "| Available Crust:       |" << endl;
        cout << "| 1. Cheesy Crust        |" << endl;
        cout << "| 2. Crackin Thin        |" << endl;
        cout << "| 3. Pan                 |" << endl;
        cout << "| 4. Stuffed Crust       |" << endl;
        cout << "|________________________|" << endl;
        string crust[] = {"Cheesy Crust", "Crackin Thin", "Pan", "Stuffed Crust"};
        while(true){
            cout << "Select crust: ";
            getline(cin,choice);
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <= 4){
                        attribute1 = crust[selection-1];
                        return attribute1;
                    }
                    else{
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                }
                catch (const invalid_argument& e){
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            }
        }
    }
    else if(category=="Beverage"){
        cout << "\n__________________________" << endl;
        cout << "| Serving Temperature:   |" << endl;
        cout << "| 1. Cold                |" << endl;
        cout << "| 2. Room Temperature    |" << endl;
        cout << "|________________________|" << endl;
        string temperature[] = {"Cold", "Room Temperature"};
        while(true){
            cout << "Select serving temperature: ";
            getline(cin,choice);
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <= 2){
                        attribute1 = temperature[selection-1];
                        return attribute1;
                    }
                    else{
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                }
                catch (const invalid_argument& e){
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            }
        }
    }
    else if(category=="Side"){
        cout << "\n_____________________________" << endl;
        cout << "| Available Sauce:          |" << endl;
        cout << "| 1. Garlic Aioli Dip       |" << endl;
        cout << "| 2. Spicy Nacho Cheese Dip |" << endl;
        cout << "|___________________________|" << endl;
        string sauce[] = {"Garlic Aioli Dip", "Spicy Nacho Cheese Dip"};
        while(true){
            cout << "Select sauce: ";
            getline(cin,choice);
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <= 2){
                        attribute1 = sauce[selection-1];
                        return attribute1;
                    }
                    else{
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                }
                catch (const invalid_argument& e){
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            }
        }
    }
}
Attribute2 getAttribute2(string category){
    Attribute2 obj;
    string choice;
    if(category=="Pizza"){
        cout << "\n___________________________________" << endl;
        cout << "| Available Size:                   |" << endl;
        cout << "| 1. Personal :  6 inches           |" << endl;
        cout << "| 2. Regular  :  9 inches (+ RM 12) |" << endl;
        cout << "| 3. Large    : 12 inches (+ RM 24) |" << endl;
        cout << "|___________________________________|" << endl;
        string size[] = {"Personal", "Regular", "Large"};
        double addPrice[] = {0.00, 12.00, 24.00};
        while(true){
            cout << "Select size: ";
            getline(cin,choice);
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <=3){
                        obj.attribute_name = size[selection-1];
                        obj.addUp = addPrice[selection-1];
                        return obj;
                    }
                    else{
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                }
                catch (const invalid_argument& e){
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            }
        }
    }
    else if(category=="Beverage"){
        cout << "\n_____________________________" << endl;
        cout << "| Available Size:             |" << endl;
        cout << "| 1. Tin    : 325 ml          |" << endl;
        cout << "| 2. Bottle : 750 ml (+ RM 2) |" << endl;
        cout << "|_____________________________|" << endl; 
        string size[] = {"Tin", "Bottle"};
        double addPrice[] = {0.00, 2.00};
        while(true){
            cout << "Select size: ";
            getline(cin,choice);
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <=2){
                        obj.attribute_name = size[selection-1];
                        obj.addUp = addPrice[selection-1];
                        return obj;
                    }
                    else{
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                }
                catch (const invalid_argument& e){
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            }
        }
    }
    else if(category=="Side"){
        cout << "\n_____________________" << endl;
        cout << "| Available Size:     |" << endl;
        cout << "| 1. 1 pax            |" << endl;
        cout << "| 2. 2 pax (+ RM  5)  |" << endl;
        cout << "| 3. 4 pax (+ RM 15)  |" << endl;
        cout << "|_____________________|" << endl;
        string size[] = {"1 pax", "2 pax", "4 pax"};
        double addPrice[] = {0.00, 5.00, 15.00};
        while(true){
            cout << "Select size: ";
            getline(cin,choice);
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <=3){
                        obj.attribute_name = size[selection-1];
                        obj.addUp = addPrice[selection-1];
                        return obj;
                    }
                    else{
                        cout << "Invalid choice. Please try again." << endl;
                        continue;
                    }
                }
                catch (const invalid_argument& e){
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
            }
        }
    }
}
void displayProduct(const Product& product) {
    if (product.status == "Active") {
        cout << "----------------------------------------------------------------------" << endl;
        cout << "| Product ID: " << left << setw(55) << product.product_id << "|" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "| Name      : " << left << setw(55) << product.product_name << "|" << endl;
        cout << "| Category  : " << left << setw(55) << product.category << "|" << endl;
        cout << "| Price     : RM " << left << setw(52) << fixed << setprecision(2) << product.price << "|" << endl;
        if (product.stock <= 0) {
            cout << "| WARNING   : SORRY! THIS PRODUCT IS CURRENTLY OUT OF STOCK!         |" << endl;
        } else {
            cout << "| Stock     : " << left << setw(55) << product.stock << "|" << endl;
            cout << "|                                                                    |" << endl;
            cout << "|";
            printWrappedText(product.description);
        }
        cout << "----------------------------------------------------------------------" << endl;
    }
}
string getCartFilename(const string& member_id) {
    return member_id + "_cart.txt";
}
bool loadCart(CartItem*& cart, int& cartSize, const string& member_id) {
    if (member_id.empty()) {
        cout << "Error: Cannot load cart. No user logged in." << endl;
        return false;
    }
    string cartFile = getCartFilename(member_id);
    ifstream file(cartFile);
    if (!file) {
        ofstream newFile(cartFile);
        if (!newFile) {
            cout << "Error: Cannot create cart file for member " << member_id << endl;
            return false;
        }
        newFile.close();
        cartSize = 0;
        cart = nullptr;
        return true;
    }
    cartSize = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) cartSize++;
    }
    file.close();
    if (cartSize == 0) {
        cart = nullptr;
        return true;
    }
    if (cart) delete[] cart;
    cart = new CartItem[cartSize];
    ifstream reopen(cartFile);
    if (!reopen) {
        cout << "Error: Cart file not found!" << endl;
        return false;
    }
    int index = 0;
    while (getline(reopen, line) && index < cartSize) {
        if (line.empty()) continue;
        string parts[8];
        int fieldsFound = splitAttribute(line, parts, 8);
        if (fieldsFound < 8) {
            cout << "Warning: Skipping invalid cart line: " << line << endl;
            continue;
        }
        for (int i = 0; i < 8; i++) {
            parts[i] = removeQuotes(parts[i]);
        }
        cart[index].product_id = parts[0];
        cart[index].product_name = parts[1];
        try {
            cart[index].price = stod(parts[2]);
            cart[index].addUp = stod(parts[5]);
            cart[index].quantity = stoi(parts[6]);
            cart[index].total = stod(parts[7]);
        } catch (const invalid_argument& e) {
            cout << "Warning: Invalid number format in cart line: " << line << endl;
            cart[index].price = 0;
            cart[index].quantity = 0;
            cart[index].total = 0;
        }
        cart[index].attribute1 = parts[3];
        cart[index].attribute2 = parts[4];
        Product* product = binarySearchProduct(products, 0, productCount - 1, cart[index].product_id, "product_id");
        if (product) {
            cart[index].product = *product;
        } else {
        }
        index++;
    }
    reopen.close();
    cartSize = index;
    return true;
}
bool saveCart(CartItem* cart, int cartSize, const string& member_id) {
    if (member_id.empty()) {
        cout << "Error: Cannot save cart. No user logged in." << endl;
        return false;
    }
    string cartFile = getCartFilename(member_id);
    ofstream file(cartFile);
    if (!file.is_open()) {
        cout << "Error: Could not update cart file!" << endl;
        return false;
    }
    for (int i = 0; i < cartSize; i++) {
        file << cart[i].product_id << ","
             << cart[i].product_name << ","
             << fixed << setprecision(2) << cart[i].price << ","
             << cart[i].attribute1 << ","
             << cart[i].attribute2 << ","
             << fixed << setprecision(2) << cart[i].addUp << ","
             << cart[i].quantity << ","
             << fixed << setprecision(2) << ((cart[i].price + cart[i].addUp) * cart[i].quantity) << endl;
    }
    file.close();
    return true;
}
void displayCart(Member loggedInMember) {
	loadProducts();
    if (loggedInMember.member_id.empty()) {
        cout << "Error: No user logged in." << endl;
        cout << "Press [ENTER] to continue.";
        cin.ignore();
        cin.get();
        return;
    }
    clearScreen();
    CartItem* cart = nullptr;
    int cartSize = 0;
    if (!loadCart(cart, cartSize, loggedInMember.member_id)) {
        cout << "Could not load cart data." << endl;
        cout << "Press [ENTER] to return.";
        cin.ignore();
        return;
    }
    quickSortCartItem(cart, 0, cartSize - 1, "product_id");
    if (cartSize == 0) {
        cout << "==================================================================" << endl;
        cout << "|                            MY CART                             |" << endl;
        cout << "==================================================================" << endl;
        cout << "|                                                                |" << endl;
        cout << "|                        Your cart is empty.                     |" << endl;
        cout << "|                                                                |" << endl;
        cout << "==================================================================" << endl;
        cout << "\n1. Return to product list" << endl;
        cout << "2. Return to main menu" << endl;
        while (true) {
        	cin.ignore();
            string choice;
            cout << "\nEnter your choice: ";
            getline(cin, choice);
            if (choice == "1") {
                clearScreen();
                filterProducts();
                return;
            } else if (choice == "2") {
                clearScreen();
                mainMenu();
                return;
            } else {
                cout << "Invalid choice. Please enter 1 or 2." << endl;
            }
        }
    }
    cout << "==================================================================" << endl;
    cout << "|                            MY CART                             |" << endl;
    cout << "==================================================================" << endl;
    double grand_total = 0.0;
    for (int i = 0; i < cartSize; i++) {
        string pid = cart[i].product_id;
        string name = cart[i].product_name;
        string category = cart[i].product.category;
        double price = cart[i].price;
        int quantity = cart[i].quantity;
        string attribute1 = cart[i].attribute1;
        string attribute2 = cart[i].attribute2;
        double addUp = cart[i].addUp;
        double total = cart[i].total;
        string status = cart[i].product.status;
        cout << " ----------------------------------------------------------------" << endl;
        cout << "| Item " << left << setw(58) << to_string(i+1) + ":" << "|" << endl;
        cout << "| Product ID : " << left << setw(50) << pid << "|" << endl;
        string nameLine = attribute2 + " " + name + " (" + attribute1 + ") ";
        int nameLineLength = nameLine.length();
        int maxAllowedLength = 50;
        if (nameLineLength <= maxAllowedLength) {
            cout << "| Name       : " << left << setw(maxAllowedLength) << nameLine << "|" << endl;
        } else {
            cout << "| Name       : " << left << setw(maxAllowedLength) << nameLine << "|" << endl;
        }
        if (status == "Inactive") {
            total = 0.0;
            cout << "| SORRY! This product is currently unavailable :(                |" << endl;
            cout << " ----------------------------------------------------------------" << endl;
        }
        else if (quantity > cart[i].product.stock) {
            total = 0.0;
            cout << "| SORRY! Insufficient stock according to the ordered quantity :( |" << endl;
            cout << " ----------------------------------------------------------------" << endl;
        }
        else {
            cout << "| Price      : RM " << left << setw(47) << fixed << setprecision(2) << (price + addUp) << "|" << endl;
            cout << "| Quantity   : " << left << setw(50) << quantity << "|" << endl;
            cout << "| Subtotal   : RM " << left << setw(47) << fixed << setprecision(2) << total << "|" << endl;
            cout << " ----------------------------------------------------------------" << endl;
            grand_total += total;
        }
    }
    cout << "==================================================================" << endl;
    cout << "| Total Price: RM " << left << setw(47) << fixed << setprecision(2) << grand_total << "|" << endl;
    cout << "==================================================================\n" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << " ____________________________________" << endl;
    cout << "|                                    |" << endl;
    cout << "|    Options:                        |" << endl;
    cout << "|  1. Delete an item from cart       |" << endl;
    cout << "|  2. Edit quantity of an item       |" << endl;
    cout << "|  3. Proceed to payment             |" << endl;
    cout << "|  4. Back to product list           |" << endl;
    cout << "|  5. Back to member menu            |" << endl;
    cout << "|____________________________________|" << endl;
	while (true) {
	    string choice;
	    cout << "\nEnter your choice: ";
	    getline(cin, choice);
	    if (choice == "1") {
	        deleteCart(cart, cartSize);
	        break;
	    } else if (choice == "2") {
	        editCart(cart, cartSize);
	        break;
	    } else if (choice == "3") {
	        proceedToPayment(cart, cartSize);
	        break;
	    } else if (choice == "4") {
	        clearScreen();
	        filterProducts();
	        return;
	    } else if (choice == "5") {
	        clearScreen();
	        memberMenu(loggedInMember);
	        return;
	    } else {
	        cout << "Invalid choice. Press [ENTER] to retry.";
	        cin.get();
	        clearScreen();
	        displayCart(loggedInMember);
	    }
	}
    displayCart(loggedInMember);
}
bool isSameCartItem(const CartItem& a, const CartItem& b) {
    return (a.product_id == b.product_id) 
           && (a.attribute1 == b.attribute1) 
           && (a.attribute2 == b.attribute2);
}
void addToCart(const string& product_id, int quantity, string attribute1, Attribute2 obj) {
    if (loggedInMember.member_id.empty()) {
        cout << "Error: Cannot add to cart. No user logged in." << endl;
        return;
    }
    if (!products || productCount == 0) {
        if (!loadProducts()) {
            cout << "Error: Could not load products." << endl;
            return;
        }
    }
    Product* selected_product = binarySearchProduct(products, 0, productCount - 1, product_id, "product_id");
    string att1 = attribute1;
    Attribute2 att2 = obj;
    if (!selected_product) {
        cout << "Error: Product with ID " << product_id << " not found." << endl;
        return;
    }
    if (selected_product->status == "Inactive") {
        cout << "Error: This product is currently unavailable.\n" << endl;
        return;
    }
    if (quantity <= 0) {
        cout << "Error: Quantity must be positive." << endl;
        return;
    }
    if (selected_product->stock < quantity) {
        cout << "Error: Not enough stock for " << selected_product->product_name 
             << ". Available: " << selected_product->stock << endl;
        return;
    }
    CartItem* cart = nullptr;
    int cartSize = 0;
    if (!loadCart(cart, cartSize, loggedInMember.member_id)) {
        cout << "Error: Could not load current cart." << endl;
        return;
    }
    CartItem tempItem;
    tempItem.product_id = product_id;
    tempItem.attribute1 = att1;
    tempItem.attribute2 = att2.attribute_name;
    bool itemExists = false;
    CartItem* existingItem = nullptr;
    for (int i = 0; i < cartSize; i++) {
        if (isSameCartItem(cart[i], tempItem)) {
            itemExists = true;
            existingItem = &cart[i];
            break;
        }
    }
    if (itemExists && existingItem) {
        if (selected_product->stock < existingItem->quantity + quantity) {
            cout << "Error: Adding " << quantity << " would exceed stock." << endl;
            delete[] cart;
            return;
        }
        existingItem->quantity += quantity;
        existingItem->total = existingItem->quantity * existingItem->price;
    } else {
        CartItem* newCart = new CartItem[cartSize + 1];
        for (int i = 0; i < cartSize; i++) {
            newCart[i] = cart[i];
        }
        newCart[cartSize] = CartItem(
            *selected_product,
            selected_product->product_id,
            selected_product->product_name,
            selected_product->price,
            quantity,
            att1,
            att2.attribute_name,
            att2.addUp,
            selected_product->price * quantity,
            selected_product->status
        );
        delete[] cart;
        cart = newCart;
        cartSize++;
    }
    selected_product->stock -= quantity;
    if (saveCart(cart, cartSize, loggedInMember.member_id)) {
        cout << "\nSuccessfully added " << quantity << " x " << selected_product->product_name << " to cart!" << endl;
        cin.ignore();
        cin.get();
        clearScreen();
        filterProducts();
    } else {
        cout << "\nError: Could not save changes." << endl;
    }
    delete[] cart;
}
bool isAllDigits(const string& str) {
    int len = str.length();
    if (len == 0) {
        return false; 
    }
    for (int i = 0; i < len; ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
void deleteCart(CartItem*& cart, int& cartSize) {
    while (true) {
        cout << "\nEnter the item number to delete (1-" << cartSize << ") or [0] to cancel: ";
        string choiceStr;
        getline(cin, choiceStr);
        bool isValid = isAllDigits(choiceStr);
        if (!isValid) {
        	cout << "\n________________________________________________________\n";
			cout << "|Invalid input! Please enter a number.                 |\n";
			cout << "|______________________________________________________|\n";
            continue;
        }
        int choice = stoi(choiceStr);
        if (choice == 0) {
            return; 
        }
        if (choice < 1 || choice > cartSize) {
        	cout << "\n________________________________________________________\n";
			cout << "|Invalid item number! Please try again.                |\n";
			cout << "|______________________________________________________|\n";
            continue;
        }
        Product* product = binarySearchProduct(products, 0, productCount - 1, cart[choice-1].product_id, "product_id");
        if (product) {
            product->stock += cart[choice-1].quantity; 
        }
        CartItem* newCart = new CartItem[cartSize - 1];
        int newIndex = 0;
        for (int i = 0; i < cartSize; i++) {
            if (i != choice - 1) {
                newCart[newIndex++] = cart[i];
            }
        }
        delete[] cart;
        cart = newCart;
        cartSize--;
        if (saveCart(cart, cartSize, loggedInMember.member_id)) {
            cout << "\nItem successfully removed from cart!" << endl;
        } else {
            cout << "\nError saving cart changes!" << endl;
        }
        cout << "\nPress [ENTER] to continue.";
        cin.ignore();
        break;
    }
}
void editCart(CartItem*& cart, int& cartSize) {
    while (true) {
        cout << "\nEnter the item number to edit (1-" << cartSize << ") or [0] to cancel: ";  
        string choiceStr;
        getline(cin, choiceStr);
        bool isValid = isAllDigits(choiceStr);
        if (!isValid) {
        	cout << "\n_______________________________________________\n";
            cout << "| Invalid input! Please enter a number.       |\n";
            cout << "|_____________________________________________|\n";
            continue;
        }
        int choice = stoi(choiceStr);
        if (choice == 0) {
            return; 
        }
        if (choice < 1 || choice > cartSize) {
        	cout << "\n_______________________________________________\n";
            cout << "| Invalid item number! Please try again.      |\n";
            cout << "|_____________________________________________|\n";
            continue;
        }
        CartItem& item = cart[choice-1];
        Product* product = binarySearchProduct(products, 0, productCount - 1, item.product_id, "product_id");
        if (!product) {
            cout << "\n_______________________________________________\n";
            cout << "| ERROR: PRODUCT NOT FOUND IN INVENTORY       |\n";
            cout << "|_____________________________________________|\n";
            cin.ignore();
            continue;
        }
        while (true) {
            cout << "\nEditing: " << item.product_name << endl;
            cout << "Current quantity: " << item.quantity << endl;
            cout << "Current attributes: " << item.attribute1 << ", " << item.attribute2 << endl;
            cout << "Available stock: " << product->stock << endl;
            cout << "\n_______________________________________________\n";
            cout << "| What would you like to edit?                |\n";
            cout << "| 1. Quantity                                 |\n";      
            cout << "| 2. Attributes                               |\n";
            cout << "| 3. Both quantity and attributes             |\n";
            cout << "| 0. Cancel                                   |\n";
            cout << "|_____________________________________________|\n";
            string editChoiceStr;
            cout << "Enter your choice: ";
            getline(cin, editChoiceStr);
            if (!isAllDigits(editChoiceStr)) {
                cout << "\n_______________________________________________\n";
		        cout << "| Invalid input! Please enter a number.       |\n";
	            cout << "|_____________________________________________|\n";
                continue;
            }
            int editChoice = stoi(editChoiceStr);
            if (editChoice == 0) {
                break;
            }
            bool editQuantity = (editChoice == 1 || editChoice == 3);
            bool editAttributes = (editChoice == 2 || editChoice == 3);
            int newQty = item.quantity;
            string newAttribute1 = item.attribute1;
            Attribute2 newAttribute2;
            newAttribute2.attribute_name = item.attribute2;
            newAttribute2.addUp = item.addUp;
            if (editQuantity) {
                while (true) {
                    cout << "\nCurrent quantity: " << item.quantity << endl;
                    cout << "Available stock: " << product->stock << endl;
                    cout << "Enter new quantity (0 to remove item): ";
                    string qtyStr;
                    getline(cin, qtyStr);
                    if (!isAllDigits(qtyStr)) {
                        cout << "Invalid quantity! Please enter a number." << endl;
                        cout << "Press [ENTER] to continue.";
                        cin.ignore();
                        continue;
                    }
                    newQty = stoi(qtyStr);
                    if (newQty < 0) {
                        cout << "Quantity cannot be negative!" << endl;
                        cout << "Press [ENTER] to continue.";
                        cin.ignore();
                        continue;
                    }
                    if (newQty == 0) {
                        product->stock += item.quantity; 
                        CartItem* newCart = new CartItem[cartSize - 1];
                        int newIndex = 0;
                        for (int i = 0; i < cartSize; i++) {
                            if (i != choice - 1) {
                                newCart[newIndex++] = cart[i];
                            }
                        }
                        delete[] cart;
                        cart = newCart;
                        cartSize--;
                        cout << "Item removed from cart." << endl;
                        if (saveCart(cart, cartSize, loggedInMember.member_id)) {
                            cout << "Cart updated successfully!" << endl;
                        } else {
                            cout << "Error saving cart changes!" << endl;
                        }
                        cout << "Press [ENTER] to continue.";
                        cin.ignore();
                        return;
                    }
                    if (newQty > product->stock + item.quantity) {
                        cout << "Not enough stock available! Maximum available: " 
                             << product->stock + item.quantity << endl;
                        cout << "Press [ENTER] to continue.";
                        cin.ignore();
                        continue;
                    }
                    break;
                }
            }
            if (editAttributes) {
                cout << "\nEditing attributes for: " << item.product_name << endl;
                cout << "Current attributes: " << item.attribute1 << ", " << item.attribute2 << endl;
                newAttribute1 = getAttribute1(product->category);
                Attribute2 tempAttr2 = getAttribute2(product->category);
                newAttribute2.attribute_name = tempAttr2.attribute_name;
                newAttribute2.addUp = tempAttr2.addUp;
            }
            if (editQuantity) {
			    product->stock += item.quantity;
			    if (newQty > 0) {
			        product->stock -= newQty;
			    }
			    item.quantity = newQty;
			}
            item.quantity = newQty;
            if (editAttributes) {
                item.attribute1 = newAttribute1;
                item.attribute2 = newAttribute2.attribute_name;
                item.addUp = newAttribute2.addUp;
            }
            item.total = (item.price + item.addUp) * newQty;
            
            cout << "Item updated successfully!" << endl;
            break;
        }
        if (saveCart(cart, cartSize, loggedInMember.member_id)) {
            cout << "Cart updated successfully!" << endl;
        } else {
            cout << "Error saving cart changes!" << endl;
        }
        cout << "Press [ENTER] to continue.";
        cin.ignore();
        break;
    }
}
void proceedToPayment(CartItem* cart, int cartSize) {
    if (cartSize == 0) {
        cout << "Your cart is empty. Please add items to your cart before proceeding to payment.\n";
        cout << "Press [ENTER] to continue.";
        cin.ignore();
        return;
    }
    clearScreen();
    double totalPayment = 0.00;
    cout << "------------------------------------------------------------------" << endl;
    cout << "                              RECEIPT                             " << endl;
    for (int i = 0; i < cartSize; ++i) {
        cout << "------------------------------------------------------------------" << endl;
        cout << "Item        : " << cart[i].attribute2 << " " << cart[i].product_name << " (" << cart[i].attribute1 << ")" << endl;
        cout << "Price       : RM " << fixed << setprecision(2) << (cart[i].price + cart[i].addUp) << endl;
        cout << "Quantity    : " << cart[i].quantity << endl;
        cout << "Total       : RM " << fixed << setprecision(2) << cart[i].total << endl;

        totalPayment += cart[i].total;
    }
    cout << "==================================================================" << endl;
    cout << "Payment Amount: RM " << fixed << setprecision(2) << totalPayment << endl;
    cout << "==================================================================" << endl;
    if (totalPayment >= 100 && totalPayment < 120) {
        double addOn = 0.00;
        char proceed;
        addOn = 120 - totalPayment;
        cout << "\nAdd-on RM " << addOn << " to get 5% discount!" << endl;
        cout << "\nEnter [0] to back to product list, enter [1] to proceed the payment: ";
        cin >> proceed;
        while (proceed != '0' && proceed != '1') {
            cout << "Invalid input." << endl;
            cout << "Enter 0 to back to product list, 1 to continue proceed to payment: ";
            cin >> proceed;
        }
        if (proceed == '0') {
            cin.ignore();
            filterProducts();
            return;
        }
    }
    if (totalPayment >= 120) {
        double discount = 0.05, discountAmount;
        discountAmount = totalPayment * discount;
        totalPayment -= discountAmount;
        cout << "\nCongratulations, you get 5% discount!" << endl;
        cout << "_________________________" << endl;
        cout << "|Discount: RM " << discountAmount << "\t|" << endl;
        cout << "|Total   : RM " << totalPayment << "\t|" << endl;
        cout << "|_______________________|" << endl;
    }
    char paymentMethod;
    cout << "\nChoose your payment method" << endl;
    cout << "1. Cash" << endl;
    cout << "2. Credit card" << endl;
    cout << "\nYour choice [0 to cancel payment]: ";
    cin >> paymentMethod;
    while(paymentMethod != '0' && paymentMethod != '1' && paymentMethod != '2') {
        cout << "Invalid choice. Please enter again: ";
        cin >> paymentMethod;	
    }
    if(paymentMethod == '0') {
        cout << "Back to main menu..." << endl;
        cin.ignore();
        cin.ignore();
        clearScreen();
        memberMenu(loggedInMember);
    }
    else if(paymentMethod == '1') {
        cashPayment(cart, cartSize, totalPayment);
    }
    else if(paymentMethod == '2') {
        creditCardPayment(cart, cartSize, totalPayment);
    }
}
void creditCardPayment(CartItem* cart, int cartSize, double totalPayment) {
    string cardNumber, expiryDate, cvv;
    cout << "Credit card number (13-16 digits): ";
    cin >> cardNumber;
    while (!isValidCardNumber(cardNumber)) {
        cout << "\nInvalid number. Please re-enter credit card number (13-16 digits): ";
        cin >> cardNumber;
    }
    cout << "\nExpiry date (MM/YY): ";
    cin >> expiryDate;
    while (!isValidExpiryDate(expiryDate)) {
        cout << "\nInvalid date. Please re-enter expiry date (MM/YY): ";
        cin >> expiryDate;
    }
    cout << "\nCVV: ";
    cin >> cvv;
    while (!isValidCVV(cvv)) {
        cout << "\nInvalid CVV. Please re-enter CVV (3 or 4 digits): ";
        cin >> cvv;
    }
    cout << "\n\nProcessing payment...";
    cout << "\nValidating card details";
    for (int i = 0; i < 5; ++i) {
        cout << ".";
    }
    cout << "\n\nPayment successful! Thank you for your purchase.";
    recordPurchaseHistory(cart, cartSize, totalPayment);
    delete[] cart;
    cartSize = 0;
    clearCartFile(loggedInMember.member_id);
    cout << "\nYour cart has been cleared.\n";
    cout << "\nDo you want to make more purchase[Y/N]?: ";
    char morePurchase;
    cin >> morePurchase;
    if (morePurchase == 'Y' || morePurchase == 'y') {
        cin.ignore();
        clearScreen();
        memberMenu(loggedInMember);
    }
    else if (morePurchase == 'N' || morePurchase == 'n') {
        cout << "\nPress [ENTER] to log out...";
        cin.ignore();
        cin.ignore();
        clearScreen();
        mainMenu();
    }
}
void cashPayment(CartItem* cart, int cartSize, double totalPayment) {
    double cash;
    cout << "\nCash  : RM ";
    cin >> cash;	
    while(cash < totalPayment) {
        cout << "Your cash is not enough!";
        cout << "\nCash  : RM ";
        cin >> cash;	
    }
    if(cash > totalPayment) {
        double change;
        change = cash - totalPayment;
        cout << "Change: RM "<< change;
    }
    cout << "\n\nProcessing payment";
    for (int i = 0; i < 5; ++i) {
        cout << ".";
    }
    cout << "\nPayment successful! Thank you for your purchase.";
    recordPurchaseHistory(cart, cartSize, totalPayment);
    delete[] cart;
    cartSize = 0;
    clearCartFile(loggedInMember.member_id);
    cout << "\nYour cart has been cleared.\n";
    cout << "\nDo you want to make more purchase[Y/N]?: ";
    char morePurchase;
    cin >> morePurchase;
    if (morePurchase == 'Y' || morePurchase == 'y') {
        cin.ignore();
        clearScreen();
        memberMenu(loggedInMember);
    }
    else if (morePurchase == 'N' || morePurchase == 'n') {
        cout << "\nPress [ENTER] to log out...";
        cin.ignore();
        cin.ignore();
        clearScreen();
        mainMenu();
    }
}
bool isValidCardNumber(const string& cardNumber) {
    if (cardNumber.length() < 13 || cardNumber.length() > 16)
        return false;

    for (int i = 0; i < cardNumber.length(); ++i) {
        if (cardNumber[i] < '0' || cardNumber[i] > '9')
            return false;
    }
    return true;
}
bool isValidExpiryDate(const string& expiryDate) {
    if (expiryDate.length() != 5 || expiryDate[2] != '/') {
        return false;
    }
    string mmStr = expiryDate.substr(0, 2);
    string yyStr = expiryDate.substr(3, 2);
    if (!isAllDigits(mmStr) || !isAllDigits(yyStr)) {
        return false;
    }
    
    int month = stoi(mmStr);
    int year = stoi(yyStr);
    
    if (month < 1 || month > 12) {
        return false;
    }
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = ltm->tm_year % 100; 
    int currentMonth = ltm->tm_mon + 1;
    if (year < currentYear || (year == currentYear && month < currentMonth)) {
        return false;
    }
    return true;
}
bool isValidCVV(const string& cvv) {
    if (cvv.length() != 3 && cvv.length() != 4)
        return false;
    for (int i = 0; i < cvv.length(); ++i) {
        if (cvv[i] < '0' || cvv[i] > '9')
            return false;
    }
    return true;
}
void recordPurchaseHistory(CartItem* cart, int cartSize, double total) {
    string orderId = generateOrderId();
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    ofstream file(PURCHASE_HISTORY_FILE, ios::app);
    if (file) {
        file << orderId << "," << loggedInMember.member_id << "," << date << "," << fixed << setprecision(2) << total << "\n";
        for (int i = 0; i < cartSize; i++) {
            file << cart[i].product_id << "," << cart[i].product_name << "," 
                 << cart[i].quantity << "," << (cart[i].price + cart[i].addUp) << "\n";
        }
        file.close();
    }
}
string generateOrderId() {
    ifstream file(ORDER_ID_FILE);
    int lastId = 0;
    if (file) {
        file >> lastId;
        file.close();
    }
    lastId++;
    ofstream outFile(ORDER_ID_FILE);
    if (outFile) {
        outFile << lastId;
        outFile.close();
    }
    return "ORD" + to_string(lastId);
}
void clearCartFile(const string& member_id) {
    string cartFile = getCartFilename(member_id);
    ofstream file(cartFile);
    file.close();
}
void viewMemberList(const string& statusFilter) {
    memberList.loadMembers();
    Node<Member>* current = memberList.getHead();
    clearScreen();
    if (statusFilter == "Active") {
        cout << "===========================================================================\n";
        cout << "|                         ACTIVE MEMBER LIST                              |\n";      
    } else {
        cout << "===========================================================================\n";
        cout << "|                          INACTIVE MEMBER LIST                           |\n";      
    }
    cout << "===========================================================================\n"; 
    bool foundAny = false;
    while (current != nullptr) {
        if (current->data.status == statusFilter) {
            foundAny = true;
            cout << "| Member ID         : " << left << setw(52) << current->data.member_id << "|\n";
            cout << "| Name              : " << left << setw(52) << current->data.full_name << "|\n";
            cout << "| Email             : " << left << setw(52) << current->data.email << "|\n";
            cout << "| Contact           : " << left << setw(52) << current->data.contact << "|\n";
            cout << "---------------------------------------------------------------------------\n";
        }
        current = current->next;
    }
    if (!foundAny) {
        cout << "|                                                                         |\n";
        cout << "|                      No " << left << setw(48) << (statusFilter + " members found.") << "|\n";
        cout << "|                                                                         |\n";
        cout << "---------------------------------------------------------------------------\n";
		cout << "\nPress [ENTER] to return.";
        cin.ignore();
        clearScreen();
        return; 
	}
    while (true) {
        string searchChoice;
        cout << "\nDo you want to search member by ID? (Y/N to return): ";
        getline(cin, searchChoice);
        if (searchChoice == "N" || searchChoice == "n") {
            return;
        } else if (searchChoice == "Y" || searchChoice == "y") {
            string searchId;
            cout << "\nEnter Member ID to search (or 'C' to cancel): ";
            getline(cin, searchId);
            if (searchId == "C" || searchId == "c") {
                continue;
            }
            current = memberList.getHead();
            bool found = false;
            while (current != nullptr) {
                if (current->data.member_id == searchId && current->data.status == statusFilter) {
                    clearScreen();
                    cout << "===========================================================================\n";
                    cout << "|                                MEMBER DETAILS                           |\n";
                    cout << "===========================================================================\n";
                    cout << "| Member ID         : " << left << setw(52) << current->data.member_id << "|\n";
                    cout << "| Name              : " << left << setw(52) << current->data.full_name << "|\n";
                    cout << "| Email             : " << left << setw(52) << current->data.email << "|\n";
                    cout << "| Contact           : " << left << setw(52) << current->data.contact << "|\n";
                    cout << "| Status            : " << left << setw(52) << current->data.status << "|\n";
                    cout << "===========================================================================\n";
                    found = true;
                    break;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Member with ID " << searchId << " not found in " << statusFilter << " members.\n";
            }
            cout << "\nPress [ENTER] to continue.";
            cin.ignore();
            clearScreen();
            break;
        } else {
            cout << "Invalid choice. Please enter Y (Yes), or N (No).\n";
        }
    }
}
void changeMemberStatus() {
    memberList.loadMembers();
    clearScreen();
    cout << "===========================================================================\n";
    cout << "|                                 MEMBER LIST                             |\n";
    cout << "===========================================================================\n";
    cout << "| ID                 | Name                          | Status             |\n";
    cout << "===========================================================================\n";
    Node<Member>* current = memberList.getHead();
    while (current != nullptr) {
        cout << "| " << left << setw(18) << current->data.member_id << " | "
             << left << setw(29) << current->data.full_name << " | "
             << left << setw(18) << current->data.status << " |\n";
        current = current->next;
    }
    cout << "===========================================================================\n";
    string chosenId;
    while (true) {
        cout << "\nEnter Member ID to change status (or 'C' to cancel): ";
        getline(cin, chosenId);
        if (chosenId == "C" || chosenId == "c") {
            return;
        }
        current = memberList.getHead();
        bool found = false;
        while (current != nullptr) {
            if (current->data.member_id == chosenId) {
                found = true;
                break;
            }
            current = current->next;
        }
        if (!found) {
            cout << "\nError: Member ID '" << chosenId << "' not found. Please try again.\n";
            continue;
        }
        break;
    }
    current = memberList.getHead();
    while (current != nullptr) {
        if (current->data.member_id == chosenId) {
        	if (current->data.status == "Active")
        		current->data.status =  "Inactive";
        	else if (current->data.status == "Inactive") 
            	current->data.status =  "Active";
            break;
        }
        current = current->next;
    }
    ofstream file(MEMBERS_FILE);
    if (file) {
        current = memberList.getHead();
        bool firstMember = true;
        while (current != nullptr) {
            if (!firstMember) {
                file << "\n";
            }
            file << current->data.member_id << "\n"
                 << current->data.full_name << "\n"
                 << current->data.email << "\n"
                 << current->data.password << "\n"
                 << current->data.contact << "\n"
                 << current->data.status;
            firstMember = false;
            current = current->next;
        }
        file.close();
    }
    cout << "\nMember " << chosenId << " status changed successfully.\n";
    cout << "\nPress [ENTER] to continue.";
    cin.ignore();
}
void manageMember() {
    while (true) {
        clearScreen();
        cout << "===========================================================================\n";
        cout << "|                            MANAGE MEMBER LIST                           |\n";      
        cout << "===========================================================================\n";
        cout << "| [1] View Active Members                                                 |\n";
        cout << "| [2] View Inactive Members                                               |\n";
        cout << "| [3] Change Member Status                                                |\n";
        cout << "| [4] Return to Admin Menu                                                |\n";
        cout << "===========================================================================\n";
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
        
        if (choice == "1") {
            viewMemberList("Active");
        }
        else if (choice == "2") {
            viewMemberList("Inactive");
        }
        else if (choice == "3") {
            changeMemberStatus();
        }
        else if (choice == "4") {
            adminMenu(loggedInAdmin);
        }
        else {
            cout << "Invalid choice, Press [ENTER] to try again.";
            cin.ignore();
        }
    }
}
void adminMenu(Admin loggedInAdmin) {
    while (true) {
        clearScreen();
        cout << "\n===============================================================\n";
        cout << "                          WELCOME " << loggedInAdmin.full_name << endl;
        cout << "===============================================================\n";
        cout << "1. View Product Inventory\n";
        cout << "2. View Admin List\n";
        cout << "3. View/Edit Member List\n";
        cout << "4. View Order Record\n";
        cout << "5. View Rating Record\n";
        cout << "6. View Sales Report\n";
        cout << "7. View My Admin Profile\n";
        cout << "8. Log Out\n";
        cout << "===============================================================\n";
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
		if(choice == "3") {
            clearScreen();
            manageMember();
            return;
        }
        else if(choice == "8") {
            clearScreen();
            mainMenu();
            return;
        }
        else {
            cout << "Invalid choice! Press [ENTER] to retry.";
            cin.get();
        }
    }
}
void mainMenu() {
    memberList.loadMembers();
    adminList.loadAdmins();
    while(true){
        clearScreen();
        cout << "\n===============================================================\n";
        cout << "               WELCOME TO YESMOLAR PIZZA STORE                \n";
        cout << "===============================================================\n";
        cout << "1. Sign Up\n";
        cout << "2. Member Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Exit\n";
        cout << "===============================================================\n";
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
        if (choice == "1") {
            clearScreen();
            cout << "\n===============================================================\n";
            cout << "                    Signing Up As Member...                    \n";
            cout << "===============================================================\n";
            signup();
        }
        else if (choice == "2") {
            clearScreen();
            cout << "\n===============================================================\n";
            cout << "                    Logging In As Member...                    \n";
            cout << "===============================================================\n";
            login();
        }
        else if (choice == "3") {
            clearScreen();
            cout << "\n===============================================================\n";
            cout << "                    Logging In As Admin...                     \n";
            cout << "===============================================================\n";
            adminLogin();
        }
        else if (choice == "4") {
            cout << "\nThank you for visiting Yesmolar Pizza Store!\n\n";
            exit(0);
        }
        else {
            cout << "\nInvalid choice. Press [ENTER] to try again.";
            cin.get();
            clearScreen();
        }
    }
}
int main() {
    mainMenu();
    return 0;
}