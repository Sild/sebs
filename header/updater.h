#ifndef UPDATER_H
#define UPDATER_H


#include "metaworker.h"
#include "md5.h"

class Updater
{
public:
    Updater();
    void update(const char *f_name);
};

#endif // UPDATER_H
