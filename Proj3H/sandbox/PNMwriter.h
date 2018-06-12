#ifndef PNMwriter_h
#define PNMwriter_h

#include <stdio.h>
#include <cstring>
#include <image.h>
#include <sink.h>
#include <iostream>
#include <fstream>

using namespace std;

class PNMwriter : public sink
{
public:
    PNMwriter();
    ~PNMwriter();
    void Write(const char *aFileName);
    virtual const char *SinkName();
    
private:
    char *fileName;
};

#endif 
