#include <numerica/fft/fft.h>
#include <numerica/tools/nvector.h>
#include <algorithm>


using namespace numerica::fft;
using namespace std;

void fft(const NVector & h, NVector &H)
{

	int n = h.size();
	if( n < 2  ||  n &(n-1) )
		throw 1;
	int nn = n << 1; //multiply n by 2
	int j  = 1;

	for(int i = 1 ; i < nn;  i += 2)
	{
		if( j > i)
		{
			swap( h[j - 1] , h[i -1]);
			swap( h[j], h[i] );
		}

		int bit_pattern = i;



	}

}
