//============================================================================
// Name           : CS-499 Milestone 1
// Author         : Ryan Hubbuck
// Created On     : 06/14/2023
// Last Modified  : 11/16/2024
// Description    : The purpose of this application is to allow users to 
//                  load an external file of courses and prerequisites. The
//                  courses are then sorted and users can search for a 
//                  specific course, add courses, or delete courses. For 
//                  proper functionality, the following files are required:
//                  - Course.h
//                  - CourseLoader.h
//                  - functions.h
//============================================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "CSVparser.hpp"
#include "Course.h"
#include "functions.h"
#include "CourseLoader.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<Course> courses; 
    CourseLoader loader;

    string fname, userFile, cName, cNumber, pNumber, userCourse, courseToManage, courseToDelete;
    int menuChoice = 0;
    int subMenuChoice = 0;
    bool validCourse;
    bool validNewCourse = false;
    bool validPre = false;
    bool validNewPre = true;
    bool validDelete = false;
    bool preToDelete = false;

    while (menuChoice != 9) { 
        validCourse = false;
        vector<vector<string>> content;
        vector<string> row;
        
        displayMenu();

        while (!(cin >> menuChoice)) { // validate user inputs type int
            std::cout << std::endl << "Error - enter a valid menu choice: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        switch (menuChoice) {

        case 1:
            std::cout << std::endl << "Please enter the exact file name you wish to load. (case sensitive / include .{file extension})" << endl;
            cin >> fname;
            courses = loader.loadCourses(fname);
            std::cout << std::endl << courses.size() << " courses read" << std::endl <<std::endl;
            break;

        case 2:
            // Sort courses in alphanumeric order by courseNumber
            quickSort(courses, 0, courses.size() - 1);
            std::cout << std::endl << "Here is a sample schedule:" << std::endl << std::endl;
            for (int i = 0; i < courses.size(); ++i) { 
                std::cout << courses[i].getNumber() << " - " << courses[i].getName() << std::endl;
            }
            std::cout << endl;
            break;

        case 3:
            std::cout << std::endl << "What course do you want to know about? " << std::endl;
            cin >> userCourse; 
            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), ::toupper);

            for (int i = 0; i < courses.size(); i++) {
                if (courses[i].getNumber() == userCourse) { 
                    std::cout << std::endl << courses[i].getNumber() << " - " << courses[i].getName() << std::endl;
                    std::cout << "Prerequisites: "; 
                    for (int j = 0; j < courses[i].prerequisitesSize(); ++j) {
                        std::cout << courses[i].getPrerequisite(j) << " ";
                    }
                    std::cout << std::endl << std::endl;
                    validCourse = true;
                    break;
                }
            }
            if (!validCourse) {
                std::cout << "The course you entered is not present." << std::endl << std::endl;
            }
            break;

        case 4:
            std::cout << std::endl << "Enter a course number you want to delete: " << std::endl;
            cin >> userCourse;
            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), ::toupper);
            for (int i = 0; i < courses.size(); i++) {
                if (courses[i].getNumber() == userCourse) {
                    validCourse = true;
                    courses.erase(courses.begin() + i);
                    std::cout << userCourse << " was deleted." << std::endl;
                }
            }
            if (!validCourse) {
                std::cout << "The course you entered is not present." << std::endl << std::endl;
            }
            break;

        case 5:
            std::cout << "Enter the new course's number (i.e. MATH101). " << std::endl;
            cin >> cNumber; 
            std::transform(cNumber.begin(), cNumber.end(), cNumber.begin(), ::toupper);
            std::cout << "Enter the new course's number (i.e. Reverse Engineering). " << std::endl;
            cin.ignore();
            getline(cin, cName);
           
            if ((0 < cNumber.length() && cNumber.length() < 10) && (0 < cName.length() && cName.length() < 40)) {
                validNewCourse = true;
            }
            else {
                std::cout << "You have entered invalid information. Please try again. " << std::endl;
            }

            if (validNewCourse) {
                Course newCourse;
                newCourse.setNumber(cNumber);
                newCourse.setName(cName);
                courses.push_back(newCourse);
            }
            break;

        case 6:
            std::cout << std::endl << "Enter a course number to manage it's prerequisites. " << std::endl;
            cin >> userCourse;
            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), ::toupper);

            for (int i = 0; i < courses.size(); i++) {
                if (courses[i].getNumber() == userCourse) {
                    validCourse = true;
                    while (subMenuChoice != 3) {
                        displaySubMenu();
                        while (!(cin >> subMenuChoice)) { 
                            std::cout << "Error - enter a valid menu choice: ";
                            cin.clear();
                            cin.ignore(123, '\n');
                        }

                        switch (subMenuChoice) {
                        case 1:
                            std::cout << "Enter the prerequisite's course number. " << std::endl;
                            cin >> pNumber;
                            std::transform(pNumber.begin(), pNumber.end(), pNumber.begin(), ::toupper);
                            for (int j = 0; j < courses[i].prerequisitesSize(); ++j) {
                                if (courses[i].getPrerequisite(j) == pNumber) {
                                    validNewPre = false;
                                }
                            }
                            if ((0 < pNumber.length() && pNumber.length() < 10) && validNewPre) {
                                courses[i].addPrerequisite(pNumber);
                            }
                            break;
                        case 2:
                            if (courses[i].prerequisitesSize() == 0) {
                                std::cout << "This course has no prerequisites. " << std::endl;
                                break;
                            }
                            else {
                                for (int j = 0; j < courses[i].prerequisitesSize(); ++j) {
                                    std::cout << courses[i].getPrerequisite(j) << std::endl;
                                }
                            }
                            std::cout << "Enter a prerequisite to delete. " << std::endl;
                            cin >> pNumber;
                            std::transform(pNumber.begin(), pNumber.end(), pNumber.begin(), ::toupper);
                            for (int l = 0; l < courses[i].prerequisitesSize(); ++l) {
                                if (courses[i].getPrerequisite(l) == pNumber) {
                                    courses[i].deletePrerequisite(l);
                                    validDelete = true;
                                }   
                            }
                            if (!validDelete) {
                                std::cout << "You entered an invalid prerequisite. Please try again. " << std::endl;
                            }
                            break;
                        case 3:
                            break;
                        default:
                            std::cout << "Please enter a valid menu choice. " << std::endl;
                        }
                    }
                }
            }
            if (!validCourse) {
                std::cout << "The course you entered is not present." << std::endl << std::endl;
            }
            break;

        default: 
            std::cout << std::endl << "Please enter a valid menu choice." << std::endl << std::endl;
        }
    }
    courses.clear();
    std::cout << "Good bye." << std::endl;
    return 0;
}
