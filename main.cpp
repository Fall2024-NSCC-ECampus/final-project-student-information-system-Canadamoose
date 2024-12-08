#include "StudentManager.h"
#include <iostream>

int main() {
    StudentManager manager;
    int choice;

    do {
        std::cout << "\n--- Student Management System ---\n";
        std::cout << "1) Print all student data\n";
        std::cout << "2) Sort the list of students in alphabetical order of last name\n";
        std::cout << "3) Add a new student\n";
        std::cout << "4) Remove a student from the list\n";
        std::cout << "5) Print the data of a specific student\n";
        std::cout << "6) Delete ALL student data\n";
        std::cout << "7) Change grading scheme\n";
        std::cout << "8) Save and Exit\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: manager.PrintAllStudents(); break;
            case 2: manager.SortStudents(); break;
            case 3: manager.AddStudent(); break;
            case 4: manager.RemoveStudent(); break;
            case 5: manager.SearchStudent(); break;
            case 6: manager.DeleteAllStudents(); break;
            case 7: manager.SetWeights(); break;
            case 8: manager.SaveAndExit(); break;
            default: std::cout << "Invalid choice\n";
        }
    } while (choice != 8);

    return 0;
}
