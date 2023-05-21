#pragma once
#ifndef INCLUDE_FIELD_
#define INCLUDE_FIELD_
#include <string>
#include<iostream>
using namespace std;

class Field
{
public:
	Field() { fieldType = ""; fieldName = ""; content = ""; }
	Field(const char * fieldType_, const char * fieldName_, const char * content_) { fieldType = fieldType_; fieldName = fieldName_; content = content_; }

	//Setters
	void setFieldType(const char* s);
	void setFieldName(const char* s);
	void setContent(const char* s);
	//Getters
	const char* getFieldsType(void);
	const char * getFieldName(void);
	const char * getContent(void);

	/*data*/
	const char * fieldType;
	const char * fieldName;
	const char * content;
};

#endif
