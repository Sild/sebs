#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <string>
#include "../header/filemanager.h"


using namespace std;

void copy(string ipath, string opath) {
	char * buffer;
    int len = 4096; //Выбираем размер буфера, какой нравится
 
    ifstream infile(ipath.c_str(), ios::in | ios::binary);
    ofstream outfile(opath.c_str(), ios::out | ios::binary);
    if(!infile || !outfile){ //ошибку открытия файлов стоит отслеживать, всякое бывает
        cout << "file not found\n";
        return;
    }
 
    buffer = new char[len];
    while (!infile.eof()){
        infile.read(buffer, len);
        if(infile.gcount()) outfile.write(buffer, infile.gcount());
        //gcount возвращает количество байт, считанных в последний раз
        //ее и используем для проверки, что что-то считалось, а заодно устанавливаем количество записываемых байт
    }
 
    infile.close();
    outfile.close(); //позакрывали файлы
    delete[] buffer;
}






int main(int argc, char *argv[])
{
    boost::filesystem::path app_path = get_app_path();

    string out = "/output/acpy.out";
    string in = "/input/a.out";
    cout << app_path.string() << endl;
    copy((app_path.string() + in).c_str(), (app_path.string() + out).c_str());

    exit(1);
}




