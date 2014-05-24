#include "../header/updater.h"

#include <stack>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


Updater::Updater()
{

}


void Updater::update(const char *fname)
{
    if (fname)
    {
        std::string path("../input/");
        path += fname;
        Metaworker meta_worker;
        meta_worker.load(std::string("../output/") + md5(fname));

        // get old hash of file
        std::string old_hash = "fakdhfhfh";

        if (old_hash == md5(fname))
        {
            // file is not changes
            // no need to update metafile
        }
        else
        {
            // find all chunks of old file
            // and try to diff it with current file
            long old_file_size = 52419;
            long new_file_size = 52435;

//            long diff_size = new_file_size - old_file_size;

            long chunks_count = meta_worker.mfile_size();

            typedef std::pair<long, metarow> meta_pair;
            typedef std::vector<meta_pair> vector_meta;

            vector_meta exist_chunks;

            int fd = open(path.c_str(), 0);
            if (-1 == fd)
            {
                std::cout << "error in open file" << std::endl;
                return;
            }
            long lost_size = new_file_size;
            long prev_lost_size = lost_size;
            long position = 0;
            long prev_position = position;
            char *buf = new char[2048];
            for (size_t i = 0; i < chunks_count; ++i)
            {
                //std::cout << "Chech chunk #" << i << std::endl;
                const metarow &row = meta_worker.read(i);
                int chunk_size = row.finish - row.start;

                bool finded = false;

                while (lost_size >= chunk_size)
                {
                    //std::cout << "CH_SIZE " << chunk_size << " LOST " << lost_size << " POS " << position << std::endl;
                    //memset(buf, 0, chunk_size);

                    off_t readed =  pread(fd, buf, chunk_size, position);
                    if (readed != chunk_size)
                    {
                        //std::cout << "We read " << readed << " but need " << chunk_size << std::endl;
                    }
                    std::string hash = md5(std::string(buf, readed));

                    if (hash == row.clean_hash)
                    {
                        exist_chunks.push_back(meta_pair(position, row));
//                                            position += readed;
//                                            lost_size -= readed;
                        prev_lost_size = lost_size - readed;
                        prev_position = position + readed;
                        finded = true;
                        break;
                    }
                    else
                    {
                        position += 1;
                        lost_size -= 1;
                    }
//                    position += readed;
//                    lost_size -= readed;
                }
                if (!finded)
                {
                    lost_size = prev_lost_size;
                    position = prev_position;
                }
            }
            delete[] buf;
            close(fd);

            for (int i=0; i < exist_chunks.size(); i++)
            {
                std::cout << "position: " << exist_chunks.at(i).first << " <-> "
                          << exist_chunks.at(i).second.as_string() << std::endl;
            }


        }
    }
}

#ifdef __UPDATER_UNIT_TEST

int main(int argc, char *argv[])
{
//    if (argc == 2)
//    {
//        Updater up;
//        up.update(argv[1]);
//    }
    Updater up;
    up.update("a.out");


    return 0;
}

#endif
