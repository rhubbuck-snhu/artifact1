#include <vector>
#include <string>
#include "functions.h"
#include "Course.h"
#include <iostream>

// Function to partition objects before use in quickSort
int partition(std::vector<Course>& courses, int begin, int end) {
    int low = begin;
    int high = end;

    // ensure overflow does not occur
    std::string pivot = courses[static_cast<std::vector<Course, std::allocator<Course>>::size_type>(low) + (static_cast<unsigned long long>(high) - low) / 2].getNumber();
    bool done = false; 

    while (!done) { 
        while (courses[low].getNumber().compare(pivot) < 0) {  
            ++low; 
        }

        while (courses[high].getNumber().compare(pivot) > 0) {
            --high; 
        }

        if (low >= high) { 
            done = true;
        }
        else { 
            std::swap(courses.at(low), courses.at(high));
            ++low; 
            --high; 
        }
    }
    return high; 
}

// Function to sort objects by courseNumber using the quickSort algorithm
void quickSort(std::vector<Course>& courses, int begin, int end) {
    int mid = 0;

    if (begin >= end) {
        return;
    }

    mid = partition(courses, begin, end); 
    quickSort(courses, begin, mid); 
    quickSort(courses, mid + 1, end); 
}

// Function to display the user menu
void displayMenu() {
    std::cout << std::string(32, '*') << std::endl;
    std::cout << "* Course Planner Main Menu:    *" << std::endl;
    std::cout << "*" <<  std::string(30, '_') << "*" << std::endl;
    std::cout << "*  1. Load Data Structure.     *" << std::endl;
    std::cout << "*  2. Print Course List.       *" << std::endl;
    std::cout << "*  3. Print Course.            *" << std::endl;
    std::cout << "*  4. Delete a Course.         *" << std::endl;
    std::cout << "*  5. Add a new Course.        *" << std::endl;
    std::cout << "*  6. Manage Prerequisites.    *" << std::endl;
    std::cout << "*  9. Exit                     *" << std::endl;
    std::cout << std::string(32, '*') << std::endl;
    std::cout << std::endl <<  "Enter an option: ";
}

// Function to display user submenu
void displaySubMenu() {
    std::cout << std::string(28, '*') << std::endl;
    std::cout << "*  1. Add prerequisite.    *" << std::endl;
    std::cout << "*  2. Delete prerequisite. *" << std::endl;
    std::cout << "*  3. Exit.                *" << std::endl;
    std::cout << std::string(28, '*') << std::endl;
    std::cout << "Enter an option:";
}