#include <PNMwriter.h>

PNMwriter::PNMwriter()
{
    fileName = new char[strlen("noName" + 1)];
    strcpy(fileName, "noName");
}

PNMwriter::~PNMwriter()
{
    if(strcmp(fileName, "noName") != 0)
    {
        delete[] fileName;
        fileName = new char[strlen("noName" + 1)];
        strcpy(fileName, "noName");
    }
}

void PNMwriter::Write(char *aFileName)
{
    FILE *f_out = fopen(aFileName, "wb");
    Pixel *aBuffer;
    
    if (!f_out)
    {
        printf("Output file could not open \n");
        return;
    }
    
    int height = imgPtr1->getHeight();
    int width = imgPtr1->getWidth();
    
    /*Writing header */
    fprintf(f_out, "P6\n");
    fprintf(f_out, "%d %d\n", width, height);
    fprintf(f_out, "%d\n", 255);
    
    aBuffer = new Pixel[width*height];
    
    aBuffer = imgPtr1->getBuffer();
    
    fwrite(aBuffer, sizeof(Pixel), width * height, f_out);
    fclose(f_out);
}
