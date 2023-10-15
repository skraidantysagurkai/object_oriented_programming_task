//
// Created by Rokas Sabaitis on 2023-10-01.
//

#include "TextReader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

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

TextReader::TextReader(std::string& fileName, int chunkSize) {
    readStudentDataFromCSV(fileName, chunkSize);
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

std::mutex fileMutex;  // Mutex to synchronize file reading

void TextReader::readChunkFromCSV(const std::string& fileName, std::vector<Student>& students, std::ifstream& inputFile) {
    // Acquire lock to ensure exclusive access to the file
    std::lock_guard<std::mutex> lock(fileMutex);

    // Read student data
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        std::string firstName, lastName;
        std::vector<int> grades;

        // Assuming the first two columns are First Name and Last Name
        std::getline(lineStream, firstName, ',');
        std::getline(lineStream, lastName, ',');

        // Read the grades
        int grade;
        while (lineStream >> grade) {
            grades.push_back(grade);

            // Check for the comma, and ignore it
            if (lineStream.peek() == ',') {
                lineStream.ignore();
            }
        }

        // Create a student and set the data
        Student student(firstName, lastName);
        student.setGradeData(grades);

        // Add the student to the vector
        students.push_back(student);
    }
}

void TextReader::readStudentDataFromCSV(const std::string& fileName, int chunkSize) {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        return;
    }

    // Assuming the first line contains headers, read and discard it
    std::string header;
    std::getline(inputFile, header);

    // Calculate the number of chunks
    const std::size_t fileSize = std::count(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), '\n');
    const std::size_t numChunks = (fileSize - 1) / chunkSize;

    // Create threads for each chunk
    std::vector<std::thread> threads;


    threads.reserve(numChunks);
    for (int i = 0; i < numChunks; ++i) {
        threads.emplace_back(readChunkFromCSV, fileName, std::ref(scraped_student_data), std::ref(inputFile));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    inputFile.close();
}