#ifndef sink_h
#define sink_h

#include <stdio.h>
#include <image.h>

class sink
{
public:
    void SetInput(Image *input1);
    void SetInput2(Image *input2);
    
protected:
    Image *imgPtr1;
    Image *imgPtr2;
};

#endif
