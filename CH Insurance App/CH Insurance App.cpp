// -------------------------------- BLANK  -------------------------
// ------------------------------------ END ------------------------



// -------------------------- CH INSURANCE APP -------------------------------
#include<iostream>
#include <fstream>
#include <string>
#include <vector> 

using namespace std;

// ------------------------ USER CLASS ATTRIBUTES ------------------------------
class User {
public:
    string username;
    string password;
    bool isAdmin;

    User(const string& uname, const string& pwd, bool admin)
        : username(uname), password(pwd), isAdmin(admin) {}
};
// ----------------------------- END ---------------------------------------------


// ------------------ UTILITY FUNCTION TO CLEAR INPUT BUFFER ------------------------
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// ------------------------------- END ----------------------------------------------



// -------------------------------- USER MENU  -------------------------

void adminMenu(vector<User>& users) {

    int choice;

    cout << "\n         Admin Menu: " << endl;
    cout << "\n          ------------ " << endl;

    cout << "\n 1. Add new user" << endl;

    cout << "\n 2. View all users" << endl;

    cout << "\n 3. Add new insurance policy" << endl;

    cout << "\n 4. View all policies" << endl;

    cout << "\n 5. Remove User" << endl;  // Option to remove a user

    cout << "\n 6. Logout" << endl;  // Log-out option

    cout << "\n Enter choice (1-6): ";
    cin >> choice;
}

// ------------------------------------ END ------------------------

// -------------------------------- USER MENU  -------------------------

void userMenu(vector<User>& users) {

    int choice;

    cout << "\n         User Menu: " << endl;
    cout << "\n        ------------ " << endl;

    cout << "\n 1. View Available Policies" << endl;

    cout << "\n 2. Make a Claim" << endl;

    cout << "\n 3. Sign-Up for Insurance Policy" << endl;

    cout << "\n 4. Logout" << endl;

    cout << "\n Enter choice (1-4): ";
    cin >> choice;
}

// ------------------------------------ END ------------------------


// -------------------------------- VIEW POLICY DESCRIPTIONS -------------------------
void policyInfo() {
    cout << "\n          Available Insurance Policies " << endl;
    cout << "            ---------------------------- " << endl;
    cout << endl;
    ifstream inputFile("policy-desc.txt");

    if (!inputFile.is_open()) {
        cout << " Error opening policy description file." << endl;
        return;
    }

    // Read the file line by line
    string line;
    while (getline(inputFile, line)) {
        // Process each line as needed
        cout << line << endl;
    }

    // Close the file
    inputFile.close();
}
// ------------------------------------ END ------------------------------------------

// ------------------ LOGIN USER / GIVES 3 ATTEMPTS -Harlen   ------------------------------------------
User loginUser(const vector<User>& users, string& currentUser) {
    const int maxAttempts = 3;

    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        cout << "Enter username: ";
        string username;
        cin >> username;
        cout << " \n" << endl;

        cout << "Enter password: ";
        string password;
        cin >> password;
        cout << " \n" << endl;
        clearInputBuffer();

        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                currentUser = username;
                cout << "Login successful. Welcome, " << username << '!' << endl;
                return user;
            }
        }

        cout << " Invalid username or password. " << maxAttempts - attempt << " attempts remaining." << endl;
        cout << " \n" << endl;
    }

    cout << " Too many failed attempts. Exiting login." << endl;
    cout << " \n" << endl;
    return User("", "", false);
}
//------------------------------------------ END -------------------------------------------------------------



// -------------------------------- USER INPUT FOR MAIN MENU  ----------------
int getUserChoice() {
    int choice;
    do {
        cout << "\n" << endl;
        cout << " Enter 1-4: ";
        cin >> choice;
        cout << "\n" << endl;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cout << "\n" << endl;
            cout << " Invalid input. Please enter a valid number between 1 and 4." << endl;
            cout << "\n" << endl;
        }
        else {
            break;
        }
    } while (true);

    return choice;
}
// ------------------------------------ END ----------------------------------


// -------------------- SAVES USER LOGIN TO : .txt FILE  --------------------------
void saveUsers(const vector<User>& users) {
    ofstream file("users.txt", ios::app);  // Open file in append mode

    for (const auto& user : users) {
        file << user.username << ' ' << user.password << ' ' << user.isAdmin << endl;
    }
}

//---------------------------------- END --------------------------------------------


//  ------------------------------------ CREATE ACCOUNT FUNCTION -----------------------------------------------
User createAccount(vector<User>& users) {
    string uname, pwd, confirmPwd;
    bool admin = false;

    cout << " Enter new username: ";
    cin >> uname;
    cout << "\n" << endl;

    // Ask for the password and its confirmation
    do {
        cout << " Enter new password: ";
        cin >> pwd;
        cout << "\n" << endl;

        cout << " Confirm password: ";
        cin >> confirmPwd;
        cout << "\n" << endl;

        if (pwd != confirmPwd) {
            cout << " Passwords do not match. Please try again." << endl;
        }
        else if (pwd == uname) {
            cout << " Password cannot be the same as the username. Please choose a different password." << endl;
        }
    } while (pwd != confirmPwd || pwd == uname);


    users.emplace_back(uname, pwd, admin);

    // Save the new user immediately
    saveUsers(users);

    cout << " Account created successfully." << endl;
    cout << "\n" << endl;
    return users.back();
}
//------------------------------------------- END -------------------------------------------------------------



// ----------------------------- DISPLAYS MAIN MENU  -------------------------
void displayMainMenu() {
   
    cout << "\n **** CH Insurance ****" << endl;
    cout << "\n ---------------------- \n" << endl;
    cout << "\n 1. View Available Policies" << endl;
    cout << "\n 2. Create Account" << endl;
    cout << "\n 3. Login" << endl;
    cout << "\n 4. Exit" << endl;
        
    }
// ------------------------------- END ------------------------------------------------------



// ------------------------------------- INT MAIN ---------------------------------------------------------------------
int main() {
    vector<User> users;
    string currentUser;
    
    int choice;

    do {

      displayMainMenu();

      choice = getUserChoice();

      switch (choice) {
      case 1:
          policyInfo();
          cout << endl;
          break;
      case 2:
          createAccount(users);
          break;
      case 3: {

          User loggedInUser = loginUser(users, currentUser);

          if (loggedInUser.isAdmin) {
              adminMenu(users);
          }
          else if (!loggedInUser.username.empty()) {
              userMenu(users);
          }
          else {
              cout << " Login failed. Please try again." << endl;
          }
          break;
      }
          case 4:
          cout << "test4" << endl;
          break;
      }
    } while (choice != 4);;

    return 0;
}
// ---------------------------------------- END ---------------------------------------------------