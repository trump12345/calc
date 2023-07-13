#include"Storage.h"
#include"SymbolTable.h"
#include<cmath>
#include<cassert>
#include<iostream>
Storage::Storage(SymbolTable& tbl)
{
    AddConstants(tbl);
}

 void Storage::Clear()
 {
    cells.clear();
    inits.clear();
 }

bool Storage::Isinit(unsigned int id) const
{
    return id < cells.size() && inits[id];
}

void Storage::AddConstants(SymbolTable& tbl)
{
    std::cout<<"variable list:"<<std::endl;
    
    unsigned int id =tbl.Add("e");
    AddValue(id,exp(1.0));
    std::cout<<"e= "<<exp(1.0)<<std::endl;

    id =tbl.Add("pi");
    AddValue(id , 2.0*acos(0.0));//反余弦 pi =2*arccos(0)
    std::cout<<"pi= "<<2.0*acos(0.0)<<std::endl;
}

double Storage::GetValue(unsigned int id) const
{
    assert(id<cells.size());
    return cells[id];
}

void Storage::SetValue(unsigned int id, double val)
{
    assert(id <= cells.size());
    if(id< cells.size())
    {
        cells[id]=val;
        inits[id]=true;
    }
    else if(id == cells.size())
    {
        AddValue(id, val);
    }
}

void Storage::AddValue(unsigned int id, double val)
{
    cells.resize(id+1);
    inits.resize(id+1);
    cells[id]=val;
    inits[id]=true;
}