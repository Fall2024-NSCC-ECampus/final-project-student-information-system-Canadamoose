//
// Created by canad on 2024-12-04.
//

#include "StudentManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

//Implementation of Student methods
double Student::CalculateAverage(double weightMid1, double weightMid2, double weightFinal) const {
    return (grades[0] * weightMid1 + grades[1] * weightMid2 + grades[2] * weightFinal) / 100.0;
}

void Student::CalculateLetterGrade(double weightMid1, double weightMid2, double weightFinal) {
    double avg = CalculateAverage(weightMid1, weightMid2, weightFinal);
    if (avg >= 90) {letterGrade = 'A';}
    else if (avg >= 80) {letterGrade = 'B';}
    else if (avg >= 70) {letterGrade = 'C';}
    else if (avg >= 60) {letterGrade = 'D';}
    else {letterGrade = 'F';}
}

//implement a way to load from file
StudentManager::StudentManager() {
    loadFromFile();
}

void StudentManager::loadFromFile() {
    std::ifstream file("students.txt");
    if (!file) {
        std::cerr << "\nError: could not open 'students.txt'. Starting with an empty list.\n";
        return;
    }

    // while not end of file, add data to student
    while (!file.eof()) {
        auto s = std::make_unique<Student>();
        file >> s->lastName >> s->firstName >> s->studentNumber
             >> s->grades[0] >> s->grades[1] >> s->grades[2] >> s->letterGrade;

        if (file) {
            students.push_back(std::move(s));
        }
    }

    file.close();
}

//Implementing student control
void StudentManager::AddStudent() {
    auto s = std::make_unique<Student>();
    std::cout << "Enter last name: ";
    std::cin >> s->lastName;
    std::cout << "Enter first name: ";
    std::cin >> s->firstName;
    std::cout << "Enter student number: ";
    std::cin >> s->studentNumber;
    std::cout << "Enter grade for midterm #1: ";
    std::cin >> s->grades[0];
    std::cout << "Enter grade for midterm #2: ";
    std::cin >> s->grades[1];
    std::cout << "Enter grade for final: ";
    std::cin >> s->grades[2];
    s->CalculateLetterGrade(weightMid1, weightMid2, weightFinal);
    students.push_back(std::move(s));
}

void StudentManager::PrintAllStudents() {
    if (students.empty()) {
        std::cout << "No students found!\n";
        return;
    }

    // create a table-like CLI structure and populate with student data
    std::cout << std::left << std::setw(15) << "Last name"
              << std::setw(15) << "First name"
              << std::setw(15) << "Student number"
              << std::setw(10) << "Midterm #1"
              << std::setw(10) << "Midterm #2"
              << std::setw(10) << "Final"
              << "Letter Grade\n";
    for (const auto& s : students) {
        std::cout << std::left << std::setw(15) << s->lastName
                  << std::setw(15) << s->firstName
                  << std::setw(15) << s->studentNumber
                  << std::setw(10) << s->grades[0]
                  << std::setw(10) << s->grades[1]
                  << std::setw(10) << s->grades[2]
                  << std::setw(10) << s->letterGrade << "\n";
    }
}

void StudentManager::SortStudents() {
    if (students.empty()) {
        std::cout << "No students found!\n";
        return;
    }
    std::sort(students.begin(), students.end(), [](const auto& a, const auto& b) {
        return a->lastName == b->lastName ? a->firstName < b->firstName : a->lastName < b->lastName;
    });
    std::cout << "Sorted students by last name.\n";
}

void StudentManager::SearchStudent() {
    int studentNumber;
    std::cout << "Enter student number to search: ";
    std::cin >> studentNumber;

    auto it = std::find_if(students.begin(), students.end(), [studentNumber](const auto& s) {
        return s->studentNumber == studentNumber;
    });

    if (it != students.end()) {
        std::cout << (*it)->lastName << ", " << (*it)->firstName << " - Final Grade: " << (*it)->letterGrade << "\n";
    } else {
        std::cout << "No student found!\n";
    }
}

void StudentManager::RemoveStudent() {
    int studentNumber;
    std::cout << "Enter student number to remove: ";
    std::cin >> studentNumber;

    auto it = std::remove_if(students.begin(), students.end(), [studentNumber](const auto& s) {
        return s->studentNumber == studentNumber;
    });

    if (it != students.end()) {
        students.erase(it, students.end());
        std::cout << "Student removed!\n";
    } else {
        std::cout << "No student found!\n";
    }
}

void StudentManager::SetWeights() {

    std::cout << "\nCurrent weights are:\n"
              << "Midterm #1: " << weightMid1 << "\n"
              << "Midterm #2: " << weightMid2 << "\n"
              << "Final: " << weightFinal << "\n";

   std::cout << "\nEnter weight for midterm #1: ";
    std::cin >> weightMid1;
    std::cout << "Enter weight for midterm #2: ";
    std::cin >> weightMid2;
    std::cout << "Enter weight for final: ";
    std::cin >> weightFinal;

    if (weightMid1 + weightMid2 + weightFinal != 100.0) {
        std::cout << "Error: weights must add up to 100%.\n";
        weightMid1 = 25.0;
        weightMid2 = 25.0;
        weightFinal = 50.0;
    }
}

void StudentManager::DeleteAllStudents() {
    students.clear();
    std::cout << "All student data deleted.\n";
}

void StudentManager::saveToFile() {
    std::ofstream file("students.txt");
    if (!file) {
        std::cerr << "Error saving to file.\n";
        return;
    }
    for (const auto& s : students) {
        file << s->lastName << " " << s->firstName << " " << s->studentNumber << " "
             << s->grades[0] << " " << s->grades[1] << " " << s->grades[2] << " "
             << s->letterGrade << "\n";
    }
    file.close();
    std::cout << "Data saved to file.\n";
}

void StudentManager::SaveAndExit() {
    saveToFile();
    std::cout << "Saving and Exiting\n";
}