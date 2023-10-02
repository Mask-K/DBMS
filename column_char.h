#ifndef COLUMN_CHAR_H
#define COLUMN_CHAR_H

#include "column.h"

class column_char : public column
{
public:
    column_char(const QString& name);

    bool validate(const std::string& value);
};

#endif // COLUMN_CHAR_H
