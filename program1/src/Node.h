#ifndef    _NODE_H
#define    _NODE_H
#include"FunctionTable.h"
#include<vector>
#include<cassert>

class Storage;
class  Nonecopyable//抽象类不用来建立对象     变成对象语义：浅拷贝
{
        protected: 
                Nonecopyable() {}
                ~Nonecopyable() {}
        private:
                Nonecopyable(const Nonecopyable&);//拷贝构造函数     自定义拷贝构造函数，系统不会再给默认拷贝构造，这里做了约束，不能拷贝构造也不能赋值，=运算符被重载了
                const Nonecopyable&  operator= (const  Nonecopyable&);//=重载
};
class Node: private  Nonecopyable//抽象类    使用私有继承是因为Node只是需要使用基类的函数，而不必继承他的接口
{
        public :  
                virtual  double Calc() const =0;   //虚函数 后边还能用
                virtual  bool Isvalue() const
                {
                        return false;
                }
                virtual void Assign(double){
                        assert(!"Assign called incorrectlly.");
                }
                virtual  ~Node() { };
};


class NumberNode : public  Node //数字节点
{
        public  :
                NumberNode(double number):number(number){}
                double  Calc()  const ;

        private:
                double   number;

};
class UnaryNode:public Node
{
        public:
                UnaryNode (Node * child): child(child) {}
                ~UnaryNode();
        protected:
                Node *const child;
};

class FunctionNode : public UnaryNode//函数节点
{
public:
        FunctionNode(Node* child, PtrFun pFun)
                :UnaryNode(child), pFun(pFun) {}
        double Calc() const;

private:
        PtrFun pFun;

        
};

class  BinaryNode: public  Node//二元运算
{
    public:
                BinaryNode(Node*  left , Node * right)  :  left (left), right (right )  {  }
                ~BinaryNode();
    protected:
                Node  *const  left;
                Node  *const  right;
};

/*
class  AddNode : public  BinaryNode //加法
{
        public :
                AddNode(Node * left  ,Node * right):BinaryNode(left ,right )  {}
                double  Calc()  const ;
        //private:
};

class  SubNode : public  BinaryNode //减法
{
        public :
                SubNode(Node * left  ,Node * right):BinaryNode(left ,right )  {}
                double  Calc()  const ;
        //private:
};
class  MulNode : public  BinaryNode //乘法
{
        public :
                MulNode(Node * left  ,Node * right):BinaryNode(left ,right )  {}
                double  Calc()  const ;
        //private:
};
class  DivNode : public  BinaryNode //除法
{
        public :
                DivNode(Node * left  ,Node * right):BinaryNode(left ,right )  {}
                double  Calc()  const ;
        //private:
};
*/
class UMinusNode : public UnaryNode
{
        public:
                UMinusNode(Node* child):UnaryNode(child) {}
                double  Calc()  const ;
};

class MultipleNode :public Node//多项式加减或乘除按顺序运算
{
        public:
                MultipleNode(Node *node)  {
                        AppendChild(node,true);
                }
                void AppendChild(Node *node,bool positive)//添加子节点
                {
                        childs.push_back(node);
                        positives.push_back(positive);//正负判断
                }
                ~MultipleNode();
        protected:
                std::vector<Node*> childs;
                std::vector<bool> positives;


};

class SumNode: public MultipleNode
{
        public:
                SumNode(Node *node)
                        : MultipleNode(node) {}
                double Calc() const;


};
class ProductNode: public MultipleNode
{
        public:
                ProductNode(Node *node)
                        : MultipleNode(node) {}
                double Calc() const;
};

class VariableNode : public Node//变量节点
{
        public:
                VariableNode(unsigned int id, Storage& storage)
                        : id (id), storage(storage) {}
                double Calc() const;
                bool Isvalue() const;
                void Assign(double val);
        private:
                const unsigned int id;
                Storage& storage;

};
class AssignNode : public BinaryNode//变量赋值
{
        public:
                AssignNode(Node* left, Node* right)
                        : BinaryNode(left,right)
                        {
                                assert(left->Isvalue());
                        }
        double Calc() const ;

};
#endif    //NODE