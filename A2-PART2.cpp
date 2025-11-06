#include <iostream>
#include <unistd.h>  //to get pid 

int main() {
    std::cout << "Process started. PID = " << getpid() << std::endl;
    return 0;
}
