#ifndef source_h
#define source_h

#include <stdio.h>
#include <stdlib.h>
#include <image.h>

class source
{
public:
    source();
    ~source();
    Image *GetOutput();
    virtual void Update();
    
protected:
    virtual void Execute() = 0; //do we need a function body for this?
    Image img;
};

#endif
