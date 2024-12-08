#pragma once
#include <vector>
#include "Course.h"

class CourseLoader {
public:
	CourseLoader();
	std::vector<Course> loadCourses(std::string fName);
};