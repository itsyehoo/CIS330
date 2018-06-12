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
};

class Shrinker : public filter
{
public:
    void Execute();
};

class LRCombine : public filter
{
public:
    void Execute();
};

class TBCombine : public filter
{
public:
    void Execute();
};

class Blender : public filter
{
public:
    Blender();
    Blender(int aFactor);
    ~Blender();
    void SetFactor(double aFactor);
    void Execute();
    
private:
    double factor;
};


#endif
