#include <iostream>
#include <fstream>
#include "tinymt64.hpp"
#include <cstring>
#include <cassert>

#define MOD 6


tinymt64_t	mt;

/*
 *    for( i = 0; i < MAX ; i++)
   {
      x = (double) rand() / (double) RAND_MAX;
      y = (double) rand() / (double) RAND_MAX;
      if (((x-1)*(x-1) + (y-1)*(y-1)) <= 1)
        cumul++;
      px = (int) (x * MAXXF);
      py = (int) (y * MAXYF);
      XDrawPoint(dpy,win,gcontext,px,py);
   }
   pi = ((double) cumul * 4. / MAX);
 */
void    buildBin(const char*    inFilename,
                 uint           inNbReplics,
                 uint           inNb)
{
    FILE*   fp = 0;
    
    fp = fopen(inFilename, "wb");
    assert(fp != 0);
    
    tinymt64_init(&mt, 23);
    
    for (unsigned r = 0 ; r < inNbReplics ; ++r)
        for(uint index = 1 ; index < inNb ; ++index)
        {
            double rnd = tinymt64_generate_double(&mt);
            fwrite(&rnd, sizeof(double), 1, fp);
        }
        
    fclose(fp);
}


void    buildSource(const char * inFileName,
                    uint inNbReplics,
                    uint inNb)
{
    std:: ofstream stream(inFileName, std::ofstream::out | std::ofstream::trunc);


    tinymt64_init(&mt, 23);
    
    stream << "size_t tabMTSize = " << inNb * inNbReplics << ";" << std::endl;
    stream << "size_t nbTirages = " << inNb << ";" << std::endl;
    stream << "double tabMT[] = {" << std::endl << "\t";
    
    for (unsigned r = 0 ; r < inNbReplics ; ++r)
    {
        if (r > 0)
           stream << " , "; 
        stream << tinymt64_generate_double(&mt);
        for(uint index = 1 ; index < inNb ; ++index)
        {
            stream << " , ";
            if((index % MOD) == 0)
            {
                stream << std::endl << "\t";
            }
            stream << tinymt64_generate_double(&mt);
        }
    }
    
    stream << std::endl << "};" << std::endl;
    stream.close();
}

// memory mapping => fic binaire balancé sur mmap

double    calcPi(unsigned inMax)
{
    double  x;
    double  y;
    ulong cumul = 0;
    double pi = 0;

    
    
    for (unsigned i = 0; i < inMax ; i += 2)
    {
        x = tinymt64_generate_double(&mt);
        y = tinymt64_generate_double(&mt);
        
        //std::cout << x << "," << y << std::endl;
        if (((x - 1) * (x - 1) + (y - 1) * (y - 1)) <= 1)
            cumul++;
    }
    
    pi = ((double) cumul * 4. / (inMax/2));

    return pi;
}

double  piReplic(unsigned inReplics, unsigned inMax)
{
    double      avrg = 0.;
    
	tinymt64_init(&mt, 23);

    for (unsigned i = 0 ; i < inReplics ; ++i)
        avrg += calcPi(inMax);
        
    avrg /= (1. * inReplics);
    return avrg;
}




int main3(int, char**)
{
    
    std::cout << piReplic(100, 10000000) << std::endl;
    
    system("cd ./userCode && make clean");
    buildSource("./userCode/src/sourceGenerated.hpp", 100, 10000000);
    system("cd ./userCode && make && ./prog");
    
    
    return (0);
}

int main(int, char**)
{
    system("cd ./userCode && make clean");
    buildBin("./userCode/binrng", 100, 10000000);
    system("cd ./userCode && make && ./prog");
    
    return 0;
}

