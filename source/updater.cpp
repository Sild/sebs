#include "../header/updater.h"

Updater::Updater() {
    this->output_dir = "./output/";
    this->buffer_size = 2048;
    this->mworker = new Metaworker();
}


std::pair<std::map<int, int>, std::vector<std::pair<long, long> > >Updater::get_similar(const std::string file_path) {
    this->mworker->load(file_path);

    long old_file_size = this->get_old_filesize();
    long new_file_size = this->get_filesize(file_path);

    long chunk_count = mworker->mdata_size();

    std::map<int, int> similar_chunk;//какой блок - на сколько изменился
    std::vector<std::pair<long, long> > diff;
    int fd = open(file_path.c_str(), 0);

    if (-1 == fd) {
        std::cout << "error in open file" << std::endl;
        std::pair<std::map<int, int>, std::vector<std::pair<long, long> > > result;
        return result;
    }

    long lost_size = new_file_size;
    long prev_lost_size = lost_size;
    long position = 0;
    long prev_position = position;  

    char *buf = new char[this->buffer_size];
    for (size_t i = 0; i < chunk_count; ++i) {

        //std::cout << "Chech chunk #" << i << std::endl;
        const metarow &row = mworker->get(i);
        int chunk_size = row.finish - row.start + 1;

        bool finded = false;
        while (lost_size >= chunk_size) {

            off_t readed =  pread(fd, buf, chunk_size, position);
            std::string hash = md5(std::string(buf, readed));
            if (hash == row.clean_hash) {
                if (( position - prev_position) > 0) {
                    diff.push_back(std::pair<long, long>(prev_position, position - 1));
                }   
                similar_chunk[i] = position - row.start;
                prev_lost_size = lost_size - readed;
                prev_position = position + readed;
                position += readed;
                lost_size -= readed;
                finded = true;
                break;
            } else {
                position += 1;
                lost_size -= 1;
            }
        }
        
        if (!finded) {
            lost_size = prev_lost_size;
            position = prev_position;  
        }
        
    }

    if(lost_size != 0) {
            diff.push_back(std::pair<long, long>(position, new_file_size - 1));
    }
    
    delete[] buf;
    close(fd);
    std::pair<std::map<int, int>, std::vector<std::pair<long, long> > > result(similar_chunk, diff);
    return result;

}

void Updater::show_similar(std::map<int, int> chunks) {
     for(std::map<int, int>::iterator itr = chunks.begin(); itr != chunks.end(); itr++) {
        std::cout << "chunk: " << (*itr).first << " moved on:" << (*itr).second << std::endl;
    }
}

void Updater::show_diff(std::vector<std::pair<long, long> > diff) {
    for(int i = 0; i < diff.size(); i++ ) {
        std::cout << "start: " << diff[i].first << " finish: " << diff[i].second << std::endl;
    }
}

long Updater::get_old_filesize() {
    return (this->mworker->get(this->mworker->mdata_size() - 1)).finish + 1;//последний finish в metadata
}

long Updater::get_filesize(std::string file_path) {
    std::ifstream in(file_path.c_str(), std::ifstream::in | std::ifstream::binary);
    in.seekg(0, std::ifstream::end);
    return in.tellg(); 
}


// #ifdef __UPDATER_UNIT_TEST

// int main(int argc, char *argv[])
// {
// //    if (argc == 2)
// //    {
// //        Updater up;
// //        up.update(argv[1]);
// //    }
//     Updater up;
//     up.update("a.out");


//     return 0;
// }

// #endif
