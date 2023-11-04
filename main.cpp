#include "libraries.h"
#include "UserInterface.h"
#include "FileGenerator.h"
#include <filesystem>

#include <chrono>

int main() {
    //UserInterface();

    //  FileGenerator(1000, "../data/gen-1000.csv");
    //  FileGenerator(10000, 5000,"../data/gen-10000.csv");
    //  FileGenerator(100000, 5000,"../data/gen-100000.csv");
    //  FileGenerator(1000000, 20000,"../data/gen-1000000.csv");
    //  FileGenerator(10000000, 20000,"../data/gen-10000000.csv");
    std::vector<std::string> filePaths = {
            "../data/gen-1000.csv",
            "../data/gen-10000.csv",
            "../data/gen-100000.csv",
            "../data/gen-1000000.csv",
            "../data/gen-10000000.csv"
    };
    for (const std::string& filePath : filePaths) {
        std::cout << filePath << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        TextReader rd = TextReader(filePath);

        auto read_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Read Time: " << read_duration.count() << " milliseconds" << std::endl;

        std::vector<Student> under_5_students;
        std::vector<Student> over_5_students;
        std::vector<Student> fileData = rd.getScrapedStudentData();
        //std::cout << fileData.size() << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (const Student &student: fileData) {
            if (student.calculateAverageGrade() < 5) {
                under_5_students.push_back(student);
            } else {
                over_5_students.push_back(student);
            }
        }
        auto sort_to_groups_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);
        std::cout << "Sort Time: " << sort_to_groups_duration.count() << " milliseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        FileGenerator(over_5_students, "../data/OverFiveStudents.csv");
        FileGenerator(under_5_students, "../data/UnderFiveStudents.csv");
        auto write_duration = std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now() - start);

        std::cout << "Write Time: " << write_duration.count() << " milliseconds" << std::endl;

        std::cout << "\n" << std::endl;
    }
    return 0;
}