#pragma once
#ifndef INCLUDE_JSON_
#define INCLUDE_JSON_

#define MAXCHARTYPE 10

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include "error.h"
#include "field.h"

using namespace std;



class JSONObject
{
	public:

		/*JSONObject Builders*/
		JSONObject() { fieldCount = 0; fields = NULL; }
		JSONObject(string& s);
		JSONObject(const char * s);

		/*Print function*/
		void partialPrint(void);
		void partialPrint(size_t tab = 0); //Prints only this object
		void fullPrint(void);
		void fullPrint(size_t tab); //Prints this objects and all its sub-objects
		void tabPrint(size_t tab); //printing tabs

		/*Getters*/
		size_t getObjectCount(void) { return objectCount; }
		Field* getFieldsPointer() { return fields; }
		unsigned int getFieldCount(void) { return fieldCount; }
		JSONError getError(void) { return error; }

		/*Setters*/
		void setFieldCount(unsigned int number) { fieldCount = number; }
		
		/*Other functions*/
		const char * getFieldType(const char * f);
		unsigned int getFieldSize(const char * f);
		JSONObject* getObjectsPointer() { return objects; }
		const char * getArrayType(const char * f);
		bool isFieldPresent(const char * f);
		void * copyField(const char * f);
		void * copyArrayValue(const char * f, unsigned int pos);
		void print(void);
		bool parseString(string& s);
		bool isEmpty(void);
		

	protected:

		/*Functions used in builder*/
		size_t countObjects(string& s);
		size_t countCorchetes(string& s);
		size_t countFields(string& s);
		size_t countFields(string& s, const char c);
		bool insideArray(string& big, string& small);

	private:

		/*Member data*/
		unsigned long fieldCount;
		Field* fields;
		JSONError error;
		size_t objectCount;
		JSONObject* objects;
};

#endif