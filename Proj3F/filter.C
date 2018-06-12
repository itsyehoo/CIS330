//Project3E

#include <filter.h>

void filter::Update()
{
    char msg[128];
 
    //Updating imgPtr1
    if(imgPtr1 != NULL)
    {
        sprintf(msg, "%s: about to update input1", FilterName());
        Logger::LogEvent(msg);
        imgPtr1->Update();
        sprintf(msg, "%s: done updating input1", FilterName());
        Logger::LogEvent(msg);
    }
 
    //Updating imgPtr2
    if(imgPtr2 != NULL)
    {
        sprintf(msg, "%s: about to update input2", FilterName());
        Logger::LogEvent(msg);
        imgPtr2->Update();
        sprintf(msg, "%s: done updating input2", FilterName());
        Logger::LogEvent(msg);
    }
 
    //Executing
    sprintf(msg, "%s: about to execute", FilterName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", FilterName());
    Logger::LogEvent(msg);
}

const char *filter::SourceName()
{
    return FilterName();
}

const char *filter::SinkName()
{
    return FilterName();
}


//Shrinker class:
void Shrinker::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
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
    free(newBuff);
}

const char *Shrinker::FilterName()
{
    return "Shrinker";
}

//LRCombine Class:
void LRCombine::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: missing input1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: missing input2", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int leftWidth = imgPtr1->getWidth();
    int rightWidth = imgPtr2->getWidth();
    int totalWidth = leftWidth + rightWidth;
    int height = imgPtr1->getHeight();
    
    if(imgPtr1->getHeight() != imgPtr2->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights are not the same: %d, %d", SinkName(), imgPtr1->getHeight(), imgPtr2->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
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
}

const char *LRCombine::FilterName()
{
    return "LRCombine";
}

//TBCombine Class:
void TBCombine::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: missing input1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: mising input2", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int topWidth = imgPtr1->getWidth();
    int topHeight = imgPtr1->getHeight();
    int bottomHeight = imgPtr2->getHeight();
    
    if(imgPtr1->getWidth() != imgPtr2->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths are not the same: %d, %d", SinkName(), imgPtr1->getWidth(), imgPtr2->getWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
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
}

const char *TBCombine::FilterName()
{
    return "TBCombine";
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
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: missing input1", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: missing input2", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr1->getHeight() != imgPtr2->getHeight() || imgPtr1->getWidth() != imgPtr2->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: images don't have the same size: %d x %d, %d x %d", SinkName(), imgPtr1->getWidth(), imgPtr1->getHeight(), imgPtr2->getWidth(), imgPtr2->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(factor > 1.0)
    {
        char msg[1024];
        sprintf(msg, "%s: Invalid factor for Blender: %f", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
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
    free(newBuff);
}

const char *Blender::FilterName()
{
    return "Blender";
}

