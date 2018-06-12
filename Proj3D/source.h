#ifndef source_h
#define source_h

#include <stdio.h>
#include <stdlib.h>
#include <image.h>

class source
{
public:
    virtual void Execute() = 0;
    Image *GetOutput();
    
protected:
    Image img;
    
};

#endif 
