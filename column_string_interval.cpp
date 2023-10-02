#include "column_string_interval.h"


column_string_interval::column_string_interval(const QString &name): column(name){
    type_ = TYPE::STRINGINVL;
}

bool column_string_interval::validate(const std::string& value){
    size_t pos = value.find(',');
    if(pos == std::string::npos)
        return false;

    auto left = value.substr(0, pos);
    auto right = value.substr(pos+1);

    //remove spaces in front and in back
    remove_spaces(left);
    remove_spaces(right);

    return left < right;
}

void column_string_interval::remove_spaces(std::string &val){
    size_t start = val.find_first_not_of(' ');
    size_t end = val.find_last_not_of(' ');
    if (start != std::string::npos && end != std::string::npos) {
        val = val.substr(start, end - start + 1);
    } else {
        val.clear();
    }
}
