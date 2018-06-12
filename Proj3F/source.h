#ifndef source_h
#define source_h

#include <stdio.h>
#include <stdlib.h>
#include <image.h>
#include <string.h>
#include <logging.h>

class source
{
public:
    source();
    Image *GetOutput();
    virtual void Update();
    virtual const char *SourceName() = 0;
    
protected:
    Image img;
    virtual void Execute() = 0;
    
};

#endif 
