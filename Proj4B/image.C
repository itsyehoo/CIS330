#include <image.h>
#include <string.h>
#include <source.h>

//Default Constructor
Image::Image()
{
    h = 0;
    w = 0;
    buffer = NULL;
}

//Parameterized Constructor
Image::Image(int width, int height, Pixel *aBuffer)
{
    w = width;
    h = height;
    
    if(buffer == NULL) //added
    {
        buffer = new Pixel[w*h];
    }
    
    for(int i = 0; i < w * h; i++)
    {
        buffer[i] = aBuffer[i];
    }
}

//Copy Constructor
Image::Image(const Image &c)
{
    w = c.w;
    h = c.h;
    
    if(buffer == NULL) //added
    {
        buffer = new Pixel[w*h];
    }
    
    for(int i = 0; i < w * h; i++)
    {
        buffer[i] = c.buffer[i];
    }
}

//Destructor
Image::~Image()
{
    delete [] buffer;
}

void Image::setBuffer(Pixel *aBuffer)
{
    if(buffer == NULL)
    {
        buffer = new Pixel[w*h];
    }
    
    for(int i = 0; i < w * h; i++)
    {
        buffer[i] = aBuffer[i];
    }
}

int Image::getHeight() const
{
    return h;
}

int Image::getWidth() const
{
    return w;
}

Pixel *Image::getBuffer() const
{
    return buffer;
}

void Image::ResetSize(int width, int height)
{
    h = height;
    w = width;
     
    if(buffer == NULL) //added
    {
        buffer = new Pixel[w*h];
    }
}

void Image::setSource(source *aSrc)
{
    if(aSrc != NULL)
    {
        src = aSrc;
    }
}

void Image::Update() const
{
    src->Update();
}
