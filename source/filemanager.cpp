#include "../header/filemanager.h"

Filemanager::Filemanager() {
	this->scrambler = new Scrambler("secret_key");
    this->input_dir = "./input";
    this->output_dir = "./output";
}

bool Filemanager::merge(std::string target_file_name) {
    std::cout << "start merge" << std::endl;
	char *buffer;
	int size = 2048;
	buffer = new char[size];
    std::string mfname = md5(target_file_name);

    Metaworker *mworker = new Metaworker();

    mworker->load(this->output_dir + "/" + mfname);
    // std::cout << mworker->mfile_size() << std::endl; 
	std::string segment_file_name;

	std::ofstream ofile( this->input_dir + "/" + target_file_name, std::ios::out | std::ios::binary );

    for(int i = 0; i < mworker->mfile_size(); i++) {
        std::ifstream ifile( (this->output_dir + "/" + mworker->read(i).cipher_hash ), std::ios::binary);
        // std::cout << mworker->read(i).cipher_hash << std::endl;
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

bool Filemanager::segmentate(std::string target_file_name) {

	char *buffer;
    int size = 2048; 

    std::ifstream ifile( (this->input_dir + "/" + target_file_name).c_str(), std::ios::in | std::ios::binary);

    if(!ifile){ //отсутствие прав постучалось в двери
        std::cout << "cannot open input files\n";
        return false;
    }
    std::string mfname = md5( target_file_name.c_str());
 	FILE *mfile = fopen( (this->output_dir + "/" + mfname).c_str(), "w");
    
    buffer = new char[size];
    long read_start = 0;

    std::string metarow;

    std::string chang_path;

    while (!ifile.eof()){
        ifile.read(buffer, size);
        if(ifile.gcount()) {
            const char* enc_buffer = this->scrambler->encode(buffer, ifile.gcount());
            std::string str_buffer(buffer, ifile.gcount());
            std::string enc_str_buffer(enc_buffer, ifile.gcount());
            metarow = md5(str_buffer) + " " + md5(enc_str_buffer) + " " + std::to_string(read_start) + " " + std::to_string(read_start+ifile.gcount());   
            chang_path = this->output_dir + "/" + md5(enc_str_buffer);
            std::ofstream ofile( chang_path.c_str(), std::ios::binary);
            read_start += ifile.gcount();  

            if(!ofile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
                std::cout << "cannot open output files named \"" << md5(enc_str_buffer) << "\" \n";
                return false;
            }

        	ofile.write(enc_buffer, ifile.gcount());
        	ofile.close();
			fprintf(mfile, "%s\n", metarow.c_str());

        } 
    }
	fclose(mfile); 
    ifile.close();
 	
    delete[] buffer;
    return true;
}