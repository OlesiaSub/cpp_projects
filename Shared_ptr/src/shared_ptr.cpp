#include <algorithm>

#include "matrix.hpp"
#include "shared_ptr.hpp"

shared_ptr::shared_ptr(Matrix *obj) {
	this->storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr &other) {
	this->storage_ = other.storage_;
	this->storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
	this->storage_->decr();
	this->storage_ = other.storage_;
	this->storage_->incr();
	return *this;
}

shared_ptr::~shared_ptr() {
	this->storage_->decr();
}

Matrix* shared_ptr::ptr() const {
	return this->storage_->getObject();
}

bool shared_ptr::isNull() const {
	return this->storage_->getObject() == 0;
}

void shared_ptr::reset(Matrix *obj) {
	this->storage_->decr();
	this->storage_ = new Storage(obj);
}

Matrix* shared_ptr::operator->() const {
	return this->storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
	return *(this->storage_->getObject());
}

shared_ptr::Storage::Storage(Matrix* matrix) {
	this->data_ = matrix;
	this->ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
	delete this->data_;
}

void shared_ptr::Storage::incr() {
	this->ref_count_++;
}

void shared_ptr::Storage::decr(){
	this->ref_count_--;
	if (this->ref_count_ == 0)
		delete this;
}

int shared_ptr::Storage::getCounter() const {
	return this->ref_count_;
}

Matrix* shared_ptr::Storage::getObject() const {
	return this->data_;
}
