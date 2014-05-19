#include "../header/filemanager.h"

Filemanager::Filemanager() {
	this->scrambler = new Scrambler("secret_key");
}

bool Filemanager::merge(std::string ifpath, std::string ofpath) {
	char *buffer;
	int size = 2048;
	buffer = new char[size];
	std::ifstream meta_file(ifpath.c_str());

	std::string segment_file_name;

	std::ofstream ofile( ofpath, std::ios::out | std::ios::binary );

	while(meta_file) {

		std::getline(meta_file, segment_file_name);
		std::ifstream ifile(segment_file_name.c_str(), std::ios::binary);
		do {

			ifile.read(buffer, size);
			if(ifile.gcount()) {	
				ofile.write( this->scrambler->decode(buffer, ifile.gcount()), ifile.gcount());
			}

		} while (ifile.gcount());
		ifile.close();
	}
	delete[] buffer;
	ofile.close();
	return true;
}

bool Filemanager::segmentate(std::string ifpath, std::string ofpath) {

	char *buffer;
    int size = 2048; 

    std::ifstream ifile(ifpath.c_str(), std::ios::in | std::ios::binary);

    if(!ifile){ //отсутствие прав постучалось в двери
        std::cout << "cannot open input files\n";
        return false;
    }

 	FILE *meta_file = fopen(ofpath.c_str(), "w");
    
    buffer = new char[size];
    int i = 0;

    std::string partname;

    while (!infile.eof()){
        infile.read(buffer, len);
        if(infile.gcount()) {

        	partname = "./output/" + md5(ofpath) + std::to_string(i++);
        	std::ofstream ofile( partname.c_str(), std::ios::binary);

        	if(!ofile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
        		std::cout << "cannot open output files named \"" << partname << "\" \n";
        		return false;
    		}

        	ofile.write(this->scrambler->encode(buffer, ifile.gcount()), ifile.gcount());
        	ofile.close();
			fprintf(meta_file, "%s\n", partname.c_str());

        } 
    }
	fclose(meta_file); 
    ifile.close();
 	
    delete[] buffer;
    return true;
}