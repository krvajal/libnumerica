#include <numerica/numerica.h>
#include <iostream>

using namespace numerica::tools;

int main(int argc, char * argv[]){

    NVector v = linspace(0,10,1000);

    std::cout << v  << std::endl;

    return 0;
}