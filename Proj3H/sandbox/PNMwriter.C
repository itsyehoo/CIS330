#include <PNMwriter.h>

PNMwriter::PNMwriter()
{
    fileName = NULL;
}

PNMwriter::~PNMwriter()
{
    delete [] fileName;
    fileName = NULL;
}

/*
void PNMwriter::Write(const char *aFileName)
{
    FILE *f_out = fopen(aFileName, "wb");
    
    if (!f_out)
    {
        printf("Output file could not open \n");
        return;
    }
    
    //Writing header
    fprintf(f_out, "%s\n%d %d\n%d\n", "P6", imgPtr1->getWidth(), imgPtr1->getHeight(), 255);
    
    //Writing Buffer
    fwrite(imgPtr1->getBuffer(), sizeof(Pixel), imgPtr1->getWidth() * imgPtr1->getHeight(), f_out);
    fclose(f_out);
}
*/

void PNMwriter::Write(const char *aFileName)
{
    ofstream outFile;

    int w = imgPtr1->getWidth();
    int h = imgPtr1->getHeight();
    
    outFile.open(aFileName, ios::binary);
    
    outFile << "P6" << endl;
    outFile << imgPtr1->getWidth() << " " << imgPtr1->getHeight() << endl;
    outFile << 255 << endl;
    
    outFile.write((char *) imgPtr1->getBuffer(), w*h*3);
    
    outFile.close();
}

const char * PNMwriter::SinkName()
{
    return "PNMwriter";
}
