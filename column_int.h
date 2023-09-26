#ifndef COLUMN_INT_H
#define COLUMN_INT_H

#include "column.h"

class column_int : public column
{
public:
    column_int(const std::string& name);;
    bool validate(const std::string value);
};

#endif // COLUMN_INT_H
