#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int roll;
    char name[50];
    char course[50];
    float marks;

    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Course: ";
        cin.getline(course, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\nRoll No: " << roll;
        cout << "\nName: " << name;
        cout << "\nCourse: " << course;
        cout << "\nMarks: " << marks << "\n";
    }

    int getRoll() {
        return roll;
    }
};

// Add new student
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student added successfully.\n";
}

// Display all students
void displayAll() {
    Student s;
    ifstream file("students.dat", ios::binary);
    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "--------------------\n";
    }
    file.close();
}

// Search student by roll number
void searchStudent(int roll) {
    Student s;
    ifstream file("students.dat", ios::binary);
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == roll) {
            s.display();
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student not found.\n";
    file.close();
}

// Update student by roll number
void updateStudent(int roll) {
    Student s;
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    bool found = false;
    while (!file.eof()) {
        streampos pos = file.tellg();
        file.read((char*)&s, sizeof(s));
        if (s.getRoll() == roll) {
            cout << "Old Data:\n";
            s.display();
            cout << "\nEnter New Details:\n";
            s.input();
            file.seekp(pos);
            file.write((char*)&s, sizeof(s));
            cout << "Record updated.\n";
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student not found.\n";
    file.close();
}

// Delete student
void deleteStudent(int roll) {
    Student s;
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.getRoll() != roll)
            temp.write((char*)&s, sizeof(s));
        else
            found = true;
    }

    file.close();
    temp.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted.\n";
    else
        cout << "Record not found.\n";
}

// Main menu
int main() {
    int choice;
    char repeat;
    int roll;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3:
                cout << "Enter roll number to search: ";
                cin >> roll;
                searchStudent(roll);
                break;
            case 4:
                cout << "Enter roll number to update: ";
                cin >> roll;
                updateStudent(roll);
                break;
            case 5:
                cout << "Enter roll number to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> repeat;

    } while (repeat == 'Y' || repeat == 'y');

    return 0;
}
