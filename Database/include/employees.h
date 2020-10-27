#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED
 
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Employee {
public:
	Employee();
	virtual ~Employee();

	virtual int salary() const = 0;

    virtual std::istream& read(std::istream& ist) = 0;
    virtual std::ostream& print(std::ostream& ost) const = 0;
    virtual std::ifstream& read(std::ifstream& ifs) = 0;
	virtual std::ofstream& print(std::ofstream& ofs) const = 0;
 
protected:
    char *name_;
	int32_t base_salary_ = 0;
};


std::istream& operator>>(std::istream& ist, Employee&);
std::ostream& operator<<(std::ostream& ost, const Employee&);
std::ifstream& operator>>(std::ifstream& ifs, Employee&);
std::ofstream& operator<<(std::ofstream& ofs, const Employee&);


class Developer : public Employee {
public:
	Developer()=default;
    ~Developer()=default;

    int salary() const {
        int salary = base_salary_;
        if (has_bonus_) { salary += 1000; }
        return salary;
    }

    std::istream& read(std::istream& ist) override;
    std::ostream& print(std::ostream& ost) const override;
    std::ifstream& read(std::ifstream& ifs) override;
    std::ofstream& print(std::ofstream& ofs) const override;

private:
    bool has_bonus_ = false;
	int32_t type_ = 1;
};


std::istream& operator>>(std::istream& ist, Developer&);
std::ostream& operator<<(std::ostream& ost, const Developer&);
std::ifstream& operator>>(std::ifstream& ifs, Developer&);
std::ofstream& operator<<(std::ofstream& ofs, const Developer&);


class SalesManager : public Employee {
public:
	SalesManager()=default;
	SalesManager(const std::string& name, int32_t const base_salary, int32_t sold_nm, int32_t price);
    ~SalesManager()=default;

	int salary() const {
        return base_salary_ + sold_nm_ * price_ * 0.01;
    }   

	std::istream& read(std::istream& ist) override;
    std::ostream& print(std::ostream& ost) const override;
    std::ifstream& read(std::ifstream& ifs) override;
    std::ofstream& print(std::ofstream& ofs) const override;

private:
    int32_t sold_nm_;
	int32_t price_;
	int32_t type_ = 2;
};


std::istream& operator>>(std::istream& ist, SalesManager&);
std::ostream& operator<<(std::ostream& ost, const SalesManager&);
std::ifstream& operator>>(std::ifstream& ifs, SalesManager&);
std::ofstream& operator<<(std::ofstream& ofs, const SalesManager&);


class EmployeesArray {
public:
	EmployeesArray()=default;
	~EmployeesArray();

    void add(Employee *emp);
    int total_salary() const;

    std::ostream& print(std::ostream& ost) const;
    std::ifstream& read(std::ifstream& ifs);
    std::ofstream& print(std::ofstream& ofs) const;

private:
    std::vector<Employee*> employees_;
	int32_t capacity_ = 0;
};


std::ostream& operator<<(std::ostream& ost, const EmployeesArray&);
std::ifstream& operator>>(std::ifstream& ifs, EmployeesArray&);
std::ofstream& operator<<(std::ofstream& ofs, const EmployeesArray&);

#endif
