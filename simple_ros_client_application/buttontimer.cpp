#include "buttontimer.h"
#include <QString>

buttontimer::buttontimer()
{
    this->button_name = "";
}


void buttontimer::set_buttonname(QString value){
    this->button_name = value;
}


QString buttontimer::get_buttonname(){
   return this->button_name;
}
