
#ifndef image_h
#define image_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pixel
{
    unsigned char r, g, b;
};

class Image
{
public:
    Image();                                        //Default Constructor
    //Image(int width, int height, Pixel *buffer);  //Parameterized Constructor
    Image(int width, int height);                   //Parameterized Constructor
    Image(Image &);                                 //Copy Constructor
    ~Image();                                       //Desstructor
    //Setters
    void ResetSize(int width, int height);
    void setBuffer(Pixel *aBuffer);
    //Getters
    int getHeight();
    int getWidth();
    Pixel *getBuffer();
    //Other
    Pixel *buffer;
    
private:
    int w, h;
};


#endif 
