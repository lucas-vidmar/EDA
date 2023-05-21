#include "json.h"

JSONObject::JSONObject(string& s) {

	fields = NULL; //better be careful
	objects = NULL;

	if (!parseString(s)) //evaluo si el json no presenta errores de forma
	{
		return;
	}
	
	s.erase(0, 1); //borramos el primer corchete
	s.pop_back(); //borramos el ultimo corchete

	objectCount = countObjects(s); //counting subObjects

	string objArr;
	size_t pos_ = 0, pos2_ = 0, oC_ = 0, arrObjCount = 0;
	for (int i = 0; i < objectCount; i++) {
		if (s.find("}]", pos_ + 1) != s.npos) {
			arrObjCount++; //counting how many objects arrays there are
			pos_ = s.find("}]", pos2_); //finding end
			pos2_ = s.rfind("[", pos_); //finding start of that array
		}	
	}
	pos_ = 0, pos2_ = 0, oC_ = 0; //resetting
	for (int i = 0; i < objectCount; i++) {
		if (s.find("}]", pos_ + 1) != s.npos) { //object array found
			pos_ = s.find("}]", pos2_); //finding end
			pos2_ = s.rfind("[", pos_); //finding start of that array
			objArr = s.substr(pos2_, pos_ - pos2_ + 2); //taking the array
			oC_ = oC_ + countObjects(objArr); //counting objects in array
			objects = new JSONObject[arrObjCount];
			JSONObject sub1(objArr); //treating array as object
			*(objects + i) = sub1;
		}
	}

	objectCount = objectCount - oC_; //not counting objects in array

	string s2 = s, s3 = s;
	
	if (objectCount != 0) { //primero crearemos los sub objetos
		this->setFieldCount(objectCount);
		fields = new Field[objectCount];

		if (objects == NULL) //no hay arrays de objetos
			objects = new JSONObject[objectCount]; //allocating memory for sub objects
		else { //adding space for other objects
			JSONObject* objects_c = new JSONObject[objectCount + arrObjCount]; //space for objects from array and not array
			memcpy(objects_c, objects, arrObjCount * sizeof(JSONObject));
			objects = objects_c;
		}

		size_t startingPos = 0, endingPos = 0;

		for (int i = 0; i < objectCount; i++) { //creating each sub object

			do {
				startingPos = s.find('{', endingPos); //looking for opening bracket after last objects closing bracket
				endingPos = s.find('}', startingPos); //looking for closing bracket after opening bracket

				s2 = s.substr(startingPos, endingPos - startingPos + 1); //creating aux string
				while (countCorchetes(s2) != 0) { //didnt take the right bracket
					endingPos = s.find('}', endingPos + 1); //looking for new closing bracket
					s2 = s.substr(startingPos, endingPos - startingPos + 1); //redefining aux string
				}
			} while (insideArray(s,s2)); //si el objeto esta dentro de un array, buscamos otro

			JSONObject sub(s2); //we have a complete new object
			*(objects + i + arrObjCount) = sub; //dont override arrobj

			s3.erase(s3.find(s2) - 2, s2.size() + 3); //creating string without the object

			size_t pos = s.rfind('"', startingPos - 3); //look for starting quote of name
			size_t length = s.find('"', pos + 1) - pos - 1;
			string fieldName = s.substr(pos + 1, length);
			fieldName = fieldName + '\0';

			string s4 = s2 + '\0'; //string de impresion

			//creating space for contents
			void* content_ = new char[s4.size()];
			memcpy(content_, s4.c_str(), s4.size() * sizeof(char));
			void* fieldType_ = new char[MAXCHARTYPE];
			memcpy(fieldType_, "object", MAXCHARTYPE * sizeof(char));
			void* fieldName_ = new char[fieldName.size()];
			memcpy(fieldName_, fieldName.c_str(), fieldName.size() * sizeof(char));

			(fields + i)->content = (const char*)content_;
			(fields + i)->fieldType = (const char*)fieldType_;
			(fields + i)->fieldName = (const char*)fieldName_;
		}
		/*ended creation of subobjects*/
		this->objectCount = this->objectCount + arrObjCount;
	}

	/*creating every other thing different than objects*/
	size_t fieldCount_c = countFields(s3) - countFields(objArr); //counting fields (dont take the objects inside array)
	this->fieldCount = fieldCount_c + this->getFieldCount();
	if (fields == NULL) //if field wasnt created before
		fields = new Field[fieldCount_c];
	else { //there are already objects
		Field* field_c = new Field[this->fieldCount]; //creating auxiliary field array with space for objects and non objects
		memcpy(field_c,fields,objectCount*sizeof(Field));
		fields = field_c;
	}

	//example: \"value1\":2,\"string1\":\"holaprueba\"
	int startPos = 0, endPos = -1;
	string fName, value;
	for (int i = objectCount - arrObjCount; i < this->fieldCount; i++) { //setting fields after objects
		do {
			startPos = s3.find('"', endPos + 1); //finding starting quote for value
			endPos = s3.find('"', startPos + 1); //finding ending quote for value
		} while (s3[endPos + 1] != ':'); //validating that is actually a name
		fName = s3.substr(startPos, endPos - startPos + 1); fName.erase(0, 1); fName.pop_back(); //copying name and taking out quotes
		fName = fName + '\0'; //le agrego terminador por las dudas

		size_t valEnd = s3.find(',', endPos);
		if (valEnd != s3.npos) { //si hay una coma
			if (s3[endPos + 2] != '[') //y no es un array
				value = s3.substr(endPos + 2, valEnd - (endPos + 2)); //hasta la coma
			else {
				valEnd = s3.find(']', endPos);
				value = s3.substr(endPos + 2, valEnd - (endPos + 1)); //hasta fin del array
				endPos = valEnd; //updating endpos for next time
			}	
		}
		else
			value = s3.substr(endPos + 2); //sino es hasta el final

		value = value + '\0'; //le agrego terminador por las dudas 

		/*alocating space for member data*/
		void* content_ = new char[value.size()];
		memcpy(content_, value.c_str(), value.size() * sizeof(char));
		void* fieldType_ = new char[MAXCHARTYPE];
		memcpy(fieldType_, getFieldType(value.c_str()), MAXCHARTYPE * sizeof(char));
		void* fieldName_ = new char[fName.size()];
		memcpy(fieldName_, fName.c_str(), fName.size() * sizeof(char));

		/*asigning pointers to alocated space*/
		(fields + i)->content = (const char*) content_;
		(fields + i)->fieldType = (const char*)fieldType_;
		(fields + i)->fieldName = (const char*)fieldName_;
	}

}


JSONObject::JSONObject(const char * s) {

	string str(s);
	JSONObject obj_c(str); //creo un objeto temporal
	*this = obj_c; //copio el objeto creado a this.
	return;
}

size_t JSONObject::countObjects(string& s) { //function that returns the cuantity of sub objects
	size_t count = 0;
	int c = 0;
	bool starting = true; //flag that indicates that its the first time running the cycle

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '{') {
			c++;
			starting = false;
		}
		else if (s[i] == '}') {
			c--;
			starting = false;
		}
		if (!starting && c == 0) { //si ya se encontro algun corchete y la resta de abiertos y cerrados da 0
			count++;
			starting = true; //restarting condition
		}
	}

	return count;
}

size_t JSONObject::countCorchetes(string& s) { //cuenta cuantos corchetes hay dentro del string
	size_t count = 0; //suma 1 si hay uno abriendo y resta 1 si hay cerrando

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '{') {
			count++;
		}
		else if (s[i] == '}') {
			count--;
		}
	}

	return count;
}

size_t JSONObject::countFields(string& s) { //counts fields by finding semicolons
	size_t count = 0, pos = 0;

	while (s.find(':', pos + 1) != s.npos) { //if found semicolon
		count++;
		pos = s.find(':', pos + 1);
	}

	return count;
}

size_t JSONObject::countFields(string& s, const char c) { //counts fields (considering objects) by counting comas
	size_t count = 0, pos = 0;

	while (s.find(',', pos + 1) != s.npos) { //if found semicolon
		count++;
		pos = s.find(',', pos + 1);
	}

	if (count == 0)
		return 1; //if there is no comas, there is one field

	if (count > 0)
		return count + 1; //if there are more than cero comas, there are "quantity of comas plus one" fields

}

bool JSONObject::insideArray(string& big, string& small) { //looking if inside array

	size_t opening = 0, closing = 0;
	size_t pos = big.find(small); //buscamos en donde empieza la cadena a analizar
	size_t pos2 = big.rfind(small); //buscamos en donde termina la cadena a analizar
	if (big.rfind('[', pos) < big.rfind(']', pos)) //econtramos (hacia la izquierda) un corchete de apertura antes que uno de clausura
		opening = big.rfind('[', pos);
	if (big.find('[', pos2) > big.find(']', pos2)) //econtramos (hacia la derecha) un corchete de clausura antes que uno de apertura
		closing = big.rfind('[', pos2);

	if (opening != big.npos && closing != big.npos && opening != 0 && closing != 0)
		return true;
	else
		return false;
}

void JSONObject::partialPrint(void) {
	partialPrint(0);
}

void JSONObject::partialPrint(size_t tab) { //prints only this object

	if (error.hasFailed() == true) //compruebo que se haya inicializado correctamente
	{
		cout << error.getErrorString() << endl;
		return;
	}
	Field* f = getFieldsPointer();

	tabPrint(tab);
	cout << "|Field counter: " << getFieldCount() << endl; tabPrint(tab); cout << "|-----------------" << endl;
	for (int i = 0; i < getFieldCount(); i++) {
		tabPrint(tab);
		cout << "|Type: " << (f + i)->getFieldsType() << "\t Name: " << (f + i)->getFieldName() << "\t Value: " << (f + i)->getContent() << endl;
		tabPrint(tab);
		cout << '|' << endl;
		if ((f + i)->getFieldsType() == "object")
			cout << "-----------" << endl;
	}
	tabPrint(tab);
	cout << "------------------------------------------------------------------------" << endl;
}

void JSONObject::fullPrint(void) {
	fullPrint(0);
}

void JSONObject::fullPrint(size_t tab) { //prints this and all its sub-objects

	JSONObject* o = getObjectsPointer();

	if (getObjectCount() != 0) { //hay sub objetos
		partialPrint(tab); //imprimimos este objeto
		tab++;
		for (int i = 0; i < getObjectCount(); i++) {
			(o + i)->fullPrint(tab); //imprimimos cada objeto
		}
	}
	else //no hay sub objetos
		partialPrint(tab); //imprimimos este objeto

	return;
}

void JSONObject::tabPrint(size_t tab) {
	for (int j = 0; j < tab; j++) {
		cout << '\t';
	}
}


const char * 
JSONObject::getFieldType(const char * f) {

	int index = 0;
	while (f[index] == ' ')
		index++;


	if (strcmp("true", &f[index]) == 0) { return "bool";}
	if (strcmp("false", &f[index]) == 0) { return "bool"; }

	switch (f[index])
	{
		case '{': return "object";
		case '[': return "array";
		case '"': return "string";
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': return "number";
		default: break;
	}
	error.failState = true;
	error.Desc = "El campo de f no pertenece a un JSONOBject";
	return "invalid";

}

const char * 
JSONObject :: getArrayType(const char * f) {

	string s(f);
	bool itIsBool = true, itIsNumber = true;

	if (s.empty())
		return "invalid";

	//checking if its bool
	for (int i = 0; i < s.size() ; i++) {
		if (f[i] != '0' && f[i] != '1') { //if any of its members is not 1 or 0 then its not bool
			itIsBool = false;
			break;
		}
	}

	if (itIsBool)
		return "bool";

	//checking if its number
	for (int i = 0; i < s.size(); i++) {
		if (!itIsNumber) //its not a number, cut cycle
			break;
		switch (f[i]) { //if its a number do nothing, if its not then break
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': break;
			default: itIsNumber = false; break;
		}
	}

	if (itIsNumber)
		return "number";

	int pos = 0, open = 0, close = 0;

	//validating arrays
	for (int i = 0; i < s.size(); i++) {
		if (f[i] == '[') { //encontramos un corchete en la pos i
			for (int j = 0; j < s.size(); j++) { 
				if (f[j] == '{' || f[j] == '}') //si encontramos un corchete no puede haber una llave
					return "invalid";
				else if (f[j] == '"') //tampoco una comilla
					return "invalid";
			}
			open++; //contador de corchetes abiertos
			pos = s.find(']',i); //buscamos un corchete a partir de i
			if (pos == s.npos) //no encontramos el corchete que cierra
				return "invalid";		
		}
		else if (f[i] == ']')
			close++; //contador de corchetes cerrados
	}
	
	if (open == close && open != 0) //misma cantidad de abiertos que cerrados
		return "array";

	pos = 0, open = 0, close = 0; //restarting counters

	//validating objects
	for (int i = 0; i < s.size(); i++) {
		if (f[i] == '{') { //encontramos una llave en la pos i
			for (int j = 0; j < s.size(); j++) {
				if (f[j] == '[' || f[j] == ']') //si encontramos una llave no puede haber un corchete
					return "invalid";
				else if (f[j] == '"') //tampoco una comilla
					return "invalid";
			}
			open++; //contador de llaves abiertas
			pos = s.find('}', i); //buscamos una lave a partir de i
			if (pos == s.npos) //no encontramos la llave que cierra
				return "invalid";
		}
		else if (f[i] == '}')
			close++; //contador de llaves cerradas
	}

	if (open == close && open != 0) //misma cantidad de abiertas que cerradas
		return "object";

	int ccount = 0;

	//validating string
	for (int i = 0; i < s.size(); i++) {
		if (f[i] == '\"') { //encontramos una comilla
			for (int j = 0; j < s.size(); j++) {
				if (f[j] == '{' || f[j] == '}') //si encontramos una comilla no puede haber una llave
					return "invalid";
				else if (f[j] == '[' || f[j] == ']') //tampoco un corchete
					return "invalid";
			}
			ccount++;
		}
	}

	if ( ccount % 2 == 0 && ccount!=0 ) //si la cantidad de comillas es par (resto da 0) y ccount no es 0
		return "string";
	error.failState = true;
	error.Desc = "El array no pertenece a un JSONObject";
	return "invalid"; //error
}

/* Devuelve en su nombre el tamaño del campo f, donde por tamaño se entiende: si f es de tipo "object" la cantidad de campos que tiene el objeto (pensar si en este caso conviene generar un JSONObject temporal)
con el contenido del campo f y devolver getFieldCount de dicho objeto).
			- si f es de tipo "array" devuelve la cantidad de elementos en el arreglo.
			- si f es de tipo "string" devuelve la cantidad de caracteres en el string.
			- si f es de tipo "number" devuelve sizeof(double).
			- si f es de tipo "bool" devuelve sizeof(bool).
			- si f es no pertenece al objeto devuelve 0. En este último caso genera un error que almacena internamente. */

unsigned int 
JSONObject::getFieldSize(const char * f) {


	string str (getFieldType(f));
	
	
	if (str == "object")
	{
		JSONObject * temp_obj = new JSONObject(f);
		int answer = (*temp_obj).getFieldCount();
		delete temp_obj;
		return answer;
	}
	else if (str == "array")
	{
		int i = 0;
		int answer = 1;
		while (f[i] != ']')
		{
			if (f[i] == ',')
			{
				answer++;
			}
			i++;
		}

		return answer;
	}
	else if (str == "string")
	{
		string mystr(f);
		size_t first = mystr.find('"');
		size_t end = mystr.find('"', first + 1);
		return end-first;
	}
	else if (str == "number")
	{
		int answer = sizeof(double);
		return answer;
	}
	else if (str == "bool")
	{
		int answer = sizeof(bool);
		return answer;
	}

	error.failState = true;
	error.Desc = "F no pertenece a un tipo válido de objeto";
	return 0;
}



bool 
JSONObject::isFieldPresent(const char * f) {

	return true;
}



void * 
JSONObject::copyField(const char * f) 
{
	const char * type =	getFieldType(f);
	if (type == "object")
	{
		JSONObject* obj = new JSONObject (f);
		return &obj;
	}
	else if (type == "array")
	{
		type = getArrayType(f);
		if (type == "object")
		{
			JSONObject* array = new JSONObject[getFieldSize(f)];
			return &array;
		}
		else if (type == "string")
		{
			string* array = new string[getFieldSize(f)];
			return &array;
		}
		else if (type == "number")
		{
			double* array = new double[getFieldSize(f)];
			return &array;
		}
		else if (type == "bool")
		{
			bool* array = new bool[getFieldSize(f)];
			return &array;
		}
		else
		{
			error.failState = true;
			error.Desc = "Los datos del array no se corresponden al JSONObject";
			return NULL;
		}
	}
	else if (type == "string")
	{
		string* str = new string(f);
		return &str;
	}
	else if (type == "number")
	{
		double* num = new double (stod(f));
		return &num;
	}
	else if (type == "bool")
	{
		if (f == "true")
		{
			bool* tof = new bool(true);
			return &tof;
		}
		else
		{
			bool* tof = new bool(false);
			return &tof;
		}
	}
	error.failState = true;
	error.Desc = "F no pertenece al JSONObject";
	return NULL;

}





void * 
JSONObject::copyArrayValue(const char * f, unsigned int pos) {

	return (void*)f;
}







void 
JSONObject::print(void) {

	cout << "Start of JSON Object: \nFIELD\t: TYPE" << endl;
	cout << "----------------" << endl;
	for (unsigned int i = 0; i < fieldCount; i++)
	{
		cout << fields[i].getFieldName() << "\t: " << fields[i].getFieldsType() << endl;
	}
	return;
}

bool 
JSONObject::parseString(string& s) {
	int validate=0;

	for (size_t i = 0; i < s.length(); i++)		//recorro el string
	{
		if (s[i] == '{') { validate++; }		//Busco si la cantidad de { es igual a la de }
		if (s[i] == '}') { validate--; }
		if (validate < 0) 
		{
			error.failState = true;
			error.Desc = "Syntax error '}' not expected";
			return false; 
		}		// si en algun momento validate es menor a 0 significa que aparecieron 2 llaves que cierran y falta una que abra.
	}
	if (validate)
	{
		error.failState = true;
		error.Desc = "Syntax error. Missing '}'";
		return false;
	}				//hay mas llaves que abren que llaves que cierran, string con error de forma



	for (size_t i = 0; i < s.length(); i++)		//recorro el string
	{
		if (s[i] == '[') { validate++; }		//Busco si la cantidad de [ es igual a la de ]
		if (s[i] == ']') { validate--; }
		if (validate < 0)						// si en algun momento validate es menor a 0 significa que aparecieron 2 corchetes que cierran y falta una que abra.
		{
			error.failState = true;
			error.Desc = "Syntax error ']' not expected";
			return false; 
		}		
		if (validate == 2)
		{
			error.failState = true;
			error.Desc = "Por el momento no permitimos arreglos de arreglos, intente de nuevo mas tarde";
			return false;
		}
	}
	if (validate)								//hay mas corchetes que abren que llaves que cierran, string con error de forma
	{ 
		error.failState = true;
		error.Desc = "Syntax error. Missing ']'";
		return false;
	}				
	

	for (size_t i = 0; i < s.length(); i++)		//recorro el string
	{
		if (s[i] == '"') { validate++; }		//Busco si la cantidad de " es par
	}
	if (validate%2)							//si el resto da impar esta mal, modifico jsonerror
	{
		error.failState = true;
		error.Desc = "Syntax error '{' not expected";
		return false;
	}

	return true;

}




/*
* Devuelve en su nombre true si el objeto JSON está vacío, o false en caso
* contrario.
*/

bool 
JSONObject::isEmpty(void) 
{
	return fieldCount == 0 ? true:false;
}
