#ifndef source_h
#define source_h

#include <stdio.h>
#include <stdlib.h>
#include <image.h>
#include <string.h>

class source
{
public:
    source();
    virtual void Execute() = 0;
    Image *GetOutput();
    virtual void Update();
    
protected:
    Image img;
    
};

#endif 
