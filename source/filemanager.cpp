
#include "../header/filemanager.h"
#include "../header/scrambler.h"
#include "../header/md5.h"

boost::filesystem::path get_app_path() {
	return boost::filesystem::current_path();
}

bool merge(string ifpath, string ofpath) {
	std::cout << "++++++++++++++" << std::endl;
	char *buffer;
	int len = 20480;
	buffer = new char[len];
	int maxstrlen = 100;
	std::ifstream segment_list(ifpath.c_str());
	std::string segment_name;

	ofstream ofile( ofpath, ios::out | ios::binary );

	while(segment_list) {
		std::getline(segment_list, segment_name);
		ifstream ifile(segment_name.c_str(), ios::in | ios::binary);
		do {

			ifile.read(buffer, len);
			if(ifile.gcount()) {
				ofile.write( decode(buffer, ifile.gcount()), ifile.gcount());
			}
		} while (ifile.gcount());
		ifile.close();
	}
	delete[] buffer;
	ofile.close();
	return true;
}

bool segmentate(string ifpath, string ofpath) {
	char * buffer;
    int len = 20480; //Выбираем размер буфера, какой нравится
 
    ifstream infile(ifpath.c_str(), ios::in | ios::binary);

    if(!infile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
        cout << "cannot open input files\n";
        return false;
    }

 	FILE *file = fopen(ofpath.c_str(), "w");
    
    buffer = new char[len];
    int i = 0;
    while (!infile.eof()){
        infile.read(buffer, len);
        if(infile.gcount()) {
        	const char *partname = ("./output/" + md5(ofpath) + to_string(i++)).c_str();
        	ofstream outfile( partname, ios::out | ios::binary);
        	if(!outfile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
        		cout << "cannot open output files named \"" << ofpath << i-1 << "\" \n";
        		return false;
    		}
        	outfile.write(encode(buffer, infile.gcount()), infile.gcount());
        	outfile.close();
        	fprintf(file, "%s\n", partname);

        } 
        // return true;
        //gcount возвращает количество байт, считанных в последний раз
        //ее и используем для проверки, что что-то считалось, а заодно устанавливаем количество записываемых байт
    }

	fclose(file); 
    infile.close();
 	
    delete[] buffer;
    return true;
}