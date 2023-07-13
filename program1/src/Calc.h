#ifndef _CALC_H
#define _CALC_H
#include"SymbolTable.h"
#include"Storage.h"
#include<string>
#include"FunctionTable.h"

class Parser;
class Calc
{
    friend class Parser;
    public:
        Calc():funtbl(symtbl),storage(symtbl) {}
    private:
         Storage& GetStorage() {
            return storage;
        }
        PtrFun GetFunction(unsigned int id) const
        {
            return funtbl.GetFunction(id);
        }
        bool IsFunction(unsigned int id) const;
        unsigned int AddSymbol(const std::string& str);
        unsigned int FindSymbol(const std::string& str) const;
        SymbolTable symtbl;
        FunctionTable funtbl;
        Storage storage;
        
};
#endif //_CALC