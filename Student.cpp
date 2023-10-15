//
// Created by Rokas Sabaitis on 2023-10-01.
//
#include "libraries.h"
#include "Student.h"
#include <mutex>

std::mutex gradeMutex;

Student::Student(std::string firstName, std::string lastName)
        : first_name(std::move(firstName)), last_name(std::move(lastName)) {}

const std::string &Student::getFirstName() const {
    return first_name;
}

const std::string &Student::getLastName() const {
    return last_name;
}

const std::vector<int> &Student::getGradeData() const {
    return grade_data;
}

void Student::add_grade(int num) {
    std::lock_guard<std::mutex> lock(gradeMutex);
    grade_data.push_back(num);
}

void Student::setGradeData(const std::vector<int>& grades) {
    grade_data = grades;
}

double Student::calculateAverageGrade() const {
    if (grade_data.empty()) {
        std::cerr << "Error: Cannot calculate average of an empty series." << std::endl;
        return 0.0; // Return 0 in case of an empty series
    }

    int sum = 0;
    for (int num: grade_data) {
        sum += num;
    }
    return static_cast<double>(sum) / grade_data.size(); // NOLINT(*-narrowing-conversions)
}

double Student::calculateMedianGrade() {
    if (grade_data.empty()) {
        std::cerr << "Error: Cannot calculate median of an empty vector." << std::endl;
        return 0.0; // Return 0 in case of an empty vector
    }

    std::sort(grade_data.begin(), grade_data.end());

    size_t size = grade_data.size();
    if (size % 2 == 0) {
        double middle1 = grade_data[size / 2 - 1];
        double middle2 = grade_data[size / 2];
        return (middle1 + middle2) / 2.0;
    } else {
        return grade_data[size / 2];
    }
}

void Student::generateRandomGrades(int num_of_grades) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    if (num_of_grades == 0){
        num_of_grades = distribution(gen);
    }

    for (int i = 0; i < num_of_grades; ++i) {
        int randomNum = distribution(gen);
        add_grade(randomNum);
    }
}

bool studentComp::operator()(const Student &a, const Student &b) {
    if (a.first_name == b.first_name) {
        return a.last_name < b.last_name;
    } else {
        return a.first_name < b.first_name;
    }
}