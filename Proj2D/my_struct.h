/* This file should contain your struct definitions for Circle, Triangle, and
 Rectangle */

typedef struct //Circle
{
    double r;
    double x;
    double y;
    
}Circle;

typedef struct //Triangle
{
    double pt1_X;
    double pt2_X;
    double max_Y;
    double min_Y;
    
}Triangle;

typedef struct //Rectangle
{
    double max_X;
    double min_X;
    double max_Y;
    double min_Y;
    
}Rectangle;


typedef union
{
    Rectangle aRectangle;
    Circle aCircle;
    Triangle aTriangle;
    
} shapeUnion;

enum shapeType{Circ, Rect, Tri};

struct Shape;

typedef struct
{
    double (*GetArea)(struct Shape * aShape);
    void (*GetBoundingBox)(struct Shape * aShape, double *);
    
} functionTable;

struct Shape
{
    shapeUnion su;
    enum shapeType st;
    functionTable ft;
    
};

