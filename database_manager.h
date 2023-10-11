#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "database.h"
class database_manager
{
public:
    database_manager(database* database = nullptr) : database__(database){}

    void set_database(database* database){
        database__ = database;
    }
    database* get_database(){
        return database__;
    }



private:
    database* database__;
};

#endif // DATABASE_MANAGER_H
