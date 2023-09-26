#ifndef COLUMN_H
#define COLUMN_H

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
    column(const std::string& name);
    virtual bool validate(const std::string& value) = 0;
    TYPE get_type(){
        return type_;
    }
protected:
    TYPE type_;

private:
    std::string name__;

};

#endif // COLUMN_H
