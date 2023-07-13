#ifndef _Scanner_H
#define _Scanner_H
#include<string>


enum EToken{//枚举类型，扫描
    TOKEN_END,
    TOKEN_ERROR,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPARENTHESIS,
    TOKEN_RPARENTHESIS,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,

};
class  Scanner//扫描类
{   
    public :
        Scanner (const std::string& buf) ;
        void Accept();//扫描方法
        bool IsEmpty() const;
        bool IsDone() const;
        double Number() const;//返回数字
        EToken Token() const;//返回状态
        std::string  GetSymbol() const;//获取符号
    private:
        const  std::string buf;
        void SkipWhite();//跳过空白字符
        EToken token;//状态
        double number;
        unsigned int curpos;//当前位置 
        std::string symbol;//符号标识符
        bool isempty;
};

#endif  //Scanner