/*
 * Copyright (C) 2017 Costa Paraskevopoulos.
 * Implementation of the EuclideanVector class library.
 */

#include <iostream>
#include <iterator>
#include "EuclideanVector.h"

namespace evec {

//construct a vector with 1 dimension & default magnitude = 0.0
EuclideanVector::EuclideanVector() :
	EuclideanVector{1, 0.0} { }

//construct a vector with given # dimensions & default magnitude = 0.0
EuclideanVector::EuclideanVector(size_t n_dim) :
	EuclideanVector(n_dim, 0.0) { }

//construct a vector with given # dimensions & given magnitude
EuclideanVector::EuclideanVector(size_t n_dim, Scalar mag) {
	_dimension = n_dim;
	_vector = new Scalar[_dimension];
	for (size_t i = 0; i < _dimension; ++i) _vector[i] = mag;
}

//construct a vector from a std::list iterator
EuclideanVector::EuclideanVector(std::list<Scalar>::iterator begin, std::list<Scalar>::iterator end) :
	_dimension{static_cast<size_t>(std::distance(begin, end))} {
	_vector = new Scalar[_dimension];
	int i = 0;
	while (begin != end) {
		_vector[i++] = *begin++;
	}
}

//construct a vector from a std::vector iterator
EuclideanVector::EuclideanVector(std::vector<Scalar>::iterator begin, std::vector<Scalar>::iterator end) :
	_dimension{static_cast<size_t>(std::distance(begin, end))} {
	_vector = new Scalar[_dimension];
	int i = 0;
	while (begin != end) {
		_vector[i++] = *begin++;
	}
}

//construct a vector from an initializer list
EuclideanVector::EuclideanVector(std::initializer_list<Scalar> lst) :
	_dimension{lst.size()} {
	_vector = new Scalar[_dimension];
	int i = 0;
	for (auto begin = lst.begin(); begin != lst.end(); ++begin) {
		_vector[i++] = *begin;
	}
}

//copy constructor
EuclideanVector::EuclideanVector(const EuclideanVector& e) {
	_dimension = e._dimension;
	_vector = new Scalar[_dimension];
	for (size_t i = 0; i < _dimension; ++i) _vector[i] = e._vector[i];
}

//move constructor
EuclideanVector::EuclideanVector(EuclideanVector&& e) :
	_vector{std::move(_vector)}, _dimension{std::move(_dimension)} {
	e._vector = nullptr;
	e._dimension = 0;
}

//destructor
EuclideanVector::~EuclideanVector() {
	if (_vector != nullptr) {
		delete [] _vector;
	}
}

//copy assignment operator
EuclideanVector& EuclideanVector::operator=(const EuclideanVector& e) {
	if (this != &e) {
		//delete [] _vector;
		_dimension = e._dimension;
		_vector = new Scalar[_dimension];
		for (size_t i = 0; i < _dimension; ++i) _vector[i] = e._vector[i];
	}
	return *this;
}

//move assignment operator
EuclideanVector& EuclideanVector::operator=(EuclideanVector&& e) {
	if (this != &e) {
		//delete [] _vector;
		_dimension = e._dimension;
		_vector = std::move(e._vector);
		//_vector = e._vector;
		//_vector = new Scalar[_dimension];
		//for (size_t i = 0; i < _dimension; ++i) _vector[i] = e._vector[i];
		//delete [] e._vector;
		e._vector = nullptr;
		e._dimension = 0;
	}
	return *this;
}

//print vector in the form [v1 v2 v3 ...]
std::ostream& operator<<(std::ostream &os, const EuclideanVector &v) {
	std::cout << "[";
	for (size_t i = 0; i < v._dimension; ++i) {
		if (i > 0) std::cout << " ";
		std::cout << v._vector[i];
	}
	std::cout << "]";
	return os;
}

}
