#include <filter.h>

//Shrinker class:
void Shrinker::Execute()
{
    
    img.ResetSize(imgPtr1->getWidth() / 2, imgPtr1->getHeight() / 2);
    
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
    free(newBuff);
     
    
    /*
    
    img.ResetSize(imgPtr1->getWidth() / 2, imgPtr1->getHeight() / 2);
    
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    int indexIn, indexOut;
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            indexIn = (j * 2) * imgPtr1->getWidth() + (i * 2);
            indexOut = j * img.getWidth() + i;
            newBuff[indexOut].r = imgPtr1->getBuffer()[indexIn].r;
            newBuff[indexOut].g = imgPtr1->getBuffer()[indexIn].g;
            newBuff[indexOut].b = imgPtr1->getBuffer()[indexIn].b;
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
     */
}

//LRCombine Class:
void LRCombine::Execute()
{
    /*
    int leftWidth = imgPtr1->getWidth();
    int rightWidth = imgPtr2->getWidth();
    int totalWidth = leftWidth + rightWidth;
    int height = imgPtr1->getHeight();
    
    img.ResetSize(totalWidth, height);
    
    Pixel *newBuff;
    
    newBuff = new Pixel[totalWidth * height];
    
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
    free(newBuff);
     
    
    if(imgPtr1 == NULL)
    {
        printf("input1 is missing");
        return;
    }
    
    if(imgPtr2 == NULL)
    {
        printf("input2 is missing");
        return;
    }
    
    if(imgPtr1->getHeight() != imgPtr2->getHeight())
    {
        printf("heights are not the same");
        return;
    }
     */
    
    int leftWidth = imgPtr1->getWidth();
    int rightWidth = imgPtr2->getWidth();
    int totalWidth = leftWidth + rightWidth;
    int totalHeight = (imgPtr1->getHeight() + imgPtr2->getHeight()) /2;
    
    img.ResetSize(totalWidth, totalHeight);
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    int indexIn, indexOut;
    
    for(int i = 0; i < leftWidth; i++)
    {
        for(int j = 0; j < totalHeight; j++)
        {
            indexOut = j * totalWidth + i;
            indexIn = j * leftWidth + i;
            
            newBuff[indexOut].r = imgPtr1->getBuffer()[indexIn].r;
            newBuff[indexOut].g = imgPtr1->getBuffer()[indexIn].g;
            newBuff[indexOut].b = imgPtr1->getBuffer()[indexIn].b;
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
        newBuff[i] = imgPtr1->getBuffer()[i];
    }
    
    for (int i = 0; i < topWidth * topHeight; i++)
    {
        newBuff[topWidth * topHeight + i] = imgPtr2->getBuffer()[i];
    }
    
    img.setBuffer(newBuff);
    free(newBuff);
     
    /*
    if(imgPtr1 == NULL)
    {
        printf("input1 is missing");
        return;
    }
    
    if(imgPtr2 == NULL)
    {
        printf("input2 is missing");
        return;
    }
    
    int topWidth = imgPtr1->getWidth();
    int topHeight = imgPtr1->getHeight();
    int bottomHeight = imgPtr2->getHeight();
    int total = topWidth * topHeight;
    
    if(imgPtr1->getWidth() != imgPtr2->getWidth())
    {
        printf("widths are not the same");
        return;
    }
    
    img.ResetSize(topWidth, topHeight + bottomHeight);
    
    Pixel *newBuff = new Pixel[img.getHeight() * img.getWidth()];
    
    for (int i = 0; i < total; i++)
    {
        newBuff[i].r = imgPtr1->getBuffer()[i].r;
        newBuff[i].g = imgPtr1->getBuffer()[i].g;
        newBuff[i].b = imgPtr1->getBuffer()[i].b;
        
    }
    
    for (int i = 0; i < total; i++)
    {
        newBuff[total + i].r = imgPtr2->getBuffer()[i].r;
        newBuff[total + i].g = imgPtr2->getBuffer()[i].g;
        newBuff[total + i].b = imgPtr2->getBuffer()[i].b;
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
     */
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
    free(newBuff);
    
    /*
    if(imgPtr1 == NULL)
    {
        printf("input1 is missing");
        return;
    }
    
    if(imgPtr2 == NULL)
    {
        printf("input2 is missing");
        return;
    }
    
    
    if(imgPtr1->getHeight() != imgPtr2->getHeight() || imgPtr1->getWidth() != imgPtr2->getWidth())
    {
        printf("images don't have the same size");
        return;
    }
    
    if(factor > 1.0)
    {
        printf("factor is invalid");
        return;
    }
    
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
     */

}
