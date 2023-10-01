//
// Created by Rokas Sabaitis on 2023-10-01.
//

#include "TextReader.h"

// File stream parser.
// Note: Haven't tried to open other format files than .txt, however structure should work with most text documents
// with minimal adjustment.
TextReader::TextReader() {
    std::cout << "Enter the filename (Absolute path): ";
    std::cin >> file_path;

    try {
        // Call the function to read the text file
        readTextFile(file_path);
    } catch (const std::exception &e) {
        // Catch and print any exceptions that occurred
        std::cerr << e.what() << std::endl;
    }
}

void TextReader::readTextFile(const std::string &file_name) {
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

            // Create a Student object and add it to the vector
            scraped_student_data.push_back(student);
        }
    }
    // Close the file
    file.close();
}