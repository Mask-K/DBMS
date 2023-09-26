#include "column_string.h"

column_string::column_string(const std::string &name): column(name){
    type_ = TYPE::STRING;
}

bool column_string::validate(const std::string value){
    return true;
}
