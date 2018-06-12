
#include <PNMreader.h>

PNMreader::PNMreader()
{
    fileName = NULL;
}

PNMreader::PNMreader(char *aFileName)
{
    //allocating memory for the fileName
    fileName = new char[strlen(aFileName + 1)];
    
    //copying aFileName into fileName
    strcpy(fileName, aFileName);
}

PNMreader::~PNMreader()
{
    free(fileName);
}

void PNMreader::Execute()
{
    FILE *f_in;
    char magicNum[128];
    int width, height, maxval;
    Pixel *aBuffer;
    
    f_in = fopen(fileName, "rb");
    
    if(!f_in)
    {
        printf("Input file could not open \n");
        return;
    }
    
    /* Reading the header of the file */
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Input file %s is not a PNM file of type P6\n", fileName);
        return;
    }
    
    aBuffer = new Pixel[width*height];
    
    /* Reading the buffer */
    fread(aBuffer, sizeof(Pixel), width*height, f_in);
    img.ResetSize(width, height);
    img.setBuffer(aBuffer);
    
    fclose(f_in);
    free(aBuffer);
}

const char * PNMreader::SourceName()
{
    return "PNMreader";
}
