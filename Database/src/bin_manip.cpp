#include <iostream>
#include <fstream>
#include <cstring>
#include <stdint.h>
#include <assert.h>

#include "bin_manip.h"

#define INT_BYTES 4
#define BYTES 8

/* bool */

std::istream& read_bool::operator()(std::istream& ist) const {
    char byte;
    ist.get(byte);
	data_ = static_cast<char>(byte);
    return ist;
}

std::istream& operator>>(std::istream& ist, read_bool r) {
	return r(ist);
}

std::ostream& write_bool::operator()(std::ostream& os) const {
    os.put(static_cast<char>(data_));
	return os;
}

std::ostream& operator<<(std::ostream& os, write_bool w) {
	return w(os);
}

/* int */

std::istream& read_le_int32::operator()(std::istream& ist) const {
    unsigned char byte;
    data_ = 0;
    for (int i = 0; i < 4; i++) {
        ist >> byte;
        data_ |= byte << (i * BYTES);
    }
    return ist;
}

std::istream& operator>>(std::istream& ist, read_le_int32 r) {
	return r(ist);
}

std::ostream& write_le_int32::operator()(std::ostream& os) const {
	int32_t data_new = data_;	
	for (int32_t i = 0; i < INT_BYTES; i++) {
		os << static_cast<char>(data_new % 256);
		data_new /= 256;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, write_le_int32 w) {
	return w(os);
}

/* string */

std::istream& read_c_str::operator()(std::istream& ist) const {
	ist.getline(data_, len_, '\0');
    return ist;
}

std::istream& operator>>(std::istream& ist, read_c_str r) {
	return r(ist);
}

std::ostream& write_c_str::operator()(std::ostream& os) const {
    os.write(data_, strlen(data_) + 1);
	return os;
}

std::ostream& operator<<(std::ostream& os, write_c_str w) {
	return w(os);
}
