#ifndef PNMreader_h
#define PNMreader_h

#include <stdlib.h>
#include <image.h>
#include <source.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class PNMreader : public source
{
public:
    PNMreader();
    ~PNMreader();
    PNMreader(const char *aFileName);
    virtual void Execute();
    virtual const char *SourceName();
    
private:
    char *fileName;
};

#endif 
