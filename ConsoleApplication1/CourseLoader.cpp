#include "CourseLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "CSVparser.hpp"

// Defines the primary method used to read in an external file and populate a vector with individual Course objects
// CSVparser is required for proper functionality
std::vector<Course> CourseLoader::loadCourses(std::string fname) {
    std::vector<std::string> possibleCourses; 
    std::vector<Course> validCourses;
    std::vector<Course> courses;


    try {
        std::vector<std::vector<std::string>> content;
        std::vector<std::string> row;
        std::string line, word;

        std::fstream file(fname, std::ios::in);
        if (file.is_open()) 
        {
            while (getline(file, line)) 
            {
                row.clear();

                std::stringstream str(line); 

                while (getline(str, word, ',')) {
                    row.push_back(word);
                }
                content.push_back(row); 
            }
        }
        else 
            std::cout << "Could not open the file" << std::endl << std::endl;

        for (int i = 0; i < content.size(); i++) 
        {
            Course course;

            course.setNumber(content[i][0]);
            possibleCourses.push_back(content[i][0]);

            if (content[i][1] != "") { 
                course.setName(content[i][1]);
            }

            for (int j = 0; j < content[i].size(); j++)
            {
                if (j > 1 && j < content[i].size()) { 
                    if (content[i][j] != "") { 
                        course.addPrerequisite(content[i][j]);
                    }
                }
            }
            courses.push_back(course);
            file.close();
        }

    }
    catch (csv::Error& e) { // catch any errors resulting from opening or reading the file
        std::cerr << e.what() << std::endl;
    }


    // loop through vector of all courses read in and return courses that are valid
    for (int i = 0; i < courses.size(); ++i) {
        Course currentCourse = courses[i];
        bool isValid = true; 

        if (currentCourse.prerequisitesSize() > 0) { 
            for (int j = 0; j < currentCourse.prerequisitesSize(); ++j) { 
                if (std::find(possibleCourses.begin(), possibleCourses.end(), currentCourse.getPrerequisite(j)) != possibleCourses.end()) {
                    isValid = true;
                }
                else {
                    isValid = false;
                }
            }
        }
        if (isValid) { 
            validCourses.push_back(currentCourse);
        }
    }
    return validCourses; 
}

CourseLoader::CourseLoader() {
}
