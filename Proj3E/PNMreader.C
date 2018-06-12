#include <PNMreader.h>

PNMreader::PNMreader()
{
    fileName = new char[strlen("noName" + 1)];
    strcpy(fileName, "noName");
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
    if(strcmp(fileName, "noName") != 0)
    {
        delete[] fileName;
        fileName = new char[strlen("noName" + 1)];
        strcpy(fileName, "noName");
    }
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
    
    img.setHeight(height);
    img.setWidth(width);
    
    /* Reading the buffer */
    fread(aBuffer, sizeof(Pixel), width*height, f_in);
    
    img.setBuffer(aBuffer);
    
    fclose(f_in);
    
}

void PNMreader::Update()
{
    this->Execute();
}
