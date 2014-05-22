#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

struct metarow {
	long position;
	std::string clean_hash;
	std::string cipher_hash;
	int start;
	int finish;
};

class Metaworker {
public:
	Metaworker(std::string mfpath);
	metarow read(int position);
	bool write(int position, std::string clean_hash, std::string cipher_hash, int start, int finish,const bool replace);

private:
	bool write_metarow(metarow *row, const bool replace);
	metarow *generate_metarow(int position, std::string clean_hash, std::string cipher_hash, int start, int finish);
	std::string mfpath;
	long get_str_count();
	bool load();
	std::vector<metarow> mdata;//meta-data
	void show_metarow(const metarow* row);
};

