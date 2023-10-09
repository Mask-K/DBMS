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
    std::vector<row>& get_rows();

    std::shared_ptr<column> get_column(int index){
        return columns__[index];
    }

    row& operator[](int index){
        if(index >= rows__.size())
            throw std::runtime_error("Wrong index");
        return rows__[index];
    }

    void add_column(std::shared_ptr<column> column);

    void remove_column(int index){
        columns__.erase(columns__.begin() + index);
    }

    std::vector<std::shared_ptr<column>> get_columns();

    void remove_row(int index){
        rows__.erase(rows__.begin() + index);
    }
private:
    QString name__;
    std::vector<row> rows__;
    std::vector<std::shared_ptr<column>> columns__;
};

#endif // TABLE_H
