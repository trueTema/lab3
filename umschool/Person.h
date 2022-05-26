#pragma once
#include <string>
#include <cstring>
#include <iostream>
using namespace std;


class Person
{
private:
	string id;
	string firstName;
	string middleName;
	string lastName;
	size_t p_age;
public:
	Person();
	Person(string, string, string, string, size_t);
	string getId();
	string getFirstName();
	string getMiddleName();
	string getLastName();
	size_t age();
	bool operator ==(Person);
	bool operator !=(Person);
	bool operator >(Person);
	bool operator <(Person);
	friend std::ostream& operator <<(std::ostream& os, Person& p);
};



class Student: public Person
{
public:
	Student();
	Student(string, string, string, string, size_t, string, string);
	string group();
	string dir();
	bool operator ==(Student);
	bool operator !=(Student);
	
	friend std::ostream& operator <<(std::ostream& os, Student& p);

private:
	string study_group;
	string study_dir;
};

class Teacher :public Person
{
public:
	Teacher();
	Teacher(string, string, string, string, size_t, string, int);
	string spec();
	int dept();
	bool operator ==(Teacher);
	bool operator !=(Teacher);
	friend std::ostream& operator << (std::ostream& os, Teacher& p);

private:
	string teach_spec;
	int teach_dept;
};


