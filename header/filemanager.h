#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
boost::filesystem::path get_app_path();

bool segmentate(string ifpath, string ofpath); //разбивает входной файл, в выходном содержится список разбитых элементов

bool merge(string ifpath, string ofpath); //принимает на вход файл со списком элементов

#endif