//
// Created by Rokas Sabaitis on 2023-10-01.
//

#ifndef OP_TEXTREADER_H
#define OP_TEXTREADER_H

#include "Student.h"
#include "libraries.h"

class TextReader {
public:
    TextReader(const std::string& fileName);
    TextReader();

    std::vector<Student> scraped_student_data;
    std::string file_path;

    std::vector<Student> &getScrapedStudentData();

private:
    void readTextFile(const std::string &file_name);

    void readStudentDataFromCSV(const std::string &fileName);
};

#endif //OP_TEXTREADER_H
