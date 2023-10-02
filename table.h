#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>
#include <QString>

#include "row.h"
#include "column.h"

class table
{
public:
    table(const QString& name);
    void add_row(const row& row);
    std::vector<row> get_rows();

    void add_column(std::shared_ptr<column> column);

    std::vector<std::shared_ptr<column>> get_columns();
private:
    QString name__;
    std::vector<row> rows__;
    std::vector<std::shared_ptr<column>> columns__;
};

#endif // TABLE_H
