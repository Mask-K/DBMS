#include "column.h"

column::column(const QString& name) : name__(name)
{

}

TYPE column::get_type(){
    return type_;
}
