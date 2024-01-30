# Vehicle Insurance App
This repository contains the source code for the CH Insurance App, a simple insurance management system written in C++. The application provides functionalities for users to view available insurance policies, create accounts, log in, and make claims. Additionally, administrators have access to additional features such as managing users and policies.

## User and Policy Classes
The code defines two main classes:

User: Represents a user with attributes such as username, password, and isAdmin (admin status).
~~~
class User {
public:
    string username;
    string password;
    bool isAdmin;

    User(const string& uname, const string& pwd, bool admin)
        : username(uname), password(pwd), isAdmin(admin) {}
};
~~~

Insurance Policy: Represents an insurance policy with attributes like customer name, car details, insurer name, policy type, and policy number.
~~~
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
~~~

## Utility Functions

The application includes functions for loading/saving user and policy data to text files.

### Saving Users & Policies: 
~~~
void saveUsers(const vector<User>& users) {
    ofstream file("users.txt");
    for (const auto& user : users) {
        file << "username: " << user.username << endl;
        file << "Password: " << user.password << endl;
        file << "Admin Rights: " << user.isAdmin << endl;
    }
}

void savePolicies(const vector<InsurancePolicy>& policies) {
    ofstream file("policies.txt");
    for (const auto& policy : policies) {
        file << policy.custName << ' ' << policy.carMake << ' ' << policy.carModel << ' ' << policy.carRego << ' ' << policy.insurerName << ' ' << policy.policyType << ' ' << policy.policyNumber << endl;
    }
}
~~~

### Loading Users & Policies:

~~~
vector<User> loadUsers() {
    vector<User> users;
    ifstream file("users.txt");
    string uname, pwd;
    bool admin;
    while (file >> uname >> pwd >> admin) {
        users.emplace_back(uname, pwd, admin);
    }
    return users;
}

vector<InsurancePolicy> loadPolicies() {
    vector<InsurancePolicy> policies;
    ifstream file("policies.txt");
    string customerName, make, model, regoNum, insurer, policyType;
    int policyNumber;

    while (file >> customerName >> make >> model >> regoNum >> insurer >> policyType >> policyNumber) {
        policies.emplace_back(customerName, make, model, regoNum, insurer, policyType);
        policies.back().policyNumber = policyNumber;
    }

    return policies;
}
~~~


## Main Menu Functionality

1. View Available Policies

    Displays information about available insurance policies from a file (policy-desc.txt).

2. Create Account

    Allows users to create a new account with a unique username and password.

3. Login
   
    Enables users to log in with their credentials. Provides different menus for regular users and administrators.

4. Exit
   
    Exits the application.

## Admin Menu Functionality:

1. Add new user
  
    Allows administrators to create new users with or without admin right.

2. View all users

    Displays all users that have accounts on the app.

3. Add new insurance policy

   Allows admin to add new policies agains vehicles

4. View all policies

   Displays all policies that have been made 

5. Remove user

     Deletes users from the app 

6. Logout

     Logs out admin and returns to main menu

## Users Menu Functionality:

1. View available policies

     Displays available policies and what they cover

2. Make a claim

    Allows user to create a claim against their vehicle

3. Sign up for a new insurance policy

     Allows a user to sign up for a policy against their vehicle

4. Logout

     Allows user to logout and return to the main menu

# How to Run
Clone the repository: git clone (link to git)

Use visual studios to open the test.sln file and run the app.

Make sure you have a C++ compiler installed on your system. We recommend Visual Studios 2022
