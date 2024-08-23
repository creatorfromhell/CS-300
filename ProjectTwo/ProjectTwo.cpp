#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

void loadCourses(const std::string& filename, std::vector<Course>& courses) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string courseNumber, courseTitle, prereq;

        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses.push_back(course);
    }
}

void printCourses(const std::vector<Course>& courses) {
    std::vector<Course> sortedCourses = courses;

    std::sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    for (const auto& course : sortedCourses) {
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
    }
}

void printCourseInformation(const std::vector<Course>& courses, const std::string& courseNumber) {
    auto it = std::find_if(courses.begin(), courses.end(), [&courseNumber](const Course& course) {
        return course.courseNumber == courseNumber;
        });

    if (it != courses.end()) {
        const Course& course = *it;
        std::cout << "Course Number: " << course.courseNumber << std::endl;
        std::cout << "Course Title: " << course.courseTitle << std::endl;
        std::cout << "Prerequisites: ";
        if (course.prerequisites.empty()) {
            std::cout << "None";
        }
        else {
            for (const auto& prereq : course.prerequisites) {
                std::cout << prereq << " ";
            }
        }
        std::cout << std::endl;
    }
    else {
        std::cerr << "Error: Course number " << courseNumber << " not found." << std::endl;
    }
}

int main() {
    std::vector<Course> courses;
    int choice;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Load Data\n";
        std::cout << "2. Print Course List\n";
        std::cout << "3. Print Course Information\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string filename;
            loadCourses("CS 300 ABCU_Advising_Program_Input.csv", courses);
            break;
        }
        case 2:
            printCourses(courses);
            break;
        case 3: {
            std::string courseNumber;
            std::cout << "Enter the course number: ";
            std::cin >> courseNumber;
            printCourseInformation(courses, courseNumber);
            break;
        }
        case 9:
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cerr << "Error: Invalid choice. Please try again." << std::endl;
        }

        //clear error state to prevent issues
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (choice != 9);

    return 0;
}