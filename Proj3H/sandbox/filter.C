//Proj3H
#include <filter.h>

int counter = 0;

void filter::Update()
{
    counter++;

    char msg[128];

    //Throwing an exception in case of stack oveflow
    int limit = 1000;
    
    if(counter > limit)
    {
        sprintf(msg, "%s: overflow", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    if(imgPtr1 != NULL)
    {
        sprintf(msg, "%s: start updating input1", FilterName());
        Logger::LogEvent(msg);
        imgPtr1->Update();
        sprintf(msg, "%s: finished updating input1", FilterName());
        Logger::LogEvent(msg);
    }
 
    if(imgPtr2 != NULL)
    {
        sprintf(msg, "%s: start updating input2", FilterName());
        Logger::LogEvent(msg);
        imgPtr2->Update();
        sprintf(msg, "%s: finished updating input2", FilterName());
        Logger::LogEvent(msg);
    }

    //Executing:
    sprintf(msg, "%s: start executing", FilterName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: finished executing", FilterName());
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

//Color class:
Color::Color()
{
    width = 0;
    height = 0;
    red = 0;
    green = 0;
    blue = 0;
}

Color::Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
    
    img.ResetSize(width, height);
}

Color::~Color()
{
    
}

void Color::Execute()
{
    //throwing exceptions in case and the colors are out of bound
    if (red > 255 || red < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: red is out of bound", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    
    if (green > 255 || green < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: green is out of bound", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    
    if (blue > 255 || blue < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: blue is out of bound", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    
    Pixel *newBuff = new Pixel[width * height];
    
    int index = 0;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            index = i * width + j;
            newBuff[index].r = red;
            newBuff[index].g = green;
            newBuff[index].b = blue;
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

const char *Color::SourceName()
{
    return "Color";
}

//CheckSum class:
void CheckSum::OutputCheckSum(const char *filename)
{
    ofstream infile;
    
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int red = 0, green = 0, blue = 0;
    
    infile.open(filename, ios::out);
    
    int index = 0;
    
    for(int i = 0; i < imgPtr1->getHeight(); i++)
    {
        for(int j = 0; j < imgPtr1->getWidth(); j++)
        {
            index = i * imgPtr1->getWidth() + j;
            
            red += imgPtr1->getBuffer()[index].r;
            green += imgPtr1->getBuffer()[index].g;
            blue += imgPtr1->getBuffer()[index].b;
        }
    }
    
    red %= 256;
    green %= 256;
    blue %= 256;
    
    infile << "CHECKSUM: " << red << ", " << green << ", " << blue << endl;
    
    infile.close();
}

const char *CheckSum::SinkName()
{
     return "CheckSum";
}

//Mirror class:
void Mirror::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    img.ResetSize(imgPtr1->getWidth(), imgPtr1->getHeight());
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    int indexOut;
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            indexOut = j * img.getWidth() + i;
            
            newBuff[indexOut] = imgPtr1->getBuffer()[(j * img.getWidth()) + (img.getWidth() - 1 - i)];
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

const char *Mirror::FilterName()
{
    return "Mirror";
}

//Rotate class:
void Rotate::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    img.ResetSize(imgPtr1->getHeight(), imgPtr1->getWidth());
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            newBuff[j * img.getWidth() + (img.getWidth() - 1 - i)] = imgPtr1->getBuffer()[i * imgPtr1->getWidth() + j];
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

const char *Rotate::FilterName()
{
    return "Rotate";
}

//Subtract class:
void Subtract::Execute() 
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input2 is missing", SinkName());
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
    
    img.ResetSize(imgPtr1->getWidth(), imgPtr1->getHeight());
    
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    int indexIn, indexOut;
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            indexIn = j * imgPtr1->getWidth() + i;
            indexOut = j * img.getWidth() + i;
            
            //red
            if(imgPtr1->getBuffer()[indexIn].r > imgPtr2->getBuffer()[indexIn].r)
            {
                newBuff[indexOut].r = imgPtr1->getBuffer()[indexIn].r -
                imgPtr2->getBuffer()[indexIn].r;
            }
            else
            {
                newBuff[indexOut].r = 0;
            }
            
            //green
            if(imgPtr1->getBuffer()[indexIn].g > imgPtr2->getBuffer()[indexIn].g)
            {
                newBuff[indexOut].g = imgPtr1->getBuffer()[indexIn].g -
                imgPtr2->getBuffer()[indexIn].g;
            }
            else
            {
                newBuff[indexOut].g = 0;
            }
            
            //blue
            if(imgPtr1->getBuffer()[indexIn].b > imgPtr2->getBuffer()[indexIn].b)
            {
                newBuff[indexOut].b = imgPtr1->getBuffer()[indexIn].b -
                imgPtr2->getBuffer()[indexIn].b;
            }
            else
            {
                newBuff[indexOut].b = 0;
            }
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

const char *Subtract::FilterName()
{
    return "Subtract";
}

//Grayscale class:
void Grayscale::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    img.ResetSize(imgPtr1->getWidth(), imgPtr1->getHeight());
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    int indexIn, indexOut;
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            indexIn = j * imgPtr1->getWidth() + i;
            indexOut = j * img.getWidth() + i;
            
            newBuff[indexOut].r = imgPtr1->getBuffer()[indexIn].r / 5 +
            imgPtr1->getBuffer()[indexIn].g / 2 +
            imgPtr1->getBuffer()[indexIn].b / 4;
            
            newBuff[indexOut].g = imgPtr1->getBuffer()[indexIn].r / 5 +
            imgPtr1->getBuffer()[indexIn].g / 2 +
            imgPtr1->getBuffer()[indexIn].b / 4;
            ;
            newBuff[indexOut].b = imgPtr1->getBuffer()[indexIn].r / 5 +
            imgPtr1->getBuffer()[indexIn].g / 2 +
            imgPtr1->getBuffer()[indexIn].b / 4;
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

const char *Grayscale::FilterName()
{
    return "Grayscale";
}

//Blur class:
void Blur::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    img.ResetSize(imgPtr1->getWidth(), imgPtr1->getHeight());
    Pixel *newBuff = new Pixel[img.getWidth() * img.getHeight()];
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            if(i == 0 || j == 0 || i == img.getWidth() - 1 || j == img.getHeight() - 1)
            {
                newBuff[j * img.getWidth() + i] = imgPtr1->getBuffer()[j * img.getWidth() + i];
            }
            
            else
            {
                newBuff[j * img.getWidth() + i].r = imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + (i - 1)].r / 8 +
                imgPtr1->getBuffer()[j * imgPtr1->getWidth() + (i - 1)].r / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + (i - 1)].r / 8 +
                imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + i].r / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + i].r / 8 +
                imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + (i + 1)].r / 8 +
                imgPtr1->getBuffer()[j * imgPtr1->getWidth() + (i + 1)].r / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + (i + 1)].r / 8;
            
                newBuff[j * img.getWidth() + i].g = imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + (i - 1)].g / 8 +
                imgPtr1->getBuffer()[j * imgPtr1->getWidth() + (i - 1)].g / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + (i - 1)].g / 8 +
                imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + i].g / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + i].g / 8 +
                imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + (i + 1)].g / 8 +
                imgPtr1->getBuffer()[j * imgPtr1->getWidth() + (i + 1)].g / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + (i + 1)].g / 8;
            
                newBuff[j * img.getWidth() + i].b = imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + (i - 1)].b / 8 +
                imgPtr1->getBuffer()[j * imgPtr1->getWidth() + (i - 1)].b / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + (i - 1)].b / 8 +
                imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + i].b / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + i].b / 8 +
                imgPtr1->getBuffer()[(j - 1) * imgPtr1->getWidth() + (i + 1)].b / 8 +
                imgPtr1->getBuffer()[j * imgPtr1->getWidth() + (i + 1)].b / 8 +
                imgPtr1->getBuffer()[(j + 1) * imgPtr1->getWidth() + (i + 1)].b / 8;
            }
        }
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
}

const char *Blur::FilterName()
{
    return "Blur";
}

//Shrinker class:
void Shrinker::Execute()
{
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
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
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input2 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int leftWidth = imgPtr1->getWidth();
    int rightWidth = imgPtr2->getWidth();
    int totalWidth = leftWidth + rightWidth;
    int totalHeight = (imgPtr1->getHeight() + imgPtr2->getHeight()) /2;
    
    if(imgPtr1->getHeight() != imgPtr2->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights are not the same: %d, %d", SinkName(), imgPtr1->getHeight(), imgPtr2->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
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
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input2 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int topWidth = imgPtr1->getWidth();
    int topHeight = imgPtr1->getHeight();
    int bottomWidth = imgPtr2->getWidth();
    int bottomHeight = imgPtr2->getHeight();
    int totalTop = topWidth * topHeight;
    int totalBottom = bottomHeight * bottomWidth;
    
    if(imgPtr1->getWidth() != imgPtr2->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths are not the same: %d, %d", SinkName(), imgPtr1->getWidth(), imgPtr2->getWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    img.ResetSize(topWidth, topHeight + bottomHeight);
    
    Pixel *newBuff = new Pixel[img.getHeight() * img.getWidth()];
    
    for (int i = 0; i < totalTop; i++)
    {
        newBuff[i].r = imgPtr1->getBuffer()[i].r;
        newBuff[i].g = imgPtr1->getBuffer()[i].g;
        newBuff[i].b = imgPtr1->getBuffer()[i].b;

    }
    
    for (int i = 0; i < totalBottom; i++)
    {
        newBuff[totalTop + i].r = imgPtr2->getBuffer()[i].r;
        newBuff[totalTop + i].g = imgPtr2->getBuffer()[i].g;
        newBuff[totalTop + i].b = imgPtr2->getBuffer()[i].b;
    }
    
    img.setBuffer(newBuff);
    delete [] newBuff;
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
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(imgPtr2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input2 is missing", SinkName());
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
        sprintf(msg, "%s: Factor is an invalid value: %f", SinkName(), factor);
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
    delete [] newBuff;
}

const char *Blender::FilterName()
{
    return "Blender";
}

