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

//Color class:
Color::Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
    
    img.ResetSize(width, height);
}

void Color::Execute()
{
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

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            newBuff[i * width + j].r = red;
            newBuff[i * width + j].g = green;
            newBuff[i * width + j].b = blue;
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
    if(imgPtr1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: input1 is missing", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int red = 0, green = 0, blue = 0;
    
    ofstream infile;
    
    infile.open(filename, ios::out);
    
    for(int i = 0; i < imgPtr1->getHeight(); i++)
    {
        for(int j = 0; j < imgPtr1->getWidth(); j++)
        {
            red += imgPtr1->getBuffer()[i * imgPtr1->getWidth() + j].r;
            green += imgPtr1->getBuffer()[i * imgPtr1->getWidth() + j].g;
            blue += imgPtr1->getBuffer()[i * imgPtr1->getWidth() + j].b;
        }
    }
    
    red %= 256;
    green %= 256;
    blue %= 256;
    
    infile << "CHECKSUM: " << red << ", " << green << ", " << blue << endl;
    
    infile.close();
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
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
    
            newBuff[j * img.getWidth() + i] = imgPtr1->getBuffer()[(j * img.getWidth()) + (img.getWidth() - 1 - i)];
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
void Subtract::Execute() //problem here: checksum gives a different output
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
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            //red
            if(imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].r > imgPtr2->getBuffer()[j * imgPtr2->getWidth() + i].r)
            {
                newBuff[j * img.getWidth() + i].r = imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].r -
                imgPtr2->getBuffer()[j * imgPtr2->getWidth() + i].r;
            }
            else
            {
                newBuff[j * img.getWidth() + i].r = 0;
            }
            
            //green
            if(imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].g > imgPtr2->getBuffer()[j * imgPtr2->getWidth() + i].g)
            {
                newBuff[j * img.getWidth() + i].g = imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].g -
                imgPtr2->getBuffer()[j * imgPtr2->getWidth() + i].g;
            }
            else
            {
                newBuff[j * img.getWidth() + i].g = 0;
            }
            
            //blue
            if(imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].b > imgPtr2->getBuffer()[j * imgPtr2->getWidth() + i].b)
            {
                newBuff[j * img.getWidth() + i].b = imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].b -
                imgPtr2->getBuffer()[j * imgPtr2->getWidth() + i].b;
            }
            else
            {
                newBuff[j * img.getWidth() + i].b = 0;
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
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            
            newBuff[j * img.getWidth() + i].r = imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].r / 5 +
            imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].g / 2 +
            imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].b / 4;
            
            newBuff[j * img.getWidth() + i].g = imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].r / 5 +
            imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].g / 2 +
            imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].b / 4;
            ;
            newBuff[j * img.getWidth() + i].b = imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].r / 5 +
            imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].g / 2 +
            imgPtr1->getBuffer()[j * imgPtr1->getWidth() + i].b / 4;
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
    
    int input = 0, output = 0;
    
    for (int i = 0; i < img.getWidth(); i++)
    {
        for(int j = 0; j < img.getHeight(); j++)
        {
            
            input = (j * 2) * imgPtr1->getWidth() + (i * 2);
            output = j * img.getWidth() + i;
            newBuff[output].r = imgPtr1->getBuffer()[input].r;
            newBuff[output].g = imgPtr1->getBuffer()[input].g;
            newBuff[output].b = imgPtr1->getBuffer()[input].b;
             
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
    delete [] newBuff;
}

const char *Blender::FilterName()
{
    return "Blender";
}

