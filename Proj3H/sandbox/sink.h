#ifndef sink_h
#define sink_h

#include <stdio.h>
#include <image.h>

class sink
{
public:
    sink();
    ~sink();
    //Setters
    void SetInput(Image *input1);
    void SetInput2(Image *input2);
    //Getters:
    Image GetInput();
    Image getInput2();
    virtual const char *SinkName() = 0;
    
protected:
    const Image *imgPtr1;
    const Image *imgPtr2;
};

#endif
