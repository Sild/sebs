#include "../header/metaworker.h"


std::string metarow::as_string() const{
		return this->clean_hash + " " + this->cipher_hash + " " + std::to_string(this->start) + " " + std::to_string(this->finish);
}

void metarow::show() const{
	std::cout << "row number:  " << this->position << std::endl;
	std::cout << "clean hash:  " << this->clean_hash << std::endl;
	std::cout << "cipher hash: " << this->cipher_hash << std::endl;
	std::cout << "start:       " << this->start << std::endl;
	std::cout << "finish:      " << this->finish << std::endl;
	std::cout << "-------------------" << std::endl;
}




Metaworker::Metaworker() {
	std::cout << "metaworker created" << std::endl;
}

Metaworker::~Metaworker() {
	std::cout << "~Metaworker called" << std::endl;
	delete this;
}

void Metaworker::load(std::string mfpath) {
	this->mfpath = mfpath;
	this->mdata.clear();
	this->get_content_from_metafile();
}


metarow Metaworker::read(int position) {
	metarow mock;
	return mock;
}



bool Metaworker::write(std::string clean_hash, std::string cipher_hash, int start, int finish, int position, const bool replace) {
	metarow *row = this->generate_metarow(position, clean_hash, cipher_hash, start, finish);
	return this->write_metarow(row, replace);
}

bool Metaworker::write(std::string clean_hash, std::string cipher_hash, int start, int finish) {
	long position = this->mdata.size();
	bool replace = false;
	metarow *row = this->generate_metarow(position, clean_hash, cipher_hash, start, finish);
	return this->write_metarow(row, replace);
}

void Metaworker::show() const {
	for(std::vector<metarow>::const_iterator itr = this->mdata.begin(); itr != mdata.end(); itr++) {
    		std::cout << (*itr).as_string() << std::endl;
	}
}
	




bool Metaworker::get_content_from_metafile() {
	std::ifstream mdatastream(this->mfpath.c_str());
	if(!mdatastream) return false;
	std::string row;
	int strlength;
	int step;
	metarow *mrow;
	int linenum = 0;
	while(mdatastream) {
		mrow = new metarow;
		mrow->clean_hash = "";
		mrow->cipher_hash = "";
		std::getline(mdatastream, row);
		strlength = row.length(); 
		if(strlength == 0) {
			break;
		}
		step = 0;
		std::string tmpstart = "";
		std::string tmpfinish = "";
		mrow->position = linenum;
		for(int i = 0; i < strlength; i++){
			if ( row[i] == '\n') {
				step++;
			} else if ( row[i] == ' ') {
				step++;
			} else  {
				switch(step) {
					case 0:
						mrow->clean_hash += row[i]; 
						break;
					case 1:
						mrow->cipher_hash += row[i];
						break;
					case 2:
						tmpstart += row[i];
						break;
					case 3:
						tmpfinish += row[i];
						break;
					default:
						std::cout << "lol wtf step no in 0-1-2-3? metaworker.cpp line 92";
						break;
				}
			}
		}
		linenum++;
		mrow->start = atoi(tmpstart.c_str());
		mrow->finish = atoi(tmpfinish.c_str());
		this->mdata.push_back(*mrow);
	}
	mdatastream.close();
	return true;
}	

metarow *Metaworker::generate_metarow(int position, std::string clean_hash, std::string cipher_hash, int start, int finish) {
	metarow *row = new metarow;
	row->position = position;
	row->clean_hash = clean_hash;
	row->cipher_hash= cipher_hash;
	row->start = start;
	row->finish = finish;
	return row;
}

bool Metaworker::write_metarow(metarow *row,const bool replace) {
	long strcount = this->get_str_count();
	
	if(replace) {
		this->mdata[row->position] = *row;
	} else {
		if(row->position >= this->mdata.size()) {
			this->mdata.push_back(*row);
		} else {
			this->mdata.insert(this->mdata.begin() + row->position, *row);
		}
	}
	delete row;
    
    return true;
}

long Metaworker::get_str_count() {
	char *str = new char [1024];
    int i=0;
    std::ifstream base(this->mfpath.c_str());

    while (!base.eof())
    {
        base.getline(str, 1024, '\n');
        i++;
    }
    base.close();
    delete str;
    return i-1;//внезапно. почему-то всегда есть последний перевод строки в конце файла.
}

bool Metaworker::save() {
	std::cout << "save start work" << std::endl;
	bool saved;
    FILE * meta_file = fopen(this->mfpath.c_str(), "w");

    if (meta_file) {
    	for(std::vector<metarow>::iterator itr = this->mdata.begin(); itr != mdata.end(); itr++) {
    		fprintf(meta_file, "%s\n", (*itr).as_string().c_str());
    	}
    	saved = true;
    } else {
    	std::cout << "can't open file to write" << std::endl;
    	saved = false;
    }
    fclose(meta_file);
    std::cout << "save finish work" << std::endl;
    return saved;
}






