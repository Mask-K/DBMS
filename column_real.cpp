#include "column_real.h"



column_real::column_real(const std::string &name): column(name){
    type_ = TYPE::REAL;
}

bool column_real::validate(const std::string value){
    try{
        size_t pos;
        double val = std::stod(value, &pos);
        if(pos != value.size())
            return false;
        return true;
    }
    catch(...){
        return false;
    }
}
