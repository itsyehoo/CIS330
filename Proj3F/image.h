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
    Image(int width, int height, Pixel *aBuffer);   //Parameterized Constructor
    Image(const Image &);                           //Copy Constructor
    ~Image();                                       //Desstructor
    //Setters
    void ResetSize(int width, int height);
    void setBuffer(Pixel *aBuffer);
    //Getters
    int getHeight() const;
    int getWidth() const;
    Pixel *getBuffer() const;
    //Other
    void setSource(source *aSrc);
    void Update() const;
    
private:
    int w, h;
    Pixel *buffer;
    source *src;
    
};


#endif
