#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>
#include <sys/mman.h>

//#include "sourceGenerated.hpp"

double* gtabmt = 0;


double    calcPi(unsigned inOff, unsigned inMax)
{
    double  x;
    double  y;
    unsigned long cumul = 0;
    double  pi;
    
    for (unsigned i = inOff; i < (inMax + inOff); i += 2)
    {
        x = gtabmt[i];
        y = gtabmt[i + 1];
        
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

/* memory mapping strategy */
void    piBin(  const char*   inFilename,
                unsigned      inReplics,
                unsigned      inMax)
{
    int     fd = -1;
    
    fd = open(inFilename, O_RDONLY);
    assert(fd != -1);
    
    gtabmt = (double*)mmap(0, inReplics * inMax * sizeof(double), PROT_READ, MAP_PRIVATE,
                        fd, 0);
                        
    assert(gtabmt != (void*)-1);
}

int main(int, char**)
{
    /*std::cout << "Nb tirages nb : " << tabMTSize << std::endl;
    std::cout << "Nb tirages MC : " <<  tabMTSize / 2 << std::endl;
    std::cout << "Nb replics MC : " << (tabMTSize / nbTirages) << std::endl;
    */
    
    piBin("./binrng", 100, 10000000);
    std::cout << piReplic(100, 10000000) << std::endl;
    //std::cout << "Hello World !" << std::endl;
    return (0);
}

