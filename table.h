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

    QString getName() const{
        return name__;
    }
    std::shared_ptr<column> get_column(int index){
        return columns__[index];
    }

    bool column_exists(const QString& col_name){
        for(const auto col : columns__){
            if(col->getName() == col_name)
                return true;
        }
        return false;
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
