#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "scrambler.h"
#include "md5.h"
#include "metaworker.h"


class Filemanager {
public:
	Filemanager();
	bool segmentate(std::string target_file_name); // of will contain meta-data
	bool merge(std::string target_file_name);//ifile - file which contain meta-data

private:
	std::string input_dir;
	std::string output_dir;
	Scrambler *scrambler;
};
#endif