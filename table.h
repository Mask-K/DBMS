#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>

#include "row.h"
#include "column.h"

class table
{
public:
    table(const std::string& name);
    void add_row(const row& row);
    std::vector<row> get_rows();

    void add_column(std::shared_ptr<column> column);

    std::vector<std::shared_ptr<column>> get_columns();
private:
    std::string name__;
    std::vector<row> rows__;
    std::vector<std::shared_ptr<column>> columns__;
};

#endif // TABLE_H
