#ifndef image_h
#define image_h

#include <stdio.h>
#include <stdlib.h>

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
    //Getters
    int getHeight();
    int getWidth();
    Pixel *getBuffer();
    //Other
    void ResetSize(int width, int height);
    
private:
    int w;
    int h;
    Pixel *buffer;
};


#endif
