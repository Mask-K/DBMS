#ifndef COLUMN_HTML_H
#define COLUMN_HTML_H

#include "column.h"

class column_html : public column
{
public:
    column_html(const std::string& name) : column(name){type_ = TYPE::HTML;}
    bool validate(const std::string& value);
};

#endif // COLUMN_HTML_H
