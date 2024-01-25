// -------------------------- CH INSURANCE APP -------------------------------
#include<iostream>

using namespace std;



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



// ----------------------------- DISPLAYS MAIN MENU  -------------------------
void displayMainMenu() {

    int choice;

        cout << " **** CH Insurance ****" << endl;
        cout << " ---------------------- " << endl;
        cout << " 1. View Available Policies" << endl;
        cout << " 2. Create Account" << endl;
        cout << " 3. Login" << endl;
        cout << " 4. Exit" << endl;    
        
    }
// ------------------------------- END ------------------------------------------------------



// ------------------------------------- INT MAIN ---------------------------------------------------------------------
int main() {

    int choice;

    displayMainMenu();

    choice = getUserChoice();

    switch (choice) {
    case 1:
        cout << "test" << endl;
        break;
    case 2:
        cout << "test2" << endl;
        break;
    case 3:
        cout << "test3" << endl;
        break;
    case 4:
        cout << "test4" << endl;
    } while (choice != 4);

    return 0;
}
// ---------------------------------------- END ---------------------------------------------------