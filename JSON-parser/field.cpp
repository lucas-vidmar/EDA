#include "field.h"

//Setters de Field
void
Field::setFieldType(const char* s)
{
	fieldType = s;
}

void
Field::setFieldName(const char* s)
{
	fieldName = s;
}

void
Field::setContent(const char* s)
{
	content = s;
}

//Getters de Field
const char*
Field::getFieldsType(void)
{
	return fieldType;
}

const char*
Field::getFieldName(void)
{
	return fieldName;
}

const char*
Field::getContent(void)
{
	return content;
}