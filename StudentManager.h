//
// Created by Brandon MacCallum on 2024-12-04.
//

#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <string>
#include <vector>
#include <memory>

//Struct to represent a student
struct Student {
    std::string firstName;
    std::string lastName;
    int studentNumber;
    //Array holds 2 midterms and final
    double grades[3];
    char letterGrade;

    double CalculateAverage(double weightMid1, double weightMid2, double weightFinal) const;
    void CalculateLetterGrade(double weightMid1, double weightMid2, double weightFinal);
};

//Class to manage students
class StudentManager {
private:
    std::vector<std::unique_ptr<Student>> students;
    double weightMid1 = 25.0, weightMid2 = 25.0, weightFinal = 50.0;

    void loadFromFile();
    void saveToFile();

public:
    //constructor and function definitions
    StudentManager();
    void AddStudent();
    void RemoveStudent();
    void PrintAllStudents();
    void SortStudents();
    void SearchStudent();
    void SetWeights();
    void DeleteAllStudents();
    void SaveAndExit();
};

#endif //STUDENTMANAGER_H