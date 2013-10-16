#include <iostream>
#include "sourceGenerated.hpp"


double    calcPi(unsigned inOff, unsigned inMax)
{
    double  x;
    double  y;
    unsigned long cumul = 0;
    double  pi;
    
    for (unsigned i = inOff; i < (inMax + inOff); i += 2)
    {
        x = tabMT[i];
        y = tabMT[i + 1];
        
        if (((x - 1) * (x - 1) + (y - 1) * (y - 1)) <= 1)
            cumul++;
    }
    
    pi = ((double) cumul * 4. / (inMax/2));
    return pi;
}

double  piReplic(unsigned inReplics, unsigned inMax)
{
    double      avrg = 0.;
    
    for (unsigned i = 0 ; i < inReplics ; ++i)
        avrg += calcPi(i*inMax, inMax);
        
    avrg /= (1. * inReplics);
    return avrg;
}

int main(int, char**)
{
    std::cout << "Nb tirages nb : " << tabMTSize << std::endl;
    std::cout << "Nb tirages MC : " <<  tabMTSize / 2 << std::endl;
    std::cout << "Nb replics MC : " << (tabMTSize / nbTirages) << std::endl;
	std::cout << piReplic((tabMTSize / nbTirages), nbTirages) << std::endl;
    //std::cout << "Hello World !" << std::endl;
    return (0);
}

