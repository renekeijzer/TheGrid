#pragma once
#include <exception>
#include <string>
class AnalyticsException : public std::exception{
public:
	AnalyticsException(){}
	AnalyticsException(std::string mess) : mes(mess){}

	const char * what() const throw() { return mes.c_str(); }

private:
	std::string mes = "An Analytics exception occured, undefine ANALYTICS or check the problem";

};