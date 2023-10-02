#ifndef COLUMN_HTML_H
#define COLUMN_HTML_H

#include <fstream>

#include "column.h"

class column_html : public column
{
public:
    column_html(const QString& name);
    bool validate(const std::string& value);
private:
    bool fileExists(const std::string& fileName);
};

#endif // COLUMN_HTML_H
