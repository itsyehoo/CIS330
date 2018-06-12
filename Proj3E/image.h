#ifndef image_h
#define image_h

#include <stdio.h>
#include <stdlib.h>

class source;

struct Pixel
{
    unsigned char r, g, b;
};

class Image
{
public:
    Image();                                        //Default Constructor
    Image(int width, int height);                   //Parameterized Constructor
    Image(Image &);                                 //Copy Constructor
    ~Image();                                       //Desstructor
    //Setters
    void setHeight(int height);
    void setWidth(int width);
    void setBuffer(Pixel *aBuffer);
    void setSource(source *aSrc);
    //Getters
    int getHeight();
    int getWidth();
    Pixel *getBuffer();
    //Other
    void ResetSize(int width, int height);
    virtual void Update();
    
    
private:
    int w;
    int h;
    Pixel *buffer;
    source *src;
};

#include <source.h>
#endif

