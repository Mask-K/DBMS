#include "column_real.h"



column_real::column_real(const QString &name): column(name){
    type_ = TYPE::REAL;
}

bool column_real::validate(const std::string& value){
    try{
        std::locale savedLocale = std::locale::global(std::locale::classic());


        size_t pos;
        double val = std::stod(value, &pos);

         std::locale::global(savedLocale);

        if(pos != value.size())
            return false;
        return true;
    }
    catch(...){
        return false;
    }
}
