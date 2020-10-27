#ifndef LAB11_BIN_MANIP_H
#define LAB11_BIN_MANIP_H

#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>

class read_bool {
public:
    read_bool(bool& data) : data_(data) {}
    std::istream& operator()(std::istream& ist) const;
private:
   bool& data_;
};

class write_bool {
public:
    write_bool(bool data) : data_(data) {}
    std::ostream& operator()(std::ostream& ost) const;
private:
    bool data_;
};

std::istream& operator>>(std::istream& ist, read_bool);
std::ostream& operator<<(std::ostream& ost, write_bool);


class read_le_int32 {
public:
    read_le_int32(int32_t &data) : data_(data) {}
    std::istream& operator()(std::istream& ist) const;
private:
    int32_t& data_;
};

class write_le_int32 {
public:
    write_le_int32(const int32_t data) : data_(data) {}
    std::ostream& operator()(std::ostream& ost) const;
private:
    int32_t data_;
};

std::ostream& operator<<(std::ostream& ost, write_le_int32);
std::istream& operator>>(std::istream& ist, read_le_int32);


class read_c_str {
public:
    read_c_str(char *data, size_t len) : data_(data), len_(len) {}
    std::istream& operator()(std::istream& ist) const;
private:
    char* data_;
	size_t len_;
};

class write_c_str {
public:
    write_c_str(char *data) : data_(data) {}
    std::ostream& operator()(std::ostream& ost) const;
private:
    char* data_;
};

std::istream& operator>>(std::istream& ist, read_c_str);
std::ostream& operator<<(std::ostream& ost, write_c_str);

#endif
