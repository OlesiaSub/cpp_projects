#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "matrix.h"

using namespace std;

const int SIZE = 10;

int get_reg(const string& id) {
    return id[1] - '0';
}

int main() {
    Matrix* regs[SIZE];
    string cmd;

    for (int i = 0; i < SIZE; i++) {
        regs[i] = new Matrix(0, 0);
    }

    while (cin >> cmd) {
		try {
		    if (cmd == "exit") {
		        break;
		    } else if (cmd == "load") {
		        string id;
		        cin >> id;
		        regs[get_reg(id)]->load_matrix();
		    } else if (cmd == "print") {
		        string id;
		        cin >> id;
		        for (int i = 0; i < regs[get_reg(id)]->get_rows(); i++) {
		            for (int j = 0; j < regs[get_reg(id)]->get_cols(); j++) {
		                cout << regs[get_reg(id)]->get_data(i, j) << ' '; 
		            }
					cout << endl;
		        }
		    } else if (cmd == "add") {
		        string id_fir, id_sec;
		        cin >> id_fir >> id_sec;
		        *regs[get_reg(id_fir)] += *regs[get_reg(id_sec)];
		    } else if (cmd == "mul") {
		        string id_fir, id_sec;
		        cin >> id_fir >> id_sec;
		        *regs[get_reg(id_fir)] *= *regs[get_reg(id_sec)];

		    } else if (cmd == "elem") {
		        string id;
		        int row, col;
		        cin >> id >> row >> col;
		            cout << regs[get_reg(id)]->get_data(row, col) << endl;
		    }
		} catch (MatrixException &ex) {
			cout << ex.get() << endl;
		} catch (std::bad_alloc) {
			cout << "Unable to allocate memory." << endl;
		}
	}
	for (int i = 0; i < SIZE; i++) {
        delete regs[i];
    }
    return 0;
}
