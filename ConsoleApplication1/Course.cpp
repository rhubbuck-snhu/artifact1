#include "Course.h"
#include <iostream>

std::string Course::getName() {
	return courseName;
}

void Course::setName(std::string cName) {
	courseName = cName;
}

std::string Course::getNumber() {
	return courseNumber;
}

void Course::setNumber(std::string cNumber) {
	courseNumber = cNumber;
}

void Course::addPrerequisite(std::string cPR) {
	if (prerequisites.size() < _maxSize) {
		prerequisites.push_back(cPR);
	}
	else {
		throw std::length_error("Maximum number of prerequisites met.");
	}
}

void Course::deletePrerequisite(int i) {
	prerequisites.erase(prerequisites.begin() + i);
}

int Course::prerequisitesSize() {
	return prerequisites.size();
}

std::string Course::getPrerequisite(int i) {
	return prerequisites[i];
}
