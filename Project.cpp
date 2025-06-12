// Library used
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <ctime>
#include <stdexcept>
using namespace std;

// File paths
const string MEMBERS_FILE = "member.txt";
const string MEMBERS_ID_FILE = "member_id.txt";
const string ADMINS_FILE = "admin.txt";
const string ADMINS_ID_FILE = "admin_id.txt";
const string PRODUCT_ID_FILE = "product_id_counter.txt";
const string PRODUCT_FILE = "product.txt";
const string ORDER_ID_FILE = "order_id_counter.txt";
const string PURCHASE_HISTORY_FILE = "purchase_history.txt";
const string FEEDBACK_FILE = "feedback.txt";

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
    string description;
    string status;

    //Constructor to initialize product data
    Product(string id = "", string name = "", string cat = "", 
            double cost = 0.0, string desc = "", string stat = "") {
        product_id = id;
        product_name = name;
        category = cat;
        price = cost;
        description = desc;
        status = stat;
    }
};

// Structure to store attribute 2 of product data
// Attrubute 2 is mainly the size of products, which will add-up price
struct Attribute2{
    string attribute_name;
    double addUp;

    //Constructor to initialize attribute2 data
    Attribute2(string name = "", double cost = 0.0) {
        attribute_name = name;
        addUp = cost;
    }
};

// Structure to store cart data
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

    //Constructor to initialize cart item data
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

struct RatingFeedback {
    string member_id;
    int rating; 
    string feedback_text;
    string datetime; 
    RatingFeedback(string m_id = "", int r = 0, string fb_text = "", string dt = "") {
        member_id = m_id;
        rating = r;
        feedback_text = fb_text;
        datetime = dt;
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


class Products : public LinkedList<Product> {
public:
	Product pro;
    bool nameExists(const string& name) const {
        Node<Product>* current = head;
        while (current != nullptr) {
            if (current->data.product_name == pro.product_name) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    Product* findProductByCategory(const string& category) {
        Node<Product>* current = head;
        while (current != nullptr) {
            if (current->data.category == category) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
    bool productNameExists(const string& product_name) const {
	    Node<Product>* current = head;
	    while (current != nullptr) {
	        if (current->data.product_name == product_name) {
	            return true;
	        }
	        current = current->next;
	    }
	    return false;
	}
    friend bool loadProducts();
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

    //function to check if the contact already exist while adding new admin
    bool contactExists(const string& contact) const {
        //set the current to the head of linked list
        Node<Admin>* current = head;
        
        //while the current is not null
        while (current != nullptr) {
            //linear search
            //return true when current contact = registered contact
            if (current->data.contact == contact) {
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

class RatingFeedbackLinkedList : public LinkedList<RatingFeedback> {
public:
    void loadFeedback() {
        ifstream file(FEEDBACK_FILE);
        if (!file) {
            ofstream createFile(FEEDBACK_FILE);
            createFile.close();
            return;
        }
        clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            RatingFeedback feedback;
            feedback.member_id = line;
            getline(file, line);
            feedback.rating = stoi(line);
            getline(file, feedback.feedback_text);
            getline(file, feedback.datetime); 
            append(feedback);
        }
        file.close();
    }
    friend void saveFeedbackToFile(const RatingFeedback& feedback);
};
void saveFeedbackToFile(const RatingFeedback& feedback) {
    ofstream file(FEEDBACK_FILE, ios::app); 
    if (file) {
        file << feedback.member_id << "\n";
        file << feedback.rating << "\n";
        file << feedback.feedback_text << "\n";
        file << feedback.datetime << "\n"; 
        file.close();
    } else {
        cout << "Error: Unable to open feedback file for writing." << endl;
    }
}

// Global variables
MemberLinkedList memberList;
AdminLinkedList adminList;
RatingFeedbackLinkedList feedbackList;
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
void displayProduct(const Product& product);
string getAttribute1(string category);
Attribute2 getAttribute2(string category);
void addToCart(const string& product_id, int quantity, string attribute1, Attribute2 obj);
void displayCart(Member loggedInMember);
void deleteCart(CartItem*& cart, int& cartSize);
void editCart(CartItem*& cart, int& cartSize);
void proceedToPayment(CartItem* cart, int cartSize);
bool isValidCardNumber(const string& cardNumber);
bool isValidExpiryDate(const string& expiryDate);
bool isValidCVV(const string& cvv);
string generateOrderId();
void clearCartFile(const string& member_id);
void viewPurchaseHistory();
void submitRatingFeedback(const string& member_id);
string getCurrentDateTime();
void manageRating();
void manageProduct(); 

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

//function for swapping and determining pivot for product
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

//function for swapping and determining pivot for cart
int partitionCartItem(CartItem* arr, int low, int high, const string& key) {
    //select last element in the subarray as pivot
    CartItem pivot = arr[high];
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
            CartItem temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //place the pivot right after the smaller element boundary
    CartItem temp = arr[i + 1];
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
// Quick Sort to sort product inventory by product id
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

// Quick Sort to sort cart item by product id
void quickSortCartItem(CartItem* arr, int low, int high, const string& key) {
    if (low < high) {
        //get the index of the pivot.
        int pi = partitionCartItem(arr, low, high, key);
        //sort the left side of the pivot
        quickSortCartItem(arr, low, pi - 1, key);
        //sort the right side of the pivot
        quickSortCartItem(arr, pi + 1, high, key);
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
// Binary Search to search product by id
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

// Binary Search to search cart item by id
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

int partitionRatingFeedback(RatingFeedback* arr, int low, int high, const string& key, bool reverse){
    RatingFeedback pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++){
        bool condition = false;
        if (key == "rating"){
            condition = reverse ? arr[j].rating > pivot.rating : arr[j].rating < pivot.rating;
        }else if (key == "datetime"){
        	condition = reverse ? arr[j].datetime > pivot.datetime : arr[j].datetime < pivot.datetime;
		}
        if (condition){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSortRatingFeedback(RatingFeedback* arr, int low, int high, const string& key, bool reverse){
    if (low < high) {
        int pivot = partitionRatingFeedback(arr, low, high, key, reverse);
        quickSortRatingFeedback(arr, low, pivot - 1, key, reverse);
        quickSortRatingFeedback(arr, pivot + 1, high, key, reverse);
    }
}
RatingFeedback* binarySearchRatingFeedback(RatingFeedback* arr, int first, int last, int targetRating) {
    while (first <= last) {
        int mid = first + (last - first) / 2;
        if (arr[mid].rating == targetRating) {
            return &arr[mid];
        } else if (arr[mid].rating < targetRating) {
            first = mid + 1;
        } else {
            last = mid - 1;
        }
    }
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
        cout << "4. Rate Our System\n";
        cout << "5. Log Out\n";
        cout << "===============================================================\n";
            
        //get choice from member
        string choice;
        cout << "Enter your choice: ";
        getline(cin, choice);
            
        //if-else statement to determine the corresponding actions
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
        else if (choice == "3") {
            clearScreen();
            viewPurchaseHistory();
            return;
        }
        else if (choice == "4") {
            clearScreen();
            submitRatingFeedback(loggedInMember.member_id);
            return;
        }
        else if (choice == "5") {
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

//function to load products from product.txt
bool loadProducts() {
	//open product.txt in read mode
    ifstream file(PRODUCT_FILE);
    //return false if unable to open file
    if (!file) {
        cout << "Error: Product file not found!" << endl;
        return false;
    }

    //total up the number of products by counting the lines
    productCount = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) productCount++;
    }
    file.close();

    //DMA to delete the existing product data
    if (products) delete[] products;

    //DMA to assign the new product data
    products = new Product[productCount];

    //open product.txt again to read data
    ifstream openfile(PRODUCT_FILE);
    //return false if unable to open file
    if (!openfile) {
        cout << "Error: Product file not found on second open!" << endl;
        return false;
    }

    //read the product.txt line-by-line (not exceeding total of products)
    int index = 0;
    while (getline(openfile, line) && index < productCount) {
        if (line.empty()) continue;

        //split the line and get the attributes (id, name, category...)
        string parts[6];
        int fieldsFound = splitAttribute(line, parts, 6);
        //skip the line if the attributes found exceeded the declared limit (7)
        if (fieldsFound < 6) {
            cout << "Warning: Line skipped because extracted fiels max out" << endl;
            continue;
        }

        //remove the quotes of the string part-by-part (if have)
        for (int i = 0; i < 6; i++) {
            parts[i] = removeQuotes(parts[i]);
        }

        //assign the attributes to product struct
        products[index].product_id = parts[0];
        products[index].product_name = parts[1];
        products[index].category = parts[2];
        //error handling (try & catch) for invalid price & stock format
        try {
            products[index].price = stod(parts[3]);
        } catch (...) {
            cout << "Warning: Invalid price format in line: " << line << endl;
            products[index].price = 0;
        }
        products[index].description = parts[4];
        products[index].status = parts[5];

        //move on to the next line
        index++;
    }
    openfile.close();

    //update productCount if some lines were skipped
    productCount = index;

    //sort products by product_id with quicksort
    quickSortProduct(products, 0, productCount - 1, "product_id");
    return true;
}

//function to filter the products according to category for the user
void filterProducts() {
    //return to Main Menu if unable to load products
    if (!loadProducts()) {
        cout << "Failed to load products." << endl;
        cout << "Press [ENTER] to return to Main Menu.";
        cin.ignore();
        cin.get();
        clearScreen();
        mainMenu();
        return;
    }

    //display the filter menu while able to load products
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

        //get choice from user
        string choiceString;
        cout << "Enter your choice : ";
        getline(cin,choiceString);

        //ask user to retry if entered null
		if (choiceString.empty()) {
		    cout << "Choice cannot be empty. Press [ENTER] to retry.";
		    cin.get();
		    continue;
		}

		//convert the choice to int
        int choice = stoi(choiceString);

        //declare a string to store the category names
        string categories[] = {"Pizza", "Side", "Beverage"};

        //ask user to re-enter when the choice is beyond stated category number
        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Press [ENTER] to retry.";
            cin.get();
            filterProducts();
        }
        //return to member menu when user entered 4
        else if (choice == 4) {
            clearScreen();
            memberMenu(loggedInMember);
            return;
        }

        //get the selected category from the category string array
        string selectedCategory = categories[choice - 1];

        //display products under the selected category
        while (true) {
            clearScreen();
            cout << "Products in Category: " << selectedCategory << endl;
            loadProducts();
            
            //linear search to look for the product according to category
            bool found = false;
            for (int i = 0; i < productCount; i++) {
                if (products[i].category == selectedCategory && products[i].status == "Active") {
                    displayProduct(products[i]);
                    found = true;
                }
            }

            //display error message if no products were found
            if (!found) {
                cout << "\nNo available products found in '" << selectedCategory << "' category." << endl;
            }

            //display the available operations for user
            cout << "\n-----------------------------------------------------------------" << endl;
            cout << " _________________________________" << endl;
            cout << "| Options:                        |" << endl;
            cout << "| Enter Product ID to add to cart |" << endl;
            cout << "| [C] View Cart                   |" << endl;
            cout << "| [B] Back to Category Selection  |" << endl;
            cout << "| [M] Back to Main Menu           |" << endl;
            cout << "|_________________________________|" << endl;

            //get selection from user
            string selection;
            cout << "\nEnter your choice: ";
            cin >> selection;

            //display cart if user entered C
            if (selection == "C" || selection == "c") {
            	cin.ignore();
                displayCart(loggedInMember);
                continue;
            //return to category selection if user entered R    
            } else if (selection == "B" || selection == "b") {
            	cin.ignore();
                break;
            //return to Main Menu is user entered M
            } else if (selection == "M" || selection == "m") {
                clearScreen();
                cin.ignore();
                memberMenu(loggedInMember);
                return;
            }

            //call binary search algorithm to search for product based on product_id entered
            string product_id = selection;
            Product* product = binarySearchProduct(products, 0, productCount - 1, product_id, "product_id");

            //display error message if no matching product found
            if (!product) {
                cout << "Product with ID '" << product_id << "' not found." << endl;
                cout << "Press [ENTER] to continue.";
                cin.ignore();
                cin.get();
                continue;
            //determine if the selected product is under the filtered category
            } else if (product->category != selectedCategory) {
                cout << "Product with ID '" << product_id << "' not found in '" 
                     << selectedCategory << "' category." << endl;
                cout << "Press [ENTER] to continue.";
                cin.ignore();
                cin.get();
                continue;
            }
            //if product found, check if the status is "Inactive"
            if (product->status == "Inactive") {
                cout << "\nThis product is currently unavailable." << endl;
                cout << "Press [ENTER] to continue.";
                cin.ignore();
                cin.get();
                continue;
            }

            //display the selected product name
            cout << "Selecting product: " << product->product_name << endl;

            //call function getattribute1 to get first attribute based on category
            string attribute1 = getAttribute1(selectedCategory);
            //call function getattribute2 to get second attribute & add-up price based on category
            Attribute2 obj = getAttribute2(selectedCategory);

            //get the quantity from the user
            while (true) {
                //display available stock
                cout << "\nEnter quantity : ";
                string quantity;
                cin >> quantity;

                //check if the entered quantity is number
                bool isNumber = true;
                for (int i=0;i<quantity.length();i++) {
                    char c = quantity[i];
                    if (!isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }
                //ask user to enter again if its not a number
                if (!isNumber) {
                    cout << "Invalid input. Please enter a number." << endl;
                    continue;
                }

                //ask user to retry if the quantity is 0
                int qty = stoi(quantity);
                if (qty <= 0) {
                    cout << "Quantity must be positive." << endl;
                } else {
                    //add to cart if the product is found active and quantity is valid
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

//function to get attribute 1 of the selected product
string getAttribute1(string category){
    string attribute1;
    string choice;
    cin.ignore();

    //if the category is "Pizza", get the preferred crust
    if(category=="Pizza"){
        //display available crust
        cout << "\n__________________________" << endl;
        cout << "| Available Crust:       |" << endl;
        cout << "| 1. Cheesy Crust        |" << endl;
        cout << "| 2. Crackin Thin        |" << endl;
        cout << "| 3. Pan                 |" << endl;
        cout << "| 4. Stuffed Crust       |" << endl;
        cout << "|________________________|" << endl;
        //declare a string array to store the available crust
        string crust[] = {"Cheesy Crust", "Crackin Thin", "Pan", "Stuffed Crust"};
        while(true){
            //get choice from user
            cout << "Select crust: ";
            getline(cin,choice);
            
            //check if the entered choice is number
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            //ask user to enter again if its not a number
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <= 4){
                        //retrieve the crust based on user input
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
    //if the category is "Beverage", get the preferred serving temperature
    else if(category=="Beverage"){
        //display available serving temperature
        cout << "\n__________________________" << endl;
        cout << "| Serving Temperature:   |" << endl;
        cout << "| 1. Cold                |" << endl;
        cout << "| 2. Room Temperature    |" << endl;
        cout << "|________________________|" << endl;
        //declare a string array to store the available serving temperature
        string temperature[] = {"Cold", "Room Temperature"};
        while(true){
            //get choice from user
            cout << "Select serving temperature: ";
            getline(cin,choice);
            
            //check if the entered choice is number
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            //ask user to enter again if its not a number
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <= 2){
                        //retrieve the serving temperature based on user input
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
    //if the category is "Side", get the preferred sauce
    else if(category=="Side"){
        //display available sauce
        cout << "\n_____________________________" << endl;
        cout << "| Available Sauce:          |" << endl;
        cout << "| 1. Garlic Aioli Dip       |" << endl;
        cout << "| 2. Spicy Nacho Cheese Dip |" << endl;
        cout << "|___________________________|" << endl;
        //declare a string array to store the available sauce
        string sauce[] = {"Garlic Aioli Dip", "Spicy Nacho Cheese Dip"};
        while(true){
            //get choice from user
            cout << "Select sauce: ";
            getline(cin,choice);
            
            //check if the entered choice is number
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            //ask user to enter again if its not a number
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    int selection = stoi(choice);
                    if(selection >=1 && selection <= 2){
                        //retrieve the sauce based on user input
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

//function to get attribute 2 of the selected product
Attribute2 getAttribute2(string category){
    Attribute2 obj;
    string choice;

    //if the category is "Pizza", get the preferred size
    if(category=="Pizza"){
        //display available size
        cout << "\n___________________________________" << endl;
        cout << "| Available Size:                   |" << endl;
        cout << "| 1. Personal :  6 inches           |" << endl;
        cout << "| 2. Regular  :  9 inches (+ RM 12) |" << endl;
        cout << "| 3. Large    : 12 inches (+ RM 24) |" << endl;
        cout << "|___________________________________|" << endl;
        //declare a string array to store the available size
        string size[] = {"Personal", "Regular", "Large"};
        //declare a double array to store the add-up price
        double addPrice[] = {0.00, 12.00, 24.00};
        while(true){
            //get choice from user
            cout << "Select size: ";
            getline(cin,choice);
            
            //check if the entered choice is number
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            //ask user to enter again if its not a number
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    //retrieve the size based on user input
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
    //if the category is "Beverage", get the preferred size
    else if(category=="Beverage"){
        //display available size
        cout << "\n_____________________________" << endl;
        cout << "| Available Size:             |" << endl;
        cout << "| 1. Tin    : 325 ml          |" << endl;
        cout << "| 2. Bottle : 750 ml (+ RM 2) |" << endl;
        cout << "|_____________________________|" << endl;
        //declare a string array to store the available size 
        string size[] = {"Tin", "Bottle"};
        //declare a double array to store the add-up price
        double addPrice[] = {0.00, 2.00};
        while(true){
            //get choice from user
            cout << "Select size: ";
            getline(cin,choice);
            
            //check if the entered choice is number
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            //ask user to enter again if its not a number
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    //retrieve the size based on user input
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
    //if the category is "Side", get the preferred size
    else if(category=="Side"){
        //display available size
        cout << "\n_____________________" << endl;
        cout << "| Available Size:     |" << endl;
        cout << "| 1. 1 pax            |" << endl;
        cout << "| 2. 2 pax (+ RM  5)  |" << endl;
        cout << "| 3. 4 pax (+ RM 15)  |" << endl;
        cout << "|_____________________|" << endl;
        //declare a string array to store the available size 
        string size[] = {"1 pax", "2 pax", "4 pax"};
        //declare a double array to store the add-up price
        double addPrice[] = {0.00, 5.00, 15.00};
        while(true){
            //get choice from user
            cout << "Select size: ";
            getline(cin,choice);
            
            //check if the entered choice is number
            bool isNumber = true;
            for (int i=0;i<choice.length();i++) {
                char c = choice[i];
                if (!isdigit(c)) {
                    isNumber = false;
                    break;
                }
            }
            //ask user to enter again if its not a number
            if (!isNumber) {
                cout << "Invalid choice. Please try again." << endl;
                continue;
            }
            else{
                try{
                    //retrieve the size based on user input
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

//function to display a product for member module
void displayProduct(const Product& product) {
    if (product.status == "Active") {
        cout << "----------------------------------------------------------------------" << endl;
        cout << "| Product ID: " << left << setw(55) << product.product_id << "|" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "| Name      : " << left << setw(55) << product.product_name << "|" << endl;
        cout << "| Category  : " << left << setw(55) << product.category << "|" << endl;
        cout << "| Price     : RM " << left << setw(52) << fixed << setprecision(2) << product.price << "|" << endl;
        cout << "|                                                                    |" << endl;
        cout << "|";
        printWrappedText(product.description);
        cout << "----------------------------------------------------------------------" << endl;
    }
}

//function to get cart filename of a loggedInMember
string getCartFilename(const string& member_id) {
    return member_id + "_cart.txt";
}

//function to load cart data from member_id_cart.txt
bool loadCart(CartItem*& cart, int& cartSize, const string& member_id) {
    //check if member is logged-in
    if (member_id.empty()) {
        cout << "Error: Cannot load cart. No user logged in." << endl;
        return false;
    }

    //get the member_id_cart.txt of the loggedInMember
    string cartFile = getCartFilename(member_id);
    //open the file on read mode
    ifstream file(cartFile);

    //create a new empty cart file if not found
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

    //count the cart item data line-by-line
    cartSize = 0;
    string line;
    //increase the count if the line is not empty
    while (getline(file, line)) {
        if (!line.empty()) cartSize++;
    }
    file.close();

    //if the cartSize is 0, means that the cart file is empty
    if (cartSize == 0) {
        cart = nullptr;
        return true;
    }

    //DMA to delete the current existing cart memory (refresh)
    if (cart) delete[] cart;
    //DMA to create a allocate new cart memory (based on the total of cart item)
    cart = new CartItem[cartSize];

    //reopen the cart.txt in read mode
    ifstream reopen(cartFile);
    if (!reopen) {
        cout << "Error: Cart file not found!" << endl;
        return false;
    }

    //read the cart data line by line starting from first line
    int index = 0;
    while (getline(reopen, line) && index < cartSize) {
        //skip of there's an empty line
        if (line.empty()) continue;

        //get the attributes from each line of cart data
        string parts[8];
        int fieldsFound = splitAttribute(line, parts, 8);
        
        //skip the line if the detected attributes is <8
        if (fieldsFound < 8) {
            cout << "Warning: Skipping invalid cart line: " << line << endl;
            continue;
        }

        //remove quotes of every attributes
        for (int i = 0; i < 8; i++) {
            parts[i] = removeQuotes(parts[i]);
        }

        // Assign cart item fields
        // parts[0] = user id (member id), parts[1] = product_id, etc.
        cart[index].product_id = parts[0];
        cart[index].product_name = parts[1];
        try {
            //convert price, add-up, quantity, and total into double and int
            cart[index].price = stod(parts[2]);
            cart[index].addUp = stod(parts[5]);
            cart[index].quantity = stoi(parts[6]);
            cart[index].total = stod(parts[7]);
        } catch (...) {
            //error handling if fail to convert them (initialize them to 0)
            cout << "Warning: Invalid number format in cart line: " << line << endl;
            cart[index].price = 0;
            cart[index].quantity = 0;
            cart[index].total = 0;
        }
        cart[index].attribute1 = parts[3];
        cart[index].attribute2 = parts[4];

        //find the product info from products array
        Product* product = binarySearchProduct(products, 0, productCount - 1, cart[index].product_id, "product_id");
        if (product) {
            cart[index].product = *product;
        }

        index++;
    }
    reopen.close();

    //dynamically adjust cartSize if some lines skipped
    cartSize = index;
    return true;
}

//function to save cart to file
bool saveCart(CartItem* cart, int cartSize, const string& member_id) {
    //error handling if no member is logged-in
    if (member_id.empty()) {
        cout << "Error: Cannot save cart. No user logged in." << endl;
        return false;
    }

    //get the member's cart file and open it in write mode
    string cartFile = getCartFilename(member_id);
    ofstream file(cartFile);

    //error handling if cannot open cart file
    if (!file) {
        cout << "Error: Could not update cart file!" << endl;
        return false;
    }

    //write the cart data into file
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
    //close cart file
    file.close();
    return true;
}

//function to display cart
void displayCart(Member loggedInMember) {
	//load the products first
    loadProducts();

    //error handling if no member is logged-in
    if (loggedInMember.member_id.empty()) {
        cout << "Error: No user logged in." << endl;
        cout << "Press [ENTER] to continue.";
        cin.ignore();
        cin.get();
        return;
    }
    clearScreen();

    //error handling if cannot load cart data
    CartItem* cart = nullptr;
    int cartSize = 0;
    if (!loadCart(cart, cartSize, loggedInMember.member_id)) {
        cout << "Could not load cart data." << endl;
        cout << "Press [ENTER] to return.";
        cin.ignore();
        return;
    }

    //sort the cart item by product_id
    quickSortCartItem(cart, 0, cartSize - 1, "product_id");

    //display if there's nothing in the cart
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

    //if there's item in the cart, display them
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

        //display in format attribute2 + product_name + attribute1
        string nameLine = attribute2 + " " + name + " (" + attribute1 + ") ";
        int nameLineLength = nameLine.length();
        int maxAllowedLength = 50; // Adjust based on your total line width (58 - "| Name       : ")

        //add spaces if the name is shorter than allowed
        if (nameLineLength <= maxAllowedLength) {
            cout << "| Name       : " << left << setw(maxAllowedLength) << nameLine << "|" << endl;
        } else {
            // If the name is too long, truncate by reducing setw
            cout << "| Name       : " << left << setw(maxAllowedLength) << nameLine << "|" << endl;
        }

        //check if product is inactive
        if (status == "Inactive") {
            //the cost of inactive product will not be included in grand total
            total = 0.0;
            cout << "| SORRY! This product is currently unavailable :(                |" << endl;
            cout << " ----------------------------------------------------------------" << endl;
        }
        //proceed to display if the product is active
        else {
            cout << "| Price      : RM " << left << setw(47) << fixed << setprecision(2) << (price + addUp) << "|" << endl;
            cout << "| Quantity   : " << left << setw(50) << quantity << "|" << endl;
            cout << "| Subtotal   : RM " << left << setw(47) << fixed << setprecision(2) << total << "|" << endl;
            cout << " ----------------------------------------------------------------" << endl;
            grand_total += total;
        }
    }
    //display the grabd total
    cout << "==================================================================" << endl;
    cout << "| Total Price: RM " << left << setw(47) << fixed << setprecision(2) << grand_total << "|" << endl;
    cout << "==================================================================\n" << endl;
    cout << "------------------------------------------------------------------" << endl;
    //display available options
    cout << " ____________________________________" << endl;
    cout << "|                                    |" << endl;
    cout << "|    Options:                        |" << endl;
    cout << "|  1. Delete an item from cart       |" << endl;
    cout << "|  2. Edit quantity of an item       |" << endl;
    cout << "|  3. Proceed to payment             |" << endl;
    cout << "|  4. Back to product list           |" << endl;
    cout << "|  5. Back to member menu            |" << endl;
    cout << "|____________________________________|" << endl;
	
    //get choice from user
    while (true) {
	    string choice;
	    cout << "\nEnter your choice: ";
	    getline(cin, choice);
        
        //if-else statement to handle the user's choice
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

// Helper function to check if two cart items are "the same" (same product + same attributes)
bool isSameCartItem(const CartItem& a, const CartItem& b) {
    return (a.product_id == b.product_id) 
           && (a.attribute1 == b.attribute1) 
           && (a.attribute2 == b.attribute2);
}

//function to add product to cart
void addToCart(const string& product_id, int quantity, string attribute1, Attribute2 obj) {
    //error handling if no member is logged-in
    if (loggedInMember.member_id.empty()) {
        cout << "Error: Cannot add to cart. No user logged in." << endl;
        return;
    }
    //error handling if no product is loaded
    if (!products || productCount == 0) {
        if (!loadProducts()) {
            cout << "Error: Could not load products." << endl;
            return;
        }
    }

    //search the selected product with binary search by product id
    Product* selected_product = binarySearchProduct(products, 0, productCount - 1, product_id, "product_id");
    string att1 = attribute1;
    Attribute2 att2 = obj;

    //if the product is not found
    if (!selected_product) {
        cout << "Error: Product with ID " << product_id << " not found." << endl;
        return;
    }
    //if the product is inactive but exists
    if (selected_product->status == "Inactive") {
        cout << "Error: This product is currently unavailable.\n" << endl;
        return;
    }
    //if the entered quantity <=0
    if (quantity <= 0) {
        cout << "Error: Quantity must be positive." << endl;
        return;
    }

    //error handling if unable to load the member's cart file
    CartItem* cart = nullptr;
    int cartSize = 0;
    if (!loadCart(cart, cartSize, loggedInMember.member_id)) {
        cout << "Error: Could not load current cart." << endl;
        return;
    }

    //create a temporary cart item object for comparison
    CartItem tempItem;
    tempItem.product_id = product_id;
    tempItem.attribute1 = att1;
    tempItem.attribute2 = att2.attribute_name;

    //check if an item with the same product_id and attributes already exists
    bool itemExists = false;
    CartItem* existingItem = nullptr;
    //check with linear search
    for (int i = 0; i < cartSize; i++) {
        if (isSameCartItem(cart[i], tempItem)) {
            itemExists = true;
            existingItem = &cart[i];
            break;
        }
    }

    if (itemExists && existingItem) {
        //if the same item + attributes exists, incraese existing quantity
        existingItem->quantity += quantity;
        existingItem->total = existingItem->quantity * existingItem->price;
    } else {
        //if it's a new item, add to cart
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

    //save the product to cart
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
        if (product->status == "Inactive") {
            cout << "\n_______________________________________________\n";
            cout << "| ERROR: CANNOT EDIT INACTIVE PRODUCT         |\n";
            cout << "|_____________________________________________|\n";
            cout << "Press [ENTER] to continue.";
            cin.ignore();
            continue;
        }
        while (true) {
            cout << "\nEditing: " << item.product_name << endl;
            cout << "Current quantity: " << item.quantity << endl;
            cout << "Current attributes: " << item.attribute1 << ", " << item.attribute2 << endl;
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
                    break;
                }
            }
            item.quantity = newQty;
            if (editAttributes) {
                cout << "\nEditing attributes for: " << item.product_name << endl;
                cout << "Current attributes: " << item.attribute1 << ", " << item.attribute2 << endl;
                newAttribute1 = getAttribute1(product->category);
                Attribute2 tempAttr2 = getAttribute2(product->category);
                newAttribute2.attribute_name = tempAttr2.attribute_name;
                newAttribute2.addUp = tempAttr2.addUp;
            }
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
class Order {
    protected:
        string orderId;
        string memberId;
        string date;
        double totalAmount;
        CartItem* items;
        int itemCount;
    public:
        Order(const string& id, const string& memId, const string& dt, double total, CartItem* cart, int cartSize)
        : orderId(id), memberId(memId), date(dt), totalAmount(total), itemCount(cartSize) {
            items = new CartItem[cartSize];
            for (int i = 0; i < cartSize; i++) {
                items[i] = cart[i];
            }
        }
        virtual ~Order() {
            delete[] items;
        }
        virtual void displayReceipt() const {
            cout << "------------------------------------------------------------------" << endl;
            cout << "                              RECEIPT                             " << endl;
            for (int i = 0; i < itemCount; ++i) {
                cout << "------------------------------------------------------------------" << endl;
                cout << "Item        : " << items[i].attribute2 << " " << items[i].product_name << " (" << items[i].attribute1 << ")" << endl;
                cout << "Price       : RM " << fixed << setprecision(2) << (items[i].price + items[i].addUp) << endl;
                cout << "Quantity    : " << items[i].quantity << endl;
                cout << "Total       : RM " << fixed << setprecision(2) << items[i].total << endl;
            }
            cout << "==================================================================" << endl;
            cout << "Payment Amount: RM " << fixed << setprecision(2) << totalAmount << endl;
            cout << "==================================================================" << endl;
        }
        virtual void processPayment() = 0; 
        friend void recordPurchase(Order* order, const string& paymentMethod); 
};
void recordPurchase(Order* order, const string& paymentMethod) {
    ofstream file(PURCHASE_HISTORY_FILE, ios::app);
    if (file) {
        string datetime = getCurrentDateTime(); 
        file << order->orderId << "," << order->memberId << "," << datetime << "," 
             << fixed << setprecision(2) << order->totalAmount << "," << paymentMethod << "\n";
        for (int i = 0; i < order->itemCount; i++) {
            file << order->items[i].product_id << "," << order->items[i].product_name << "," 
                << order->items[i].quantity << "," << (order->items[i].price + order->items[i].addUp) << ","
                << order->items[i].attribute1 << "," << order->items[i].attribute2 << "\n"; 
        }
        file << "\n"; 
        file.close();
    }
}
class CashOrder : public Order {
    private:
        double cashReceived;
        double change;
    public:
        CashOrder(const string& id, const string& memId, const string& dt, double total, CartItem* cart, int cartSize)
        : Order(id, memId, dt, total, cart, cartSize), cashReceived(0), change(0) {}
        void displayReceipt() const override {
            Order::displayReceipt();
            cout << "Cash Received: RM " << fixed << setprecision(2) << cashReceived << endl;
            if (change > 0) {
                cout << "Change       : RM " << fixed << setprecision(2) << change << endl;
            }
        }
        void processPayment() override {
            cout << "\nCash  : RM ";
            cin >> cashReceived;	
            while(cashReceived < totalAmount) {
                cout << "Your cash is not enough!";
                cout << "\nCash  : RM ";
                cin >> cashReceived;	
            }
            if(cashReceived > totalAmount) {
                change = cashReceived - totalAmount;
                cout << "Change: RM "<< change;
            }
            cout << "\n\nProcessing payment";
            for (int i = 0; i < 5; ++i) {
                cout << ".";
            }
            cout << "\nPayment successful! Thank you for your purchase.";
        }
};
class DebitCreditCardOrder : public Order {
private:
    string cardNumber;
    string expiryDate;
    string cvv;
public:
    DebitCreditCardOrder(const string& id, const string& memId, const string& dt, double total, CartItem* cart, int cartSize)
    : Order(id, memId, dt, total, cart, cartSize) {}

    void processPayment() override {
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
    }
};
void proceedToPayment(CartItem* cart, int cartSize) {
    if (cartSize == 0) {
        cout << "Your cart is empty. Please add items to your cart before proceeding to payment.\n";
        cout << "Press [ENTER] to continue.";
        cin.ignore();
        return;
    }
    bool canProceed = true;
    double totalPayment = 0.00;
    clearScreen();
    cout << "==================================================================" << endl;
    cout << "|                       CHECKING CART ITEMS                      |" << endl;
    cout << "==================================================================" << endl;
    for (int i = 0; i < cartSize; ++i) {
        Product* product = binarySearchProduct(products, 0, productCount - 1, cart[i].product_id, "product_id");
        if (!product || product->status == "Inactive") {
            cout << "------------------------------------------------------------------" << endl;
            cout << "| WARNING: Product '" << cart[i].product_name << "' is no longer available!" << endl;
            cout << "------------------------------------------------------------------" << endl;
            canProceed = false;
        } else {
            totalPayment += cart[i].total;
        }
    }
    if (!canProceed) {
        cout << "==================================================================" << endl;
        cout << "| CANNOT PROCEED TO PAYMENT DUE TO ISSUES WITH ABOVE ITEMS!      |" << endl;
        cout << "| Please edit or remove these items from your cart.              |" << endl;
        cout << "==================================================================" << endl;
        cout << "\nPress [ENTER] to return to cart.";
        cin.ignore();
        cin.get();
        clearScreen();
        displayCart(loggedInMember);
        return;
    }
    string orderId = generateOrderId();
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string datetime = to_string(ltm->tm_mday) + "/" + 
                     to_string(1 + ltm->tm_mon) + "/" + 
                     to_string(1900 + ltm->tm_year) + " " +
                     to_string(ltm->tm_hour) + ":" +
                     to_string(ltm->tm_min) + ":" +
                     to_string(ltm->tm_sec);
    Order* order = nullptr;
    string paymentMethod;
    char choicePayment;
    cout << "\nChoose your payment method" << endl;
    cout << "1. Cash" << endl;
    cout << "2. Credit card" << endl;
    cout << "3. Debit card" << endl;
    cout << "\nYour choice [0 to cancel payment]: ";
    cin >> choicePayment;
    while(choicePayment != '0' && choicePayment != '1' && choicePayment != '2' && choicePayment != '3') {
        cout << "Invalid choice. Please enter again: ";
        cin >> choicePayment;	
    }
    if(choicePayment == '1') {
        order = new CashOrder(orderId, loggedInMember.member_id, datetime, totalPayment, cart, cartSize);
        paymentMethod = "Cash";
    }
    else if(choicePayment == '2') {
        order = new DebitCreditCardOrder(orderId, loggedInMember.member_id, datetime, totalPayment, cart, cartSize);
        paymentMethod = "Credit Card";
    }
    else if(choicePayment == '3') {
        order = new DebitCreditCardOrder(orderId, loggedInMember.member_id, datetime, totalPayment, cart, cartSize);
        paymentMethod = "Debit Card";
    }
    order->displayReceipt();
    order->processPayment();
    recordPurchase(order, paymentMethod); 
    delete order;
    delete[] cart;
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
void viewPurchaseHistory() {
    if (loggedInMember.member_id.empty()) {
        cout << "Error: No user logged in." << endl;
        cout << "Press [ENTER] to continue.";
        cin.ignore();
        return;
    }
    ifstream file(PURCHASE_HISTORY_FILE);
    if (!file) {
        cout << "No purchase history found." << endl;
        cout << "Press [ENTER] to continue.";
        cin.ignore();
        return;
    }
    clearScreen();
    cout << "==================================================================" << endl;
    cout << "|                      PURCHASE HISTORY                          |" << endl;
    cout << "==================================================================" << endl;
    string line;
    bool foundPurchases = false;
    int orderCount = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        int commaCount = 0;
        for (char ch : line) {
            if (ch == ',') {
                commaCount++;
            }
        }
        if (commaCount == 4) {
            stringstream ss(line);
            string orderId, memberId, date, paymentMethod;
            double total;
            getline(ss, orderId, ',');
            getline(ss, memberId, ',');
            getline(ss, date, ',');
            ss >> total;
            ss.ignore();
            getline(ss, paymentMethod);
            if (memberId == loggedInMember.member_id) {
                foundPurchases = true;
                orderCount++;
                cout << "------------------------------------------------------------------" << endl;
                cout << "| Order ID: " << left << setw(53) << orderId << "|" << endl;
                cout << "| Date    : " << left << setw(53) << date << "|" << endl;
                cout << "| Payment : " << left << setw(53) << paymentMethod << "|" << endl;
				cout << "------------------------------------------------------------------" << endl;
                while (getline(file, line) && !line.empty()) {
                    stringstream itemSS(line);
                    string productId, productName, attribute1, attribute2;
                    int quantity;
                    double price;
                    getline(itemSS, productId, ',');
                    getline(itemSS, productName, ',');
                    itemSS >> quantity;
                    itemSS.ignore(); 
                    itemSS >> price;
                    itemSS.ignore(); 
                    getline(itemSS, attribute1, ',');
                    getline(itemSS, attribute2);
                    cout << " Product ID   : " << productId << endl;
                    cout << " Product Name : " << productName << endl;
                    cout << " Attribute 1  : " << attribute1 << endl;
                    cout << " Attribute 2  : " << attribute2 << endl;
                    cout << " Quantity     : " << quantity << endl;
                    cout << " Price        : RM " << fixed << setprecision(2) << price << endl;
                    cout << "------------------------------------------------------------------" << endl;
                }
                cout << "| Total: RM " << left << setw(53) << fixed << setprecision(2) << total << "|" << endl;
                cout << "==================================================================" << endl << endl;
            } else {
                while (getline(file, line) && !line.empty()) {
                    continue;
                }
            }
        }
    }
    file.close();
    if (!foundPurchases) {
        cout << "|                  No purchase history found.                    |" << endl;
        cout << "==================================================================" << endl;
    }
    cout << "Press [ENTER] to return to menu.";
    cin.ignore();
	clearScreen();
    memberMenu(loggedInMember);
}
string getCurrentDateTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    return string(buffer);
}
void submitRatingFeedback(const string& member_id) {
    clearScreen();
    cout << "\n===============================================================\n";
    cout << "                         RATE OUR SYSTEM                       \n";
    cout << "===============================================================\n";
    int rating;
    string feedback_text;
    while (true) {
        cout << "Enter your rating (1-5, 5 being excellent): ";
        string ratingInput;
        getline(cin, ratingInput);
        try {
            rating = stoi(ratingInput);
            if (rating >= 1 && rating <= 5) {
                break;
            } else {
                cout << "Invalid rating. Please enter a number between 1 and 5.\n";
            }
        } catch (const invalid_argument& e) {
            cout << "Invalid input. Please enter a number.\n";
        } catch (const out_of_range& e) {
            cout << "Input out of range. Please enter a number between 1 and 5.\n";
        }
    }
    cout << "Enter your feedback: ";
    getline(cin, feedback_text);
    string currentDateTime = getCurrentDateTime();
    RatingFeedback newFeedback(member_id, rating, feedback_text, currentDateTime);
    saveFeedbackToFile(newFeedback); 
    feedbackList.append(newFeedback);

    cout << "\nThank you for your feedback!\n";
    cout << "\nPress [ENTER] to return to Member Menu.";
    cin.get();
    memberMenu(loggedInMember);
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
void saveProduct(const Product& product) {
    bool fileIsEmpty = true;
    {
        ifstream inFile(PRODUCT_FILE);
        if (inFile) {
            string line;
            if (getline(inFile, line)) {
                fileIsEmpty = false;
            }
            inFile.close();
        }
    }
    ofstream outFile(PRODUCT_FILE, ios::app);
    if (outFile) {
        if (!fileIsEmpty) {
            outFile << "\n";
        }
        outFile << product.product_id << ","
                << "\"" << product.product_name << "\","
                << "\"" << product.category << "\","
                << fixed << setprecision(2) << product.price << ","
                << "\"" << product.description << "\","
                << "\"" << product.status << "\"";
        outFile.close();
    }
}
string getNextProductId() {
    int lastId = 0;
    ifstream file(PRODUCT_ID_FILE);
    if (file) {
        file >> lastId;
        file.close();
    }
    lastId++;
    ofstream outFile(PRODUCT_ID_FILE);
    if (outFile) {
        outFile << lastId; 
        outFile.close();
    }
    return to_string(lastId);
}
void addProduct(){
	Products products;
	string product_id = getNextProductId();
    string status = "Active";
    string product_name, category, price, stock, description;
    string categories[] = {"Pizza", "Side", "Beverage"};
    int choice;
    clearScreen();
    while (true) {
        cout << "\nEnter product name (or 'C' to cancel): ";
        getline(cin, product_name);
        if (product_name == "C" || product_name == "c") {
            cout << "\nOperation cancelled.\n";
            cout << "Press [ENTER] to continue.";
            cin.ignore();
            manageProduct();
        }
        bool valid = true;
        int letterCount = 0;
        for (int i = 0; i < product_name.length(); ++i) {
            char c = product_name[i];
            if (!isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
            if (isalpha(c)) 
                letterCount++;
        }
        if (product_name.empty()) {
            cout << "Name cannot be empty.\n";
            continue;
        }
        if (!valid || letterCount < 3 || letterCount > 100) {
            cout << "Invalid name! Please enter a valid name.\n";
            continue;
        }
        if (!products.productNameExists(product_name)){
        	cout << "This product name already exist, please use the different name.\n";
        	continue;
		}
        break;
    }
    while(true){
    	cout << "\nSelect category\n";
    	for (int i = 0; i < 3; ++i) {
            cout << i + 1 << ". " << categories[i] << "\n";
        }
        cout << "Enter choice (1-3):";
        string input;
	    getline(cin, input);
	    try {
	        choice = stoi(input);
	        if (choice >= 1 && choice <= 3) {
	            category = categories[choice - 1];
	            break;
	        } else {
	            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
	        }
	    } catch (const invalid_argument& e) {
	        cout << "Invalid input. Please enter a number.\n";
	    }
	}
	while (true) {
        cout << "\nEnter price: ";
        getline(cin, price);
        try {
            if (stof(price) <= 0) throw invalid_argument("Price must be positive.");
            break;
        } catch (const invalid_argument& e) {
            cout << "Invalid price! Please enter a valid positive number.\n";
        }
    }
    while (true){
    	cout << "\nEnter product description: ";
    	getline(cin, description);
    	if (description.empty()) {
	        cout << "Description cannot be empty. Please try again.\n";
	    } else {
	        break;
	    }
	}
	Product newProduct(product_id, product_name, category, stod(price), description, status);
	
	products.append(newProduct);
	saveProduct(newProduct); 
	cout << product_name << " added successfully!\n";
    cout << "Press [ENTER] to continue.";
    cin.ignore();
    manageProduct();
}
void displayProductAdmin(const Product& product) {
    cout << "----------------------------------------------------------------------" << endl;
    cout << "| Product ID: " << left << setw(55) << product.product_id << "|" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "| Name      : " << left << setw(55) << product.product_name << "|" << endl;
    cout << "| Category  : " << left << setw(55) << product.category << "|" << endl;
    cout << "| Price     : RM " << left << setw(52) << fixed << setprecision(2) << product.price << "|" << endl;
    cout << "| Status    : " << left << setw(55) << product.status << "|" << endl;
    cout << "|                                                                    |" << endl;
    cout << "|";
    printWrappedText(product.description);
    cout << "----------------------------------------------------------------------" << endl;
}
void manageProduct() {
	Products P;
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
        cout << "| Select a category:                                          |" << endl;
        cout << "| 1. Pizza                                                    |" << endl;
        cout << "| 2. Side                                                     |" << endl;
        cout << "| 3. Beverage                                                 |" << endl;
        cout << "| 4. Back to Main Menu                                        |" << endl;
        cout << "===============================================================" << endl;
        string choiceString;
		cout << "Enter your choice : ";
		getline(cin, choiceString);
		if (choiceString.empty()) {
		    cout << "Choice cannot be empty. Press [ENTER] to retry.";
		    cin.get();
		    continue;
		}
		int choice = stoi(choiceString);
        string categories[] = {"Pizza", "Side", "Beverage"};
        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Press [ENTER] to retry.";
            cin.get();
            manageProduct();
        }
        else if (choice == 4) {
            clearScreen();
            adminMenu(loggedInAdmin);
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
                    displayProductAdmin(products[i]);
                    found = true;
                }
            }
            if (!found) {
                cout << "\nNo available products found in '" << selectedCategory << "' category." << endl;
            }
            cout << " ________________________________________" << endl;
	        cout << "| Options:                               |" << endl;
	        cout << "| [1] Add New Product to This Category   |" << endl;
	        cout << "| [2] Edit Existing Product              |" << endl;
	        cout << "| [3] Change Product Status              |" << endl;
	        cout << "| [4] Return to Category Selection       |" << endl;
	        cout << "|________________________________________|" << endl;
            string selection;
            cout << "\nEnter your choice: ";
            getline(cin,selection);
            if(selection == "1") {
	            clearScreen();
	            addProduct();
	            return;
	        }
	        else if(selection == "2") {
	            clearScreen();
	            //editProduct();
	            return;
	        }
	        else if(selection == "3") {
	            clearScreen();
	            //changeProductStatus();
	            return;
	        }
	        else if(selection == "4") {
	            clearScreen();
	            manageProduct();
	            return;
	        }else {
	        	cout << "Invlid choice. Press [ENTER] to continue.";
	        	cin.get();
			}
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
void viewAdminList(const string& statusFilter) {
    adminList.loadAdmins();
    Node<Admin>* current = adminList.getHead();
    clearScreen();
    if (statusFilter == "Active") {
        cout << "===========================================================================\n";
        cout << "|                          ACTIVE ADMIN LIST                              |\n";      
    } else {
        cout << "===========================================================================\n";
        cout << "|                           INACTIVE ADMIN LIST                           |\n";      
    }
    cout << "===========================================================================\n"; 
    bool foundAny = false;
    while (current != nullptr) {
        if (current->data.status == statusFilter) {
            foundAny = true;
            cout << "| Member ID         : " << left << setw(52) << current->data.admin_id << "|\n";
            cout << "| Name              : " << left << setw(52) << current->data.full_name << "|\n";
            cout << "| Email             : " << left << setw(52) << current->data.email << "|\n";
            cout << "| Contact           : " << left << setw(52) << current->data.contact << "|\n";
            cout << "| Position          : " << left << setw(52) << current->data.position << "|\n";
            cout << "---------------------------------------------------------------------------\n";
        }
        current = current->next;
    }
    if (!foundAny) {
        cout << "|                                                                         |\n";
        cout << "|                      No " << left << setw(48) << (statusFilter + " admins found.") << "|\n";
        cout << "|                                                                         |\n";
        cout << "---------------------------------------------------------------------------\n";
		cout << "\nPress [ENTER] to return.";
        cin.ignore();
        clearScreen();
        return; 
	}
    while (true) {
        string searchChoice;
        cout << "\nDo you want to search admin by ID? (Y/N to return): ";
        getline(cin, searchChoice);
        if (searchChoice == "N" || searchChoice == "n") {
            return;
        } else if (searchChoice == "Y" || searchChoice == "y") {
            string searchId;
            cout << "\nEnter Admin ID to search (or 'C' to cancel): ";
            getline(cin, searchId);
            if (searchId == "C" || searchId == "c") {
                continue;
            }
            current = adminList.getHead();
            bool found = false;
            while (current != nullptr) {
                if (current->data.admin_id == searchId && current->data.status == statusFilter) {
                    clearScreen();
                    cout << "===========================================================================\n";
                    cout << "|                                ADMIN DETAILS                            |\n";
                    cout << "===========================================================================\n";
                    cout << "| Admin ID          : " << left << setw(52) << current->data.admin_id << "|\n";
                    cout << "| Name              : " << left << setw(52) << current->data.full_name << "|\n";
                    cout << "| Email             : " << left << setw(52) << current->data.email << "|\n";
                    cout << "| Contact           : " << left << setw(52) << current->data.contact << "|\n";
                    cout << "| Position          : " << left << setw(52) << current->data.position << "|\n";
                    cout << "| Status            : " << left << setw(52) << current->data.status << "|\n";
                    cout << "===========================================================================\n";
                    found = true;
                    break;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Admin with ID " << searchId << " not found in " << statusFilter << " admins.\n";
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
void changeAdminStatus() {
   	adminList.loadAdmins();
    clearScreen();
    cout << "==========================================================================================\n";
    cout << "|                                     ADMIN LIST                                         |\n";
    cout << "==========================================================================================\n";
    cout << "| ID            | Name                  | Position              | Status                 |\n";
	cout << "==========================================================================================\n";    
	Node<Admin>* current = adminList.getHead();
    while (current != nullptr) {
        cout << "| " << left << setw(13) << current->data.admin_id << " | " 
			 << left << setw(21) << current->data.full_name << " | "
             << left << setw(21) << current->data.position << " | "
             << left << setw(22) << current->data.status << " |\n";
        current = current->next;
    }
    cout << "==========================================================================================\n";
    string chosenID;
    while (true) {
        cout << "\nEnter admin name to change status (or 'C' to cancel): ";
        getline(cin, chosenID);
        if (chosenID == "C" || chosenID == "c") {
            return;
        }
        current = adminList.getHead();
        bool found = false;
        while (current != nullptr) {
            if (current->data.admin_id == chosenID) {
                found = true;
                break;
            }
            current = current->next;
        }
        if (!found) {
            cout << "\nError: Admin ID '" << chosenID << "' not found. Please try again.\n";
            continue;
        }
        if(chosenID == loggedInAdmin.admin_id && loggedInAdmin.position == "superadmin") {
	    	cout << "\nERROR: Superadmin cannot change their own status.\n";
	    	continue;
    	}
        break;
    }
    current = adminList.getHead();
    while (current != nullptr) {
        if (current->data.admin_id == chosenID) {
        	if (current->data.status == "Active")
        		current->data.status =  "Inactive";
        	else if (current->data.status == "Inactive") 
            	current->data.status =  "Active";
            break;
        }
        current = current->next;
    }
    ofstream file(ADMINS_FILE);
    if (file) {
        current = adminList.getHead();
        bool firstAdmin = true;
        while (current != nullptr) {
            if (!firstAdmin) {
                file << "\n";
            }
            file << current->data.admin_id << "\n"
                 << current->data.full_name << "\n"
                 << current->data.email << "\n"
                 << current->data.password << "\n"
                 << current->data.contact << "\n"
                 << current->data.position << "\n"
                 << current->data.status << "\n";
            firstAdmin = false;
            current = current->next;
        }
        file.close();
    }
    cout << "\nAdmin " << chosenID << " status changed successfully.\n";
    cout << "\nPress [ENTER] to continue.";
    cin.ignore();
}
void saveAdmin(const Admin& admin) {
    bool fileIsEmpty = true;
    {
        ifstream file(ADMINS_FILE);
        if (file) {
            string line;
            if (getline(file, line)) {
                fileIsEmpty = false;
            }
        }
    }
    ofstream file(ADMINS_FILE, ios::app);
    if (file) {
        if (!fileIsEmpty) {
            file << "\n";
        }
        file << admin.admin_id << "\n"
             << admin.full_name << "\n"
             << admin.email << "\n"
             << admin.password << "\n"
             << admin.contact << "\n"
             << admin.position << "\n"
             << admin.status << "\n";
    }
}
void addNewAdmin() {
	string admin_id = getNextAdminId();
	string position = "admin";
    string status = "Active";
    string name, email, password, confirm_password, contact;
    clearScreen();
    cout << "===========================================================================\n";
    cout << "|                            ADD NEW ADMIN                                |\n";
    cout << "===========================================================================\n";
    cout << "| Requirement:                                                            |\n";
    cout << "| -> Name cannot be same                                                  |\n";
    cout << "| -> Password need at least 8 chars                                       |\n";
    cout << "| -> Password need one uppercase, lowercase, number                       |\n";
    cout << "| -> Contact format: 012-3456789 or 012-34567890                          |\n";
    cout << "===========================================================================";
    while (true) {
        cout << "\nEnter admin name (or 'C' to cancel): ";
        getline(cin, name);
        if (name == "C" || name == "c") {
            cout << "\nOperation cancelled.\n";
            cout << "Press [ENTER] to continue.";
            cin.ignore();
            return;
        }
        bool valid = true;
        int letterCount = 0;
        for (int i = 0; i < name.length(); ++i) {
            char c = name[i];
            if (!isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
            if (isalpha(c)) 
                letterCount++;
        }
        if (name.empty()) {
            cout << "Name cannot be empty.\n";
            continue;
        }
        if (!valid || letterCount < 5) {
            cout << "Invalid name! Please enter a valid name.\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "\nEnter email (example: user@example.com): ";
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
        if (email.empty()) {
            cout << "Email cannot be empty.\n";
            continue;
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
            cout << "Invalid email format! Please enter a valid email.\n";
            continue;
        }
        if (adminList.emailExists(email)) {
            cout << "This email is already registered!\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "\nEnter password: ";
        getline(cin, password);
        if (password.empty()) {
            cout << "Password cannot be empty.\n";
            continue;
        }
		if (password.length() < 8) {
            cout << "Password must be at least 8 characters!\n";
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
            cout << "Password must have at least 1 uppercase!\n";
            continue;
        }
        if (!hasLower) {
            cout << "Password must have at least 1 lowercase!\n";
            continue;
        }
        if (!hasDigit) {
            cout << "Password must have at least 1 number!\n";
            continue;
        }
        cout << "\nConfirm your password: ";
        getline(cin, confirm_password);
        if (confirm_password != password) {
            cout << "Passwords do not match!\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "\nEnter contact number (example: 012-3456789): ";
        getline(cin, contact);
        const char* p = contact.c_str();
        bool valid = true;
		int i = 0;
		int digitCount = 0;
		if (contact.empty()) {
            cout << "Contact number cannot be empty.\n";
            continue;
        }
        if (!(p[0] == '0' && p[1] == '1')) {
	        cout << "Contact number must start with '01'.\n";
	        valid = false;
	    }
		while (p[i] != '\0') {
			if (i == 3 && p[i] != '-'){
				valid = false;
            	break;
			}
			char c = p[i];
			if (!((c >= '0' && c <= '9') || c == '-' )){
				valid = false;
            	break;
			}
			if (c >= '0' && c <= '9'){
				digitCount++;
			}
			i++;
		}
		if (valid && (digitCount < 10 || digitCount > 11)) {
	        cout << "Contact number must be 10 or 11 digits total.\n";
	        valid = false;
	    }
	    if (valid && i < 4) {
	        cout << "Invalid contact number. Please enter a valid contact number.\n";
	        valid = false;
	    }
	    if (!valid) {
	        cout << "Invalid contact number format.\n";
	        continue;
	    }
	    if (adminList.contactExists(contact)) {
	        cout << "This contact number is already registered!\n";
	        continue;
	    }
        break;
    }
	Admin newAdmin(admin_id, name, email, password, contact, position, status);
	adminList.append(newAdmin);
	saveAdmin(newAdmin); 
    ofstream idFile(ADMINS_ID_FILE, ios::app);
    if (idFile) {
        idFile << admin_id << "\n";
        idFile.close();
	}
	cout << "\nAdmin " << name << " added successfully!\n";
    cout << "Press [ENTER] to continue.";
    cin.ignore();
}
void manageAdmin() {
    while (true) {
    	string choice;
        clearScreen();
        cout << "===========================================================================\n";
        cout << "|                            MANAGE ADMIN LIST                            |\n";      
        cout << "===========================================================================\n";
        cout << "| [1] View Active Admins                                                  |\n";
        cout << "| [2] View Inactive Admins                                                |\n";
        if (loggedInAdmin.position == "superadmin"){
        	cout << "| [3] Add New Admin                                                       |\n";
	        cout << "| [4] Change Admin Status                                                 |\n";
	        cout << "| [5] Return to Admin Menu                                                |\n";
	        cout << "===========================================================================\n";
		}
		else{
			cout << "| [3] Return to Admin Menu                                                |\n";
        	cout << "===========================================================================\n";
		}
		cout << "Enter your choice: ";
        getline(cin, choice);
		if (choice == "1") {
            viewAdminList("Active");
        }
        else if (choice == "2") {
            viewAdminList("Inactive");
        }
        else if (choice == "3" && loggedInAdmin.position == "superadmin") {
        	addNewAdmin();
        }
        else if (choice == "3" && loggedInAdmin.position == "admin") {
        	adminMenu(loggedInAdmin);
        }
        else if (choice == "4" && loggedInAdmin.position == "superadmin") {
            changeAdminStatus();
        }
        else if (choice == "5" && loggedInAdmin.position == "superadmin") {
            adminMenu(loggedInAdmin);
        }
        else {
            cout << "Invalid choice, Press [ENTER] to try again.";
            cin.ignore();
        }
    }
}
void filterFeedbackRating(RatingFeedbackLinkedList& RF) {
    clearScreen();
    cout << "Enter the rating level to filter by (1 to 5): ";
    string input;
    getline(cin, input);

    if (input.empty()) {
        cout << "Invalid input. Rating cannot be empty.\n";
        cin.ignore();
        clearScreen();
    	manageRating();
    }
    bool onlyDigits = true;
        for (int i = 0; i < input.length(); ++i) {
            if (!isdigit(input[i])) {
                onlyDigits = false;
                break;
            }
        }
    if (!onlyDigits) {
        cout << "Invalid input. Please enter a number between 1 and 5.\n";
        cin.ignore();
        clearScreen();
    	manageRating();
    }
    int rate_filter = stoi(input);
    if (rate_filter < 1 || rate_filter > 5) {
        cout << "Invalid rating. Please enter a number between 1 and 5.\n";
        cin.ignore();
        clearScreen();
    	manageRating();
    }
    int total = 0;
    Node<RatingFeedback>* current = RF.getHead();
    while (current != nullptr) {
        total++;
        current = current->next;
    }
    if (total == 0) {
        cout << "No feedback records found.\n";
        cin.get();
        clearScreen();
        manageRating();
    }
    RatingFeedback* feedbackArr = new RatingFeedback[total];
    current = RF.getHead();
    for (int i = 0; i < total && current != nullptr; ++i) {
        feedbackArr[i] = current->data;
        current = current->next;
    }
    quickSortRatingFeedback(feedbackArr, 0, total - 1, "rating", false);
    RatingFeedback* match = binarySearchRatingFeedback(feedbackArr, 0, total - 1, rate_filter);
    bool found = false;
    if (match != nullptr) {
        cout << "===========================================================================\n";
        cout << "|                    Filtered Feedback (Rating = " << rate_filter << ")                       |\n";
        for (int i = 0; i < total; ++i) {
            if (feedbackArr[i].rating == rate_filter) {
                found = true;
                cout << "===========================================================================\n";
                cout << "| Date & Time  : " << left << setw(57) << feedbackArr[i].datetime << "|\n";
                cout << "===========================================================================\n";
                cout << "| Member ID    : " << left << setw(57) << feedbackArr[i].member_id << "|\n";
                cout << "| Rating       : " << left << setw(57) << feedbackArr[i].rating << "|\n";
                cout << "| Comment      : " << left << setw(57) << feedbackArr[i].feedback_text << "|\n";
                cout << "---------------------------------------------------------------------------\n";
            }
        }
    }
    if (!found) {
    	cout << "---------------------------------------------------------------------------\n";
        cout << "|                                                                         |\n";
        cout << "|                  No records found for rating level " << rate_filter << setw(20) << "." << "|\n";
        cout << "|                                                                         |\n";
        cout << "---------------------------------------------------------------------------\n";
    }
    cout << "\nPress [ENTER] to return to feedback menu.";
    cin.get();
    clearScreen();
    manageRating();
}
void sortFeedbackRating(){
	RatingFeedbackLinkedList RF;
	RF.loadFeedback();
	int total = 0;
    Node<RatingFeedback>* current = RF.getHead();
    while (current != nullptr) {
        total++;
        current = current->next;
    }
    RatingFeedback* feedbackArr = new RatingFeedback[total];
    current = RF.getHead();
    for (int i = 0; i < total && current != nullptr; ++i) {
        feedbackArr[i] = current->data;
        current = current->next;
    }
    if (total == 0) {
        cout << "No feedback records found.\n";
        return;
    }
	string choice;
	cout << "-------------------------------" << endl;
	cout << "| Sort feedback by:" << "           |" << endl;
	cout << "| 1. Rating (High to Low)" << "     |" << endl;
	cout << "| 2. Rating (Low to High)" << "     |" << endl;
	cout << "| 3. Date (Newest)" << "            |" << endl;
	cout << "| 4. Date (Oldest)" << "            |" << endl;
	cout << "| 5. Cancel" << "                   |" << endl;
	cout << "-------------------------------" << endl;
	cout << "Enter your choice (1-5): ";
    getline(cin, choice);
    if (choice == "1") {
        clearScreen();
        cout << "======================================================================" << endl;
        cout << "|         SORTED FEEDBACK & RATING (Rating - Highest First)          |" << endl;
	    quickSortRatingFeedback(feedbackArr, 0, total - 1, "rating", true);
    } else if (choice == "2") {
    	clearScreen();
        cout << "======================================================================" << endl;
        cout << "|         SORTED FEEDBACK & RATING (Rating - Lowest First)           |" << endl;
	    quickSortRatingFeedback(feedbackArr, 0, total - 1, "rating", false);
    } else if (choice == "3") {
    	clearScreen();
        cout << "======================================================================" << endl;
        cout << "|          SORTED FEEDBACK & RATING (Date - Newest First)            |" << endl;
	    quickSortRatingFeedback(feedbackArr, 0, total - 1, "datetime", true); 
	} else if (choice == "4") {
    	clearScreen();
        cout << "======================================================================" << endl;
        cout << "|          SORTED FEEDBACK & RATING (Date - Oldest First)            |" << endl;
	    quickSortRatingFeedback(feedbackArr, 0, total - 1, "datetime", false);  
    } else if (choice == "5") {
    	clearScreen();
		manageRating();
    } else  {
        cout << "Invalid option. Press [ENTER] to try again.\n";
	        cin.get();
		    clearScreen();
		    manageRating();
    }
	for (int i = 0; i < total; ++i) {
	    cout << "======================================================================\n";
	    cout << "| Member ID     	: " << setw(43) << feedbackArr[i].member_id << "|\n";
	    cout << "| Rating   		: " << setw(43) << feedbackArr[i].rating << "|\n";
	    cout << "| Comment  		: " << setw(43) << feedbackArr[i].feedback_text << "|\n";
	    cout << "| Datetime 		: " << setw(43) << feedbackArr[i].datetime << "|\n";
	    cout << "----------------------------------------------------------------------\n";
	}
	delete[] feedbackArr;
	cout << "\nPress [ENTER] to return to feedback menu.";
    cin.get();
    clearScreen();
    manageRating();
}
void manageRating() {
	RatingFeedbackLinkedList RF;
	RF.loadFeedback();
	Node<RatingFeedback>* current = RF.getHead();
	bool foundRatingFeedback = false;
    while (current != nullptr) {
        RatingFeedback fb = current->data;
        foundRatingFeedback = true;
        cout << "===========================================================================\n";
        cout << "| Date & Time  : " << left << setw(57) << fb.datetime << "|\n";
        cout << "===========================================================================\n";
        cout << "| Member ID    : " << left << setw(57) << fb.member_id << "|\n";
        cout << "| Rating       : " << left << setw(57) << fb.rating << "|\n";
        cout << "| Comment      : " << left << setw(57) << fb.feedback_text << "|\n";
        cout << "---------------------------------------------------------------------------\n";
        current = current->next;
    }
    if (!foundRatingFeedback) {
    	cout << "---------------------------------------------------------------------------\n";
        cout << "|                                                                         |\n";
        cout << "|                       No feedback records found.                        |\n";
        cout << "|                                                                         |\n";
        cout << "---------------------------------------------------------------------------\n";
        cout << "Press [Enter] to return to the admin menu.";
        cin.ignore();
        cin.get();
        adminMenu(loggedInAdmin);
    }
    while (true){
        cout << "1. Filter feedback by rate level\n";
        cout << "2. Sort feedback and rating\n";
        cout << "\nEnter your choice (R for return): ";
        string choice;
        getline(cin, choice);
        if (choice == "1") {
            clearScreen();
            filterFeedbackRating(RF);
        } else if (choice == "2") {
            sortFeedbackRating();
        } else if (choice == "R" || choice == "r") {
            clearScreen();
            adminMenu(loggedInAdmin);
        } else if (choice.empty()) {
            cout << "\nInvalid input. The choice cannot be empty.\n";
        } else {
            cout << "\nInvalid choice. Please enter 1, 2 or R.\n";
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
        if (loggedInAdmin.position == "superadmin"){
        	cout << "2. View/Edit Admin List\n";
		}
		else{
			cout << "2. View Admin List\n";
		}
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
        if(choice == "1") {
            clearScreen();
            manageProduct();
            return;
        }
        else if(choice == "2") {
            clearScreen();
            manageAdmin();
            return;
        }
		else if(choice == "3") {
            clearScreen();
            manageMember();
            return;
        }
        else if(choice == "4") {
            clearScreen();
            //manageOrder();
            return;
        }
        else if(choice == "5") {
            clearScreen();
            manageRating();
            return;
        }
        else if(choice == "6") {
            clearScreen();
            //dashboard();
            return;
        }
        else if(choice == "7") {
            clearScreen();
            //adminProfile();
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