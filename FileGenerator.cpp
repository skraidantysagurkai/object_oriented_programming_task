//
// Created by Rokas Sabaitis on 2023-10-13.
//

#include "FileGenerator.h"
#include <iostream>
#include <string>

#include <fstream>
#include <vector>
#include <thread>
#include <mutex>


FileGenerator::FileGenerator(int len) {
    generateData(len);

    const std::string fileName = "output.csv";
    const int chunkSize = 1000;  // Adjust the chunk size based on your needs

    exportStudentDataToCSV(generated_data, fileName, chunkSize);

}

void FileGenerator::generateData(int student_num) {
    for (int i = 0; i < student_num; ++i) {
        std::ostringstream oss;
        oss << "FirstName_" << i+1;
        std::string name = oss.str();
        oss << "LastName_" << i+1;
        std::string last_name = oss.str();

        Student student = Student(name, last_name);
        student.generateRandomGrades(15);
        generated_data.push_back(student);
    }
}

std::mutex fileMutex;  // Mutex to synchronize file writing

void FileGenerator::writeStudentToCSV(const Student& student, std::ofstream& outputFile) {
    outputFile << student.getFirstName() << "," << student.getLastName();
    for (int grade : student.getGradeData()) {
        outputFile << "," << grade;
    }
    outputFile << "\n";
}

void FileGenerator::writeChunkToCSV(const std::vector<Student>& students, std::ofstream& outputFile) {
    // Acquire lock to ensure exclusive access to the file
    std::lock_guard<std::mutex> lock(fileMutex);

    // Write the header if this is the first chunk
    static bool isFirstChunk = true;
    if (isFirstChunk) {
        outputFile << "First Name,Last Name";
        Student student = students[0];
        const std::vector<int>& grades = student.getGradeData();
        for (std::size_t i = 0; i < grades.size(); ++i) {
            outputFile << ",Grade_" << i + 1;
        }
        outputFile << "\n";
        isFirstChunk = false;
    }

    // Write student data to the file
    for (const auto& student : students) {
        writeStudentToCSV(student, outputFile);
    }
}

void FileGenerator::exportStudentDataToCSV(const std::vector<Student>& studentData, const std::string& fileName, int chunkSize) {
    std::ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Calculate the number of chunks
    const std::size_t dataSize = studentData.size();
    const std::size_t numChunks = (dataSize + chunkSize - 1) / chunkSize;

    // Create threads for each chunk
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < numChunks; ++i) {
        std::size_t startIdx = i * chunkSize;
        std::size_t endIdx = std::min((i + 1) * chunkSize, dataSize);

        threads.emplace_back(writeChunkToCSV, std::vector<Student>(studentData.begin() + startIdx, studentData.begin() + endIdx), std::ref(outputFile));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    outputFile.close();

    std::cout << "CSV file written successfully." << std::endl;
}