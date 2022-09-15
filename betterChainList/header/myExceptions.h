#ifndef MYEXCEPTIONS
#define MYEXCEPTIONS
#include <cstdio>

class EmptyChain
{
public:
    EmptyChain() { strcat_s(prefix, message); }
    EmptyChain(const char* str) { message = str; strcat_s(prefix, message); }
    void show() { puts(prefix); }
private:
    char prefix[100] = "\n[WARNING] ";
    const char* message = "Operating on an empty chain.";
};

class ErrorType
{
public:
    ErrorType() { strcat_s(prefix, message); }
    ErrorType(const char* str) { message = str; strcat_s(prefix, message); }
    void show() { puts(prefix); }
private:
    char prefix[100] = "\n[WARNING] ";
    const char* message = "Error type.";
};
#endif // !MYEXCEPTIONS
