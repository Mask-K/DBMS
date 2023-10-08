#include "row.h"

row::row(int amount)
{
    for(int i = 0; i < amount; ++i){
        add_cell();
    }
}
