#ifndef UPDATER_H
#define UPDATER_H

#include <string>
#include <stack>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "metaworker.h"
#include "md5.h"
#include <fstream>
#include <map>

class Updater
{
public:
    Updater();
    std::pair<std::map<int, int>, std::vector<std::pair<long, long> > >get_similar(const std::string file_path);
	void show_similar(std::map<int, int> chunks);
	void show_diff(std::vector<std::pair<long, long> > diff);
private:
	std::string output_dir;
	std::string file_path;
	int buffer_size;
	long get_filesize(std::string file_path);
	long get_old_filesize();

	Metaworker *mworker;
};

#endif