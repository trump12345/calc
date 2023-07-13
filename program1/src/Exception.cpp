#include"Exception.h"

 const char* Exception:: what() const throw()
{
    return message.c_str();
}