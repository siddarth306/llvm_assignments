#include <cstdio>
using namespace std;
bool foo()
{
    return true;
}
int main()
{
    int a=1;
    a=a+foo();
        printf("%d",a);
    
}

