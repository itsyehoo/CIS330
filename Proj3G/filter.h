#ifndef filter_h
#define filter_h

#include <stdio.h>
#include <image.h>
#include <sink.h>
#include <source.h>


 class filter : public sink, public source
 {
 public:
    virtual void Update();
    virtual const char *FilterName() = 0;
    virtual const char *SourceName();
    virtual const char *SinkName();
 };

class Color : public source
{
public:
    Color(int w, int h, unsigned char r, unsigned char g, unsigned char b);
    Color();
    virtual void Execute();
    virtual const char *SourceName();
    
protected:
    int width, height;
    unsigned char red, green, blue;
};

class CheckSum : public sink
{
public:
    void OutputCheckSum(const char *filename);
    const char *SinkName() { return "CheckSum"; }
};

class Mirror : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class Rotate : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class Subtract : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class Grayscale : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class Blur : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class Shrinker : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class LRCombine : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class TBCombine : public filter
{
public:
    void Execute();
    virtual const char *FilterName();
};

class Blender : public filter
{
public:
    Blender();
    Blender(int aFactor);
    ~Blender();
    void SetFactor(double aFactor);
    void Execute();
    virtual const char *FilterName();
    
private:
    double factor;
};


#endif
