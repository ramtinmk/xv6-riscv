#include "kernel/types.h" 
#include "user/user.h" 

int main() { 
    int result = trigger();
    printf("hello");
    return result;

} 