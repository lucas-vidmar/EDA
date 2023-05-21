#pragma once

#ifndef SEARCH_FILE_H
#define	SEARCH_FILE_H


#include <vector>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

using namespace std;
using namespace boost::filesystem;


bool search_files_with_extension(vector<string>& paths_vector, const char* directory_wanted, const char* extension_wanted);

#endif // !SEARCH_FILE_H





