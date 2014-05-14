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
    string clone = "/clone/a.out";
    string ipath = app_path.string() + in;
    string opath = app_path.string() + out;
    string cpath = app_path.string() + clone;
    
    if( segmentate( ipath.c_str(), opath.c_str() ) ) {
    	merge( opath.c_str(), cpath.c_str() );	
    }

    
    exit(1);
}




