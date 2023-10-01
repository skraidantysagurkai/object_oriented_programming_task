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
#include <fstream>
#include <stdexcept>
#include <algorithm>


using std::string;

struct Student{
    string first_name;
    string last_name;
    std::vector<int> grade_data;

    Student(string firstName, string lastName) : first_name(std::move(firstName)), last_name(std::move(lastName)) {}

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
    double calculateAverageGrade() {
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
    double calculateMedianGrade() {
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

    // Function to randomly generate a random series of grades
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

// Comparator structure for Student structure
struct studentComp
{
    inline bool operator() (const Student& a, const Student& b)
    {
        if (a.first_name == b.first_name){
            return a.last_name < b.last_name;
        } else {
            return a.first_name < b.first_name;
        }
    }
};

// File stream parser.
// Note: Haven't tried to open other format files than .txt, however structure should work with most text documents
// with minimal adjustment.
class TextReader{
public:
    std::vector<Student> scraped_student_data;
    string file_path;

    TextReader() {
        std::cout << "Enter the filename (Absolute path): ";
        std::cin >> file_path;

        try {
            // Call the function to read the text file
            readTextFile(file_path);
        } catch (const std::exception& e) {
            // Catch and print any exceptions that occurred
            std::cerr << e.what() << std::endl;
        }
    }

private:
    void readTextFile(const std::string& file_name) {
        // Attempt to open the file
        std::ifstream file(file_name);

        // Check if the file is open
        if (!file.is_open()) {
            throw std::runtime_error("Error: Unable to open file.");
        }

        // Skip the first line
        std::string dummyLine;
        std::getline(file, dummyLine);

        std::string line;
        // Read contents of file
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, surname;

            // Extract name and surname
            if (iss >> name >> surname) {
                int grade;
                Student student(name, surname);
                // Extract grades
                while (iss >> grade) {
                    student.add_grade(grade);
                }

                // Create a Person object and add it to the vector
                scraped_student_data.push_back(student);
            }
        }
        // Close the file
        file.close();
    }

};

class UserInterface{
public:
    UserInterface() {
        Greet();
        string insert_method = dataInsertMethod();

        if(insert_method == "manual"){
            // Executing series of events if user chooses manual insertion
            std::pair<std::string, std::string> user_output = userInsertMethod();

            Student student(user_output.first, user_output.second);
            manualGradeInsertion(student);

            std::pair<std::string, double> aggregated_data = manualGradeAggregationOperation(student);
            printUserContent(student, aggregated_data);
        } else {
            TextReader parser;
            printFileContent(parser.scraped_student_data);
        }
    }

private:
    static void Greet(){ std::cout << "Hello, this program is made for a University project\n\n";}

    // Function to check what data insert method the user has chosen
    static string dataInsertMethod(){
        std::string input;

        while(true){
            std::cout << "Please choose an insert method, either manual or file: ";
            std::getline(std::cin, input);

            if (input == "manual" or input == "file"){
                break;
            } else {
                std::cout << "Invalid Input, check that you wrote manual or file correctly." << std::endl;
            }
        }
        return input;
    }

    // Function to manually insert student data
    static std::pair<std::string, std::string> userInsertMethod() {

        string first_name;
        string last_name;
        std::string input;

        std::cout << "Please insert your first name and last name: ";
        std::getline(std::cin, input);

        // Create a stringstream to separate the full name into parts
        std::istringstream iss(input);

        // Extract the first part (the name) from the stringstream
        iss >> first_name;

        // Use the remaining part of the stringstream as the last_name
        std::getline(iss, last_name);

        // Trim any leading whitespace from the last_name
        size_t pos = last_name.find_first_not_of(" \t");
        if (pos != std::string::npos) {
            last_name = last_name.substr(pos);
        }

        return std::make_pair(first_name, last_name);
    }

    // Function to either manually insert grades or have them generated
    // Calls checkIfGenerate() and addUserGrades()
    static void manualGradeInsertion(Student& student){
        bool is_generate = checkIfGenerate();

        if(is_generate){
            student.generateRandomGrades();
        } else {
            addUserGrades(student);
        }
    }

    static bool checkIfGenerate() {
        string input;

        while(true){
            std::cout << "Enter a insert method: manual or generate: ";
            std::getline(std::cin, input);

            if (input == "generate") {
                return true;
            } else if (input == "manual"){
                return false;
            } else {
                std::cout << "Invalid input. Please enter either manual or generate." << std::endl;
            }
        }
    }

    static void addUserGrades(Student& student){
        int consecutiveEmptyLines = 0;
        int grade;

        while(true){
            std::cout << "Enter an integer or press Enter twice to finish: ";
            string input;

            // Read a line of input from the user
            std::getline(std::cin, input);

            // Check if the input is empty (an empty line)
            if (input.empty()) {
                consecutiveEmptyLines++;
                if (consecutiveEmptyLines == 2) {
                    break; // Exit the loop if two consecutive empty lines are entered
                }
            } else {
                consecutiveEmptyLines = 0; // Reset the consecutive empty lines counter

                // Use a stringstream to convert the input to an integer
                std::stringstream ss(input);
                if (ss >> grade) {
                    student.add_grade(grade);
                } else {
                    std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                }
            }
        }
    }

    // Function to either average grades or median them
    static std::pair<std::string, double> manualGradeAggregationOperation(Student& student){
        std::string operation;

        while (true) {
            std::cout << "Choose an operation (average or median) or 'quit' to exit: ";
            std::cin >> operation;

            if (operation == "average") {
                return std::make_pair(operation, student.calculateAverageGrade());
            } else if (operation == "median") {
                return std::make_pair(operation, student.calculateMedianGrade());
            } else if (operation == "quit") {
                std::cout << "Exiting the program, goodbye." << std::endl;
                std::exit(0);
            } else {
                std::cerr << "Invalid operation. Please enter 'average', 'median', or 'quit'." << std::endl;
            }
        }
    }

    // Printing user inserted content
    static void printUserContent(const Student& student, const std::pair<std::string, double>& aggregated_data){

        // Print the table header
        std::cout << std::left << std::setw(30) << "Name" << "|"
                  << std::right << std::setw(30) << "Surname" << "|"
                  << std::right << std::setw(15) << aggregated_data.first << std::endl;

        // Print the separator line
        std::cout << std::setfill('_') << std::setw(30) << "" << "|"
                  << std::setw(30) << "" << "|"
                  << std::setw(15) << "" << std::setfill(' ') << std::endl;

        // Print the data
        std::cout << std::left << std::setw(30) << student.getFirstName() << "|"
                  << std::right << std::setw(30) << student.getLastName() << "|"
                  << std::right << std::setw(15) << std::setprecision(2) << aggregated_data.second << std::endl;

    }

    // Printing file content
    static void printFileContent(std::vector<Student>& student_list){
        // Sort the vector by first_name and last_name
        std::sort(student_list.begin(), student_list.end(), studentComp());

        // Print header
        std::cout << std::left << std::setw(30) << "Name" << "|"
                  << std::right << std::setw(30) << "Surname" << "|"
                  << std::right << std::setw(15) << "Avg. Grade" << "|"
                  << std::right << std::setw(15) << "Med. Grade" << std::endl;

        for(Student student : student_list){
            // Print the separator line
            std::cout << std::setfill('_') << std::setw(30) << "" << "|"
                      << std::setw(30) << "" << "|"
                      << std::setw(15) << "" << "|"
                      << std::setw(15) << "" << std::setfill(' ') << std::endl;

            // Print the data
            std::cout << std::left << std::setw(30) << student.getFirstName() << "|"
                      << std::right << std::setw(30) << student.getLastName() << "|"
                      << std::right << std::setw(15) << std::setprecision(2) << student.calculateAverageGrade() << "|"
                      << std::right << std::setw(15) << std::setprecision(2) << student.calculateMedianGrade() << std::endl;
        }
    }
};

#endif //OP_HEADER_H
