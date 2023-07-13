#include"Parser.h"
#include"Scanner.h"
#include"Node.h"
#include<cassert>
#include<iostream>
#include"Calc.h"
#include"SymbolTable.h"
#include"Exception.h"
#include<cstring>
Parser ::Parser(Scanner& scanner,Calc& calc):scanner(scanner), calc(calc),tree(0) ,status(STATUS_OK) { }

STATUS Parser::Parse()
{
    tree =Expr();
    if(!scanner.IsDone())
    {
        status=STATUS_ERROR;
    }
    return status;
}

 Node *Parser::Expr()//表达式
 {  
    Node *node = Term();
    EToken token = scanner.Token();
    // if(token == TOKEN_PLUS)
    // {
    //     scanner.Accept();
    //     Node *noderight =Expr();//递归
    //     node =new AddNode (node,noderight);
    // }
    // else if(token == TOKEN_MINUS){
    //     scanner.Accept();
    //     Node *noderight =Expr();
    //     node =new SubNode (node,noderight);
    // }
    if(token ==TOKEN_PLUS || token == TOKEN_MINUS)//左结合加减法
    {
        MultipleNode *multipleNode =new SumNode(node);
        do
        {
            scanner.Accept();
            Node *nextnode = Term();
            multipleNode->AppendChild(nextnode, (token ==TOKEN_PLUS));
            token= scanner.Token();
            

        }while(token ==TOKEN_PLUS || token == TOKEN_MINUS);
        node = multipleNode;
    }
    else if(token==TOKEN_ASSIGN)
    {
        scanner.Accept();
        Node *nodeRight = Expr();
        if(node->Isvalue())
        {
            node = new AssignNode(node, nodeRight);
        }
        else{
            status = STATUS_ERROR;
            //std::cout<<"The left-hand side of an assignment must be a variable."<<std::endl;
            throw SyntaxError("The left-hand side of an assignment must be a variable.");
        }
    }
    
    return node;
 }

 Node *Parser::Term(){//项
    Node *node = Factor();
    EToken token = scanner.Token();
    // if(token == TOKEN_MULTIPLY)
    // {
    //     scanner.Accept();
    //     Node *noderight =Term();
    //     node =new MulNode(node,noderight);
    // } 
    // else if(token == TOKEN_DIVIDE){
    //     scanner.Accept();
    //     Node *noderight =Term();
    //     node =new DivNode(node,noderight);
    // }
    if(token ==TOKEN_MULTIPLY || token == TOKEN_DIVIDE)//左结合乘除法
    {
        MultipleNode *multipleNode =new ProductNode(node);
        do
        {
            scanner.Accept();
            Node *nextnode = Factor();
            multipleNode->AppendChild(nextnode, (token ==TOKEN_MULTIPLY));
            token= scanner.Token();

        }while(token ==TOKEN_MULTIPLY || token == TOKEN_DIVIDE);
        node = multipleNode;
    }
    return node;

 }


Node *Parser::Factor()//因式
{
    Node *node=0;
    EToken token =scanner.Token();
    if(token==TOKEN_LPARENTHESIS)
    {
        scanner.Accept();//接受（
        node =Expr();
        if(scanner.Token( )== TOKEN_RPARENTHESIS)
        {
            scanner.Accept();//接受）
        }else
        {
            status=STATUS_ERROR;
            //炮异常
            //std::cout<<"missing parenthsis."<<std::endl;
            throw SyntaxError("missing parenthsis.");
            node=0;
        }
    }else if(token == TOKEN_NUMBER)
    {   
        node = new NumberNode(scanner.Number());
        scanner.Accept();
        
    }else if(token== TOKEN_IDENTIFIER)//支持变量赋值
    {
        std::string symbol =scanner.GetSymbol();//获取标识符名称
        unsigned int id =calc.FindSymbol(symbol);
        scanner.Accept();
        if(scanner.Token()==TOKEN_LPARENTHESIS)//函数,如abc()
        {
            scanner.Accept(); //接受“（”
            node=Expr();
            if(scanner.Token()==TOKEN_RPARENTHESIS)
            {
                scanner.Accept(); //接受“)”
                if(id != SymbolTable::IDNOTFOUND && calc.IsFunction(id))
                {
                    node = new FunctionNode(node, calc.GetFunction(id));
                }else
                {
                    status=STATUS_ERROR;
                    //std::cout<<"unknown function."<<symbol<<std::endl;
                    char buf[256]={0};
                    sprintf(buf,"unknown function \"%s\".",symbol);
                    throw SyntaxError(buf);
                }
            }else
            {
                status=STATUS_ERROR;
                //std::cout<<"missing )."<<std::endl;
                throw SyntaxError("missing )");
            }
        }
        else
        {
            if(id== SymbolTable::IDNOTFOUND) //变量
        {
            id = calc.AddSymbol(symbol);
        }
        node=new VariableNode(id,calc.GetStorage());

        }
        
    }
    else if(token==TOKEN_MINUS)
    {
        scanner.Accept();//接受-
        node = new UMinusNode(Factor());
       
    }else{
        status= STATUS_ERROR;
        //std::cout<<"Not a valid expression."<<std::endl;
         throw SyntaxError("Not a valid expression.");
        node=0;
    }
    return node;
}

double Parser::Calculate() const
{
    assert(tree != 0);
    return tree->Calc();//tree是node类，所以可以引用node里边的函数
    
}