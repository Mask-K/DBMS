#include "column.h"

column::column(const std::string& name) : name__(name)
{

}

TYPE column::get_type(){
    return type_;
}
