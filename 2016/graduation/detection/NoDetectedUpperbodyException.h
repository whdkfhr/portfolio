#pragma once

#include <iostream>
#include <string>

class NoDetectedUpperbodyException
{
public:
	NoDetectedUpperbodyException(const std::string& _message) : message(_message) { }
	void print() const { std::cout << message << std::endl; }
	~NoDetectedUpperbodyException() { };

private:
	std::string message;
};

