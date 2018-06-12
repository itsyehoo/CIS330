//Project 3B
#include <functions.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//File read and write functions
void ReadImage(char *filename, Image &output)
{
    FILE *f_in;
    char magicNum[128];
    int width, height, maxval;
    Pixel *aBuffer;
    
    f_in = fopen(filename, "rb");
    
    if(!f_in)
    {
        printf("Input file could not open \n");
        return;
    }
    
    /* Reading the header of the file */
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Input file %s is not a PNM file of type P6\n", filename);
        return;
    }
    
    aBuffer = new Pixel[width*height];
    
    /* Reading the buffer */
    fread(aBuffer, sizeof(Pixel), width*height, f_in);
    output.ResetSize(width, height);
    output.setBuffer(aBuffer);
    
    fclose(f_in);
    free(aBuffer);
}

void WriteImage(char *filename, Image &img)
{
    FILE *f_out = fopen(filename, "wb");
    Pixel *aBuffer;
    
    if (!f_out)
    {
        printf("Output file could not open \n");
        return;
    }
    
    /*Writing header */
    fprintf(f_out, "%s\n%d %d\n%d\n", "P6", img.getWidth(), img.getHeight(), 255);
    
    /*Writing Buffer*/
    fwrite(img.getBuffer(), sizeof(Pixel), img.getWidth() * img.getHeight(), f_out);
    fclose(f_out);
}

 //Image manipulation functions
 void HalfSize(Image &input, Image &output)
 {
     output.ResetSize(input.getWidth() / 2, input.getHeight() / 2);
     
     output.buffer = new Pixel[output.getHeight() * output.getWidth()];
     
     int in = 0, out = 0;
     
     for (int i = 0; i < output.getHeight(); i++)
     {
         for(int j = 0; j < output.getWidth(); j++)
         {
             in = i*2*input.getWidth()+j*2;
             out = i*output.getWidth()+j;
             output.buffer[out] = input.buffer[in];
         }
     }
}


 void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output)
 {
     int leftWidth = leftInput.getWidth();
     int rightWidth = rightinput.getWidth();
     
     int totalWidth = leftWidth + rightWidth;
     int height = leftInput.getHeight();
     
     output.ResetSize(totalWidth, height);
     
     output.buffer = new Pixel[totalWidth * height];
     
     for( int i  = 0; i < totalWidth; i++)
     {
         for(int j = 0; j < height; j++)
         {
             if(i < leftWidth)
             {
                 output.buffer[j*totalWidth+i] = leftInput.buffer[j*leftWidth+i];
             }
             else
             {
                 output.buffer[j*totalWidth+i] = rightinput.buffer[j*leftWidth+i];
             }
         }
     }
 }


 
 void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output)
 {
     int topWidth = topInput.getWidth();
     int topHeight = topInput.getHeight();
     
     int bottomWidth = bottomInput.getWidth();
     int bottomHeight = bottomInput.getHeight();
     
     int totalHeight = topHeight + bottomHeight;
     int totalWidth = (topWidth + bottomWidth) / 2;
     
     output.ResetSize(totalWidth,totalHeight);
     
     if (topWidth != bottomWidth)
     {
         printf("Error: inputs have different widths. \n");
     }
     
     output.buffer = new Pixel[totalHeight * totalWidth];

     
     for (int i = 0; i < topInput.getWidth() * topInput.getHeight(); i++)
     {
         output.buffer[i] = topInput.buffer[i];
     }
     
     for (int i = 0; i < topInput.getWidth() * topInput.getHeight(); i++)
     {
         output.buffer[topInput.getWidth() * topInput.getHeight() + i] = bottomInput.buffer[i];
     }
     
 
 }
 
 void Blend(Image &input1, Image &input2, double factor, Image &output)
 {
     int width1 = input1.getWidth();
     int height1 = input1.getHeight();
     int width2 = input2.getWidth();
     int height2 = input2.getHeight();
     
     int totalHeight = (height1 + height2) / 2;
     int totalWidth = (width1 + width2) / 2;
     //float factor = f;
     
     output.ResetSize(totalWidth, totalHeight);
     
     if (width1 != width2 && height1 != height2)
     {
         printf("Error: inputs have different heights and widths\n");
     }
     
     output.buffer = new Pixel[totalHeight * totalWidth];
     
     for(int i = 0; i < output.getWidth() * output.getHeight(); i++)
     {
         output.buffer[i].r = input1.buffer[i].r * factor + input2.buffer[i].r * (1 - factor);
         output.buffer[i].g = input1.buffer[i].g * factor + input2.buffer[i].g * (1 - factor);
         output.buffer[i].b = input1.buffer[i].b * factor + input2.buffer[i].b * (1 - factor);
         
     }
     
 }
 

