#ifndef COLUMN_STRING_INTERVAL_H
#define COLUMN_STRING_INTERVAL_H

#include "column.h"

class column_string_interval : public column
{
public:
    column_string_interval(const QString& name);;
    bool validate(const std::string& value);

private:
    void remove_spaces(std::string& val);
};

#endif // COLUMN_STRING_INTERVAL_H
