#include <iostream>
#include <iomanip>   // For table formatting
#include <string>
#include <vector>
#include <limits>    // For input validation
#include <conio.h>   // For getch() and clrscr()
using namespace std;

// Employee structure to store data
struct Employee {
    int empID;
    string name;
    double salary;
    string dateJoined;
    char gender;
    double tax;
    double loan;
    double debts;
    string role;
    string department;
    string employmentType; // Permanent/Temporary
    double hoursWorked;
    double overtime;
    double deductions;
};

// Global variables
vector<Employee> employees;
string adminPassword = "admin123"; // Admin password

// Function declarations
void clrscr() { system("CLS"); }  // Clears screen
void adminMenu();
void employeeMenu();
void displayEmployeeTable();
void addEmployee();
void modifyEmployee();
void calculateSalary(Employee &emp);
void displayMainMenu();

// Function to handle invalid inputs
void clearInvalidInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please try again.\n";
}

// Function to display data as a formatted table
void displayEmployeeTable() {
    cout << "\n---------------------------------------------------------------\n";
    cout << "| ID   | Name          | Salary   | Hours Worked | Tax   | Loan |\n";
    cout << "---------------------------------------------------------------\n";

    for (const auto &emp : employees) {
        cout << "| " << setw(5) << emp.empID
             << " | " << setw(13) << emp.name
             << " | " << setw(8) << emp.salary
             << " | " << setw(12) << emp.hoursWorked
             << " | " << setw(5) << emp.tax
             << " | " << setw(5) << emp.loan << " |\n";
    }

    cout << "---------------------------------------------------------------\n";
}

// Admin functionalities
void adminMenu() {
    string password;
    cout << "Enter Admin Password: ";
    cin >> password;

    if (password != adminPassword) {
        cout << "Invalid Password. Returning to Main Menu.\n";
        return;
    }

    int choice;
    do {
        clrscr();
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Modify Employee\n";
        cout << "3. View All Employees\n";
        cout << "4. Exit to Main Menu\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            clearInvalidInput();
            continue;
        }

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: modifyEmployee(); break;
            case 3: displayEmployeeTable(); break;
            case 4: cout << "Returning to Main Menu...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
        getch();
    } while (choice != 4);
}

// Employee functionalities
void employeeMenu() {
    int id;
    cout << "Enter your Employee ID: ";
    if (!(cin >> id)) {
        clearInvalidInput();
        return;
    }

    bool found = false;
    for (const auto &emp : employees) {
        if (emp.empID == id) {
            found = true;
            clrscr();
            cout << "--- Employee Information ---\n";
            cout << "ID: " << emp.empID << "\n";
            cout << "Name: " << emp.name << "\n";
            cout << "Salary: " << emp.salary << "\n";
            cout << "Hours Worked: " << emp.hoursWorked << "\n";
            cout << "Tax: " << emp.tax << "\n";
            cout << "Loan: " << emp.loan << "\n";
            break;
        }
    }

    if (!found) {
        cout << "Employee ID not found.\n";
    }
    getch();
}

// Add employee details
void addEmployee() {
    Employee emp;
    cout << "--- Add Employee ---\n";
    cout << "Enter Employee ID: ";
    if (!(cin >> emp.empID)) {
        clearInvalidInput();
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, emp.name);
    
    cout << "Enter Salary: ";
    if (!(cin >> emp.salary)) {
        clearInvalidInput();
        return;
    }

    cout << "Enter Date Joined: ";
    cin >> emp.dateJoined;

    cout << "Enter Gender (M/F): ";
    cin >> emp.gender;

    cout << "Enter Tax: ";
    if (!(cin >> emp.tax)) {
        clearInvalidInput();
        return;
    }

    cout << "Enter Loan: ";
    if (!(cin >> emp.loan)) {
        clearInvalidInput();
        return;
    }

    cout << "Enter Debts: ";
    if (!(cin >> emp.debts)) {
        clearInvalidInput();
        return;
    }

    cout << "Enter Role: ";
    cin.ignore();
    getline(cin, emp.role);

    cout << "Enter Department: ";
    getline(cin, emp.department);

    cout << "Enter Employment Type (Permanent/Temporary): ";
    cin >> emp.employmentType;

    cout << "Enter Hours Worked: ";
    if (!(cin >> emp.hoursWorked)) {
        clearInvalidInput();
        return;
    }

    cout << "Enter Overtime Hours: ";
    if (!(cin >> emp.overtime)) {
        clearInvalidInput();
        return;
    }

    cout << "Enter Deductions: ";
    if (!(cin >> emp.deductions)) {
        clearInvalidInput();
        return;
    }

    calculateSalary(emp);
    employees.push_back(emp);

    cout << "Employee added successfully!\n";
}

// Modify employee details
void modifyEmployee() {
    int id;
    cout << "Enter Employee ID to Modify: ";
    if (!(cin >> id)) {
        clearInvalidInput();
        return;
    }

    for (auto &emp : employees) {
        if (emp.empID == id) {
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, emp.name);

            cout << "Enter New Salary: ";
            if (!(cin >> emp.salary)) {
                clearInvalidInput();
                return;
            }

            cout << "Enter Hours Worked: ";
            if (!(cin >> emp.hoursWorked)) {
                clearInvalidInput();
                return;
            }

            cout << "Enter Overtime Hours: ";
            if (!(cin >> emp.overtime)) {
                clearInvalidInput();
                return;
            }

            cout << "Enter Deductions: ";
            if (!(cin >> emp.deductions)) {
                clearInvalidInput();
                return;
            }

            calculateSalary(emp);
            cout << "Employee details updated successfully!\n";
            return;
        }
    }

    cout << "Employee ID not found.\n";
}

// Calculate final salary based on conditions
void calculateSalary(Employee &emp) {
    double overtimePay = emp.overtime * 50; // Assume overtime is paid at $50/hour
    double deduction = emp.deductions;

    if (emp.hoursWorked > 160) { // 160 hours = standard monthly work hours
        emp.salary += (emp.hoursWorked - 160) * 30; // Extra pay for extra hours
    }

    emp.salary += overtimePay;
    emp.salary -= deduction;
}

// Main menu
void displayMainMenu() {
    int choice;
    do {
        clrscr();
        cout << "\n--- Payroll Management System ---\n";
        cout << "1. Admin Mode\n";
        cout << "2. Employee Mode\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            clearInvalidInput();
            continue;
        }

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: employeeMenu(); break;
            case 3: cout << "Exiting the program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// Main function
int main() {
    displayMainMenu();
    return 0;
}
