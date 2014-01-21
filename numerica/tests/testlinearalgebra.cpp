#include <numerica/tests/testlinearalgebra.h>
#include <numerica/linearalgebra/linearalgebra.h>

using namespace std;
using namespace numerica;
using namespace linearAlgebra;
using namespace tools;

void TestLinearAlgebra()
{
    cout<<"Testing Gauss"<<endl;

    double data[]={3.03, -12.1, 14,  //Burden & Faires, Ex 5c p. 369
                   -3.03, 12.1, -7,
                   6.11, -14.2, 21};
    double datab[]={-119,120,-139};
    const int n=sizeof(datab)/sizeof(double);
    Matrix A(data,n,n);
    NVector b(datab,n);
    cout<<"Matrix A:"<<endl<<A;
    cout<<"Vector b: "<<b<<endl;
    cout<<"Solution: "<<Solve(A,b)<<endl;
    cout<<"Determinant: "<<Determinant(A)<<endl<<endl;
    cout<<"Inverse matrix:"<<endl<<Inverse(A);
}
