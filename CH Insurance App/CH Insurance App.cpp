


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


// -------------------------------- INSURANCE POLICY CLASS ATTRIBUTES  -------------------------

class InsurancePolicy {
public:
    string custName;
    string carMake;
    string carModel;
    string carRego;
    string insurerName;
    string policyType;
    int policyNumber;

    InsurancePolicy(const string& customerName, const string& make, const string& model, const string& regoNum, const string& insurer, const string& type)
        : custName(customerName), carMake(make), carModel(model), carRego(regoNum), insurerName(insurer), policyType(type) {}
};

// ------------------------------------ END ------------------------


// ------------------ UTILITY FUNCTION TO CLEAR INPUT BUFFER ------------------------
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// ------------------------------- END ----------------------------------------------




// ----------------------- SAVES POLICY TO : .txt FILE ---------------------------
void savePolicies(const vector<InsurancePolicy>& policies) {
    ofstream file("policies.txt");

    for (const auto& policy : policies) {
        file << policy.custName << ' ' << policy.carMake << ' ' << policy.carModel << ' '
            << policy.carRego << ' ' << policy.insurerName << ' ' << policy.policyType << ' '
            << policy.policyNumber << endl;
    }
}

//--------------------------------- END ---------------------------------------------------



// -------------------------- LOADS POLICY FROM TXT FILE ---------------------------------- 
vector<InsurancePolicy> loadPolicies() {
    vector<InsurancePolicy> policies;
    ifstream file("policies.txt");

    if (!file.is_open()) {
        cout << "Error opening policies file." << endl;
        return policies;
    }

    string customerName, make, model, regoNum, insurer, policyType;
    int policyNumber;

    while (file >> customerName >> make >> model >> regoNum >> insurer >> policyType >> policyNumber) {
        policies.emplace_back(customerName, make, model, regoNum, insurer, policyType);
        policies.back().policyNumber = policyNumber;
    }

    return policies;
}
// ------------------------------ END -------------------------------------------------------

// ------------------ View user policies ------------------------

void viewUserPolicies(const vector<InsurancePolicy>& policies, const string& currentUser) {
    cout << "\n" << endl;
    cout << " Insurance Policies for User: " << currentUser << endl;
    cout << " --------------------------------" << endl;

    bool found = false;
    for (const auto& policy : policies) {
        if (policy.custName == currentUser) {
            found = true;
            cout << " Customer Name: " << policy.custName << " | Car Make: " << policy.carMake
                << " | Car Model: " << policy.carModel << " | Rego: " << policy.carRego
                << " | Insurer: " << policy.insurerName << " | Policy Type: " << policy.policyType
                << " | Policy Number: " << policy.policyNumber << endl;
        }
    }

    if (!found) {
        cout << " No policies found for user: " << currentUser << endl;
    }
}


// ------------------------------- END ----------------------------------------------

// -------------------------------- VIEW POLICY DESCRIPTIONS -------------------------
void policyInfo() {
    cout << "\n                           Available Insurance Policies " << endl;
    cout << "                           ---------------------------- " << endl;
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
        cout << "       " << line << endl;
    }

    // Close the file
    inputFile.close();
}
// ------------------------------------ END ------------------------------------------





// ----------------------------- DISPLAYS MAIN MENU  ------------------------------------------
void displayMainMenu() {
    cout << "\n" << endl;
    cout << "                              CH Insurance  " << endl;
    cout << "                         ---------------------- " << endl;
    cout << " Welcome to the CH Insurance App where you can manage your insurance policies with ease."<<endl;
    cout << " If you're interested in signing-up to one of our amzaing policies,our user-friendly interface makes it simple." << endl;
    cout << "\n" << endl;
    cout << " Please select an option from the menu below to get started: " << endl; 
    cout << "\n" << endl;
    cout << " 1. View Available Policies" << endl;
    cout << "\n" << endl;
    cout << " 2. Create Account" << endl;
    cout << "\n" << endl;
    cout << " 3. Login" << endl;
    cout << "\n" << endl;
    cout << " 4. Exit" << endl;
    cout << "\n" << endl;
    cout << " ----------------------" << endl;
}
// ------------------------------- END ------------------------------------------------------





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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    bool userExistsInFile(const User & userToCheck);
    ofstream file("users.txt", ios::trunc);

    for (const auto& user : users) {
        if (userExistsInFile(user)) {
            continue;
        }

        file << user.username << ' ' << user.password << ' ' << user.isAdmin << endl;
    }
}

bool userExistsInFile(const User& userToCheck) {
    ifstream file("users.txt");
    string uname, pwd;
    bool admin;

    while (file >> uname >> pwd >> admin) {
        if (uname == userToCheck.username && pwd == userToCheck.password && admin == userToCheck.isAdmin) {
            return true;  // User already exists in the file
        }
    }

    return false;  // User does not exist in the file
}
//---------------------------------- END --------------------------------------------

//------------------------- LOADS USERS FROM TXT FILE  -------------------------------------
vector<User> loadUsers() {
    vector<User> users;
    ifstream file("users.txt");
    string uname, pwd;
    bool admin;

    // Add default admin user
    users.emplace_back("admin", "admin1", true);
    
    while (file >> uname >> pwd >> admin) {
        users.emplace_back(uname, pwd, admin);
    }

    return users;
}
// -------------------------- END ---------------------------------------------------------

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

// ------------------ FUNCTION TO MAKE A CLAIM ----------------------------
void makeClaim(vector<InsurancePolicy>& policies) {
    cout << "\n" << endl;
    cout << "          Choose claim type:" << endl;
    cout << "           ------------------ " << endl;
    cout << "\n" << endl;
    cout << " You have chosen to make a claim please select from the options below: " << endl;
    cout << "\n" << endl;
    cout << " 1. Stolen" << endl;
    cout << "\n" << endl;
    cout << " 2. Damaged" << endl;
    cout << "\n" << endl;

    int claimType;
    while (true) {
        cout << " Enter the number 1-2 for claim type: ";
        cin >> claimType;
        clearInputBuffer();  // Clear input buffer after reading claim type

        if (cin.fail() || (claimType != 1 && claimType != 2)) {
            cin.clear();
            clearInputBuffer();
            cout << " Invalid input. Please enter either 1 or 2 for the claim type." << endl;
        }
        else {
            break;
        }
    }

    // Add logic to process the claim based on the selected type
    switch (claimType) {
    case 1:
        cout << "\n" << endl;
        cout << " Claim for stolen vehicle submitted successfully." << endl;
        break;
    case 2:
        cout << "\n" << endl;
        cout << " Claim for damaged vehicle submitted successfully." << endl;
        break;
    default:
        cout << "\n" << endl;
        cout << " Invalid claim type. Please try again." << endl;
        break;
    }
}
// ------------------------------ END -----------------------------------------------

// ------------------- FUNCTION TO REMOVE USER BY NAME ------------------------
void removeUser(vector<User>& users, const string& username) {
    auto it = find_if(users.begin(), users.end(), [username](const User& user) {
        return user.username == username;
        });

    if (it != users.end()) {
        // Ask for confirmation before removing the user
        cout << " \n" << endl;
        cout << " Are you sure you want to remove user '" << username << "'? (Y/N): ";
        char confirm;
        cin >> confirm;
        cout << " \n" << endl;

        if (confirm == 'Y' || confirm == 'y') {
            users.erase(it);
            cout << " \n" << endl;
            cout << " User '" << username << "' removed successfully." << endl;
            cout << " \n" << endl;
            saveUsers(users); // Save the updated user list to the file
        }
        else {
            cout << " User removal canceled." << endl;
            cout << " \n" << endl;
        }
    }
    else {
        cout << " User not found." << endl;
        cout << " \n" << endl;
    }
}
//---------------------------------- END ---------------------------------------------------

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


// ---------------------------------- DISPLAY ADMIN MENU ----------------------------------------------------

// LOGIN USER AND PASSWORD FOR ADMIN ACCOUNT : admin / admin1

void adminMenu(vector<User>& users, vector<InsurancePolicy>& policies) {
    int choice;

    do {
        cout << "\n" << endl;
        cout << "\n         Admin Menu: " << endl;
        cout << "          ------------ " << endl;
        cout << "\n" << endl;
        cout << " Welcome to the Admin Menu, Please select from the following: " << endl;
        cout << "\n" << endl;
        cout << " 1. Add new user" << endl;
        cout << "\n" << endl;
        cout << " 2. View all users" << endl;
        cout << "\n" << endl;
        cout << " 3. Add new insurance policy" << endl;
        cout << "\n" << endl;
        cout << " 4. View all policies" << endl;
        cout << "\n" << endl;
        cout << " 5. Remove User" << endl;  // Option to remove a user
        cout << "\n" << endl;
        cout << " 6. Logout" << endl;  // Log-out option
        cout << "\n" << endl;
        cout << " Enter choice (1-6): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            // Create account from admin menu 
            string uname, pwd, confirmPwd;
            bool admin;
            cout << " To Create a new customer or Admin account please follow prompts below: " << endl;
            cout << " \n" << endl;
            cout << " Enter new username: ";
            cin >> uname;
            cout << " \n" << endl;

            // passwrd confirmation 
            do {
                cout << " Enter new password: ";
                cin >> pwd;
                cout << " \n" << endl;

                cout << " Confirm password: ";
                cin >> confirmPwd;
                cout << " \n" << endl;

                if (pwd != confirmPwd) {
                    cout << " Passwords do not match. Please try again." << endl;
                }
                else if (pwd == uname) {
                    cout << " Password cannot be the same as the username. Please choose a different password." << endl;
                }
            } while (pwd != confirmPwd || pwd == uname);

            cout << " Is the user an admin? (1 for Yes, 0 for No): ";
            cin >> admin;

            users.emplace_back(uname, pwd, admin);
            saveUsers(users);

            cout << " \n" << endl;
            cout << " User added successfully." << endl;
            break;
        }
        case 2: {
            // View current users
            cout << "\n All Registered Users below:" << endl;
            for (const auto& user : users) {
                cout << " Username: " << user.username << ", Admin: " << user.isAdmin << endl;
            }
            break;
        }
        case 3: { // Add new policy
            string customerName, make, model, regNum, insurer, policyType;
            int policyNumber;

            cout << " Thank you for choosing to register for a new policy please input details as prompted: " << endl; 
            cout << " \n" << endl;
            cout << " Enter customer name: ";
            cin >> customerName;
            cout << " \n" << endl;
            cout << " Enter car make: ";
            cin >> make;
            cout << " \n" << endl;
            cout << " Enter car model: ";
            cin >> model;
            cout << " \n" << endl;
            cout << " Enter vehicle registration number: ";
            cin >> regNum;
            cout << " \n" << endl;
            cout << " Enter insurer name: ";
            cout << "\n" << endl;
            getline(cin, insurer);

            // Policy type input and validation
            cout << "\n" << endl;
            cout << " Please Select policy type:";
            cout << "\n" << endl;
            cout << " 1: Full ";
            cout << "\n" << endl;
            cout << " 2: Third-Party ";
            cout << "\n" << endl;
            cout << " 3: Theft" << endl;
            
            while (true) {
                cout << "\n" << endl;
                cout << " Please select policy type you require : ";
                cin >> policyNumber;

                if (cin.fail() || policyNumber < 1 || policyNumber > 3) {
                    cin.clear();
                    clearInputBuffer();
                    cout << "\n" << endl;
                    cout << " Invalid input. Please enter a valid number between 1 and 3." << endl;
                }
                else {
                    clearInputBuffer();
                    break;
                }
            }

            switch (policyNumber) {
            case 1:
                policyType = "Full";
                break;
            case 2:
                policyType = "Third-Party";
                break;
            case 3:
                policyType = "Theft";
                break;
            default:
                // Validators 
                cout << " Invalid policy type. Please choose a number between 1 and 3." << endl;
                continue;  // loop for incorrect input continues to run 
            }
            // Print the entered details for confirmation

            cout << "\n Confirming entered details:" << endl;
            cout << " Customer Name: " << customerName << endl;
            cout << " Car Make: " << make << endl;
            cout << " Car Model: " << model << endl;
            cout << " Rego: " << regNum << endl;
            cout << " Insurer name: " << insurer << endl;
            cout << " Policy Type: " << policyType << endl;


            // Ask for confirmation
            char confirm;
            cout << "\n" << endl;
            cout << " Confirm details? (Y/N): ";
            cin >> confirm;
            if (toupper(confirm) != 'Y') {
                cout << "\n" << endl;
                cout << " Details not confirmed. Exiting without saving." << endl;
                break;
            }

            // Add the policy to the vector and save
            policies.emplace_back(customerName, make, model, regNum, insurer, policyType);
            policies.back().policyNumber = policyNumber;
            savePolicies(policies);
            cout << "\n" << endl;
            cout << " Insurance policy added successfully." << endl;
            break;
        }
        case 4:
            cout << "\n All Currently Registered Insurance Policies:" << endl;
            for (const auto& policy : policies) {
                cout << " Customer Name: " << policy.custName << " | Car Make: " << policy.carMake
                    << " | Car Model: " << policy.carModel << " | Rego: " << policy.carRego
                    << " | Insurer: " << policy.insurerName << " | Policy Type: " << policy.policyType
                    << " | Policy Number: " << policy.policyNumber << endl;
            }
            break;

        case 5: {
            // Display list of users
            cout << "\n All Users:" << endl;
            for (size_t i = 0; i < users.size(); ++i) {
                cout << " " << i + 1 << ". Username: " << users[i].username << ", Admin: " << users[i].isAdmin << endl;
            }

            // Remove user by index
            if (!users.empty()) {
                int userIndex;
                do {
                    cout << "\n Enter the number corresponding to the user you want to remove (1 - " << users.size() << "): ";
                    cin >> userIndex;

                    if (cin.fail() || userIndex < 1 || userIndex > static_cast<int>(users.size())) {
                        cin.clear();
                        clearInputBuffer();
                        cout << "\n Invalid input. Please enter a valid number between 1 and " << users.size() << "." << endl;
                    }
                    else {
                        clearInputBuffer();
                        string usernameToRemove = users[userIndex - 1].username;
                        removeUser(users, usernameToRemove);
                        cout << "\n User removed successfully." << endl;
                        break;
                    }
                } while (true);
            }
            else {
                cout << "\n No users to remove." << endl;
            }
            break;
        }

        case 6: {
            // Log-out
            cout << " Logging out..." << endl;
            return;
        }

        default: {
            cout << " Invalid choice. Please try again." << endl;
            break;
        }
        }

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "\n" << endl;
            cout << " Invalid input. Please enter a valid number between 1 and 6." << endl;
            cout << "\n" << endl;
        }
        else {
            clearInputBuffer();
        }
    } while (true);
}
// ----------------------------------------- END ---------------------------------------------------------------



// ------------------------------------- USER MENU -------------------------------------------------------------
void userMenu(const vector<User>& users, vector<InsurancePolicy>& policies, const string& currentUser) {
    while (true) {
        cout << "\n" << endl;        
        
        cout << "\n        User Menu :" << endl;
        cout << "       ------------ " << endl;
        cout << "\n" << endl;
        cout << "\n Welcome " << currentUser << ",\n\n Please choose from the following menu options below:" << endl;
        cout << "\n" << endl;
        cout << " 1. View Available Policies" << endl;
        cout << "\n" << endl;
        cout << " 2. Make a Claim" << endl;
        cout << "\n" << endl;
        cout << " 3. Sign-Up for Insurance Policy" << endl;
        cout << "\n" << endl;
        cout << " 4. View My Policies" << endl;  // New option
        cout << "\n" << endl; 
        cout << " 5. Log-Out" << endl; 

        int choice;
        while (true) {
            cout << "Please input choice (1 - 5) : ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 5) {
                cin.clear();
                clearInputBuffer();
                cout << "\n" << endl;
                cout << " Invalid input. Please enter a valid number between 1 and 5." << endl;
            }
            else {
                clearInputBuffer();
                break;
            }
        }

        switch (choice) {
        case 1://calls policy info from txt file 
            policyInfo();
            break;
        case 2:
            // make a claim - calls function 
            makeClaim(policies);
            break;
        case 3: {
            //  signing up for a new insurance policy
            string customerName, make, model, regNum, insurer, policyType;
            int policyNumber;
            cout << "\n" << endl;
            cout << " Thank you for choosing to register for a new policy please input details as prompted: " << endl;
            // list policy requirements 
            cout << "\n" << endl;
            cout << " Enter customer name: ";
            getline(cin, customerName);
            cout << "\n" << endl;
            cout << " Enter car make: ";
            getline(cin, make);
            cout << "\n" << endl;
            cout << " Enter car model: ";
            getline(cin, model);
            cout << "\n" << endl;
            cout << " Enter vehicle registration number: ";
            getline(cin, regNum);
            cout << "\n" << endl;
            cout << " Enter insurer name: ";
            getline(cin, insurer);

            // Policy type input and validation
            cout << "\n" << endl;
            cout << "Select policy type:";
            cout << "\n" << endl;
            cout << " 1: Full ";
            cout << "\n" << endl;
            cout << " 2: Third-Party ";
            cout << "\n" << endl;
            cout << " 3: Theft" << endl;

            while (true) {
                cout << "\n" << endl;
                cout << " Please select policy type you require : ";
                cin >> policyNumber;

                if (cin.fail() || policyNumber < 1 || policyNumber > 3) {
                    cin.clear();
                    clearInputBuffer();
                    cout << "\n" << endl;
                    cout << " Invalid input. Please enter a valid number between 1 and 3." << endl;
                }
                else {
                    clearInputBuffer();
                    break;
                }
            }

            switch (policyNumber) {
            case 1:
                policyType = "Full";
                break;
            case 2:
                policyType = "Third-Party";
                break;
            case 3:
                policyType = "Theft";
                break;
            default:
                // Validators 
                cout << " Invalid policy type. Please choose a number between 1 and 3." << endl;
                continue;  // loop for incorrect input continues to run 
            }
            // Print the entered details for confirmation

            cout << "\n Confirming entered details:" << endl;
            cout << " Customer Name: " << customerName << endl;
            cout << " Car Make: " << make << endl;
            cout << " Car Model: " << model << endl;
            cout << " Rego: " << regNum << endl;
            cout << " Insurer name: " << insurer << endl;
            cout << " Policy Type: " << policyType << endl;


            // Ask for confirmation
            char confirm;
            cout << "\n" << endl;
            cout << " Confirm details? (Y/N): ";
            cin >> confirm;
            if (toupper(confirm) != 'Y') {
                cout << "\n" << endl;
                cout << " Details not confirmed. Exiting without saving." << endl;
                break;
            }

            // Add the policy to the vector and save
            policies.emplace_back(customerName, make, model, regNum, insurer, policyType);
            policies.back().policyNumber = policyNumber;
            savePolicies(policies);
            cout << "\n" << endl;
            cout << " Insurance policy added successfully." << endl;
            break;
        }
        case 4:
            // View policies for the current user
            viewUserPolicies(policies, currentUser);
            break;
        case 5:
            cout << "Logging out..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            clearInputBuffer();
        }
    }
}
//--------------------------------------- END -----------------------------------------------------------------



// ------------------------------------- INT MAIN ---------------------------------------------------------------------
int main() {
    vector<User> users = loadUsers();
    vector<InsurancePolicy> policies = loadPolicies();
    
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
          string currentUser;
          User loggedInUser = loginUser(users, currentUser);

          if (loggedInUser.isAdmin) {
              adminMenu(users, policies);
          }
          else if (!loggedInUser.username.empty()) {
              userMenu(users, policies, currentUser);
          }
          else {
              cout << " Login failed. Please try again." << endl;
          }
          break;
      }
       case 4:

           cout << " Exiting... " << endl;
           break;
       default:
           
           cout << " Invalid choice. Please try again. " << endl;
           ;  // Clear invalid input
      }

    } while (choice != 4);;

    return 0;
}
// ---------------------------------------- END ---------------------------------------------------