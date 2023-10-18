// ABCDUniversity.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <regex> // Add this line to include the <regex> header

const std::string RED_COLOR = "\033[1;31m";
const std::string GREEN_COLOR = "\033[1;32m";
const std::string YELLOW_COLOR = "\033[1;33m";
const std::string BLUE_COLOR = "\033[1;34m";
const std::string RESET_COLOR = "\033[0m"; // Reset to default color


using namespace std;

// Define the Course class with appropriate member variables and methods

class Course {
private:
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;

public:
    //std::string courseNumber;  // Define courseNumber as a string variable

    // Constructor to initialize course data
    Course(const std::string& number, const std::string& title, const std::vector<std::string>& prereqs)
        : courseNumber(number), courseTitle(title), prerequisites(prereqs) { }

    // Getter for course number
    std::string getCourseNumber() const {
        return courseNumber;
    }

    // Getter for course title
    std::string getCourseTitle() const {
        return courseTitle;
    }

    // Getter for prerequisites
    std::vector <std::string> getPrerequisites() const {
        return prerequisites;
    }

    // Add a prerequisite to the course
    void addPrerequisite(const std::string& prereq) {
        prerequisites.push_back(prereq);
    }
};
// Function to check if a course number is valid 
bool isValidCourseNumber(const std::string& courseNumber) {
    // validation logic 
    std::regex pattern("^[A-Z]{4}\\d{3}$");
    // Use std::regex_match to check if courseNumber matches the pattern
    return std::regex_match(courseNumber, pattern);
}
// Function to check if a course is already in the course list 
bool isCourseInList(const std::vector<Course>& courseList, const std::string& courseNumber) {
    // logic to check if the course already exists
    for (const Course& course : courseList) {
        if (course.getCourseNumber() == courseNumber) {
            return true; // Course found in the list
        }
    }
    return false; // Course not found in the list
    // Return true if found, false otherwise
}
// Function to load course data from a file and create course objects
void loadDataFromFile(std::vector<Course>& courseList) {
    std::string fileName;
    std::cout << "Enter the file name that contains the course data: ";
    std::cin >> fileName;
    
    std::ifstream inputFile(fileName);
    std::string line;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Failed to open " << fileName << std::endl;
        return;
    } else {
        std::cout << "File loaded" << std::endl;
    }
    while (std::getline(inputFile, line)) {
    std::string courseNumber, courseTitle;
    std::vector<std::string> prerequisites;

    // Split 'line' into courseNumber and the rest
    size_t pos = line.find(',');
    if (pos != std::string::npos) {
        courseNumber = line.substr(0, pos);
        std::string remaining = line.substr(pos + 1);

        // Check if the remaining part contains prerequisites
        if (remaining.find(',') != std::string::npos) {
            // Split the remaining part into courseTitle and prerequisites
            pos = remaining.find(',');
            courseTitle = remaining.substr(0, pos);
            remaining = remaining.substr(pos + 1);

            // Split prerequisites using ',' as the delimiter
            size_t start = 0;
            while ((pos = remaining.find(',', start)) != std::string::npos) {
                prerequisites.push_back(remaining.substr(start, pos - start));
                start = pos + 1;
            }
            prerequisites.push_back(remaining.substr(start));  // Add the last prerequisite
        } else {
            courseTitle = remaining;
        }

            // Check for valid course number
            if (!isValidCourseNumber(courseNumber)) {
                continue;  // Skip this line
            }

            // Check if the course already exists in the courseList
            if (isCourseInList(courseList, courseNumber)) {
                continue;  // Skip this line
            }

            // Create a new course object
            Course newCourse(courseNumber, courseTitle, prerequisites);
            courseList.push_back(newCourse);
        }
    }

    // Close the input file
    inputFile.close();
}

// Function to print the course list
void printCourseList(const std::vector<Course>& courses) {
    // Create a copy of the course list to sort it alphabetically
    std::vector<Course> sortedCourses = courses;
    
    // Sort the courses based on the courseTitle
    std::sort(sortedCourses.begin(), sortedCourses.end(),
              [](const Course& a, const Course& b) {
                  return a.getCourseTitle() < b.getCourseTitle();
              });

    // Print the sorted list of courses
    std::cout << "Here is a sample schedule sorted Alphabetically by course title:" << std::endl;
    for (const Course& course : sortedCourses) {
        std::cout << GREEN_COLOR << course.getCourseNumber() << ", " << course.getCourseTitle() << RESET_COLOR <<std::endl;
    }
}
// Function to print course information
void printCourseInfo(const std::vector<Course>& courses) {
    std::cout << "What course do you want to know about? ";
    std::string courseNumber;
    std::cin >> courseNumber;

    auto it = std::find_if(courses.begin(), courses.end(),
        [&courseNumber](const Course& course) {
            return course.getCourseNumber() == courseNumber;
        });
    // print prerequisites
    if (it != courses.end()) {
        std::cout << RED_COLOR << it->getCourseNumber() << ", " << it->getCourseTitle() << RESET_COLOR;
        const std::vector<std::string>& prereqs = it->getPrerequisites();
        if (!prereqs.empty()) {
            std::cout <<endl; std::cout << RED_COLOR <<"Prerequisites: "<< RESET_COLOR;
            for (size_t i = 0; i < prereqs.size(); ++i) {
                std::cout << RED_COLOR<< prereqs[i] << RESET_COLOR;
                if (i < prereqs.size() - 1) {
                    std::cout <<RED_COLOR <<", " << RESET_COLOR;
                }
            }
        }
        else {
            std::cout << RED_COLOR <<"\nPrerequisites: None" <<RESET_COLOR;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Course not found." << std::endl;
    }
}

int main() {
    std::vector<Course> courseList;

    std::cout << "Welcome to the course planner." << std::endl;

    int choice;
    std::string input;
    do {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "ABC University Course Planner" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "1. Load Data Structure" << std::endl;
        std::cout << "2. Print Course List" << std::endl;
        std::cout << "3. Print Course Details" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> input; // Prompt user for their choice
         
         // Check if the input is a numeric value
        if (std::regex_match(input, std::regex("[0-9]+"))) {
        // Convert the numeric string to an integer
        choice = std::stoi(input);
        
        switch (choice)
        {
        case 1:
            // Load Data Structure
            loadDataFromFile(courseList);
            break;
        case 2:
            // Print Course List
            printCourseList(courseList);
            break;
        case 3:
            // Print Course
            printCourseInfo(courseList);
            break;
        case 9:
            // Exit
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;
        default:
            std::cout << choice << " is not a valid option." << std::endl;
            break;
        }
        } else {
        std::cout << "Invalid input. Please enter a numeric choice." << std::endl;
        }    

    } while (choice != 9);

    return 0;
    }

