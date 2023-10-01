//
// Created by Rokas Sabaitis on 2023-10-01.
//

#ifndef OP_STUDENT_H
#define OP_STUDENT_H

#include "libraries.h"

struct Student {
    std::string first_name;
    std::string last_name;
    std::vector<int> grade_data;

    Student(std::string firstName, std::string lastName);

    const std::string &getFirstName() const;

    const std::string &getLastName() const;

    // Function to add integers to the series
    void add_grade(int num);

    // Function to calculate the average of the series
    double calculateAverageGrade() const;

    // Function to calculate the median of the series
    double calculateMedianGrade();

    // Function to randomly generate a random series of grades
    void generateRandomGrades();
};

// Comparator structure for Student structure
struct studentComp {
    inline bool operator()(const Student &a, const Student &b);
};

#endif //OP_STUDENT_H
