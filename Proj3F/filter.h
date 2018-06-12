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
