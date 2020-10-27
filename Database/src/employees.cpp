#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>

#include "employees.h"
#include "bin_manip.h"

const int MAX_NAME_LENGTH = 101;

/* Employee */

Employee::Employee() {
	name_ = new char[MAX_NAME_LENGTH];
}

Employee::~Employee() {
	delete [] name_;
}

std::istream& operator>>(std::istream& ist, Employee& emp) {
	assert(ist.good());
    emp.read(ist);
	assert(!ist.fail());
	return ist;
}

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
	assert(os.good());
    emp.print(os);
	assert(!os.fail());
	return os;
}

std::ifstream& operator>>(std::ifstream& ifs, Employee& emp) {
    emp.read(ifs);
	return ifs;
}

std::ofstream& operator<<(std::ofstream& ofs, const Employee& emp) {
    emp.print(ofs);
	return ofs;
}

/* Developer */

char is_has_bonus(bool has_bonus) {
	assert(has_bonus == 1 || has_bonus == 0);
	if (has_bonus)
		return '+';
	return '-';
}

std::istream& Developer::read(std::istream& ist) {
	assert(ist.good());
    ist >> name_ >> base_salary_ >> has_bonus_;
	assert(!ist.fail());
	return ist;
}

std::ostream& Developer::print(std::ostream& os) const {
	assert(os.good());
    os << "Developer";
    os << "\nName: " << name_;
    os << "\nBase Salary: " << base_salary_;
    os << "\nHas bonus: " << (is_has_bonus(has_bonus_));
	os << '\n';
	assert(!os.fail());
	return os;
}

std::ifstream& Developer::read(std::ifstream& ifs) {
    ifs >> read_c_str(name_, MAX_NAME_LENGTH) >> read_le_int32(base_salary_) >> read_bool(has_bonus_);
    return ifs;
}

std::ofstream& Developer::print(std::ofstream& ofs) const {
    ofs << write_le_int32(1) << write_c_str(name_) << write_le_int32(base_salary_) << write_bool(has_bonus_);
    return ofs;
}
 
/* SalesManager */

std::istream& SalesManager::read(std::istream& ist) {
	assert(ist.good());
    ist >> name_ >> base_salary_ >> sold_nm_ >> price_;
	assert(!ist.fail());
	return ist;
}

std::ostream& SalesManager::print(std::ostream& os) const {
	assert(os.good());
    os << "Sales Manager";
    os << "\nName: " << name_;
    os << "\nBase Salary: " << base_salary_;
	os << "\nSold items: " << sold_nm_;
	os << "\nItem price: " << price_;
	os << '\n';
	assert(!os.fail());
	return os;
}

std::ifstream& SalesManager::read(std::ifstream& ifs) {
    ifs >> read_c_str(name_, MAX_NAME_LENGTH) >> read_le_int32(base_salary_) >> read_le_int32(sold_nm_) >> read_le_int32(price_);
    return ifs;
}

std::ofstream& SalesManager::print(std::ofstream& ofs) const {
    ofs << write_le_int32(2) << write_c_str(name_) << write_le_int32(base_salary_) << write_le_int32(sold_nm_) << write_le_int32(price_);
    return ofs;
}
 
/* EmployeesArray */

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < capacity_; i++) {
        delete employees_[i];
    }
	capacity_ = 0;
}

int32_t EmployeesArray::total_salary() const {
    int32_t sum = 0;
    for (int i = 0; i < capacity_; i++) {
        sum += employees_[i]->salary();
    }
    return sum;
}

void EmployeesArray::add(Employee *emp) {
	assert(emp != nullptr);
    employees_.push_back(emp);
	capacity_++;
}

std::ifstream& EmployeesArray::read(std::ifstream& ifs) {
    int32_t size;
    ifs >> read_le_int32(size);
    for (int32_t i = 0; i < size; i++) {
        int32_t type;
        ifs >> read_le_int32(type);
        Employee *emp;
        if (type == 1) {
            emp = new Developer();
			ifs >> (*emp);
        	add(emp);
        } 
		else if (type == 2) {
            emp = new SalesManager();
			ifs >> (*emp);
        	add(emp);
        }
		else {
			std::cout << "Unknown type\n";
			break;
		}
    }
    return ifs;
}
 
std::ifstream& operator>>(std::ifstream& ifs, EmployeesArray& emp) {
    emp.read(ifs);
	return ifs;
}

std::ostream& EmployeesArray::print(std::ostream& os) const {
	assert(os.good());
    for (int i = 0; i < capacity_; i++) {
        os << (i + 1) << ". " << (*employees_[i]);
    }
    os << "== Total salary: " << this->total_salary() << '\n' << '\n';
	assert(this->total_salary() >= 0);
	assert(!os.fail());
    return os;
}
 
std::ostream& operator<<(std::ostream& os, const EmployeesArray& emps) {
	assert(os.good());
    emps.print(os);
	assert(!os.fail());
	return os;
}
 
std::ofstream& EmployeesArray::print(std::ofstream& ofs) const {
    ofs << write_le_int32(capacity_);
    for (int i = 0; i < capacity_; i++) {
        ofs << (*employees_[i]);
    }
    return ofs;
}
 
std::ofstream& operator<<(std::ofstream& ofs, const EmployeesArray& emps) {
    emps.print(ofs);
	return ofs;
}
