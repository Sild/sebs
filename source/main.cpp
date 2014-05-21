#include "../header/main.h"

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
    Diff *diff = new Diff();

    Metaworker *mworker = new Metaworker("./input/testcountstr");
    mworker->write(1, "cleanhash", "cpherhash", 0, 200, false);
    exit(1);
}




