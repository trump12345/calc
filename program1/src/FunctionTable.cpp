#include"FunctionTable.h"
#include<cmath>
#include"SymbolTable.h"
#include<cassert>
#include<iostream>
struct FunctionEntry
{
    /* data */
    PtrFun pFun;
    char* FunName;
};
FunctionEntry Entrys[]=//数组保存函数表
{
    log,    (char*)"log",
    log10,  (char*)"log10",
    exp,    (char*)"exp",
    sqrt,   (char*)"sqrt",
    sin,    (char*)"sin",
    cos,    (char*)"cos",
    tan,    (char*)"tan",
    sinh,   (char*)"sinh",
    cosh,   (char*)"cosh",
    tanh,   (char*)"tanh",
    asin,   (char*)"asin",
    acos,   (char*)"acos",
    atan,   (char*)"atan",
};
FunctionTable::FunctionTable(SymbolTable& tbl) : size(sizeof(Entrys)/sizeof(Entrys[0]))//函数表
{
    
    Init(tbl);
}
void FunctionTable::Init(SymbolTable& tbl)
{
    std::cout<<"function list:"<<std::endl;//打印函数表
    pFuns =new PtrFun[size];
    for(unsigned int i=0; i<size; ++i)
    {
        pFuns[i] = Entrys[i].pFun;
        unsigned int j=tbl.Add(Entrys[i].FunName);
        assert(i==j);
        std::cout<<Entrys[i].FunName<<std::endl;
    }
}
FunctionTable::~FunctionTable()
{
    delete[] pFuns;
}
