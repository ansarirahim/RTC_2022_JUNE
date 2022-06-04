#include <unistd.h>
int main()
{ 
execlp( "login", "login", "-f", "zymos", 0);
}
