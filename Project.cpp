// Library used
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// File paths
const string MEMBERS_FILE = "member.txt";
const string MEMBERS_ID_FILE = "member_id.txt";
const string ADMINS_FILE = "admin.txt";
const string ADMINS_ID_FILE = "admin_id.txt";

// Structures
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

//Helper functions
void clearScreen() {
    system("cls");
}

//Landing Page for the store system
void mainMenu() {
    //should load linked list for admin and member data first

    //display landing page interface
    while(true){
        clearScreen();
        cout << "\n===============================================================\n";
        cout << "               WELCOME TO YESMOLAR PIZZA STORE                \n";
        cout << "===============================================================\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
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
            //signup();
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