
#include <image.h>

//Default Constructor
Image::Image()
{
    h = 0;
    w = 0;
    buffer = NULL;
}

//Parameterized Constructor
Image::Image(int width, int height)
{
    w = width;
    h = height;
    
    buffer = new Pixel[width*height];
}

/*
Image::Image(int width, int height, Pixel *aBuffer)
{
    w = width;
    h = height;
    //buffer = (Pixel*) malloc(3*width*height); //alloacating memory for the buffer;
    buffer = new Pixel[width*height];
    
     for(int i = 0; i < width * height; i++)
     {
     buffer[i] = aBuffer[i];
     }
}
 */

//Copy Constructor
Image::Image(Image &c)
{
    w = c.w;
    h = c.h;
    
    for(int i = 0; i < c.w * c.h; i++)
    {
        buffer[i] = c.buffer[i];
    }
}

//Destructor
Image::~Image()
{
    delete [] buffer;
}

void Image::ResetSize(int width, int height)
{
    h = height;
    w = width;
    
    buffer = new Pixel[width*height];
}

/*
void Image::setHeight(int height)
{
    h = height;
}

void Image::setWidth(int width)
{
    w = width;
}
*/
void Image::setBuffer(Pixel *aBuffer)
{
    buffer = new Pixel[w*h];
    
    for(int i = 0; i < w * h; i++)
    {
        buffer[i] = aBuffer[i];
    }
}

int Image::getHeight()
{
    return h;
}

int Image::getWidth()
{
    return w;
}

Pixel *Image::getBuffer()
{
    return buffer;
}

