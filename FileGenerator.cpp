//
// Created by Rokas Sabaitis on 2023-10-13.
//

#include "FileGenerator.h"
#include <format>
#include <iostream>
#include <string>
#include <string_view>


FileGenerator::FileGenerator() {}

void FileGenerator::generateFile(int grade_num, int student_num) {
    for (int i = 0; i < student_num; ++i) {
        std::string name = std::format("FirstName_{}!\n", i+1);
        std::string last_name = std::format("LastName_{}!\n", i+1);
        Student student = Student(name, last_name)
    }
}

void generateAndWriteChunk(std::ofstream& file, size_t chunkSize) {
    std::vector<Student> students;
    students.reserve(chunkSize);

    for (size_t i = 0; i < chunkSize; ++i) {
        students.push_back({"John", "Doe", 75.5});  // Replace with your data generation logic
    }

    // Write the chunk to the file
    {
        std::lock_guard<std::mutex> lock(fileMutex);
        writeCsvChunk(students, file);
    }
}

void FileGenerator::writeCsvChunk(const std::vector<Student> &students, std::ofstream &file) {
    for (const auto& student : students) {

    }
}

void FileGenerator::writeLargeCsvParallel(const std::string& filename, size_t totalRows, size_t chunkSize, size_t numThreads) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Write header line
    file << "First Name,Last Name,Average Grade\n";

    // Measure the time it takes to write the data
    auto startTime = std::chrono::high_resolution_clock::now();

    // Create threads
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    // Distribute the totalRows among threads
    size_t rowsPerThread = totalRows / numThreads;

    // Start threads
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(generateAndWriteChunk, std::ref(file), chunkSize);
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Data written to " << filename << " successfully in " << duration << " milliseconds." << std::endl;

    // Close the file
    file.close();
}



