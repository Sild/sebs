#include "../header/metaworker.h"

Metaworker::Metaworker(std::string mfpath) {
	this->mfpath = mfpath;
	this->load();
	std::cout << "metaworker created" << std::endl;
}

metarow Metaworker::read(int position) {
	metarow mock;
	return mock;
}

bool Metaworker::write(int position, std::string clean_hash, std::string cipher_hash, int start, int finish,const bool replace) {
	metarow *row = this->generate_metarow(position, clean_hash, cipher_hash, start, finish);
	return this->write_metarow(row, replace);
}
	


bool Metaworker::write_metarow(metarow *row,const bool replace) {
	long strcount = this->get_str_count();
	
	if(replace) {
		this->mdata[row->position] = *row;
	} else {
		std::cout << "хуйтаманетест" << std::endl;
	}
	int num = row->position;
	delete row;
	std::cout << this->mdata[row->position].clean_hash << std::endl;

	
	std::cout << strcount << std::endl;
    
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

metarow *Metaworker::generate_metarow(int position, std::string clean_hash, std::string cipher_hash, int start, int finish) {
	metarow *row = new metarow;
	row->position = position;
	row->clean_hash = clean_hash;
	row->clean_hash = cipher_hash;
	row->start = start;
	row->finish = finish;
	return row;
}

bool Metaworker::load() {
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
		step = 0;
		std::string tmpstart = "";
		std::string tmpfinish = "";
		for(int i = 0; i < strlength; i++){
			if ( row[i] == '\n') {
				step++;
			} else {
				switch(step) {
					case 0:
						mrow->position = linenum;
						break;

					case 1:
						mrow->clean_hash += row[i]; 
						break;

					case 2:
						mrow->cipher_hash += row[i];
						break;

					case 3:
						tmpstart += row[i];
						break;

					case 4:
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



