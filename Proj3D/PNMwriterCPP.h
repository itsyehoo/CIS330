#ifndef PNMwriterCPP_h
#define PNMwriterCPP_h

#include <stdio.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <image.h>
#include <sink.h>

using namespace std;

class PNMwriterCPP : public sink
{
public:
    PNMwriterCPP();
    ~PNMwriterCPP();
    void Write(char *aFileName);
    
private:
    char *fileName;
};

#endif
