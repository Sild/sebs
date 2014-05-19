#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <string>
#include "../header/filemanager.h"


using namespace std;


int main(int argc, char *argv[])
{
    string ofile = "./output/acpy.out";
    string ifile = "./input/a.out";
    string clone = "./clone/a.out";
    Filemanager *filemanager = new Filemanager();
    if( filemanager->segmentate( ifile.c_str(), ofile.c_str() ) ) {
    	filemanager->merge( ofile.c_str(), clone.c_str() );	
    }
    exit(1);
}




