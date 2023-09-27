#ifndef DATABASE_H
#define DATABASE_H



#include "table.h"

#include <QString>

class database
{
public:
    database(const QString& name);

    QString get_name();
    std::vector<table> get_tables();
    void add_table(const table& table);
private:
    QString name__;
    std::vector<table> tables__;
};

#endif // DATABASE_H
