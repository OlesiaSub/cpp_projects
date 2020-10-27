#include <iostream>
#include <fstream>
#include <assert.h>

#include <employees.h>

void load_array(EmployeesArray &emp, std::string &out) {
	std::ifstream ifs(out, std::ios::binary);
	ifs >> emp;
	ifs.close();
}

void save_array(EmployeesArray &emp, std::string &in) {
	std::ofstream ofs;
	ofs.open(in);
	ofs << emp;
	ofs.close();
}

int main() {
	std::string dir;
	EmployeesArray emps;
	while (std::cin >> dir) {
		if (dir == "exit") {
			return 0;
		}
		if (dir == "load") {
			std::string name_of_file;
			std::cin >> name_of_file;
			load_array(emps, name_of_file);
		} 
		else if (dir == "save") {
			std::string name_of_file;
			std::cin >> name_of_file;
			save_array(emps, name_of_file);
		}
		else if (dir == "list") {
			std::cout << emps;
		}
		else if (dir == "add") {
			int32_t type;
			std::cin >> type;
			Employee *emp;
			if (type == 1) {
				emp = new Developer;
			}
			else if (type == 2) {
				emp = new SalesManager;
			}
			else {
				std::cout << "Unknown type\n" << std::endl;
				return 0;
			}
			std::cin >> (*emp);
			emps.add(emp);
		}
		else {
			std::cout << "Unknown command\n";
		}
	}
	return 0;
}
