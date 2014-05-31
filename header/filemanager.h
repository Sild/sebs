#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "scrambler.h"
#include "md5.h"
#include "metaworker.h"
#include "updater.h"


class Filemanager {
public:
	Filemanager();
	~Filemanager();
	bool segmentate(std::string file_path); // of will contain meta-data
	bool segmentate(std::string file_path, long begin, long end);
	bool merge(std::string file_path);//ifile - file which contain meta-data
	bool update(std::string file_path);

private:
	int buffer_size;
	std::string input_dir;
	std::string output_dir;
	Scrambler *scrambler;
	bool rm_file(std::string path);
	Metaworker *mworker;
};
#endif