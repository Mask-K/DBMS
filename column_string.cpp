#include "column_string.h"

column_string::column_string(const QString &name): column(name){
    type_ = TYPE::STRING;
}

bool column_string::validate(const std::string& value){
    return true;
}
