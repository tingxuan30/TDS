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

// Function Prototype
void mainMenu();

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

// Helper functions
void clearScreen() {
    system("cls");
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
        
        bool hasAt = false, hasDot = false;
        //for loop to read the email letter-by-letter
        //check if the email contains @ and .
        for (int i = 0; i < email.length(); ++i) {
            char c = email[i];
            if (c == '@') hasAt = true;
            if (c == '.') hasDot = true;
        }

        //display error message if the format is incorrect(no @ && .)
        if (!hasAt || !hasDot) {
            cout << "____________________________________________________\n";
            cout << "|Invalid email format! Must include @ and . symbol |\n";
            cout << "|__________________________________________________|\n";
            continue;
        }

        //call function emailExist() in member linked list to check if email already exist
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
    cout << "Registration successful! Your Member ID: " << member_id << endl;
    cout << "\nPress [ENTER] to return to login menu.";
    cin.ignore();
    clearScreen();
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
            //login();
        }
        else if (choice == "3") {
            clearScreen();
            cout << "\n===============================================================\n";
            cout << "                    Logging In As Admin...                     \n";
            cout << "===============================================================\n";
            //adminLogin();
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