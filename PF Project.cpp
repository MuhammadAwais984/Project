#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string name;
    string rollNumber;
    string cnic;
    string fatherName;
    string department;
    string area;
    string gender;
    string dateOfBirth;
    float gpa;
};

void signUp() {
    Student student;
    ofstream outputFile("students.txt", ios::app); // Open file in append mode

    cout << "Enter Name: ";
    cin >> student.name;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cout << "Enter CNIC: ";
    cin >> student.cnic;
    cout << "Enter Father's Name: ";
    cin >> student.fatherName;
    cout << "Enter Department: ";
    cin >> student.department;
    cout << "Enter Area: ";
    cin >> student.area;
    cout << "Enter Gender: ";
    cin >> student.gender;
    cout << "Enter Date of Birth (DD/MM/YYYY): ";
    cin >> student.dateOfBirth;
    cout << "Enter GPA: ";
    cin >> student.gpa;

    if (outputFile.is_open()) {
        outputFile << student.name << " " << student.rollNumber << " " << student.cnic << " "
                   << student.fatherName << " " << student.department << " " << student.area << " "
                   << student.gender << " " << student.dateOfBirth << " " << student.gpa << endl;
        outputFile.close();
        cout << "Student record added successfully!" << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

void displayAllRecords() {
    ifstream inputFile("students.txt");
    Student student;

    if (!inputFile.is_open()) {
        cerr << "Unable to open file." << endl;
        return;
    }

    cout << "Student Records:\n";
    cout << "----------------------------------------------\n";
    while (inputFile >> student.name >> student.rollNumber >> student.cnic >> student.fatherName 
           >> student.department >> student.area >> student.gender >> student.dateOfBirth >> student.gpa) {
        cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber 
             << ", CNIC: " << student.cnic << ", Father's Name: " << student.fatherName 
             << ", Department: " << student.department << ", Area: " << student.area 
             << ", Gender: " << student.gender << ", DOB: " << student.dateOfBirth 
             << ", GPA: " << student.gpa << endl;
    }
    inputFile.close();
}

void searchStudent(const string& rollNumber) {
    ifstream inputFile("students.txt");
    Student student;
    bool found = false;

    if (!inputFile.is_open()) {
        cerr << "Unable to open file." << endl;
        return;
    }

    while (inputFile >> student.name >> student.rollNumber >> student.cnic >> student.fatherName 
           >> student.department >> student.area >> student.gender >> student.dateOfBirth >> student.gpa) {
        if (student.rollNumber == rollNumber) {
            cout << "Student Found:\n";
            cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber 
                 << ", CNIC: " << student.cnic << ", Father's Name: " << student.fatherName 
                 << ", Department: " << student.department << ", Area: " << student.area 
                 << ", Gender: " << student.gender << ", DOB: " << student.dateOfBirth 
                 << ", GPA: " << student.gpa << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student not found." << endl;
    }
    inputFile.close();
}

void updateRecord(const string& rollNumber) {
    ifstream inputFile("students.txt");
    ofstream tempFile("temp.txt");
    Student student;
    bool found = false;

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Unable to open file." << endl;
        return;
    }

    while (inputFile >> student.name >> student.rollNumber >> student.cnic >> student.fatherName 
           >> student.department >> student.area >> student.gender >> student.dateOfBirth >> student.gpa) {
        if (student.rollNumber == rollNumber) {
            cout << "Updating record for Roll Number: " << rollNumber << endl;
            cout << "Enter new Name: ";
            cin >> student.name;
            cout << "Enter new CNIC: ";
            cin >> student.cnic;
            cout << "Enter new Father's Name: ";
            cin >> student.fatherName;
            cout << "Enter new Department: ";
            cin >> student.department;
            cout << "Enter new Area: ";
            cin >> student.area;
            cout << "Enter new Gender: ";
            cin >> student.gender;
            cout << "Enter new Date of Birth (DD/MM/YYYY): ";
            cin >> student.dateOfBirth;
            cout << "Enter new GPA: ";
            cin >> student.gpa;
            found = true;
        }
        tempFile << student.name << " " << student.rollNumber << " " << student.cnic << " "
                 << student.fatherName << " " << student.department << " " << student.area << " "
                 << student.gender << " " << student.dateOfBirth << " " << student.gpa << endl;
    }

    inputFile.close();
    tempFile.close();

    // Replace old file with updated one
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "Record updated successfully!" << endl;
    } else {
        cout << "No record found for Roll Number: " << rollNumber << endl;
    }
}

void removeRecord(const string& rollNumber) {
    ifstream inputFile("students.txt");
    ofstream tempFile("temp.txt");
    Student student;
    bool found = false;

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Unable to open file." << endl;
        return;
    }

    while (inputFile >> student.name >> student.rollNumber >> student.cnic >> student.fatherName 
           >> student.department >> student.area >> student.gender >> student.dateOfBirth >> student.gpa) {
        if (student.rollNumber != rollNumber) {
            tempFile << student.name << " " << student.rollNumber << " " << student.cnic << " "
                     << student.fatherName << " " << student.department << " " << student.area << " "
                     << student.gender << " " << student.dateOfBirth << " " << student.gpa << endl;
        } else {
            found = true;
        }
    }

    inputFile.close();
    tempFile.close();

    // Replace old file with updated one
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "Record removed successfully!" << endl;
    } else {
        cout << "No record found for Roll Number: " << rollNumber << endl;
    }
}

void displayGPAReport() {
    ifstream inputFile("students.txt");
    Student student;
    float highestGPA = 0.0, lowestGPA = 4.0; // Assuming GPA is between 0.0 and 4.0
    int totalStudents = 0;
    float totalGPA = 0.0;

    if (!inputFile.is_open()) {
        cerr << "Unable to open file." << endl;
        return;
    }

    while (inputFile >> student.name >> student.rollNumber >> student.cnic >> student.fatherName 
           >> student.department >> student.area >> student.gender >> student.dateOfBirth >> student.gpa) {
        totalGPA += student.gpa;
        totalStudents++;
        if (student.gpa > highestGPA) {
            highestGPA = student.gpa;
        }
        if (student.gpa < lowestGPA) {
            lowestGPA = student.gpa;
        }
    }

    inputFile.close();

    if (totalStudents > 0) {
        cout << "Highest GPA: " << highestGPA << endl;
        cout << "Lowest GPA: " << lowestGPA << endl;
        cout << "Average GPA: " << (totalGPA / totalStudents) << endl;
    } else {
        cout << "No records found." << endl;
    }
}

int main() {
    int choice;
    string rollNumber;

    do {
        cout << "\nStudent Database Menu:\n";
        cout << "1. Sign Up [Please use underscore for spaces] \n";
        cout << "2. Display All Records\n";
        cout << "3. Search Student\n";
        cout << "4. Update Record\n";
        cout << "5. Remove Record\n";
        cout << "6. Display GPA Report\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signUp(); // Add new student record
                break;
            case 2:
                displayAllRecords(); // Display all student records
                break;
            case 3:
                cout << "Enter Roll Number to search: ";
                cin >> rollNumber;
                searchStudent(rollNumber); // Search for a student
                break;
            case 4:
                cout << "Enter Roll Number to update: ";
                cin >> rollNumber;
                updateRecord(rollNumber); // Update student record
                break;
            case 5:
                cout << "Enter Roll Number to remove: ";
                cin >> rollNumber;
                removeRecord(rollNumber); // Remove student record
                break;
            case 6:
                displayGPAReport(); // Display GPA report
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 7);

    return 0; // Successful execution
}
