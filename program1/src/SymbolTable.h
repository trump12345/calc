#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_
#include<map>

#include<string>
class SymbolTable//符号表 变量函数都算符号
{
    
    public:
        enum {IDNOTFOUND = 0xffffffff};
        SymbolTable() : curid(0) {}
        unsigned int Add(const std::string& str);
        unsigned int Find(const std::string& str) const;
        void Clear();
        std:: string GetSymbolName(unsigned int id) const;
        ~SymbolTable(){}
    private:
        std::map<const std::string, unsigned int> dictionary;
        unsigned int curid;//当前符号id
};




#endif //_SYMBOL_TABLE_H_