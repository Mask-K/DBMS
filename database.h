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

    bool table_exists(const QString& name){
        for(const auto& t : tables__){
            if(t.getName() == name)
                return true;
        }
        return false;
    }
    void remove_table(const int& index){
        tables__.erase(tables__.begin()+index);
    }
    table& get_table(const int index){
        return tables__[index];
    }
private:
    QString name__;
    std::vector<table> tables__;
};

#endif // DATABASE_H
