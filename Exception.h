#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
using namespace std;

class TestNotFound : public exception {
public:
	virtual const char* what() const noexcept {
		return "Test not found";
	}
};

class PassedTestNotSaved : public exception {
public:
	virtual const char* what() const noexcept {
		return "Passed test not saved";
	}
};

#endif // EXCEPTION_H
