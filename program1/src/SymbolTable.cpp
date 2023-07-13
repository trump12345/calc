#include"SymbolTable.h"
#include<algorithm>
#include"Exception.h"
using namespace std;
unsigned int SymbolTable::Add(const std::string& str)
{
    dictionary[str]=curid;
    return curid++;

}

unsigned int SymbolTable::Find(const std::string& str) const
{
    map<const std::string, unsigned int> ::const_iterator it;
    it =dictionary.find(str);
    if(it!=dictionary.end())
        return it->second;
    return IDNOTFOUND;
}

void SymbolTable::Clear()
{
    dictionary.clear();
    curid=0;
}
//函数对象 STL组件 让一个类对象使用起来像一个函数
class IsEqualId
{
    public:
        explicit IsEqualId(unsigned int id):id(id) {}
        bool operator() (const std::pair<const string, unsigned int>& it) const{
            return it.second==id;
        }
    private:
        unsigned int id;

};
std:: string SymbolTable::GetSymbolName(unsigned int id) const//根据符号id 查找符号名称
{
    map<const std::string, unsigned int> ::const_iterator it;
    it = find_if(dictionary.begin(), dictionary.end(), IsEqualId(id));
    if(it==dictionary.end())
    {
        throw Exception("Internal error missing entry in symboltable.");
    }
    
    return it->first;
}