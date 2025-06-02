// Library used
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

// File paths
const string MEMBERS_FILE = "member.txt";
const string MEMBERS_ID_FILE = "member_id.txt";
const string ADMINS_FILE = "admin.txt";
const string ADMINS_ID_FILE = "admin_id.txt";
const string PRODUCT_FILE = "product.txt";

// Structures
// struct Node that can store any data type "T"
template <typename T>
struct Node {
    T data;
    Node* next;
    
    // Constructor to set the data and next
    Node(const T& value) {
        data = value;
        next = nullptr;
    }
};

// Structure to store member data
struct Member {
    //declare variables
    string member_id;
    string full_name;
    string email;
    string password;
    string contact;
    string status;
    
    //Constructor to initialize member data
    Member( string id="", string name="", string mail="", string pass="", 
            string cont="", string stat="Active"){
        member_id = id;
        full_name = name;
        email = mail;
        password = pass;
        contact = cont;
        status = stat;
    }
};

// Structure to store admin data
struct Admin {
    //declare variables
    string admin_id;
    string full_name;
    string email;
    string password;
    string contact;
    string position;
    string status;
    
    //Constructor to initialize admin data
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

// Structure to store product data
struct Product {
    string product_id;
    string product_name;
    string category;
    double price;
    int stock;
    string description;
    string status;

    //Constructor to initialize product data
    Product(string id = "", string name = "", string cat = "", double cost = 0.0,
            int quantity = 0, string att1="", string att2="", string desc = "", string stat = "") {
        product_id = id;
        product_name = name;
        category = cat;
        price = cost;
        stock = quantity;
        description = desc;
        status = stat;
    }
};

// LinkedList base class that can store any data type "T"
template <typename T>
class LinkedList {
    //protected data
    protected:
        Node<T> *head, *temp;
        
    //public functions
    public:
        // Constructor to set the head to null (create an empty list)
        LinkedList() {head=nullptr;}
        
        //check if the list is empty
        bool isEmpty() const {
            if (head == nullptr)
                return true;
            else
                return false;
        }
        
        //append data at the end of list with the received value
        void append(const T& value) {

            //DMA for a new node with the value
            Node<T>* newNode = new Node<T>(value);

            //if list is empty, set head as newnode, else temp is new node
            if (isEmpty()) {
                head = newNode;
            } 
            else {
                temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }//loop to reach the last node
                temp->next = newNode;
            }
        }
        
        //return head node pointer for accessing the list from outside the class.
        Node<T>* getHead() const {
            return head;
        }
        
        //delete all nodes in the list.
        void clear() {
            while (head != nullptr) {
                temp = head;
                head = head->next;
                delete temp;
            }
        }
        
        //virtual Destructor to call clear() and clean up the list.
        virtual ~LinkedList() {
            clear();
        }
};

// Derived class for member linked list
class MemberLinkedList : public LinkedList<Member> {
public:
    //open member.txt in read mode
    void loadMembers() {
        ifstream file(MEMBERS_FILE);

        //if file doesnt exist, create an empty file and return
        if (!file) {
            ofstream createFile(MEMBERS_FILE);
            createFile.close();
            return;
        }

        // Clear existing list
        clear();

        string line;
        while (getline(file, line)) {
            //skip the empty line
            if (line.empty()) continue;
            
            //declare an obj for struct Member
            Member member;

            //assign the data in files to the obj attributes
            member.member_id = line;
            getline(file, member.full_name);
            getline(file, member.email);
            getline(file, member.password);
            getline(file, member.contact);
            getline(file, member.status);
            
            //add the collected Member obj to the linked list;
            append(member);
        }
        //close file after reading and appending
        file.close();
    }
    
    //function to check if the email already exist in member signup()
    bool emailExists(const string& email) const {
        //set the current to the head of linked list
        Node<Member>* current = head;

        //while the current is not null
        while (current != nullptr) {
            //linear search
            //return true when current email = registered email
            if (current->data.email == email) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    //function to find the member by email
    Member* findMemberByEmail(const string& email) {
        //set the current to the head of linked list
        Node<Member>* current = head;

        //while the current is not null
        while (current != nullptr) {
            //linear search
            //return true and pointer to the current Member data
            if (current->data.email == email) {
                return &(current->data);
            }
            current = current->next;
        }
        //return null if not found
        return nullptr;
    }
};

// Derived class for admin linked list
class AdminLinkedList : public LinkedList<Admin> {
public:
    //open admin.txt in read mode
    void loadAdmins() {
        ifstream file(ADMINS_FILE);

        //if file doesnt exist, create an empty file and return
        if (!file) {
            ofstream createFile(ADMINS_FILE);
            createFile.close();
            return;
        }

        // Clear existing list
        clear();

        string line;
        while (getline(file, line)) {
            //skip the empty line
            if (line.empty()) continue;
            
            //declare an Admin obj
            Admin admin;

            //assign the data in files to the obj attributes
            admin.admin_id = line;
            getline(file, admin.full_name);
            getline(file, admin.email);
            getline(file, admin.password);
            getline(file, admin.contact);
            getline(file, admin.position);
            getline(file, admin.status);
            
            //add the collected Admin obj to the linked list;
            append(admin);
        }
        //close file after reading and appending
        file.close();
    }

    //function to check if the email already exist while adding new admin
    bool emailExists(const string& email) const {
        //set the current to the head of linked list
        Node<Admin>* current = head;

        //while the current is not null
        while (current != nullptr) {
            //linear search
            //return true when current email = registered email
            if (current->data.email == email) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    //function to find the admin by email
    Admin* findAdminByEmail(const string& email) {
        //set the current to the head of linked list
        Node<Admin>* current = head;

        //while the current is not null
        while (current != nullptr) {
            //linear search
            //return true and pointer to the current Admin data
            if (current->data.email == email) {
                return &(current->data);
            }
            current = current->next;
        }
        //return null if not found
        return nullptr;
    }
};

// Global variables
MemberLinkedList memberList;
AdminLinkedList adminList;
Member loggedInMember;
Admin loggedInAdmin;
Product* products = nullptr;
int productCount = 0;

// Function Prototype
void mainMenu();
void memberMenu(Member loggedInMember);
void adminMenu(Admin loggedInAdmin);
void filterProducts();
void printWrappedText(const string& text);

// Helper functions
//function to refresh the screen
void clearScreen() {
    system("cls");
}

//function to wrapped the product description
void printWrappedText(const string& text) {
    //each line should only display maximum 60 words
 	int lineLength = 60;
    int count = 0;
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        count++;

        // Wrap the product description by moving to a new line
        if (count >= lineLength && text[i] == ' ') {
            cout << '\n';
            count = 0;
        }
    }
    cout << endl;
}

//function to split and get the attributes from a line in txt files
//line: A line of text from the txt file
//parts: A string array to store the attributes
//maxParts: maximum aattributes can be retrived
int splitAttribute(const string& line, string* parts, int maxParts) {
    //track total of attributes retrieved
    int count = 0;
    //determine whether the current text is inside the quotes
    bool inQuotes = false;
    //temporarily stores the current field
    string current;

    //read through each char until reach a "
    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes;
        } 
        //if it reach a "," seperate the text
        else if (c == ',' && !inQuotes) {
            if (count < maxParts) {
                parts[count++] = current;//save current value
                current.clear();//reset the current value
            }
            else {
                break;
            }
        } 
        else {
            current += c;//if the char is not " OR , add to current
        }
    }
    //save the remaining parts (if have)
    if (count < maxParts) {
        parts[count++] = current;
    }
    return count;
}

//function to remove quotes from a string
string removeQuotes(const string& s) {

    string trimmed="";

    //check if string has at least two char and starts and ends with ""
    if (s.length() >= 2 && s[0] == '"' && s[s.length() - 1] == '"') {
        // Extract substring without first and last character
        for(int i=1;i<s.length()-1;i++){
            trimmed+=s[i];
        }
        return trimmed;
    }
    //if string does not have "" return the originals
    else
        return s;
}

//Quick Sort Algorithm to sort product data
//function for swapping and determining pivot for quicksort
int partitionProduct(Product* arr, int low, int high, const string& key) {
    //select last element in the subarray as pivot
    Product pivot = arr[high];
    //record the smaller element border, start before the low element
    int i = low - 1;

    //looping from the low element to the last element before pivot
    for (int j = low; j < high; j++) {
        //store the comparison result
        bool condition = false;

        //compare with product_id
        if (key == "product_id") {
            condition = arr[j].product_id < pivot.product_id;
        }

        //if the current < pivot, increase i (smaller element boundary)
        if (condition) {
            i++;
            //swap current element with element at boundary index
            Product temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //place the pivot right after the smaller element boundary
    Product temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    //return the partition index(where the pivot ended up)
    return i + 1;
}

/*Main recursive quicksort function
  ==============================================================
    1. It gets the pivot for the array/subarray
    2. Seperates the array into left(<pivot) & right(>pivot)
    3. Sort both sides of the array by repeating 1-2
*/
void quickSortProduct(Product* arr, int low, int high, const string& key) {
    if (low < high) {
        //get the index of the pivot.
        int pivot = partitionProduct(arr, low, high, key);
        //sort the left side of the pivot
        quickSortProduct(arr, low, pivot - 1, key);
        //sort the right side of the pivot
        quickSortProduct(arr, pivot + 1, high, key);
    }
}

/*Binary Search Algorithm
  ==============================================================
    1. It returns a pointer to the founded Product in the array
    2. arr is the Product array
    3. low & high is the range of current subarray
    4. target is the product_id the user's looking for
    5. key is the field used to perform search (product_id)
*/
Product* binarySearchProduct(Product* arr, int first, int last, const string& target, const string& key) {
    //loop while the first index <= last index
    while (first <= last) {
        //get the middle index
        int mid = first + (last - first) / 2;
        string current;

        //get the value of the product_id at mid index
        if (key == "product_id") {
            current = arr[mid].product_id;
        }
        //if the mid value == target, return result(found)
        if (current == target) return &arr[mid];
        //if the mid value < target, loop again with F=M+1
        else if (current < target) first = mid + 1;
        //if the mid value > target, loop again with L=M-1
        else last = mid - 1;
    }
    //return pointer to null if no result found
    return nullptr;
}

// Function to get next member ID
string getNextMemberId() {
    //open member_id.txt in read mode
    ifstream file(MEMBERS_ID_FILE);
    string lastId;

    //if the file is open, read line-by-line to get the latest member_id
    if (file) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) lastId = line;
        }
        file.close();
    //if unable to open file, create one and write U0001(first member_id)
    } else {
        ofstream createFile(MEMBERS_ID_FILE);
        createFile << "U0001\n";
        createFile.close();
        return "U0001";
    }

    //create a new member_id by incrementing latest member_id (exp: U0001+1 = U0002)
    if (!lastId.empty()) {
        //initialize the numeric part of member_id as null
        string numericPart = "";
        //add up the numeric part of the lastest member_id
        numericPart += lastId[1]; //0
        numericPart += lastId[2]; //0
        numericPart += lastId[3]; //0
        numericPart += lastId[4]; //1

        //convert the numeric part of the latest member_id into int
        int num = stoi(numericPart);
        stringstream finalId;
        finalId << "U" << setw(4) << setfill('0') << (num + 1);
        return finalId.str();
    }
    //return initial member_id if the latest member_id is null
    return "U0001";
}

// Function to get next admin ID
string getNextAdminId() {
    //open admin_id.txt in read mode
    ifstream file(ADMINS_ID_FILE);
    string lastId;

    //if the file is open, read line-by-line to get the latest admin_id
    if (file) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) lastId = line;
        }
        file.close();
    //if unable to open file, create one and write A0001(first admin_id)
    } else {
        ofstream createFile(ADMINS_ID_FILE);
        createFile << "A0001\n";
        createFile.close();
        return "A0001";
    }

    //create a new admin_id by incrementing latest admin_id (exp: A0001+1 = A0002)
    if (!lastId.empty()) {
        //initialize the numeric part of admin_id as null
        //add up the numeric part of the lastest admin_id
        string numericPart = "";
        numericPart += lastId[1]; //0
        numericPart += lastId[2]; //0
        numericPart += lastId[3]; //0
        numericPart += lastId[4]; //1

        //convert the numeric part of the latest admin_id into int
        int num = stoi(numericPart);
        stringstream finalId;
        finalId << "A" << setw(4) << setfill('0') << (num + 1);
        return finalId.str();
    }
    //return initial admin_id if the latest admin_id is null
    return "A0001";
}

//function to append new member account/data into member.txt
void saveMember(const Member& member) {
    //open member.txt in read mode
    bool fileIsEmpty = true;
    {
        ifstream file(MEMBERS_FILE);
        if (file) {
            string line;
            //check if file is empty
            if (getline(file, line)) {
                fileIsEmpty = false;
            }
        }
    } //file closes

    //open member.txt in append mode
    ofstream file(MEMBERS_FILE, ios::app);
    if (file) {
        //add newline only if file isn't empty
        if (!fileIsEmpty) {
            file << "\n";
        }
        
        //append new member data into member.txt
        file << member.member_id << "\n"
             << member.full_name << "\n"
             << member.email << "\n"
             << member.password << "\n"
             << member.contact << "\n"
             << member.status << "\n";
    }
    //file closes
}

//function to register a new member account/data
void signup() {
    //call getNextMemberId to auto-create the latest member_id
    string member_id = getNextMemberId();

    //initialize the member account status as Active
    string status = "Active";

    //declare other attributes for member account
    string full_name, email, password, confirm_password, contact;
    
    //full_name validation
    while (true) {
        //display requirements
        cout << "_______________________________________________\n";
        cout << "| NAME REQUIREMENTS                           |\n";
        cout << "|_____________________________________________|\n";
        cout << "|1. Name must have at least 5 characters      |\n";
        cout << "|2. No special character(s) allowed           |\n";
        cout << "|3. No number(s) allowed                      |\n";
        cout << "|_____________________________________________|\n";
        cout << "\nEnter your full name, [R] to return to the main menu: ";
        //get full_name from user
        getline(cin, full_name);
        
        //return to mainMenu() if user enters R
        if (full_name == "R" || full_name == "r") {
            clearScreen();
            mainMenu();
            return;
        }

        bool valid = true;
        int letterCount = 0;
        //for loop to read the full_name letter-by-letter
        for (int i = 0; i < full_name.length(); ++i) {
            char c = full_name[i];
            //check if every single char is an alphabet with isalpha()
            //if yes, increase the lettercount
            if (!isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
            if (isalpha(c)) 
                letterCount++;
        }

        //display error message if full_name contains non-alphabet and length<5
        if (!valid || letterCount < 5) {
            cout << "_______________________________________________\n";
            cout << "| ERROR! INVALID NAME                         |\n";
            cout << "|_____________________________________________|\n";
            continue;
        }
        break;
    }

    //email validation
    while (true) {
        //get email from user
        cout << "\nEnter your email (example: user@example.com): ";
        getline(cin, email);

        //keep track for the position of @ and .
        int atPosition = -1;
        int dotPosition = -1;
        int atCount = 0;

        //read char by char for '@' and '.'
        for (int i = 0; i < email.length(); i++) {
            //add the count for @ if there's one and track the position
            if (email[i] == '@') {
                atCount++;
                atPosition = i;
            //track the . position (if there's one)
            } else if (email[i] == '.' && atPosition != -1 && i > atPosition) {
                dotPosition = i;
            }
        }

        bool valid = true;

        //check for the format
        if (email.length() < 5) 
            valid = false; 
            //too short (e.g w@m.c)
        else if (atCount != 1) 
            valid = false;  
            //must have one & only one @ (e.g.loy@@mail.com)
        else if (atPosition <= 0 || atPosition >= email.length() - 1) 
            valid = false; 
            //@ cannot be first/last (e.g. @gmail.com)
        else if (dotPosition == -1 || dotPosition == atPosition + 1) 
            valid = false; 
            //must have . after @, but not right after (e.g. lll@.com)
        else if (dotPosition >= email.length() - 1) 
            valid = false; 
            //. cannot be the last char (e.g. lll@gmail.)
        else if (email[0] == '.' || email[email.length() - 1] == '.') 
            valid = false; 
            //cannot start/end with '.' (e.g. lll@gmai.com.)
        
        //. cannot stick together
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

        // call function emailExist() in member linked list to check if email already exists
        if (memberList.emailExists(email)) {
            cout << "____________________________________________________\n";
            cout << "|This email is already registered!                 |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }

        break;
    }

    //password validation
    while (true) {
        //display password requirements
        cout << "_______________________________________________\n";
        cout << "| PASSWORD REQUIREMENTS                       |\n";
        cout << "|_____________________________________________|\n";
        cout << "|1. Password must be at least 8 characters    |\n";
        cout << "|2. Password must have at least 1 uppercase   |\n";
        cout << "|3. Password must have at least 1 lowercase   |\n";
        cout << "|4. Password must have at least 1 number      |\n";
        cout << "|_____________________________________________|\n";
        cout << "\nEnter your new password (example: Xuanting123): ";
        //get password from user
        getline(cin, password);

        //check if the password length >= 8
        if (password.length() < 8) {
            cout << "____________________________________________________\n";
            cout << "|Password must be at least 8 characters!           |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }

        //for loop to check if password contains uppercase, lowercase, and number
        bool hasUpper = false, hasLower = false, hasDigit = false;
        for (int i = 0; i < password.length(); ++i) {
            char c = password[i];
            if (isupper(c)) hasUpper = true;
            if (islower(c)) hasLower = true;
            if (isdigit(c)) hasDigit = true;
        }

        //display error message if password don't contain uppercase, lowercase OR number
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
        
        //ask user to confirm the entered password
        cout << "\nConfirm your password: ";
        getline(cin, confirm_password);

        //check if the password and confirm_password match
        if (confirm_password != password) {
            cout << "____________________________________________________\n";
            cout << "|Passwords do not match!                           |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }
        break;
    }

    //contact validation
    while (true) {
        //get contact from user
        cout << "\nEnter your contact number (example: 012-34567890): ";
        getline(cin, contact);

        //check if the phone front format is XXX- & contain the remaining XXXXXXX
        if (contact.length() < 4 || contact[3] != '-') {
            cout << "____________________________________________________\n";
            cout << "|Invalid format! Example: 012-34567890             |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }

        //seperate the contact into 2 parts for validation
        string part1 = "";
        //add up the front part of the contact
        for(int i=0;i<3;i++){
            part1 += contact[i]; //01X
        }

        string part2 = "";
        for (int i = 4; i < contact.length(); ++i) {
            part2 += contact[i];
        }

        //check if phone number starts with 01X-XXXXXXX
        if (!(part1[0] == '0' && part1[1] == '1')) {
            cout << "____________________________________________________\n";
            cout << "|Phone number must start with '01'!                |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }

        //combine part1(01X) with part2(-XXXXXXX)
        //check if contact id pure digits
        string combined = part1 + part2;
        bool onlyDigits = true;
        for (int i = 0; i < combined.length(); ++i) {
            if (!isdigit(combined[i])) {
                onlyDigits = false;
                break;
            }
        }

        //display error message if the phone number is not pure digits
        if (!onlyDigits) {
            cout << "____________________________________________________\n";
            cout << "|Phone number cannot contain symbols (except '-')  |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }

        //display error message if the contact length id not 10 OR 11 (contain -)
        if (combined.length() != 10 && combined.length() != 11) {
            cout << "________________________________________________________\n";
            cout << "|Phone number must be 10 or 11 digits (excluding '-')! |\n";
            cout << "|______________________________________________________|\n";
            continue;
        }

        break;
    }

    //create and append new member into member linked list
    Member newMember(member_id, full_name, email, password, contact, status);
    memberList.append(newMember);
    //append new member data into member.txt as well
    saveMember(newMember);

    //update member_id.txt with the new member_id
    ofstream idFile(MEMBERS_ID_FILE, ios::app);
    if (idFile) {
        idFile << member_id << "\n";
        idFile.close();
    }

    //display message for successful registration and redirect to mainMenu()
    cout << "________________________________________________________\n";
    cout << "|Registration successful! Your Member ID: " << member_id << "        |\n";
    cout << "|______________________________________________________|\n";
    cout << "\nPress [ENTER] to return to Main Menu.";
    cin.ignore();
    clearScreen();
}

//function to login to memberMenu using member account
void login() {
    //declare the required attributes (email & password)
    string email, password;
    bool hasAt = false, hasDot = false;
    
    do {
        //get email from user
        cout << "\nEnter your email, [R] to return to the main menu: ";
        getline(cin, email);
        
        //return to mainMenu if user entered R
        if (email == "R" || email == "r") {
            clearScreen();
            mainMenu();
            return;
        }
        
        //check if email is correct format (contains @ & .)
        for (int i=0;i<email.length();i++) {
            char c = email[i];
            if (c == '@') hasAt = true;
            if (c == '.') hasDot = true;
        }
        
        //display error message if email format is incorrect
        if (!hasAt || !hasDot) {
            cout << "________________________________________________________\n";
            cout << "|Invalid email format! Must include @ and . symbol     |\n";
            cout << "|______________________________________________________|\n";
        }
    } while (!hasAt || !hasDot);
    
    //call function in member linked list to check if the email is registered
    Member* member = memberList.findMemberByEmail(email);
    //if member == null, the linear search reach till the end of linked list with
    //no matching result (email is not registered)
    if (member == nullptr) {
        cout << "________________________________________________________\n";
        cout << "|Email not found.                                      |\n";
        cout << "|______________________________________________________|\n";
        cout << "\nPress [ENTER] to return to Main Menu.";
        cin.ignore();
        clearScreen();
        return;
    }
    
    //if the email exists but the member's status is Inactive, display error message
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

    //get password from user
    cout << "\nEnter your password: ";
    getline(cin, currentPassword);
    
    //user only gets 3 attemps to enter the correct password
    while (attempts < 3) {
        //login successful if the password match
        if (currentPassword == member->password) {
            cout << "________________________________________________________\n";
            cout << "|Logged in Successfully!                               |\n";
            cout << "|______________________________________________________|\n";
            
            //assign the loggedInMember
            loggedInMember = *member;
            cout << "\nPress [ENTER] to continue.";
            cin.ignore();
            
            //call memberMenu and pass the loggedInMember data
            memberMenu(loggedInMember);
            return;
        } else {
            //if the password does not match, increase the attempt
            //ask member to re-enter until max out
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
    //display error message when attempt max-out & return to mainMenu()
    cout << "\n________________________________________________________\n";
    cout << "|Too many failed attempts. Login terminated.           |\n";
    cout << "|______________________________________________________|\n";
    cout << "\nPress [ENTER] to return to Main Menu.";
    cin.ignore();
    clearScreen();
}

//function to login to adminMenu with admin account/data
void adminLogin() {
    //declare the required attributes (email & password)
    string email, password;
    bool hasAt = false, hasDot = false;
    
    do {
        //get email from admin
        cout << "\nEnter your email, [R] to return to the main menu: ";
        getline(cin, email);
    
        //return to Main Menu if admin entered R
        if (email == "R" || email == "r") {
            clearScreen();
            mainMenu();
            return;
        }
        
        //check if the email format is correct (contains @ & .)
        for (int i=0;i<email.length();i++) {
            char c = email[i];
            if (c == '@') hasAt = true;
            if (c == '.') hasDot = true;
        }
        
        //display error message if email format is incorrect
        if (!hasAt || !hasDot) {
            cout << "________________________________________________________\n";
            cout << "|Invalid email format! Must include @ and . symbol     |\n";
            cout << "|______________________________________________________|\n";
        }
    } while (!hasAt || !hasDot);

    //call function in admin linked list to check if the email is registered
    Admin* admin = adminList.findAdminByEmail(email);
    //if admin == null, the linear search reach till the end of linked list with
    //no matching result (email is not registered)
    if (admin == nullptr) {
        cout << "________________________________________________________\n";
        cout << "|Email not found.                                      |\n";
        cout << "|______________________________________________________|\n";
        cout << "\nPress [ENTER] to continue.";
        cin.ignore();
        clearScreen();
        return;
    }
    
    //check if the account is active
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

    //get password from admin
    cout << "\nEnter your password: ";
    getline(cin, currentPassword);
    
    //allow the admin to re-enter password until attempt max-out
    while (attempts < 3) {
        //login successful if password matched
        if (currentPassword == admin->password) {
            cout << "________________________________________________________\n";
            cout << "|Logged in Successfully!                               |\n";
            cout << "|______________________________________________________|\n";
            loggedInAdmin = *admin;
            cout << "\nPress [ENTER] to continue.";
            cin.ignore();
            adminMenu(loggedInAdmin);
            return;
        //ask admin to re-enter password if unmatched
        } else {
            //if the password does not match, increase the attempt
            //ask admin to re-enter until max out
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

    //display error message when attempt max-out & return to mainMenu()
    cout << "\n________________________________________________________\n";
    cout << "|Too many failed attempts. Login terminated.           |\n";
    cout << "|______________________________________________________|\n";
    cout << "\nPress [ENTER] to return to Main Menu.";
    cin.ignore();
    clearScreen();
}

//function to display memberMenu
void memberMenu(Member loggedInMember) {
    while (true) {
        //display the memberMenu
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
            
        //get choice from member
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
            
        //if-else statement to determine the corresponding actions
        if (choice == "6") {
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

//function to display adminMenu
void adminMenu(Admin loggedInAdmin) {
    while (true) {
        //display adminMenu
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
            
        //get choice from admin
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
            
        //if-else statement to determine the corresponding actions
        if(choice == "8") {
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

//Landing Page for the store system
void mainMenu() {
    //load both members & admins linked list to get existing accounts' info
    memberList.loadMembers();
    adminList.loadAdmins();

    //display landing page interface
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

        //get choice from user
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
        
        //if-else statement to determine the corresponding actions
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
            //thank the user and exit the program
            cout << "\nThank you for visiting Yesmolar Pizza Store!\n\n";
            exit(0);
        }
        else {
            //error handling for invalid choice
            cout << "\nInvalid choice. Press [ENTER] to try again.";
            cin.get();
            clearScreen();
        }
    }
}

//main() - load initial data and call landing page functions
int main() {
    mainMenu();
    return 0;
}