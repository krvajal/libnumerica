#include <numerica/tests/testroots.h>
#include <iostream>

#include <numerica/roots/roots.h>

using namespace std;
using namespace numerica::roots;


void TestRoots()
{
    TestBisection();
    TestBrent();
    TestMuller();
    TestNewton();
    TestSecant();
}


//------------------------------ Functions ----------------------------//

double f(double x)
{
    double a=cos(2.0*x);
    return a*a-x*x;

}

complex<double> myfunction(complex<double> x)
{
    double a[]={6,20,5,-40,16};

    complex<double> eval=a[4];
    for(int i=3;i>=0;i--)
        eval=eval*x+a[i];
    return eval;

}

double fnewton(double x)
{
    return sin(x);
}

double fnder(double x)
{
    return cos(x);
}

//----------------------- Tests ----------------------//

void TestBisection()
{
    cout<<"Bisection"<<endl;
    auto intervs=LocalizeRoots(f,0.,5.,.1);
    Bisection x=Bisection(intervs[0].first,intervs[0].second);
    cout<<x.DoIt(f)<<endl;
}

void TestBrent()
{
    cout << "Brent" << endl;
    Brent x = Brent(0.3,2.1);
    cout << x.DoIt(f) << endl;
}

void TestMuller()
{
    cout<<"Muller"<<endl;
    cout<<"example 3 section 2.6 Burden and Faires"<<endl;
    Muller x= Muller(2.5,2.0,2.25,1e-5,50);
    cout<<x.DoIt(myfunction)<<endl<<endl;;

}


void TestNewton()
{
    cout<<"Newton"<<endl;
    Newton x=Newton(3.25,1e-8,20);
    cout<<x.DoIt(fnewton,fnder)<<endl<<endl;;

}

void TestSecant()
{
    cout<<"Secant"<<endl;
    Secant x=Secant(0.5,3.54,1e-5,100);
    cout<<x.DoIt(fnewton)<<endl<<endl;

}
