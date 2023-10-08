#ifndef ROW_H
#define ROW_H


#include <vector>
#include <string>
#include <stdexcept>
class row
{
public:
    row(int amount);
    void add_cell(const std::string value = ""){
        values__.push_back(value);
    }
    std::string& operator[](int index){
        if(index >= values__.size())
            throw std::runtime_error("Wrong index");
        return values__[index];
    }

private:
    std::vector<std::string> values__;
};

#endif // ROW_H
