//Project3E

#include <filter.h>

void filter::Update()
{
    if(imgPtr1 != NULL)
    {
        imgPtr1->Update();
    }
    
    if(imgPtr2 != NULL)
    {
        imgPtr2->Update();
    }
    
    Execute();
}

//Shrinker class:
void Shrinker::Execute()
{
    img.ResetSize(imgPtr1->getWidth() / 2, imgPtr1->getHeight() / 2);
    
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    int in = 0, out = 0;
    
    for (int i = 0; i < img.getHeight(); i++)
    {        
        for(int j = 0; j < img.getWidth(); j++)
        {
            in = i*2*imgPtr1->getWidth()+j*2;
            out = i*img.getWidth()+j;
            newBuff[out] = imgPtr1->getBuffer()[in];
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

//LRCombine Class:
void LRCombine::Execute()
{
    int leftWidth = imgPtr1->getWidth();
    int rightWidth = imgPtr2->getWidth();
    int totalWidth = leftWidth + rightWidth;
    int totalHeight = (imgPtr1->getHeight() + imgPtr2->getHeight()) /2;
    
    img.ResetSize(totalWidth, totalHeight);
    
    Pixel *newBuff;
    
    newBuff = new Pixel[totalWidth * totalHeight];
    
    for(int i = 0; i < leftWidth; i++)
    {
        for(int j = 0; j < totalHeight; j++)
        {
            newBuff[j * totalWidth + i].r = imgPtr1->getBuffer()[j * leftWidth + i].r;
            newBuff[j * totalWidth + i].g = imgPtr1->getBuffer()[j * leftWidth + i].g;
            newBuff[j * totalWidth + i].b = imgPtr1->getBuffer()[j * leftWidth + i].b;
        }
    }
    
    for(int i = 0; i < rightWidth; i++)
    {
        for(int j = 0; j < totalHeight; j++)
        {
            newBuff[j * totalWidth + leftWidth + i].r = imgPtr2->getBuffer()[j * rightWidth + i].r;
            newBuff[j * totalWidth + leftWidth + i].g = imgPtr2->getBuffer()[j * rightWidth + i].g;
            newBuff[j * totalWidth + leftWidth + i].b = imgPtr2->getBuffer()[j * rightWidth + i].b;
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

//TBCombine Class:
void TBCombine::Execute()
{
    int topWidth = imgPtr1->getWidth();
    int topHeight = imgPtr1->getHeight();
    int bottomHeight = imgPtr2->getHeight();
    
    img.ResetSize(topWidth, topHeight + bottomHeight);
    
    Pixel *newBuff = new Pixel[img.getHeight() * img.getWidth()];
    
    for (int i = 0; i < topWidth * topHeight; i++)
    {
        newBuff[i].r = imgPtr1->getBuffer()[i].r;
        newBuff[i].g = imgPtr1->getBuffer()[i].g;
        newBuff[i].b = imgPtr1->getBuffer()[i].b;
        
    }
    
    for (int i = 0; i < topWidth * topHeight; i++)
    {
        newBuff[topWidth * topHeight + i].r = imgPtr2->getBuffer()[i].r;
        newBuff[topWidth * topHeight + i].g = imgPtr2->getBuffer()[i].g;
        newBuff[topWidth * topHeight + i].b = imgPtr2->getBuffer()[i].b;
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
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
    img.ResetSize(imgPtr1->getWidth(), imgPtr1->getHeight());
    
    Pixel * newBuff = new Pixel[img.getHeight() * img.getWidth()];
    
    for(int i = 0; i < img.getWidth() * img.getHeight(); i++)
    {
        newBuff[i].r = imgPtr1->getBuffer()[i].r * factor + imgPtr2->getBuffer()[i].r * (1 - factor);
        newBuff[i].g = imgPtr1->getBuffer()[i].g * factor + imgPtr2->getBuffer()[i].g * (1 - factor);
        newBuff[i].b = imgPtr1->getBuffer()[i].b * factor + imgPtr2->getBuffer()[i].b * (1 - factor);
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}
