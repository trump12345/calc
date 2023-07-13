#ifndef FUNCTION_TABLE_H
#define FUNCTION_TABLE_H

class SymbolTable;
typedef double(*PtrFun)(double);

class FunctionTable  //函数表
{
    public:
        FunctionTable(SymbolTable& tbl);
        ~FunctionTable();
        void Init(SymbolTable& tbl);
        unsigned int Size() const
        {
            return size;
        }
        PtrFun GetFunction(unsigned int id) const
        {
            return pFuns[id];
        }
    private:
        PtrFun* pFuns;
        unsigned int size;

};
#endif  //FUNCTION_TABLE_H