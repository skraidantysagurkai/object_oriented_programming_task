#include "libraries.h"
#include "UserInterface.h"
#include "FileGenerator.h"
#include <filesystem>

int main() {
    //UserInterface();

    //  FileGenerator(1000, 500,"../data/gen-1000.csv");
    //  FileGenerator(10000, 5000,"../data/gen-10000.csv");
    //  FileGenerator(100000, 5000,"../data/gen-100000.csv");
    //  FileGenerator(1000000, 20000,"../data/gen-1000000.csv");
    //  FileGenerator(10000000, 20000,"../data/gen-10000000.csv");

    TextReader rd = TextReader("../data/gen-10000.csv");

    std::vector<Student> under_5_students;
    std::vector<Student> over_5_students;
    std::vector<Student> fileData = rd.getScrapedStudentData();
    //std::cout << fileData.size() << std::endl;


    for (const Student& student : fileData){
        if(student.calculateAverageGrade() < 5){
            under_5_students.push_back(student);
        } else {
            over_5_students.push_back(student);
        }
        std::cout << student.getFirstName() << std::endl;
    }

    FileGenerator(500, "../data/OverFiveStudents.csv", over_5_students);
    FileGenerator(500, "../data/UnderFiveStudents.csv", under_5_students);

    return 0;
}