/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>

//Initializing
void InitializeCircle(Circle *aCircle, double radius, double originX, double originY)
{
    aCircle->r = radius;
    aCircle->x = originX;
    aCircle->y = originY;
    
}

void InitializeRectangle(Rectangle *aRectangle, double minX, double maxX, double minY, double maxY)
{
    aRectangle->min_X = minX;
    aRectangle->max_X = maxX;
    aRectangle->min_Y = minY;
    aRectangle->max_Y = maxY;
    
}

void InitializeTriangle(Triangle *aTriangle, double pt1X, double pt2X, double minY, double maxY)
{
    aTriangle->pt1_X = pt1X;
    aTriangle->pt2_X = pt2X;
    aTriangle->min_Y = minY;
    aTriangle->max_Y = maxY;
}

//getting Areas
double GetCircleArea(Circle *aCircle)
{
    double pi = 3.14159;
    double area = pi * aCircle->r * aCircle->r;

    return area;
}

double GetRectangleArea(Rectangle *aRectangle)
{
    //(maxX-minX)*(maxY-minY)
    double area = (aRectangle->max_X - aRectangle->min_X) * (aRectangle->max_Y - aRectangle->min_Y);
    
    return area;
}

double GetTriangleArea(Triangle *aTriangle)
{
    double area = ((aTriangle->pt2_X - aTriangle->pt1_X) * (aTriangle->max_Y - aTriangle->min_Y)) / 2;
    
    return area;
}


//getting bounding box
void GetCircleBoundingBox(Circle *aCircle, double *bbox)
{
    bbox[0] = aCircle->x - aCircle->r;
    bbox[1] = aCircle->x + aCircle->r;
    bbox[2] = aCircle->y - aCircle->r;
    bbox[3] = aCircle->y + aCircle->r;

}

void GetRectangleBoundingBox(Rectangle *aRectangle, double *bbox)
{
    bbox[0] = aRectangle->min_X;
    bbox[1] = aRectangle->max_X;
    bbox[2] = aRectangle->min_Y;
    bbox[3] = aRectangle->max_Y;
    
}

void GetTriangleBoundingBox(Triangle *aTriangle, double *bbox)
{
    bbox[0] = aTriangle->pt1_X;
    bbox[1] = aTriangle->pt2_X;
    bbox[2] = aTriangle->min_Y;
    bbox[3] = aTriangle->max_Y;
    
}
