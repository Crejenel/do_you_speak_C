#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <exception>
#include <string>

using std::string;
using std::cerr;
using std::endl;
using std::exception;

class ExceptionContainer : public exception {

private:

	string message;

public:

	ExceptionContainer(const string& message) : message(message) {}

	const char* what() const noexcept override {
		return message.c_str();
	}

	string get_message() const noexcept {
		return message;
	}

	void  print_exception() const noexcept {
		cerr << "\033[31mERROR : " << message << " \033[0m" << endl;
	}

};

class ExceptionRepository : public exception {

private:
	string message;
public:

	ExceptionRepository(const string& message) : message(message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}

	string get_message() const noexcept {
		return message;
	}

	void  print_exception() const noexcept {
		cerr << "\033[31mERROR : " << message << " \033[0m" << endl;
	}
};

class ExceptionService : public exception {

private:

	string message;

public:

	ExceptionService(const string& message) : message(message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}
	string get_message() const noexcept {
		return message;
	}
	void  print_exception() const noexcept {
		cerr << "\033[31mERROR : " << message << " \033[0m" << endl;
	}
};

#endif