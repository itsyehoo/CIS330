#include <PNMwriterCPP.h>

PNMwriterCPP::PNMwriterCPP()
{
    fileName = new char[strlen("noName" + 1)];
    strcpy(fileName, "noName");
}

PNMwriterCPP::~PNMwriterCPP()
{
    if(strcmp(fileName, "noName") != 0)
    {
        delete[] fileName;
        fileName = new char[strlen("noName" + 1)];
        strcpy(fileName, "noName");
    }
}

void PNMwriterCPP::Write(char *aFileName)
{
    ofstream outFile;
    outFile.open(aFileName, ios::binary | ios::out);
    Pixel *aBuffer;
    
    if (!outFile)
    {
        cout << "Output file could not open" << endl;
        return;
    }
    
    int height = imgPtr1->getHeight();
    int width = imgPtr1->getWidth();
    
    //Writing header
    outFile << "P6" << endl;
    outFile << width << " " << height << endl;
    outFile << 255 << endl;
    
    aBuffer = new Pixel[width*height];
    aBuffer = imgPtr1->getBuffer();
    
    for(int i = 0; i < width*height; i++)
    {
        outFile.write(reinterpret_cast<char*>(&aBuffer[i]), sizeof(Pixel));
    }
    
    outFile.close();
}

