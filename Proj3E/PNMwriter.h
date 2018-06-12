#ifndef PNMwriter_h
#define PNMwriter_h

#include <stdio.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <image.h>
#include <sink.h>

class PNMwriter : public sink
{
public:
    PNMwriter();
    ~PNMwriter();
    void Write(char *aFileName);
    
private:
    char *fileName;
};

#endif
