#ifndef _STORAGE_H
#define _STORAGE_H
#include<vector>
class SymbolTable;

class Storage//存储常量和变量的值
{
    public:
        Storage(SymbolTable& tbl);
        void Clear();
        bool Isinit(unsigned int id) const;
        void AddConstants(SymbolTable& tbl);//常量
        double GetValue(unsigned int id) const;
        void SetValue(unsigned int id, double val);
        void AddValue(unsigned int id, double val);

    private:
        std::vector<double> cells;
        std::vector<bool> inits;
};


#endif //STORAGE