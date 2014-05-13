#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
boost::filesystem::path get_app_path();

bool copy(string ifpath, string ofpath);

#endif