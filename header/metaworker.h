#ifndef METAWORKER_H
#define METAWORKER_H


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "md5.h"
struct metarow {
	long position;
	std::string clean_hash;
	std::string cipher_hash;
	int start;
	int finish;
	std::string as_string() const;
	void show() const;
};

class Metaworker {
public:
	Metaworker();
	~Metaworker();
	void load(std::string file_path);
    const metarow &get(int position) const ;
	bool set(std::string clean_hash, std::string cipher_hash, int start, int finish, int position, const bool replace);
	bool set(std::string clean_hash, std::string cipher_hash, int start, int finish);
	bool remove(int position);
	long mdata_size() const;
	void show() const;
	bool save();
	std::vector<metarow> mdata;//meta-data
	bool sort();
private:
	std::string mfpath;
	std::string output_dir;
	static bool sort_func(metarow a, metarow b);
	bool get_content_from_metafile();
	metarow *generate_metarow(int position, std::string clean_hash, std::string cipher_hash, int start, int finish);
	bool write_metarow(metarow *row, const bool replace);
	long get_str_count();

};

#endif