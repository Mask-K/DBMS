#include "database.h"

database::database(const QString& name) : name__(name)
{

}

QString database::get_name(){return name__;}

std::vector<table> database::get_tables(){return tables__;}

void database::add_table(const table &table){tables__.push_back(table);}
