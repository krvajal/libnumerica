#ifndef ROOTLOCALIZER_H
#define ROOTLOCALIZER_H

#include<vector>
#include<functional>


namespace numerica
{
    namespace roots
    {
        using std::function;
        using std::vector;
        using std::pair;
        template<class Function,class Number=double>
        vector<pair<Number,Number> > LocalizeRoots(Function& f,Number a,Number b,
                                                   Number dx,int n_roots=0)
        {
            vector<pair<Number,Number> > intervals;
            int n=(b-a)/dx,c=0;
            Number xa=a,fa=f(a),x,fx;
            for(int i=0;i<=n;i++)
            {
                x=xa+dx;
                if (x>b) x=b;
                fx=f(x);
                if (fx*fa<0. || fa==0.)
                {
                    intervals.push_back({xa,x});
                    if (++c==n_roots) break;
                }
                xa=x;
                fa=fx;
            }
            return intervals;
        }
    }
}



#endif // ROOTLOCALIZER_H
