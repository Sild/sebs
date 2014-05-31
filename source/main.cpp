#include "../header/main.h"

using namespace std;


int main(int argc, char *argv[])
{
    string target = "./input/a.out";
    Filemanager *filemanager = new Filemanager(); 
    if(!strncmp(argv[1], "seg", 3)) {
         filemanager->segmentate(target);
    }  else if (!strncmp(argv[1], "mer", 3)) {
        filemanager->merge( target );   
    } else if (!strncmp(argv[1], "upd", 3)) {
        filemanager->update(target);     
    }
    
    
    // Diff *diff = new Diff();

    // Metaworker *mworker = new Metaworker();
    // mworker->load("./input/testcountstr");
    // mworker->write("clean_hash3last", "cipher_hashlast", 0, 200);
    // // mworker->show();
    // mworker->save();
    // delete mworker;
    // int inotify = inotify_init();
    // int watcher = inotify_add_watch(inotify, "./output", IN_CREATE | IN_MODIFY | IN_DELETE);

    // Inotify *inotify = new Inotify();
    // inotify->set_watcher("./input");
    // inotify->start_watch();
    exit(1);
}




