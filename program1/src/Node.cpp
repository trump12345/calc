#include "Node.h"
#include<cmath>
#include<iostream>
#include<cassert>
#include"Storage.h"
double NumberNode ::Calc ()  const 
{
    return number;
}
UnaryNode::~UnaryNode(){
    delete child;
}
BinaryNode::~BinaryNode(){
    delete left;
    delete right;
}
/*
double AddNode::Calc() const//加
{
        return  left->Calc() + right->Calc();
   }

double SubNode::Calc() const//减
{
        return  left->Calc() -right->Calc();
   }
 
double MulNode::Calc() const//乘
{
        return  left->Calc() *right->Calc();
   }
 
double DivNode::Calc() const//除
{
    double  divisor =right->Calc();
    
    if(divisor!=0.0){
                return  left->Calc()/ right->Calc();
    }else {
       std::cout<<"Error :除数不能为0"<<std::endl;
       return  HUGE_VAL;
    }
       
   }
   */
double FunctionNode ::Calc() const
   {
            return (*pFun)(child->Calc());
   }

   
double UMinusNode ::Calc() const
   {
            return -child->Calc();
   }

MultipleNode::~MultipleNode(){
    std::vector<Node*>::const_iterator it;
    for(it=childs.begin(); it!=childs.end(); ++it)
    {
        delete *it;
    }
}
double SumNode::Calc() const//加减法
{
    double result =0.0;
    std::vector<Node*>:: const_iterator childit=childs.begin();
    std::vector<bool>::const_iterator positiveit=positives.begin();

    for(;childit!=childs.end();++childit,++positiveit)
    {
        assert(positiveit!=positives.end());
        double val= (*childit)->Calc();
        if(*positiveit)
        {
            result +=val;
        }
        else result -=val;
    }
    assert(positiveit==positives.end());

    return result;
}
double ProductNode::Calc() const//乘除法
{
    double result =1.0;
    std::vector<Node*>:: const_iterator childit=childs.begin();
    std::vector<bool>::const_iterator positiveit=positives.begin();

    for(;childit!=childs.end();++childit,++positiveit)
    {
        assert(positiveit!=positives.end());
        double val= (*childit)->Calc();
        if(*positiveit)
        {
            result *=val;
        }
        else if(val!=0.0){
            result /=val;
         }
        else{
            std::cout<<"除数为0。"<<std::endl;
            return HUGE_VAL;
        }
    }
    assert(positiveit==positives.end());

    return result;

}

double VariableNode::Calc() const
{
    double x=0.0;
    if(storage.Isinit(id))
    {
        x= storage.GetValue(id);
    }
    else
    {
        std::cout<<"Use of uninitialized variable."<<std::endl;
    }
    return x;
}

bool VariableNode::Isvalue() const
{
    return true;
}

void VariableNode::Assign(double val)
{
    storage.SetValue(id , val);
}

double AssignNode::Calc() const //赋值
{
    double x=0.0;
    x= right->Calc();
    left->Assign(x);
    return x;

}