#include "header.h"

int main() {
    string first_name;
    string last_name;
    std::string input;

    std::cout << "Hello, please insert your first name and last name: ";
    std::getline(std::cin, input);

    // Create a stringstream to separate the full name into parts
    std::istringstream iss(input);

    // Extract the first part (the name) from the stringstream
    iss >> first_name;

    // Use the remaining part of the stringstream as the last_name
    std::getline(iss, last_name);

    // Trim any leading whitespace from the last_name
    size_t pos = last_name.find_first_not_of(" \t");
    if (pos != std::string::npos) {
        last_name = last_name.substr(pos);
    }

    student stud1 (first_name, last_name);
    int grade;
    int consecutiveEmptyLines = 0;

    while (true) {
        // Prompt the user to enter an integer or press Enter to finish
        std::cout << "Enter an integer or enter generate (or press Enter to finish): ";

        // Read a line of input from the user
        std::getline(std::cin, input);

        // Check if the input is empty (an empty line)
        if (input.empty()) {
            consecutiveEmptyLines++;
            if (consecutiveEmptyLines == 2) {
                break; // Exit the loop if two consecutive empty lines are entered
            }
        } else {
            consecutiveEmptyLines = 0; // Reset the consecutive empty lines counter

            if (input == "generate") {
                stud1.generateRandomGrades(); // Generate random numbers
                break;
            } else {
                // Use a stringstream to convert the input to an integer
                std::stringstream ss(input);
                if (ss >> grade) {
                    stud1.add_grade(grade);
                } else {
                    std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                }
            }
        }
    }


    std::string operation;
    double result;
    while (true) {
        std::cout << "Choose an operation (average or median) or 'quit' to exit: ";
        std::cin >> operation;

        if (operation == "average") {
            result = stud1.average_grade();
            break; // Exit the loop if a valid operation is chosen
        } else if (operation == "median") {
            result = stud1.calculateMedian();
            break; // Exit the loop if a valid operation is chosen
        } else if (operation == "quit") {
            std::cout << "Exiting the program." << std::endl;
            return 0; // Exit the program
        } else {
            std::cerr << "Invalid operation. Please enter 'average', 'median', or 'quit'." << std::endl;
        }
    }

    // Print the table header
    std::cout << std::left << std::setw(10) << "Name" << "|"
              << std::right << std::setw(10) << "Surname" << "|"
              << std::right << std::setw(10) << operation << std::endl;

    // Print the separator line
    std::cout << std::setfill('_') << std::setw(10) << "" << "|"
              << std::setw(10) << "" << "|"
              << std::setw(10) << "" << std::setfill(' ') << std::endl;

    // Print the data
    std::cout << std::left << std::setw(10) << stud1.getFirstName() << "|"
              << std::right << std::setw(10) << stud1.getLastName() << "|"
              << std::right << std::setw(10) << std::setprecision(2) << result << std::endl;

    return 0;
}