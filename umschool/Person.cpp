#include "Person.h"
#include <ostream>
#include <string>

Person::Person(string id, string firstName, string middleName, string lastName, size_t age) {
	this->id = id;
	this->firstName = firstName;
	this->middleName = middleName;
	this->lastName = lastName;
	this->p_age = age;
}
Person::Person() {
	this->id = "";
	this->firstName = "";
	this->middleName = "";
	this->lastName = "";
	this->p_age = 0;
}


string Person::getId() {
	return this->id;
}
string Person::getFirstName() {
	return this->firstName;
}
string Person::getMiddleName() {
	return this->middleName;
}
string Person::getLastName() {
	return this->lastName;
}
size_t Person::age() {
	return this->p_age;
}
bool Person::operator==(Person p) {
	if (p.age() != this->age()) return false;
	if (p.getFirstName() != this->getFirstName()) return false;
	if (p.getId() != this->getId()) return false;
	if (p.getMiddleName() != this->getMiddleName()) return false;
	if (p.getLastName() != this->getLastName()) return false;
	return true;
}
bool Person::operator!=(Person p) {
	if (p.age() != this->age()) return true;
	if (p.getFirstName() != this->getFirstName()) return true;
	if (p.getId() != this->getId()) return true;
	if (p.getMiddleName() != this->getMiddleName()) return true;
	if (p.getLastName() != this->getLastName()) return true;
	return false;
}

bool Person::operator >(Person p) {
	return this->age() > p.age();
}
bool Person::operator <(Person p) {
	return this->age() < p.age();
}

//===========================
Student::Student():Person() {
	this->study_dir = "";
	this->study_group = "";
}
Student::Student(string id, string firstName, string middleName, string lastName, size_t age,
	string study_group, string study_dir) :Person(id, firstName, middleName, lastName, age)
{
	this->study_group = study_group;
	this->study_dir = study_dir;
}

string Student::group() {
	return this->study_group;
}
string Student::dir() {
	return this->study_dir;
}

bool Student::operator==(Student p) {
	if (p.age() != this->age()) return false;
	if (p.getFirstName() != this->getFirstName()) return false;
	if (p.getId() != this->getId()) return false;
	if (p.getMiddleName() != this->getMiddleName()) return false;
	if (p.getLastName() != this->getLastName()) return false;
	if (p.group() != this->group()) return false;
	if (p.dir() != this->dir()) return false;
	return true;
}

bool Student::operator!=(Student p) {
	if (p.age() != this->age()) return true;
	if (p.getFirstName() != this->getFirstName()) return true;
	if (p.getId() != this->getId()) return true;
	if (p.getMiddleName() != this->getMiddleName()) return true;
	if (p.getLastName() != this->getLastName()) return true;
	if (p.group() != this->group()) return true;
	if (p.dir() != this->dir()) return true;
	return false;
}

//================================================
Teacher::Teacher() :Person() {
	this->teach_spec = "";
	this->teach_dept = 0;
}

Teacher::Teacher(string id, string firstName, string middleName, string lastName, size_t age,
	string teach_spec, int teach_dept) :Person(id, firstName, middleName, lastName, age)
{
	this->teach_spec = teach_spec;
	this->teach_dept = teach_dept;
}

string Teacher::spec() {
	return this->teach_spec;
}
int Teacher::dept() {
	return this->teach_dept;
}

bool Teacher::operator==(Teacher p) {
	if (p.age() != this->age()) return false;
	if (p.getFirstName() != this->getFirstName()) return false;
	if (p.getId() != this->getId()) return false;
	if (p.getMiddleName() != this->getMiddleName()) return false;
	if (p.getLastName() != this->getLastName()) return false;
	if (p.spec() != this->spec()) return false;
	if (p.dept() != this->dept()) return false;
	return true;
}

bool Teacher::operator!=(Teacher p) {
	if (p.age() != this->age()) return true;
	if (p.getFirstName() != this->getFirstName()) return true;
	if (p.getId() != this->getId()) return true;
	if (p.getMiddleName() != this->getMiddleName()) return true;
	if (p.getLastName() != this->getLastName()) return true;
	if (p.spec() != this->spec()) return true;
	if (p.dept() != this->dept()) return true;
	return false;
}

std::ostream& operator << (std::ostream& os, Person &p) {
	os << std::endl << "ID: " << p.getId() << std::endl << "ФИО: " << p.getFirstName() << " " << p.getMiddleName() << " " << p.getLastName()
		<< std::endl << "Возраст: " << p.age();
	return os;
}

std::ostream& operator << (std::ostream& os, Student& p) {
	os << std::endl << "ID: " << p.getId() << endl << "ФИО: " << p.getFirstName() << " " << p.getMiddleName() << " " << p.getLastName()
		<< endl << "Возраст: " << p.age() << endl << "Специальность: " << p.dir() << endl << "Учебная группа: " << p.group();
	return os;
}

std::ostream& operator << (std::ostream& os, Teacher& p) {
	os << std::endl << "ID: " << p.getId() << endl << "ФИО: " << p.getFirstName() << " " << p.getMiddleName() << " " << p.getLastName()
		<< endl << "Возраст: " << p.age() << endl << "Специализация: " << p.spec() << endl << "Кафедра: №" << p.dept();
	return os;
}