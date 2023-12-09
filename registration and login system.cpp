#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;
void displayMenu();
void registerUser();
void loginUser();
void deleteUser();
void showExistingUsers();
int main() {
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                deleteUser();
                break;
            case 4:
                showExistingUsers(); 
                break;
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

void displayMenu() {
    cout << "\n=== User Authentication System ===\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Delete User\n";
    cout << "4. Show Existing Users\n"; 
    cout << "5. Exit\n";
}

void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    ifstream inputFile("users.txt");
    string line;
    bool userExists = false;
    while (getline(inputFile, line)) {
        if (line.find(username) != string::npos) {
            userExists = true;
            break;
        }
    }
    inputFile.close();

    if (userExists) {
        cout << "Username already exists. Please choose a different one.\n";
        return;
    }
    cout << "Enter a password: ";
    cin >> password;
    ofstream outputFile("users.txt", ios::app);
    outputFile << username << " " << password << endl;
    outputFile.close();

    cout << "User registered successfully!\n";
}

void loginUser() {
    string username, password;

    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your password: ";
    cin >> password;

    ifstream inputFile("users.txt");
    string line;
    bool loginSuccess = false;

    while (getline(inputFile, line)) {
        size_t found = line.find(username + " " + password);
        if (found != string::npos) {
            loginSuccess = true;
            break;
        }
    }

    inputFile.close();

    if (loginSuccess) {
        cout << "Login successful!\n";
    } else {
        cout << "Login failed. Please check your username and password.\n";
    }
}

void deleteUser() {
    string username, password;

    cout << "Enter the username of the user to be deleted: ";
    cin >> username;

    cout << "Enter the password: ";
    cin >> password;

    ifstream inputFile("users.txt");
    ofstream tempFile("temp.txt");
    

    string line;
    bool userFound = false;

    while (getline(inputFile, line)) {
        size_t found = line.find(username + " " + password);
        if (found != string::npos) {
            userFound = true;
        } else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (userFound) {
        cout << "User deleted successfully!\n";
    } else {
        cout << "User not found. Deletion failed.\n";
    }
}
void showExistingUsers() {
    cout << "\n=== Existing Users ===\n";
    ifstream inputFile("users.txt");
    string line;

    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
    cout << "=== End of User List ===\n";
}
