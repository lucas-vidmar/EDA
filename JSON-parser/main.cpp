#include"json.h"
#include"testBase.h"
#include <fstream>

void printTitle(string s);

using namespace std;

#define prueba
#ifndef prueba

int main(void)
{
	string s;
	cin >> s;

	cout << "inserted line:" << s << endl;

	cout << X << endl;

	system("pause");
}

#else

int main(void)
{
	
	//#define compilingflag1
	#ifdef compilingflag1
	const char* f1 = { "[2119513111110]" }, *f2 = { "[21195131{11110]" }, *f3 = { "[21195131]11110]" }, *f4 = { "][2119513a111110]" },
		*f5 = { "1000110" }, *f6 = { "\"asdasd\"" }, *f7 = { "123104" }, *f8 = { "{a1231}" };

	JSONObject obj;

	const char* type = obj.getArrayType(f1);
	cout << "1:" << f1 << "\t" << type << endl;
	type = obj.getArrayType(f2);
	cout << "2:" << f2 << "\t" << type << endl;
	type = obj.getArrayType(f3);
	cout << "3:" << f3 << "\t" << type << endl;
	type = obj.getArrayType(f4);
	cout << "4:" << f4 << "\t" << type << endl;
	type = obj.getArrayType(f5);
	cout << "5:" << f5 << "\t" << type << endl;
	type = obj.getArrayType(f6);
	cout << "6:" << f6 << "\t" << type << endl;
	type = obj.getArrayType(f7);
	cout << "7:" << f7 << "\t" << type << endl;
	type = obj.getArrayType(f8);
	cout << "8:" << f8 << "\t" << type << endl;


	cout << "\n\n\n" << endl;

	

	/*Testing getFieldSize*/
	const char * str = {"[1,2,3,4]"};
	size_t size = obj.getFieldSize(str);
	cout <<"1:"<< str << " es un " << obj.getFieldType(str) << " size -> " << size << "\n" << endl;
	
	str = {"true"};
	size = obj.getFieldSize(str);
	cout << "1:" << str << " es un " << obj.getFieldType(str) << " size -> " << size << "\n" << endl;

	str = { "\"mistring\"" };
	size = obj.getFieldSize(str);
	cout << "1:" << str << " es un " << obj.getFieldType(str) << " size -> " << size << "\n" << endl;

	#endif

	string fileName, nullString("test"), exitString("exit"), s;
	bool executeAgain = true;

	do {
		system("CLS"); //cleaning screen
		cout << "Please input file name or \"test\" if wanna see a test data base. Write \"exit\" or close button to exit." << endl << endl;
		cin >> fileName;

		if (fileName == exitString) //asked to exit
			return 0;
		else if (fileName == nullString) { //Testing object builder
			test();
			system("pause");
		}
		else { //filename inserted
			ifstream in; //file
			in.open(fileName.c_str()); //opening file with provided name
			if (!in) { //error opening file
				cout << endl << "Error: Can't open the file named " << '"' << fileName << '"' << ". Try again." << endl;
				system("pause");
				in >> s;
			}
			else {
				JSONObject obj(s);
				printTitle(s);
				obj.fullPrint();
				cout << endl << endl;
				system("pause");
			}
		}
	} while (executeAgain);
	

	cout << "Fatal error" << endl; //shouldnt get here
	system("pause");
	return 0;
}

#endif