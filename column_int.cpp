#include "column_int.h"



column_int::column_int(const QString &name) : column(name){
    type_ = TYPE::INT;
}

bool column_int::validate(const std::string& value){
    for (char c : value){
        if(c < '0' || c > '9')
            return false;
    }
    return value.size() < 10 || value < "2147483647";
}
