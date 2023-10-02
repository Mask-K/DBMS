#include "column_html.h"



column_html::column_html(const QString &name) : column(name){type_ = TYPE::HTML;}

bool column_html::validate(const std::string &value){
    if(value.size() <= 5 || value.substr(value.size() - 4) != "html"
        || !fileExists(value)){
        return false;
    }
    return true;
}

bool column_html::fileExists(const std::string &fileName) {
    std::ifstream file(fileName);
    return file.good();
}
