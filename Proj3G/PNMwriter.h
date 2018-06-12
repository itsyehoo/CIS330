#ifndef PNMwriter_h
#define PNMwriter_h

#include <stdio.h>
#include <cstring>
#include <image.h>
#include <sink.h>

class PNMwriter : public sink
{
public:
    PNMwriter();
    ~PNMwriter();
    void Write(char *aFileName);
    virtual const char *SinkName();
    
private:
    char *fileName;
};

#endif 
