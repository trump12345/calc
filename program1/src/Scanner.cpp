#include"Scanner.h"
#include<cctype>

Scanner::Scanner(const std::string& buf): buf(buf),curpos(0)
{
    Accept();
    isempty = (token ==TOKEN_END);
}
bool Scanner::IsEmpty() const
{
    return isempty;
}
bool Scanner::IsDone() const
{
    return token==TOKEN_END;
}
double Scanner::Number() const
{
    return number;
}

std::string Scanner::GetSymbol() const//获取标识符名字
{
    return symbol;
}

EToken Scanner::Token() const{
    return token;
}

void Scanner::SkipWhite()
{
    while(isspace(buf[curpos]))
        ++curpos;
}

void Scanner::Accept()//扫描
{
    SkipWhite();
    switch(buf[curpos])
    {
        case '+':
            token = TOKEN_PLUS;
            ++curpos;
            break;
        case '-':
            token = TOKEN_MINUS;
            ++curpos;
            break;
        case '*':
            token = TOKEN_MULTIPLY;
            ++curpos;
            break;
        case '/':
            token = TOKEN_DIVIDE;
            ++curpos;
            break;
        case '=' :
            token =TOKEN_ASSIGN;
            ++curpos;
            break;
        case '(':
            token = TOKEN_LPARENTHESIS;
            ++curpos;
            break;
        case ')':
            token = TOKEN_RPARENTHESIS;
            ++curpos;
            break;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9': case '.' :
            token = TOKEN_NUMBER;
            char *p;
            number=strtod(&buf[curpos], &p);
            curpos = p - &buf[0];
            break;
        case '\0' : case '\n' : case '\r' : case EOF :
            token = TOKEN_END;
            break;
        default :
            if(isalpha(buf[curpos])||buf[curpos]=='_')//解析标识符
            {
                token =TOKEN_IDENTIFIER;
                symbol.erase();
                char ch= buf[curpos];
                do
                {
                    symbol += ch;
                    ++curpos;
                    ch= buf[curpos];
                }while(isalnum(ch) || ch=='_');
            }
            else
                token=TOKEN_ERROR;
            break;

    }
}
