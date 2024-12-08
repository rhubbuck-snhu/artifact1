#pragma once
#include <string>
#include <vector>

class Course {
public:
    Course() {}
    std::string getNumber();
    std::string getName();
    std::string getPrerequisite(int i);
    void setName(std::string cName);
    void setNumber(std::string cNumber);
    void addPrerequisite(std::string cPR);
    void deletePrerequisite(int i);
    int prerequisitesSize();

private:
    int _maxSize = 10;
    std::string courseNumber;
    std::string courseName;
    std::vector<std::string> prerequisites;
};

