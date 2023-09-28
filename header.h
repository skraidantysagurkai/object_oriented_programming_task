//
// Created by Rokas Sabaitis on 2023-09-28.
//

#ifndef OP_HEADER_H
#define OP_HEADER_H

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <iomanip>
#include <random>

using std::string;

struct student{
    string first_name;
    string last_name;
    std::vector<int> grade_data;

    student(string firstName, string lastName) : first_name(std::move(firstName)), last_name(std::move(lastName)) {}

    const string &getFirstName() const {
        return first_name;
    }

    const string &getLastName() const {
        return last_name;
    }

    // Function to add integers to the series
    void add_grade(int num) {
        grade_data.push_back(num);
    }

    // Function to calculate the average of the series
    double average_grade() {
        if (grade_data.empty()) {
            std::cerr << "Error: Cannot calculate average of an empty series." << std::endl;
            return 0.0; // Return 0 in case of an empty series
        }

        int sum = 0;
        for (int num : grade_data) {
            sum += num;
        }

        return static_cast<double>(sum) / grade_data.size();
    }

    // Function to calculate the median of the series
    double calculateMedian() {
        // Check if the vector is empty
        if (grade_data.empty()) {
            std::cerr << "Error: Cannot calculate median of an empty vector." << std::endl;
            return 0.0; // Return 0 in case of an empty vector
        }

        // Sort the vector in ascending order
        std::sort(grade_data.begin(), grade_data.end());

        // Calculate the median
        size_t size = grade_data.size();
        if (size % 2 == 0) {
            // If the size is even, take the average of the two middle elements
            double middle1 = grade_data[size / 2 - 1];
            double middle2 = grade_data[size / 2];
            return (middle1 + middle2) / 2.0;
        } else {
            // If the size is odd, return the middle element
            return grade_data[size / 2];
        }
    }

    // Function to randomly generate random series of number
    void generateRandomGrades() {

        // Seed the random number generator with a value
        std::random_device rd;
        std::mt19937 gen(rd());

        // Define a distribution for numbers between 1 and 10 (inclusive)
        std::uniform_int_distribution<int> distribution(1, 10);

        int count = distribution(gen);
        // Generate random numbers and store them in the vector
        for (int i = 0; i < count; ++i) {
            int randomNum = distribution(gen);
            add_grade(randomNum);
        }
    }
};


#endif //OP_HEADER_H
