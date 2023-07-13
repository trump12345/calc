#include"Calc.h"

unsigned int Calc::FindSymbol(const std::string& str) const
{
    return symtbl.Find(str);
}
bool Calc::IsFunction(unsigned int id) const //判断是不是一个函数
{
    return id<funtbl.Size();
}
 unsigned int Calc::AddSymbol(const std::string& str)
 {
    return symtbl.Add(str);
 }