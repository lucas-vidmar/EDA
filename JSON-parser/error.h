#pragma once
#ifndef INCLUDE_ERROR_
#define INCLUDE_ERROR_
#include <string>
#include<iostream>

using namespace std;

class JSONError
{
public:

	JSONError(bool hasFailed_ = false, const char * Desc_ = NULL) { failState = false; Desc = "No error"; }
	string getErrorString(void) { return Desc; }
	bool hasFailed(void) { return failState; }

	bool failState;
	const char* Desc;

private:


};

#endif
