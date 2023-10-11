#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <memory>
#include <QString>

#include "column.h"

class table
{
public:
    table(const QString& name);


    std::shared_ptr<column> get_column(int index){
        return columns__[index];
    }

    void add_column(std::shared_ptr<column> column);

    void remove_column(int index){
        columns__.erase(columns__.begin() + index);
    }

    std::vector<std::shared_ptr<column>> get_columns();
private:
    QString name__;
    std::vector<std::shared_ptr<column>> columns__;
};

#endif // TABLE_H
