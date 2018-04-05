#pragma once

#include <iostream>
#include <string>

class NoDetectedFaceException
{
public:
	NoDetectedFaceException(const std::string& _message) : message(_message) { }
	void print() const { std::cout << message << std::endl; }
	~NoDetectedFaceException() { };

private:
	std::string message;
};

