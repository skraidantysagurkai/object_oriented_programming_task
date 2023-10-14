//
// Created by Rokas Sabaitis on 2023-10-13.
//

#ifndef OP_FILEGENERATOR_H
#define OP_FILEGENERATOR_H
#include <format>
#include "libraries.h"

class FileGenerator {
public:
    FileGenerator();


private:
    void generateFile(int n, int student_num);
    void writeCsvChunk(const std::vector<Student> &students, std::ofstream &file);
    void writeLargeCsvParallel(const string &filename, size_t totalRows, size_t chunkSize, size_t numThreads);
};


#endif //OP_FILEGENERATOR_H
