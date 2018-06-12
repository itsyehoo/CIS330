#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    
} Pixel;

typedef struct
{
    int w;
    int h;
    Pixel *buffer;
    
} Image;

Image * ReadImage(char *filename)
{
    FILE *f_in;
    char magicNum[128];
    int width, height, maxval;
    Image *aImage;
    
    f_in = fopen(filename, "rb");
    
    if(!f_in)
    {
        printf("File could not open \n");
        return 0;
    }
    
    /* Reading the header of the file */
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "File %s is not a PNM file of type P6\n", filename);
        return 0;
    }
    
    /* Allocating memory for the image */
    aImage = (Image *) malloc(sizeof(Image));
    
    aImage->h = height;
    aImage->w = width;
    
    /* Allocating memory for the buffer */
    aImage->buffer = (Pixel*) malloc(aImage->w * aImage->h * sizeof(Pixel));
    
    /* Reading the buffer */
    fread(aImage->buffer, sizeof(Pixel), width*height, f_in);
    
    fclose(f_in);
    
    return aImage;
}


void WriteImage(Image *img, char *filename)
{
    FILE *f_out = fopen(filename, "wb");
    
    if (!f_out)
    {
        printf("File could not open \n");
        return;
    }
    
    /*Writing header */
    fprintf (f_out, "P6\n");
    fprintf (f_out, "%d %d\n", img->w, img->h);
    fprintf (f_out, "%d\n", 255);
    
    fwrite(img->buffer, sizeof(Pixel), img->w * img->h, f_out);
    fclose(f_out);
}

Image *
YellowDiagonal(Image *input)
{
    Image *newImg;
    
    sizeOfPixels = input->h * input->w;
    newImg = (Image *) malloc(sizeof(Image));
    newImg->buffer = (Pixel*) malloc(input->w * input->h * sizeof(Pixel));
    
    newImg->h = input->h;
    newImg->w = input->w;
    
    for(int i  = 0; i < sizeOfPixels; i++)
    {
        newImg->buffer[i] = input->buffer[i];
    }
    
    
    int height = 0, width = 0;
    
    height = input->h;
    width = input->w;
    
    int i, j;
    
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            if(i == j)
            {
                int location = i + j * width;
                input->buffer[location].r = 255;
                input->buffer[location].g = 255;
                input->buffer[location].b = 0;
            }
        }
    }
    
    return input;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <file1> <file2> \n", argv[0]);
    }
    
    Image * img;
    
    img = ReadImage(argv[1]);
    //newImg = img;
    YellowDiagonal(img);
    WriteImage(img, argv[2]);
    
    /* Freeing the image */
    free(img->buffer);
    free(img);
    
    return 0;
}
