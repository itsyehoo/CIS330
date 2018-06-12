#include <filter.h>

//Shrinker class:
void Shrinker::Execute()
{
    img.setWidth(imgPtr1->getWidth() / 2);
    img.setHeight(imgPtr1->getHeight() / 2);
    
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    int index = 0, pIndex = 0;
    
    for (int i = 0; i < img.getHeight(); i++)
    {
        pIndex = i * imgPtr1->getWidth() * 2;
        
        for(int j = 0; j < img.getWidth(); j++)
        {
            newBuff[index] = imgPtr1->getBuffer()[pIndex + (j * 2)];
            index++;
        }
    }
    
    img.setBuffer(newBuff);
}

//LRCombine Class:
void LRCombine::Execute()
{
    int leftWidth = imgPtr1->getWidth();
    int rightWidth = imgPtr2->getWidth();
    int totalWidth = leftWidth + rightWidth;
    int height = imgPtr1->getHeight();
    
    img.setWidth(totalWidth);
    img.setHeight(height);
    
    Pixel *newBuff;
    
    newBuff = new Pixel[totalWidth *height];
    
    for( int i  = 0; i < totalWidth; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(i < leftWidth)
            {
                newBuff[j*totalWidth+i] = imgPtr1->getBuffer()[j*leftWidth+i];
            }
            else
            {
                newBuff[j*totalWidth+i] = imgPtr2->getBuffer()[j*leftWidth+i];
            }
        }
    }
    
    img.setBuffer(newBuff);
}

//TBCombine Class:
void TBCombine::Execute()
{
    int topWidth = imgPtr1->getWidth();
    int topHeight = imgPtr1->getHeight();
    int bottomHeight = imgPtr2->getHeight();
    
    img.setWidth(topWidth); //topInput
    img.setHeight(topHeight + bottomHeight); //imgPtr2 = bottomInput
    
    Pixel *newBuff = new Pixel[img.getHeight() * img.getWidth()];
    
    for (int i = 0; i < topWidth * topHeight; i++)
    {
        newBuff[i] = imgPtr1->getBuffer()[i];
    }
    
    for (int i = 0; i < topWidth * topHeight; i++)
    {
        newBuff[topWidth * topHeight + i] = imgPtr2->getBuffer()[i];
    }
    
    img.setBuffer(newBuff);
}


//Blender Class:
Blender::Blender()
{
    factor = 0;
}

Blender::Blender(int aFactor)
{
    factor = aFactor;
}

Blender::~Blender()
{
    if(factor != 0)
    {
        factor = 0;
    }
}

void Blender::SetFactor(double aFactor)
{
    factor = aFactor;
}

void Blender::Execute()
{
    img.setWidth(imgPtr1->getWidth());
    img.setHeight(imgPtr1->getHeight());
    
    Pixel * newBuff = new Pixel[img.getHeight() * img.getWidth()];
    
    for(int i = 0; i < img.getWidth() * img.getHeight(); i++)
    {
        newBuff[i].r = imgPtr1->getBuffer()[i].r * factor + imgPtr2->getBuffer()[i].r * (1 - factor);
        newBuff[i].g = imgPtr1->getBuffer()[i].g * factor + imgPtr2->getBuffer()[i].g * (1 - factor);
        newBuff[i].b = imgPtr1->getBuffer()[i].b * factor + imgPtr2->getBuffer()[i].b * (1 - factor);
    }
    
    img.setBuffer(newBuff);
}
