//
// Created by Rokas Sabaitis on 2023-10-13.
//

#ifndef OP_FILEGENERATOR_H
#define OP_FILEGENERATOR_H
#include <format>
#include "libraries.h"

class FileGenerator {
public:
    FileGenerator(int len);


private:
    std::vector<Student> generated_data;

    void generateData(int student_num);
    void exportStudentDataToCSV(const std::vector<Student>& studentData,
                                const std::string& fileName, int chunkSize);

    static void writeChunkToCSV(const std::vector<Student> &students, std::ofstream &outputFile);

    static void writeStudentToCSV(const Student &student, std::ofstream &outputFile);
};


#endif //OP_FILEGENERATOR_H
