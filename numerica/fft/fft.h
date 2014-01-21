#ifndef FFT_H
#define FFT_H


namespace nuemerica{

	namespace fft{

		class NVector;
		
		void fft(const NVector & h, NVector &H);

	}

}



#endif //FFT_H