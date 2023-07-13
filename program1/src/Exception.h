#ifndef   _EXPTION_H
#define   _EXPTION_H
#include<exception>
#include<string>

class Exception : public std::exception
{
    public:
        explicit Exception(const char *message)//explicit 可以避免隐式转换的发生
            :message(message)
        {

        }
        virtual ~Exception() throw()
        {
            
        }
        virtual const char* what() const throw();
    private:
        std::string message;
};

class SyntaxError : public Exception
{
    public:
        explicit SyntaxError(const char *message)
            :Exception(message)
            {

            }
        virtual ~SyntaxError() throw()
        {

        }
    private:
};




#endif    //_EXPTION_H