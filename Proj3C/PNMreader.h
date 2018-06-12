#ifndef PNMreader_h
#define PNMreader_h

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <image.h>
#include <source.h>


class PNMreader : public source
{
public:
    PNMreader();
    ~PNMreader();
    PNMreader(char *aFileName);
    virtual void Execute();
    
private:
    char *fileName;
};

#endif 
