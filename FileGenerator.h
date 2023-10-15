//
// Created by Rokas Sabaitis on 2023-10-13.
//

#ifndef OP_FILEGENERATOR_H
#define OP_FILEGENERATOR_H
#include "libraries.h"
#include <iostream>
#include <string>

#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

class FileGenerator {
public:
    FileGenerator(int chunkSize, string fileName, std::vector<Student> data);
    FileGenerator(int len, int chunkSize, string fileName);

private:
    std::vector<Student> generated_data;

    void generateData(int student_num);

    static void exportStudentDataToCSV(const std::vector<Student>& studentData,
                                const std::string& fileName, int chunkSize);

    static void writeChunkToCSV(const std::vector<Student> &students, std::ofstream &outputFile);

    static void writeStudentToCSV(const Student &student, std::ofstream &outputFile);
};


#endif //OP_FILEGENERATOR_H
