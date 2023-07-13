#ifndef _Parser_H
#define _parser_H
class Node;
class Scanner;
class Calc;

enum STATUS
{
    STATUS_OK,
    STATUS_QUIT,
    STATUS_ERROR

};
class  Parser//解析类
{
    public :
        Parser(Scanner&  scanner,Calc& calc);
        STATUS Parse();
        Node *Expr();//表达式
        Node *Term();//项
        Node *Factor();//因式
        double Calculate() const;
    private:
        Node *tree;
        STATUS status;
        Scanner& scanner;
        Calc& calc;

};
#endif  //Parser