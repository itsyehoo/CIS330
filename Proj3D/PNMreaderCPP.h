#ifndef PNMreaderCPP_h
#define PNMreaderCPP_h

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <image.h>
#include <source.h>

using namespace std;

class PNMreaderCPP : public source
{
public:
    PNMreaderCPP();
    ~PNMreaderCPP();
    PNMreaderCPP(char *aFileName);
    virtual void Execute();
    
private:
    char *fileName;
};

#endif
