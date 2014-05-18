#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "scrambler.h"
#include "md5.h"


class Filemanager {
public:
	Filemanager();
	bool segmentate(std::string ifile, std::string ofile); // of will contain meta-data
	bool merge(std::string ifile, std::string ofile);//ifile - file which contain meta-data

private:
	Scrambler *scrambler;
};
#endif