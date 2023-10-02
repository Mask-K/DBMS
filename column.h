#ifndef COLUMN_H
#define COLUMN_H

#include <QString>
#include <string>

enum TYPE{
    INT = 0,
    REAL,
    CHAR,
    STRING,
    HTML,
    STRINGINVL
};


class column
{
public:
    column(const QString& name);
    virtual bool validate(const std::string& value) = 0;
    TYPE get_type();
protected:
    TYPE type_;

private:
    QString name__;

};

#endif // COLUMN_H
