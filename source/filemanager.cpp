#include "../header/filemanager.h"

Filemanager::Filemanager() {
	this->scrambler = new Scrambler("secret_key");
    this->output_dir = "./output/";
    this->buffer_size = 2048;
}

Filemanager::~Filemanager() {

}


bool Filemanager::update(std::string file_path) {
    Updater *updater = new Updater();
    std::pair<std::map<int, int>, std::vector<std::pair<long, long> > > updater_result = updater->get_similar(file_path);
    std::map<int, int> similar_chunk = updater_result.first;
    std::vector<std::pair<long, long> > diff = updater_result.second;
    // std::cout << "similar:" << std::endl;
    // updater->show_similar(similar_chunk);
    std::cout << "diff bytes:" << std::endl;
    updater->show_diff(diff);
    this->mworker = new Metaworker();
    this->mworker->load(file_path);
    std::vector<int> chunk_to_del;
    std::cout << "diff blocks:" << std::endl;
    for(int i = 0; i < mworker->mdata_size(); i++) {
        if(similar_chunk.find(i) == similar_chunk.end()) {
            std::cout << i << " ";
            chunk_to_del.push_back(i);

        }
    }
    std::cout << std::endl << "old mdata: " << std::endl;;

    this->mworker->show();
    for(int i = 0; i < chunk_to_del.size(); i++) {
        // std::cout << "num: " << i << std::endl;
        this->rm_file(this->mworker->get(chunk_to_del[i]).cipher_hash);
        this->mworker->remove(chunk_to_del[i]);
    }

    for(int i = 0; i < diff.size(); i++) {
        this->segmentate(file_path, diff[i].first, diff[i].second);
    }

std::cout << std::endl << "new mdata: " << std::endl;;
    this->mworker->show();



    // this->mworker->save();
    return true;

}


bool Filemanager::segmentate(std::string file_path, long begin, long end) {
    char *buffer = new char[this->buffer_size];
    int start_read_byte = begin;
    std::string chang_path;
    int readed;
    int ifile = open(file_path.c_str(), 0);

    if(!ifile){ //отсутствие прав постучалось в двери
        std::cout << "cannot open input files\n";
        return false;
    }

    int lost = end-start_read_byte;

    while ( lost > 0 ){

        if(lost >= this->buffer_size) {
            readed = this->buffer_size;
        } else {
            readed = lost;
        }
        pread(ifile, buffer, readed, start_read_byte);
        const char* enc_buffer = this->scrambler->encode(buffer, readed);
        std::string str_buffer(buffer, readed);
        std::string enc_str_buffer(enc_buffer, readed);

        mworker->set( md5(str_buffer), md5(enc_str_buffer), start_read_byte, start_read_byte + readed - 1);
        
        chang_path = this->output_dir + md5(enc_str_buffer);
        
        std::ofstream ofile( chang_path.c_str(), std::ios::binary);
        start_read_byte += readed; 
        lost = end - start_read_byte;
        if(!ofile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
            std::cout << "cannot open output files named \"" << md5(enc_str_buffer) << "\" \n";
            return false;
        }
        ofile.write(enc_buffer, readed);
        ofile.close();
    }
    close(ifile);
    delete[] buffer;
    return true;
}

bool Filemanager::rm_file(std::string path) {
    std::cout << "file" << path << "was deleted" << std::endl;
    return true;
}

bool Filemanager::merge(std::string file_path) {
    std::cout << "start merge" << std::endl;
	char *buffer = new char[this->buffer_size];
    Metaworker *mworker = new Metaworker();

    mworker->load(file_path);
	std::string segment_file_name;

	std::ofstream ofile( file_path.c_str(), std::ios::out | std::ios::binary );

    for(int i = 0; i < mworker->mdata_size(); i++) {
        std::ifstream ifile( (this->output_dir + mworker->get(i).cipher_hash ), std::ios::binary);
        do {

            ifile.read(buffer, this->buffer_size);
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

bool Filemanager::segmentate(std::string file_path) {       

	char *buffer = new char[this->buffer_size];
    int start_read_byte = 0;
    Metaworker *mworker = new Metaworker();
    mworker->load(file_path.c_str());

    std::string chang_path;

    std::ifstream ifile( file_path.c_str(), std::ios::in | std::ios::binary);

    if(!ifile){ //отсутствие прав постучалось в двери
        std::cout << "cannot open input files\n";
        return false;
    }



    while (!ifile.eof()){

        ifile.read(buffer, this->buffer_size);
        if(ifile.gcount()) {

            const char* enc_buffer = this->scrambler->encode(buffer, ifile.gcount());
            std::string str_buffer(buffer, ifile.gcount());
            std::string enc_str_buffer(enc_buffer, ifile.gcount());

            mworker->set( md5(str_buffer), md5(enc_str_buffer), start_read_byte, start_read_byte + ifile.gcount() - 1);
            
            chang_path = this->output_dir + md5(enc_str_buffer);
            
            std::ofstream ofile( chang_path.c_str(), std::ios::binary);
            
            start_read_byte += ifile.gcount();  

            if(!ofile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
                std::cout << "cannot open output files named \"" << md5(enc_str_buffer) << "\" \n";
                return false;
            }

        	ofile.write(enc_buffer, ifile.gcount());
        	ofile.close();

        } 
    }
    mworker->save();
    ifile.close();
 	
    delete[] buffer;
    return true;
}