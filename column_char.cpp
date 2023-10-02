#include "column_char.h"



column_char::column_char(const QString &name) : column(name){
    type_ = TYPE::CHAR;
}

bool column_char::validate(const std::string& value){
    if(value.size() == 1)
        return true;
    return false;
}
