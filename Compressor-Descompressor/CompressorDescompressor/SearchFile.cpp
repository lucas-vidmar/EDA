#include "SearchFile.h"

bool search_files_with_extension(vector<string>& paths_vector, const char* directory_wanted, const char* extension_wanted)
{
	path directory(directory_wanted);
	string name;
	string file_extension;


	if (exists(directory))																						//me fijo si existe el path
	{
		if (is_directory(directory))																			//me fijo si realmente es un directorio
		{
			for (directory_iterator itr(directory); itr != directory_iterator(); itr++)							//itero en todo los archivos del directorio
			{
				if (itr->path().has_extension())																//el archivo tiene extension
				{
					file_extension = itr->path().extension().string();											//obtengo la extension del archivo
					
					if (strcmp(extension_wanted, (file_extension.c_str())) == 0)								//es la extension que yo quiero?
					{
						name = (itr->path().parent_path().string()) + "/" + (itr->path().filename().string());	//si, guardo el path del archivo con la extension buscada
						paths_vector.push_back(name); //Guarda el path en el vector.
					}
				}
				
			}
			return true;
		}
		else
		{
			return false; //No es directorio
		}

	}
	else
	{
		return false; //No existe el path recibido.
	}
}