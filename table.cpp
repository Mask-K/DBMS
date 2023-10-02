#include "table.h"

table::table(const QString& name) : name__(name)
{

}

void table::add_row(const row &row){
    rows__.push_back(row);
}

std::vector<row> table::get_rows(){
    return rows__;
}

void table::add_column(std::shared_ptr<column> column){
    columns__.push_back(column);
}

std::vector<std::shared_ptr<column> > table::get_columns(){
    return columns__;
}
