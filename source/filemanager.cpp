#include "../header/filemanager.h"

Filemanager::Filemanager() {
	this->scrambler = new Scrambler("secret_key");
}

bool Filemanager::merge(std::string ifpath, std::string ofpath) {
	char *buffer;
	int len = 20480;
	buffer = new char[len];
	int maxstrlen = 100;
	std::ifstream segment_list(ifpath.c_str());
	std::string segment_name;
	std::string dec_buf;
	std::ofstream ofile( ofpath, std::ios::out | std::ios::binary );

	while(segment_list) {
		std::getline(segment_list, segment_name);
		std::ifstream ifile(segment_name.c_str(), std::ios::binary);
		do {

			ifile.read(buffer, len);
			if(ifile.gcount()) {
				    		std::cout << this->scrambler->decode(buffer).c_str() << std::endl << "-----" << std::endl;
				ofile.write( this->scrambler->decode(buffer).c_str(), ifile.gcount());
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
    int len = 20480; //ширина блока
 
    std::ifstream infile(ifpath.c_str(), std::ios::in | std::ios::binary);
    std::ofstream target("./output/a.out", std::ios::out | std::ios::binary);

    if(!infile){ //отсутствие прав постучалось в двери
        std::cout << "cannot open input files\n";
        return false;
    }

 	FILE *file = fopen(ofpath.c_str(), "w");
    
    buffer = new char[len];
    int i = 0;

    std::string partname;
    std::string enc_buf;
    std::string meta_line;
    while (!infile.eof()){
        infile.read(buffer, len);
        if(infile.gcount()) {
        	partname = "./output/" + md5(ofpath) + std::to_string(i++);
        	std::ofstream outfile( partname.c_str(), std::ios::binary);

        	if(!outfile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
        		std::cout << "cannot open output files named \"" << ofpath << i-1 << "\" \n";
        		return false;
    		}
    		std::cout << buffer << std::endl << "----------" << std::endl << this->scrambler->encode(buffer) << std::endl << "-----" << std::endl;
    		
    		std::cout << this->scrambler->decode(this->scrambler->encode(buffer).c_str()) << std::endl;
        	std::cout << "+++++++++++" << std::endl;
        	outfile.write(this->scrambler->encode(buffer).c_str(), infile.gcount());

        	

        	target.write( this->scrambler->decode(this->scrambler->encode(buffer).c_str()).c_str(), infile.gcount());

        	outfile.close();
			fprintf(file, "%s\n", partname.c_str());
        	// return true;

        } 
    }
    target.close();
	fclose(file); 
    infile.close();
 	
    delete[] buffer;
    return true;
}