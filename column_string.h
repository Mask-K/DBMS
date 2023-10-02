#ifndef COLUMN_STRING_H
#define COLUMN_STRING_H

#include "column.h"

class column_string : public column
{
public:
    column_string(const QString& name);

    bool validate(const std::string& value);
};

#endif // COLUMN_STRING_H
