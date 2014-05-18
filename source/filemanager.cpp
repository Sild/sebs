#include "../header/filemanager.h"

Filemanager::Filemanager() {
	this->scrambler = new Scrambler("secret_key");
}

bool Filemanager::merge(std::string ifpath, std::string ofpath) {
	char *buffer;
	int len = 2048;
	buffer = new char[len];
	int maxstrlen = 100;
	std::ifstream segment_list(ifpath.c_str());
	std::string segment_name;

	std::ofstream ofile( ofpath, std::ios::out | std::ios::binary );

	while(segment_list) {
		std::getline(segment_list, segment_name);
		std::ifstream ifile(segment_name.c_str(), std::ios::binary);
		do {

			ifile.read(buffer, len);
			if(ifile.gcount()) {
				ofile.write( this->scrambler->decode(buffer), ifile.gcount());
			}
		} while (ifile.gcount());
		ifile.close();
	}
	delete[] buffer;
	ofile.close();
	return true;
}

bool Filemanager::segmentate(std::string ifpath, std::string ofpath) {
	char * buffer;
    int len = 2048; //ширина блока
 
    std::ifstream infile(ifpath.c_str(), std::ios::in | std::ios::binary);

    if(!infile){ //отсутствие прав постучалось в двери
        std::cout << "cannot open input files\n";
        return false;
    }

 	FILE *file = fopen(ofpath.c_str(), "w");
    
    buffer = new char[len];
    int i = 0;
    while (!infile.eof()){
        infile.read(buffer, len);
        if(infile.gcount()) {
        	const char *partname = ("./output/" + md5(ofpath) + std::to_string(i++)).c_str();
        	std::cout <<  partname << std::endl;
        	std::ofstream outfile( partname, std::ios::binary);
        	std::cout << partname << std::endl;
        	if(!outfile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
        		std::cout << "cannot open output files named \"" << ofpath << i-1 << "\" \n";
        		return false;
    		}
    		// std::cout << buffer << std::endl;
    		std::cout << partname << std::endl;
        	outfile.write(this->scrambler->encode(buffer), infile.gcount());
        	std::cout << partname << std::endl;
        	outfile.close();
        	fprintf(file, "%s\n", partname);
        	return true;

        } 
    }

	fclose(file); 
    infile.close();
 	
    delete[] buffer;
    return true;
}