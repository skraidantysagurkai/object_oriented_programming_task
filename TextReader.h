//
// Created by Rokas Sabaitis on 2023-10-01.
//

#ifndef OP_TEXTREADER_H
#define OP_TEXTREADER_H

#include "Student.h"
#include "libraries.h"

class TextReader {
public:
    TextReader(std::string fileName, int chunkSize);
    TextReader();

    std::vector<Student> scraped_student_data;
    std::string file_path;

    const std::vector<Student> &getScrapedStudentData() const;

private:
    void readTextFile(const std::string &file_name);

    static void readChunkFromCSV(const std::string& fileName, std::vector<Student>& students, std::ifstream& inputFile);

    void readStudentDataFromCSV(const std::string &fileName, int chunkSize);
};

#endif //OP_TEXTREADER_H
