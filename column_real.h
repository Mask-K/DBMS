#ifndef COLUMN_REAL_H
#define COLUMN_REAL_H

#include "column.h"

class column_real : public column
{
public:
    column_real(const QString& name);;
    bool validate(const std::string& value);
};

#endif // COLUMN_REAL_H
