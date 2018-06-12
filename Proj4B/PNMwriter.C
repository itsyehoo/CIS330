#include <PNMwriter.h>

PNMwriter::PNMwriter()
{
    fileName = NULL;
}

PNMwriter::~PNMwriter()
{
    delete[] fileName;
}

void PNMwriter::Write(char *aFileName)
{
    FILE *f_out = fopen(aFileName, "wb");
    
    if (!f_out)
    {
        printf("Output file could not open \n");
        return;
    }
    
    /*Writing header */
    fprintf(f_out, "%s\n%d %d\n%d\n", "P6", imgPtr1->getWidth(), imgPtr1->getHeight(), 255);
    
    /*Writing Buffer*/
    fwrite(imgPtr1->getBuffer(), sizeof(Pixel), imgPtr1->getWidth() * imgPtr1->getHeight(), f_out);
    fclose(f_out);
}
