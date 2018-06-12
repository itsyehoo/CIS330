/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>

//Initializing
void InitializeCircle(struct Shape *aShape, double radius, double originX, double originY)
{
    aShape->su.aCircle.r = radius;
    aShape->su.aCircle.x = originX;
    aShape->su.aCircle.y = originY;
    aShape->ft.GetArea = GetCircleArea;
    aShape->ft.GetBoundingBox = GetCircleBoundingBox;
}

void InitializeRectangle(struct Shape *aShape, double minX, double maxX, double minY, double maxY)
{
    aShape->su.aRectangle.min_X = minX;
    aShape->su.aRectangle.max_X = maxX;
    aShape->su.aRectangle.min_Y = minY;
    aShape->su.aRectangle.max_Y = maxY;
    aShape->ft.GetArea = GetRectangleArea;
    aShape->ft.GetBoundingBox = GetRectangleBoundingBox;
    
}

void InitializeTriangle(struct Shape *aShape, double pt1X, double pt2X, double minY, double maxY)
{
    aShape->su.aTriangle.pt1_X = pt1X;
    aShape->su.aTriangle.pt2_X = pt2X;
    aShape->su.aTriangle.min_Y = minY;
    aShape->su.aTriangle.max_Y = maxY;
    aShape->ft.GetArea = GetTriangleArea;
    aShape->ft.GetBoundingBox = GetTriangleBoundingBox;
}

//getting Areas
double GetCircleArea(struct Shape *aShape)
{
    double pi = 3.14159;
    double area = pi * aShape->su.aCircle.r * aShape->su.aCircle.r;
    return area;
}

double GetRectangleArea(struct Shape *aShape)
{
    double area = (aShape->su.aRectangle.max_X - aShape->su.aRectangle.min_X) * (aShape->su.aRectangle.max_Y - aShape->su.aRectangle.min_Y);
    return area;
}

double GetTriangleArea(struct Shape *aShape)
{
    double area = ((aShape->su.aTriangle.pt2_X - aShape->su.aTriangle.pt1_X) * (aShape->su.aTriangle.max_Y - aShape->su.aTriangle.min_Y)) / 2;
    return area;
}


//getting bounding box
void GetCircleBoundingBox(struct Shape *aShape, double *bbox)
{
    bbox[0] = aShape->su.aCircle.x - aShape->su.aCircle.r;   //aCircle->x - aCircle->r;
    bbox[1] = aShape->su.aCircle.x + aShape->su.aCircle.r;   //aCircle->x + aCircle->r;
    bbox[2] = aShape->su.aCircle.y - aShape->su.aCircle.r;   //aCircle->y - aCircle->r;
    bbox[3] = aShape->su.aCircle.y + aShape->su.aCircle.r;   //aCircle->y + aCircle->r;
    
}

void GetRectangleBoundingBox(struct Shape *aShape, double *bbox)
{
    bbox[0] = aShape->su.aRectangle.min_X;   //aRectangle->min_X;
    bbox[1] = aShape->su.aRectangle.max_X;   //aRectangle->max_X;
    bbox[2] = aShape->su.aRectangle.min_Y;   //aRectangle->min_Y;
    bbox[3] = aShape->su.aRectangle.max_Y;   //aRectangle->max_Y;
    
}

void GetTriangleBoundingBox(struct Shape *aShape, double *bbox)
{
    bbox[0] = aShape->su.aTriangle.pt1_X;   //aTriangle->pt1_X;
    bbox[1] = aShape->su.aTriangle.pt2_X;   //aTriangle->pt2_X;
    bbox[2] = aShape->su.aTriangle.min_Y;   //aTriangle->min_Y;
    bbox[3] = aShape->su.aTriangle.max_Y;   //aTriangle->max_Y;
    
}

