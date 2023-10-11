#include "table.h"

table::table(const QString& name) : name__(name)
{

}

void table::add_column(std::shared_ptr<column> column){
    columns__.push_back(column);
}

std::vector<std::shared_ptr<column> > table::get_columns(){
    return columns__;
}
