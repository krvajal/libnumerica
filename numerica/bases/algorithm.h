#ifndef ALGORITHM_H
#define ALGORITHM_H


namespace numerica
{

enum class AlgorithmState {initialized, running, finished};

class Algorithm
{
    int i,N0;
public:

    virtual void DoNext(int steps=1);
    virtual void DoAll();
    float ProgressPercent(){return (1.0+i)/N0;}

    std::string logs;
    AlgorithmState state;
};
}


#endif // ALGORITHM_H
