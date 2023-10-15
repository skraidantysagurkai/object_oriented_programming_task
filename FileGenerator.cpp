//
// Created by Rokas Sabaitis on 2023-10-13.
//

#include "FileGenerator.h"

std::mutex fileMutex;  // Mutex to synchronize file writing

FileGenerator::FileGenerator(int len, int chunkSize, string fileName) {
    generateData(len);
    exportStudentDataToCSV(generated_data, fileName, chunkSize);
}
FileGenerator::FileGenerator(int chunkSize, string fileName, std::vector<Student> data) {
    exportStudentDataToCSV(data, fileName, chunkSize);
}

void FileGenerator::generateData(int student_num) {
    for (int i = 0; i < student_num; ++i) {
        std::ostringstream oss;
        oss << "FirstName_" << i+1;
        std::string name = oss.str();

        std::ostringstream pss;
        pss << "LastName_" << i+1;
        std::string last_name = pss.str();

        Student student = Student(name, last_name);
        student.generateRandomGrades(15);
        generated_data.push_back(student);
    }
}

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
        const Student& student = students[0];
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
    std::remove(fileName.c_str());  // Remove the file if it exists to start fresh

    std::ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    // Calculate the number of chunks
    const std::size_t dataSize = studentData.size();
    const std::size_t numChunks = (dataSize - 1) / chunkSize;

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