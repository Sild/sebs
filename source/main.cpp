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

	string A("abc");
	string B("abd");
	dtl::Diff< char, string > d(A, B);
// d.onOnlyEditDistance();
	d.compose();             // construct an edit distance and LCS and SES
	    d.printSES();
	    d.getEditDistance();
d.composeUnifiedHunks(); // construct a difference as Unified Format with SES.
std::cout << "lol" << std::endl;
d.printUnifiedFormat();  // print a difference as Unified Format.

    exit(1);
}




