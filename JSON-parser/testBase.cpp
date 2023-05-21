#include"testBase.h"

void test(void) {
	/*Caso de objeto dentro de objeto*/
	string s1("{\"object1\":{\"object2\":{\"value1\":2,\"string1\":\"holaprueba\"}},\"text\":\"mi string de prueba\",\"object3\":{\"object4\":{\"value2\":3,\"string2\":\"comoestas\"}}}");
	/*Caso arrays*/
	string s2("{\"array1\":[1,2,3,4],\"array2\":[a,b,c,d]}");
	/*Caso arrays de objetos*/
	string s3("{\"array1\":[\"obj1\":{\"field2\":\"hola2\"},\"obj2\":{\"field3\":\"hola3\"}],\"mistring\":\"soy un string\",\"object2\":{\"value1\":2,\"string1\":\"holaprueba\"}}");
	/*Caso arrays de arrays*/
	string s4("{\"array\":[\"array1\":[1,2],\"array2\":[3,4]]}");

	JSONObject obj1(s1), obj2(s2), obj3(s3), obj4(s4);

	/*Printing*/
	printTitle(s1);
	obj1.fullPrint();
	cout << endl << endl;
	printTitle(s2);
	obj2.fullPrint();
	cout << endl << endl;
	printTitle(s3);
	obj3.fullPrint();
	cout << endl << endl;
	printTitle(s4);
	obj4.fullPrint();
	cout << endl << endl;

	return;
}

void printTitle(string s) {
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << s << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
}