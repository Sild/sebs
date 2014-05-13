#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <string>
#include "../header/filemanager.h"


using namespace std;


int main(int argc, char *argv[])
{
    boost::filesystem::path app_path = get_app_path();

    string out = "/output/acpy.out";
    string in = "/input/a.out";
    string close = "/close/a.out"
    
    copy((app_path.string() + in).c_str(), (app_path.string() + out).c_str());

    exit(1);
}




