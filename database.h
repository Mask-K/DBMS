#ifndef DATABASE_H
#define DATABASE_H



#include "table.h"

class database
{
public:
    database(const std::string& name);

    std::string get_name();
    std::vector<table> get_tables();
    void add_table(const table& table);
private:
    std::string name__;
    std::vector<table> tables__;
};

#endif // DATABASE_H
